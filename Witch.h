#pragma once
#include "Actor.h"

/*�O���錾*/
class Game;
class SpriteComponent;

class Witch : public Actor
{
public:
	Witch(Game* game);

	void ProcessInput(const BYTE* input) override;
	void UpdateActor(float deltaTime, const BYTE* input) override;

private:

public:

private:
	SpriteComponent* p_spriteComponent;
};