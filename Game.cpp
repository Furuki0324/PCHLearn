#include "Game.h"
#include "Direct2D.h"
#include "Camera.h"
#include "SoundManager.h"
#include "Actor.h"
#include "Witch.h"
#include "MapComponent.h"

constexpr float FPS = (60.0f);
constexpr float MIN_DELTA_TIME = (1.0f / FPS);
constexpr float MAX_DELTA_TIME = (0.05f);
constexpr int STAGE_WIDTH = (1280);
constexpr int STAGE_HEIGHT = (960);

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
	: windowWidth(width)
	, windowHeight(height)
	, isRunning(false)
	, p_direct2D(nullptr)
	, p_camera(nullptr)
{
	p_direct2D = new Direct2D();
	p_camera = new Camera(windowWidth, windowHeight, STAGE_WIDTH, STAGE_HEIGHT);
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

	RECT wrc = { 0,0,windowWidth, windowHeight };
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

	delete p_camera;
	p_camera = nullptr;
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

	BYTE key[256];
	GetKeyboardState(m_input);

	if (m_input[VK_ESCAPE] & 0x80)
	{
		isRunning = false;
	}

	if (m_input[VK_R] & 0x80)
	{
		p_camera->SetFollowTarget(nullptr);
	}
	if (m_input[VK_T] & 0x80)
	{
		p_camera->SetFollowTarget(p_witch);
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

	/*フォロー対象のアクターが設定されている場合、1フレーム前の位置にカメラが移動する*/
	p_camera->UpdateCamera();

	for (Actor* actor : m_actors)
	{
		actor->UpdateActor(m_deltaTime, m_input);
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
	p_witch->SetActorMoveSpeed(1.0f);
	p_witch->SetActorWorldLocation(Vector2{ 500.0f,600.0f });
	p_camera->SetFollowTarget(p_witch);

	Actor* temp = new Actor(this);
	MapComponent* map = new MapComponent(temp, "./CSV/mapchip.csv", 0);
	MapComponent* object = new MapComponent(temp, "./CSV/mapchip_object.csv", 1);
}

const Vector2& Game::GetCameraLocation()
{
	if (p_camera) { return p_camera->GetLocation(); }
	else
	{
		std::cout << "No Camera." << std::endl;
		return Vector2::Zero;
	}
}

const Vector2& Game::GetCameraOrigin()
{
	if (p_camera) { return p_camera->GetOrigin(); }
	else
	{
		std::cout << "No Camera." << std::endl;
		return Vector2::Zero;
	}
}