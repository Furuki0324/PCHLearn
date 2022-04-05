#include "Witch.h"
#include "Game.h"
#include "Direct2D.h"
#include "SpriteComponent.h"

Witch::Witch(Game* game)
	:Actor(game)
{
	p_spriteComponent = new SpriteComponent(this);
	p_spriteComponent->SetAnimation(true);
	//ID2D1Bitmap* bitmap = GetGame()->GetDitect2DPtr()->LoadImageFile(L"./Image/witch.png");
	ID2D1Bitmap* bitmap = GetGame()->GetDirect2D()->LoadImageFile(L"./Image/witch.png");
	if (bitmap != nullptr) { p_spriteComponent->SetBitmap(bitmap, 32, 32); }
}

void Witch::ProcessInput(const BYTE* input)
{
	Vector2 direction = Vector2::Zero;

	if (input[VK_5] & 0x80)
	{
		m_moveSpeed = 5.0f;
	}

	if (input[VK_A] & 0x80)
	{
		direction.x -= 1;
	}
	if (input[VK_D] & 0x80)
	{
		direction.x += 1;
	}
	if (input[VK_W] & 0x80)
	{
		direction.y -= 1;
	}
	if (input[VK_S] & 0x80)
	{
		direction.y += 1;
	}

	m_worldLocation += direction * m_moveSpeed;
}

void Witch::UpdateActor(float deltaTime, const BYTE* input)
{
	Actor::UpdateActor(deltaTime, input);


}