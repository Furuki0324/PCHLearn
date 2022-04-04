#pragma once

/*‘O•ûéŒ¾*/
class Application;

class BaseScene
{
public:
	BaseScene(Application* app)
		:p_app(app) 
	{};

	void RunLoop();

protected:

public:

protected:
	Application* p_app;
};