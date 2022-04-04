#include "Actor.h"
#include "Game.h"
#include "Component.h"

Actor::Actor(Game* game)
	:m_game(game)
	,m_moveSpeed(0.0f)
	,m_worldLocation(Vector2::Zero)
	,m_screenLocation(Vector2::Zero)
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

void Actor::UpdateActor(float deltaTime, const BYTE* input)
{
	/*コンポーネントが更新される前にスクリーン座標に変換*/
	m_screenLocation = LocationWorldToScreen(m_worldLocation, m_game->GetCameraOrigin());

	for (Component* component : m_components)
	{
		component->UpdateComponent(deltaTime);
	}
}

const Vector2 Actor::LocationWorldToScreen(const Vector2& worldLocation, const Vector2& camera)
{
	return worldLocation - camera;
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