#pragma once

/*‘O•ûéŒ¾*/
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