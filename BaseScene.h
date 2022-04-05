#pragma once

/*‘O•ûéŒ¾*/
class Application;
class Direct2D;

class BaseScene
{
public:
	BaseScene(Application* app)
		:p_app(app) 
	{};

	virtual void RunLoop() {};
	virtual void ProcessInput() {};
	virtual void UpdateScene() {};

	const Application* GetApplication() { return p_app; }
	Direct2D* const GetDirect2D();

protected:

public:

protected:
	Application* p_app;
};