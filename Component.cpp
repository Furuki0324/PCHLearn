#include "Component.h"
#include "Actor.h"

Component::Component(Actor* owner)
	:m_owner(owner)
{
	m_owner->AddComponent(this);
}

Component::~Component()
{
	std::cout << "component destructer.\n";
	m_owner->RemoveComponent(this);
}

void Component::UpdateComponent(float deltaTime)
{

}