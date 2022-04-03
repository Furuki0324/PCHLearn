#pragma once
#include "Actor.h"

/*‘O•ûéŒ¾*/
class Game;
class SpriteComponent;

class Witch : public Actor
{
public:
	Witch(Game* game);

	void UpdateActor(float deltaTime) override;

private:

public:

private:
	SpriteComponent* p_spriteComponent;
};