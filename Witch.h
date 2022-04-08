#pragma once
#include "Actor.h"

/*�O���錾*/
class SpriteComponent;

class Witch : public Actor
{
public:
	Witch(BaseScene* scene);

	void ProcessInput(const BYTE* input) override;
	void UpdateActor(float deltaTime) override;

private:

public:

private:
	SpriteComponent* p_spriteComponent;
};