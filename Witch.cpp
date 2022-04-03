#include "Witch.h"
#include "Game.h"
#include "Direct2D.h"
#include "SpriteComponent.h"

Witch::Witch(Game* game)
	:Actor(game)
{
	p_spriteComponent = new SpriteComponent(this);
	p_spriteComponent->SetAnimation(true);
	ID2D1Bitmap* bitmap = GetGame()->GetDitect2DPtr()->LoadImageFile(L"./Image/witch.png");
	if (bitmap != nullptr) { p_spriteComponent->SetBitmap(bitmap, 32, 32); }
}

void Witch::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);

	Vector2 direction = Vector2::Zero;
	BYTE key[256];
	GetKeyboardState(key);

	if (key[VK_A] & 0x80)
	{
		direction.x -= 1;
	}
	if (key[VK_D] & 0x80)
	{
		direction.x += 1;
	}
	if (key[VK_W] & 0x80)
	{
		direction.y -= 1;
	}
	if (key[VK_S] & 0x80)
	{
		direction.y += 1;
	}

	m_worldLocation += direction;
}