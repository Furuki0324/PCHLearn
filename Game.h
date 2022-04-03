#pragma once

/*前方宣言*/
class Actor;
class Witch;
class Direct2D;

class Game
{
public:
	Game(int width, int height);

	HRESULT Initialize();
	void QuitGame();
	void RunLoop();

	static HWND GetHwnd() { return hwnd; }

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
	int window_width, window_height;
	Direct2D* p_direct2D;

	std::vector<Actor*> m_actors;
	Witch* p_witch;

	/*FPS制御用の変数*/
	LARGE_INTEGER m_timeFreq;
	LARGE_INTEGER m_timeBefore;
	LARGE_INTEGER m_timeNow;
	float m_deltaTime;
};