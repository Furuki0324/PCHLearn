#include "Actor.h"
#include "Game.h"
#include "Component.h"

Actor::Actor(Game* game)
	:m_game(game)
	,m_location(Vector2::Zero)
{
	m_game->AddActor(this);
}

Actor::~Actor()
{
	m_game->RemoveActor(this);

	while (!m_components.empty())
	{
		delete m_components.back();
	}
}

void Actor::UpdateActor(float deltaTime)
{
	for (Component* component : m_components)
	{
		component->UpdateComponent(deltaTime);
	}
}

void Actor::AddComponent(Component* component)
{
	m_components.push_back(component);
}

void Actor::RemoveComponent(Component* component)
{
	auto iter = std::find(m_components.begin(), m_components.end(), component);
	m_components.erase(iter);
}