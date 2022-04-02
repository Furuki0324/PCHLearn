#pragma once
#include "Actor.h"

/*�O���錾*/
class Game;
class SpriteComponent;

struct Cell
{
	int gh;
};

class Map : public Actor
{
public:
	Map(Game* game);
	void UpdateActor(float deltaTime) override;
	
private:

public:

private:
	SpriteComponent* p_spriteComponent;
	std::vector<std::vector<int>> m_map;
};