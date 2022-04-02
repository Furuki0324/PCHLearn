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

	void SetActorLocation(const Vector2& loc) { m_location = loc; }
	const Vector2& GetActorLocation() const { return m_location; }

	void AddComponent(Component* component);
	void RemoveComponent(Component* component);

private:

public:

private:
	Game* m_game;
	Vector2 m_location;
	std::vector<Component*> m_components;
};