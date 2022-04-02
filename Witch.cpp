#include "Witch.h"
#include "Game.h"
#include "Direct2D.h"
#include "SpriteComponent.h"

Witch::Witch(Game* game)
	:Actor(game)
{
	SpriteComponent* sprite = new SpriteComponent(this);
	ID2D1Bitmap* bitmap = GetGame()->GetDitect2DPtr()->LoadImageFile(L"./Image/witch.png");
	if (bitmap != nullptr) { sprite->SetBitmap(bitmap, 32, 32); }

	SetActorLocation(Vector2{ 50.0f, 30.0f });
}
