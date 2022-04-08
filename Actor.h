#pragma once

/*‘O•ûéŒ¾*/
class BaseScene;
class Game;
class Component;

class Actor
{
public:
	Actor(BaseScene* scene, int updateOrder = 100);
	virtual ~Actor();
	int GetUpdateOrder() { return m_updateOrder; }

	virtual void ProcessInput(const BYTE* input) {};
	virtual void UpdateActor(float deltaTime);

	BaseScene* GetScene()
	{
		if (m_scene) { return m_scene; }
		else
		{
			std::cout << "Don't have any scene." << std::endl;
			return nullptr;
		}
	}

	void SetActorMoveSpeed(const float& speed) { m_moveSpeed = speed; }
	const float& GetActorMoveSpeed() const { return m_moveSpeed; }

	void SetActorWorldLocation(const Vector2& loc) { m_worldLocation = loc; }
	const Vector2& GetActorWorldLocation() const { return m_worldLocation; }
	const Vector2& GetActorScreenLocation() const { return m_screenLocation; }

	void AddComponent(Component* component);
	void RemoveComponent(Component* component);
	void UpdateComponent(float deltaTime);

protected:
	const Vector2 LocationWorldToScreen(const Vector2& worldLocation, const Vector2& camera);

protected:
	BaseScene* m_scene;
	int m_updateOrder;

	float m_moveSpeed;
	Vector2 m_worldLocation;
	Vector2 m_screenLocation;
	std::vector<Component*> m_components;
};