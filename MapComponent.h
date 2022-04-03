#pragma once
#include "SpriteComponent.h"

/*‘O•ûéŒ¾*/
class Game;
class Actor;

class MapComponent : public SpriteComponent
{
public:
	MapComponent(Actor* owner, const char* csvPath, int drawOrder = 0);
	~MapComponent();
	void SplitCSVData(std::ifstream& ifs);

	void Render(ID2D1HwndRenderTarget* pRT) override;

private:
	int* p_mapData;
};