#include "Game.h"
#include "Application.h"
#include "Camera.h"
#include "SoundManager.h"
#include "Actor.h"
#include "Witch.h"
#include "UI.h"
#include "MapComponent.h"

constexpr float FPS = (60.0f);
constexpr float MIN_DELTA_TIME = (1.0f / FPS);
constexpr float MAX_DELTA_TIME = (0.05f);
constexpr int STAGE_WIDTH = (1280);
constexpr int STAGE_HEIGHT = (960);


GameScene::GameScene(Application* app, int width, int height)
	: BaseScene(app)
	, windowWidth(width)
	, windowHeight(height)
	, isRunning(false)
{
	InitScene();
}

bool GameScene::InitScene()
{
	p_camera = new Camera(this, windowWidth, windowHeight, STAGE_WIDTH, STAGE_HEIGHT);

	QueryPerformanceFrequency(&m_timeFreq);
	QueryPerformanceCounter(&m_timeBefore);

	SoundManager::GetInstance().Play(1);
	LoadData();

	///*ゲームループを開始*/
	isRunning = true;

	return true;
}

void GameScene::ExitScene()
{
	SoundManager::GetInstance().Stop();

	while (!m_actors.empty())
	{
		delete m_actors.back();
	}

	p_camera = nullptr;

	p_app->ChangeScene(Application::Scene::title);
}

void GameScene::RunLoop()
{
	ProcessInput();
	UpdateGame();

	if (!isRunning) { ExitScene(); }
}

void GameScene::ProcessInput()
{
	BYTE key[256];
	GetKeyboardState(key);

	if (key[VK_ESCAPE] & 0x80)
	{
		/*ゲームループを終了させる*/
		isRunning = false;
	}

	if (key[VK_R] & 0x80)
	{
		p_camera->SetFollowTarget(nullptr);
	}
	if (key[VK_T] & 0x80)
	{
		p_camera->SetFollowTarget(p_witch);
	}

	for (Actor* actor : m_actors)
	{
		actor->ProcessInput(key);
	}
}

void GameScene::UpdateGame()
{
	do
	{
		QueryPerformanceCounter(&m_timeNow);
		m_deltaTime = static_cast<float>((m_timeNow.QuadPart - m_timeBefore.QuadPart) / static_cast<float>(m_timeFreq.QuadPart));
	} while (m_deltaTime < MIN_DELTA_TIME);

	m_timeBefore = m_timeNow;
	if (m_deltaTime > MAX_DELTA_TIME) { m_deltaTime = MAX_DELTA_TIME; }

	/*フォロー対象のアクターが設定されている場合、1フレーム前の位置にカメラが移動する*/
	//p_camera->UpdateCamera();

	for (Actor* actor : m_actors)
	{
		actor->UpdateActor(m_deltaTime);
	}
}

void GameScene::LoadData()
{
	p_witch = new Witch(this);
	p_witch->SetActorMoveSpeed(1.0f);
	p_witch->SetActorWorldLocation(Vector2{ 500.0f,600.0f });
	p_camera->SetFollowTarget(p_witch);

	UI* ui = new UI(this);
	ui->SetActorWorldLocation(Vector2{ 0.0f, 0.0f });

	Actor* temp = new Actor(this);
	MapComponent* map = new MapComponent(temp, "./CSV/mapchip.csv", 0);
	MapComponent* object = new MapComponent(temp, "./CSV/mapchip_object.csv", 101);
}