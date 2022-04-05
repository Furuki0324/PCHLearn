#pragma once
#include "BaseScene.h"

/*ëOï˚êÈåæ*/
class Application;
class Actor;
class Witch;
class Direct2D;
class Camera;

class Game : public BaseScene
{
public:
	Game(Application* app, int width, int height);

	HRESULT Initialize();
	void QuitGame();
	void RunLoop() override;

	static HWND GetHwnd() { return hwnd; }

	void AddActor(Actor* actor);
	void RemoveActor(Actor* actor);

	Camera* GetCameraPtr()
	{
		if (p_camera) { return p_camera; }
		else
		{
			std::cout << "No Camera." << std::endl;
			return nullptr;
		}
	}

	const Vector2& GetCameraLocation();
	const Vector2& GetCameraOrigin();

private:
	void ProcessInput();
	void UpdateGame();

	void LoadData();

public:
	bool isRunning;

private:
	MSG msg;
	static HWND hwnd;
	int windowWidth, windowHeight;
	BYTE m_input[256];
	Camera* p_camera;

	std::vector<Actor*> m_actors;
	Witch* p_witch;

	/*FPSêßå‰ópÇÃïœêî*/
	LARGE_INTEGER m_timeFreq;
	LARGE_INTEGER m_timeBefore;
	LARGE_INTEGER m_timeNow;
	float m_deltaTime;
};