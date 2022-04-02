#pragma once

/*ëOï˚êÈåæ*/
class Actor;
class Witch;
class Map;
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
		if (m_direct2D) { return m_direct2D; }
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
	Direct2D* m_direct2D;

	std::vector<Actor*> m_actors;
	Witch* m_witch;
	Map* m_map;
};