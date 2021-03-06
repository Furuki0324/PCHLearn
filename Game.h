#pragma once
#include "BaseScene.h"

/*前方宣言*/
class Witch;

class GameScene : public BaseScene
{
public:
	GameScene(Application* app, int width, int height);

	bool InitScene() override;
	void RunLoop() override;
	void ExitScene() override;

private:
	void ProcessInput();
	void UpdateGame();

	void LoadData();

public:
	bool isRunning;

private:
	int windowWidth, windowHeight;

	Witch* p_witch;

	/*FPS制御用の変数*/
	LARGE_INTEGER m_timeFreq;
	LARGE_INTEGER m_timeBefore;
	LARGE_INTEGER m_timeNow;
	float m_deltaTime;
};