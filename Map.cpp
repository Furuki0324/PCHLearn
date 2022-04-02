#include "Map.h"
#include "Game.h"
#include "Direct2D.h"
#include "SpriteComponent.h"

#define STAGE_WIDTH			(640)
#define STAGE_HEIGHT		(320)
#define MAPCHIP_WIDTH		(32)
#define MAPCHIP_HEIGHT		(32)
#define NUM_MAPCHIP_WIDTH	(STAGE_WIDTH / MAPCHIP_WIDTH)
#define NUM_MAPCHIP_HEIGHT	(STAGE_HEIGHT / MAPCHIP_HEIGHT)

Map::Map(Game* game)
	:Actor(game)
{
	std::ifstream ifs("./CSV/mapchip.csv");
	if (!ifs)
	{
		std::cout << "No CSV file found." << std::endl;
	}
	else
	{
		std::cout << "Load CSV file." << std::endl;
	}

	p_spriteComponent = new SpriteComponent(this);
	p_spriteComponent->SetAnimation(false);
	ID2D1Bitmap* m_bitmap = GetGame()->GetDitect2DPtr()->LoadImageFile(L"./Image/base.png");
	if (m_bitmap != nullptr) { p_spriteComponent->SetBitmap(m_bitmap, 16, 16); }
}

void Map::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);


}