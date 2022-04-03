#include "Game.h"
#include "Direct2D.h"
#include "SoundManager.h"
#include "Actor.h"
#include "Witch.h"
#include "MapComponent.h"

#define FPS				(60)
#define MIN_DELTA_TIME	(1.0f / FPS)
#define MAX_DELTA_TIME	(0.05f)

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
	, p_direct2D(nullptr)
{
	p_direct2D = new Direct2D();
}

HRESULT Game::Initialize()
{
	QueryPerformanceFrequency(&m_timeFreq);
	QueryPerformanceCounter(&m_timeBefore);

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

	hr = p_direct2D->Initialize();
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

	delete p_direct2D;
	p_direct2D = nullptr;
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
	do
	{
		QueryPerformanceCounter(&m_timeNow);
		m_deltaTime = static_cast<float>((m_timeNow.QuadPart - m_timeBefore.QuadPart) / static_cast<float>(m_timeFreq.QuadPart));
	} while (m_deltaTime < MIN_DELTA_TIME);

	m_timeBefore = m_timeNow;
	if (m_deltaTime > MAX_DELTA_TIME) { m_deltaTime = MAX_DELTA_TIME; }

	for (Actor* actor : m_actors)
	{
		actor->UpdateActor(m_deltaTime);
	}
}

void Game::GenerateOutput()
{
	p_direct2D->Render();
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
	p_witch = new Witch(this);

	Actor* temp = new Actor(this);
	MapComponent* map = new MapComponent(temp, "./CSV/mapchip.csv", 0);
	MapComponent* object = new MapComponent(temp, "./CSV/mapchip_object.csv", 1);
}