#pragma once

/*�O���錾*/
class Actor;

class Component
{
public:
	Component(Actor* owner);
	virtual ~Component();

	virtual void UpdateComponent(float deltaTime);

protected:
	Actor* m_owner;
};