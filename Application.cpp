#include "Application.h"
#include "Direct2D.h"
#include "SoundManager.h"
#include "Title.h"
#include "Game.h"

/*シングルトンオブジェクトの作成*/
SoundManager soundManager;

/*static変数の実体*/
HWND Application::m_hwnd = nullptr;

LRESULT CALLBACK MainWndProc(HWND hwnd, UINT uMsg, WPARAM wparam, LPARAM lparam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	default:
		return DefWindowProc(hwnd, uMsg, wparam, lparam);
	}

	return 0;
}

Application::Application(unsigned int windowWidth, unsigned int windowHeight)
	:m_isActive(false)
	,m_windowWidth(windowWidth)
	,m_windowHeight(windowHeight)
{
	HRESULT hr = Initialize();
	if (FAILED(hr))
	{
		std::cout << "Application initialize failed.\n" << std::system_category().message(hr) << std::endl;
		return;
	}

	p_playScene = std::make_unique<TitleScene>(this);
	m_isActive = true;
}

Application::~Application()
{
	CoUninitialize();
}

HRESULT Application::Initialize()
{
	p_direct2D = std::make_unique<Direct2D>();

	HRESULT hr = S_OK;

	/*COMの初期化*/
	hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
	if (FAILED(hr))
	{
		return hr;
	}

	/*ウィンドウの作成*/
	WNDCLASSEX w = {};
	w.cbSize = sizeof(WNDCLASSEX);
	w.lpfnWndProc = (WNDPROC)MainWndProc;
	w.lpszClassName = _T("SimpleRPG");
	w.hInstance = GetModuleHandle(0);
	RegisterClassEx(&w);

	RECT wrc = { 0,0,m_windowWidth, m_windowHeight };
	AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);

	m_hwnd = CreateWindow(
		w.lpszClassName,
		_T("SimpleRPG"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		wrc.right - wrc.left,
		wrc.bottom,
		nullptr,
		nullptr,
		w.hInstance,
		nullptr
	);

	hr = p_direct2D->Initialize();
	if (FAILED(hr))
	{
		return hr;
	}

	ShowWindow(m_hwnd, SW_SHOW);

	return S_OK;
}

void Application::Run()
{
	while (m_isActive) 
	{
		PatchMessage();
		p_playScene->RunLoop();
		p_direct2D->Render();
	}
}

void Application::Quit()
{
	m_isActive = false;
	DestroyWindow(m_hwnd);
}

void Application::ChangeScene(Scene scene)
{
	switch (scene)
	{
	case Scene::title:
		std::cout << "New scene is title." << std::endl;
		p_playScene.reset(new TitleScene(this));
		break;

	case Scene::game:
		std::cout << "New scene is game." << std::endl;
		p_playScene.reset(new Game(this, 640, 480));
		break;
	}
}

void Application::PatchMessage()
{
	if (PeekMessage(&m_msg, NULL, 0, 0, PM_REMOVE))
	{
		if (m_msg.message == WM_QUIT)
		{
			std::cout << "WM_QUIT\n";
			Quit();
		}

		TranslateMessage(&m_msg);
		DispatchMessage(&m_msg);
	}
}