#pragma once

/*ëOï˚êÈåæ*/
class SpriteComponent;

class Direct2D
{
public:
	Direct2D();
	~Direct2D();

	HRESULT Initialize();
	ID2D1Bitmap* LoadImageFile(LPCWSTR path);

	void Render();

	void AddSpriteComponent(SpriteComponent* component);
	void RemoveSpriteComponent(SpriteComponent* component);

private:

public:

private:
	struct CacheBitmap
	{
		LPCWSTR path;
		ID2D1Bitmap* bitmap;
	};

	ID2D1Factory* pD2DFactory;
	IDWriteFactory* pDWriteFactory;
	ID2D1HwndRenderTarget* pRT;
	ID2D1SolidColorBrush* pSolidBrush;
	IDXGISurface* pDXGISurface;
	IDXGISwapChain* pDXGISwapChain;
	

	IWICImagingFactory* pWICImagingFactory;

	std::vector<SpriteComponent*> m_spriteComponents;
	std::unordered_map<LPCWSTR, ID2D1Bitmap*> m_bitmaps;
};