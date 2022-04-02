#include "Game.h"
#include "Direct2D.h"
#include "SoundManager.h"
#include "Actor.h"
#include "Witch.h"
#include "Map.h"

/*シングルトンオブジェクトの作成*/
SoundManager soundManager;

/*static変数の実体*/
HWND Game::hwnd = nullptr;

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

Game::Game(int width, int height)
	: window_width(width)
	, window_height(height)
	, isRunning(false)
	, m_direct2D(nullptr)
{
	m_direct2D = new Direct2D();
}

HRESULT Game::Initialize()
{
	/*COMの初期化*/
	HRESULT hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);

	/*ウィンドウの作成*/
	WNDCLASSEX w = {};
	w.cbSize = sizeof(WNDCLASSEX);
	w.lpfnWndProc = (WNDPROC)MainWndProc;
	w.lpszClassName = _T("SimpleRPG");
	w.hInstance = GetModuleHandle(0);
	RegisterClassEx(&w);

	RECT wrc = { 0,0,window_width, window_height };
	AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);

	hwnd = CreateWindow(
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

	hr = m_direct2D->Initialize();
	if (hr != S_OK)
	{
		return hr;
	}

	SoundManager::GetInstance().Play(1);
	LoadData();

	ShowWindow(hwnd, SW_SHOW);

	/*ゲームループを開始*/
	isRunning = true;

	return S_OK;
}

void Game::QuitGame()
{
	while (!m_actors.empty())
	{
		delete m_actors.back();
	}

	CoUninitialize();

	delete m_direct2D;
	m_direct2D = nullptr;
}

void Game::RunLoop()
{
	while (isRunning)
	{
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}

	QuitGame();
}

void Game::ProcessInput()
{
	if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		if (msg.message == WM_QUIT)
		{
			std::cout << "WM_QUIT\n";

			/*ゲームループを終了させる*/
			isRunning = false;
		}

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	if (GetKeyState(VK_ESCAPE) & 0x8000)
	{
		isRunning = false;
	}
}

void Game::UpdateGame()
{
	for (Actor* actor : m_actors)
	{
		actor->UpdateActor(0.05f);
	}
}

void Game::GenerateOutput()
{
	m_direct2D->Render();
}

void Game::AddActor(Actor* actor)
{
	m_actors.push_back(actor);
}

void Game::RemoveActor(Actor* actor)
{
	auto iter = std::find(m_actors.begin(), m_actors.end(), actor);
	m_actors.erase(iter);
}

void Game::LoadData()
{
	m_witch = new Witch(this);
}