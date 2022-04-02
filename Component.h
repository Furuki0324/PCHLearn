#pragma once

/*�O���錾*/
class Actor;

class Component
{
public:
	Component(Actor* owner);
	~Component();

	virtual void UpdateComponent(float deltaTime);

protected:
	Actor* m_owner;
};