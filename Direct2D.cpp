#include "Direct2D.h"
#include "Game.h"
#include "SpriteComponent.h"

Direct2D::Direct2D()
	:pD2DFactory(nullptr)
	,pDWriteFactory(nullptr)
	,pRT(nullptr)
	,pSolidBrush(nullptr)
	,pDXGISurface(nullptr)
	,pWICImagingFactory(nullptr)
{

}

Direct2D::~Direct2D()
{
	if (pWICImagingFactory) pWICImagingFactory->Release();
	if (pDXGISurface) pDXGISurface->Release();
	if (pSolidBrush) pSolidBrush->Release();
	if (pRT) pRT->Release();
	if (pDWriteFactory) pDWriteFactory->Release();
	if (pD2DFactory) pD2DFactory->Release();
}

HRESULT Direct2D::Initialize()
{
	HRESULT hr = S_OK;

	RECT rect;
	GetClientRect(Game::GetHwnd(), &rect);

	UINT window_width = rect.right - rect.left;
	UINT window_height = rect.bottom - rect.top;

	/*ID2D1Factoryを作成する*/
	hr = D2D1CreateFactory(
		D2D1_FACTORY_TYPE_SINGLE_THREADED,
		&pD2DFactory
	);

	if (FAILED(hr))
	{
		return hr;
	}

	/*ID2D1HwndRenderTargetを作成する*/
	hr = pD2DFactory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(
			Game::GetHwnd(),
			D2D1::SizeU(window_width, window_height)
		),
		&pRT
	);

	/*IWICImagingFactoryを作成する*/
	hr = CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_IWICImagingFactory, reinterpret_cast<void**>(&pWICImagingFactory));
	if (FAILED(hr))
	{
		return hr;
	}

	return S_OK;
}

ID2D1Bitmap* Direct2D::LoadImageFile(LPCWSTR path)
{
	IWICBitmapDecoder* decoder = nullptr;
	IWICBitmapFrameDecode* frameDecode = nullptr;
	IWICFormatConverter* converter = nullptr;
	ID2D1Bitmap* outBitmap = nullptr;

	/*一度読み込んだことのある画像であればそのポインタを返す*/
	auto iter = m_bitmaps.find(path);
	if (iter != m_bitmaps.end())
	{
		outBitmap = iter->second;
		std::cout << "Found in cache." << std::endl;
		return outBitmap;
	}

	/*新たに画像を読み込む*/
	HRESULT hr = S_OK;

	/*フォーマットコンバーターを作成する*/
	hr = pWICImagingFactory->CreateFormatConverter(&converter);
	if (FAILED(hr))
	{
		std::cout << "Error:0 " << std::system_category().message(hr) << std::endl;
		return nullptr;
	}

	/*画像をビットマップに変換するデコーダを作成する*/
	hr = pWICImagingFactory->CreateDecoderFromFilename(
		path,
		NULL,
		GENERIC_READ,
		WICDecodeMetadataCacheOnLoad,
		&decoder
	);
	if (FAILED(hr))
	{
		std::cout << "Error:1 " << std::system_category().message(hr) << std::endl;
		return nullptr;
	}

	/*ビットマップフレームを取得する*/
	hr = decoder->GetFrame(0, &frameDecode);
	if (FAILED(hr))
	{
		std::cout << "Error:2 " << std::system_category().message(hr) << std::endl;
		return nullptr;
	}

	hr = converter->Initialize(frameDecode, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, nullptr, 1.0f, WICBitmapPaletteTypeMedianCut);
	if (FAILED(hr))
	{
		std::cout << "Error:3 " << std::system_category().message(hr) << std::endl;
		return nullptr;
	}

	hr = pRT->CreateBitmapFromWicBitmap(converter, nullptr, &outBitmap);
	if (FAILED(hr))
	{
		std::cout << "Error:4 " << std::system_category().message(hr) << std::endl;
		return nullptr;
	}

	m_bitmaps.emplace(path, outBitmap);
	if (outBitmap == nullptr)
	{
		std::cout << "Error:5 Bitmap is null." << std::endl;
	}

	return outBitmap;
}

void Direct2D::Render()
{
	pRT->BeginDraw();
	pRT->Clear(D2D1::ColorF(D2D1::ColorF::Blue));

	for (SpriteComponent* sprite : m_spriteComponents)
	{
		sprite->Render(pRT);
	}

	pRT->EndDraw();
}

void Direct2D::AddSpriteComponent(SpriteComponent* sprite)
{
	int order = sprite->GetUpdateOrder();
	auto iter = m_spriteComponents.begin();

	for (; iter != m_spriteComponents.end(); ++iter)
	{
		if (order < (*iter)->GetUpdateOrder())
		{
			break;
		}
	}

	m_spriteComponents.insert(iter, sprite);
}

void Direct2D::RemoveSpriteComponent(SpriteComponent* sprite)
{
	auto iter = std::find(m_spriteComponents.begin(), m_spriteComponents.end(), sprite);
	m_spriteComponents.erase(iter);
}