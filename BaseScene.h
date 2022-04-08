#pragma once

/*‘O•ûéŒ¾*/
class Application;
class Direct2D;
class Actor;
class Camera;

class BaseScene
{
public:
	BaseScene(Application* app)
		:p_app(app) 
	{};

	virtual bool InitScene() = 0;
	virtual void RunLoop() = 0;
	virtual void ExitScene() = 0;

	const Application* GetApplication() { return p_app; }
	Direct2D* const GetDirect2D();
	Camera* const GetCamera()
	{
		if (p_camera) { return p_camera; }
		else
		{
			std::cout << "Current scene doesn't have a camera." << std::endl;
			return nullptr;
		}
	}
	const Vector2& GetCameraOrigin();

	void AddActor(Actor* actor);
	void RemoveActor(Actor* actor);

protected:

public:

protected:
	Application* p_app;
	std::vector<Actor*> m_actors;
	Camera* p_camera;
};