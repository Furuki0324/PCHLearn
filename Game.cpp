#include "Game.h"
#include "Application.h"
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

/*static変数の実体*/
HWND Game::hwnd = nullptr;

Game::Game(Application* app, int width, int height)
	: BaseScene(app)
	, windowWidth(width)
	, windowHeight(height)
	, isRunning(false)
	, p_camera(nullptr)
{
	p_camera = new Camera(windowWidth, windowHeight, STAGE_WIDTH, STAGE_HEIGHT);

	Initialize();
}

HRESULT Game::Initialize()
{
	QueryPerformanceFrequency(&m_timeFreq);
	QueryPerformanceCounter(&m_timeBefore);

	SoundManager::GetInstance().Play(1);
	LoadData();

	///*ゲームループを開始*/
	isRunning = true;

	return S_OK;
}

void Game::QuitGame()
{
	SoundManager::GetInstance().Stop();

	while (!m_actors.empty())
	{
		delete m_actors.back();
	}

	delete p_camera;
	p_camera = nullptr;

	p_app->ChangeScene(Application::Scene::title);
}

void Game::RunLoop()
{
	ProcessInput();
	UpdateGame();

	if (!isRunning) { QuitGame(); }
}

void Game::ProcessInput()
{
	BYTE key[256];
	GetKeyboardState(key);

	GetKeyboardState(m_input);

	if (m_input[VK_ESCAPE] & 0x80)
	{
		/*ゲームループを終了させる*/
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

	for (Actor* actor : m_actors)
	{
		actor->ProcessInput(key);
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