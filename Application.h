#pragma once

/*前方宣言*/
class BaseScene;
class Game;
class Direct2D;

class Application
{
public:
	enum Scene
	{
		title, game
	};

	Application(unsigned int windowWidth, unsigned int windowHeight);
	~Application();
	void Quit();

	static HWND GetHwnd() { return m_hwnd; }
	Direct2D* const GetDirect2D() { return p_direct2D.get(); }

	void Run();
	void ChangeScene(Scene scene);

private:
	HRESULT Initialize();
	void PatchMessage();

public:

private:
	/*ウィンドウ*/
	static HWND m_hwnd;
	unsigned int m_windowWidth;
	unsigned int m_windowHeight;
	MSG m_msg;

	std::unique_ptr<BaseScene> p_playScene;
	std::unique_ptr<Direct2D> p_direct2D;
	bool m_isActive;
};