#pragma once

/*ëOï˚êÈåæ*/
class Actor;
class Witch;
class Direct2D;
class Camera;

class Game
{
public:
	Game(int width, int height);

	HRESULT Initialize();
	void QuitGame();
	void RunLoop();

	static HWND GetHwnd() { return hwnd; }
	static Vector2 GetCamera() { return camera; }


	void AddActor(Actor* actor);
	void RemoveActor(Actor* actor);

	Direct2D* GetDitect2DPtr()
	{
		if (p_direct2D) { return p_direct2D; }
		else
		{
			std::cout << "No Direct2D." << std::endl;
			return nullptr;
		}
	}

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
	void GenerateOutput();

	void LoadData();

public:
	bool isRunning;

private:
	MSG msg;
	static HWND hwnd;
	static Vector2 camera;
	int window_width, window_height;
	Direct2D* p_direct2D;
	Camera* p_camera;

	std::vector<Actor*> m_actors;
	Witch* p_witch;

	/*FPSêßå‰ópÇÃïœêî*/
	LARGE_INTEGER m_timeFreq;
	LARGE_INTEGER m_timeBefore;
	LARGE_INTEGER m_timeNow;
	float m_deltaTime;
};