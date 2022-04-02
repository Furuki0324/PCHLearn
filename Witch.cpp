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

	SetActorLocation(Vector2{ 50.0f, 30.0f });
}
