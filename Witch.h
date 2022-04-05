#pragma once
#include "Actor.h"

/*‘O•ûéŒ¾*/
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