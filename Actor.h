#pragma once

/*‘O•ûéŒ¾*/
class Game;
class Component;

class Actor
{
public:
	Actor(Game* game);
	~Actor();

	virtual void UpdateActor(float deltaTime);
	Game* GetGame()
	{
		if (m_game) { return m_game; }
		else
		{
			std::cout << "No game." << std::endl;
			return nullptr;
		}
	}

	void SetActorWorldLocation(const Vector2& loc) { m_worldLocation = loc; }
	const Vector2& GetActorWorldLocation() const { return m_worldLocation; }
	const Vector2& GetActorScreenLocation() const { return m_screenLocation; }

	void AddComponent(Component* component);
	void RemoveComponent(Component* component);

private:
	const Vector2 LocationWorldToScreen(const Vector2& worldLocation, const Vector2& camera);

protected:
	Game* m_game;
	Vector2 m_worldLocation;
	Vector2 m_screenLocation;
	std::vector<Component*> m_components;
};