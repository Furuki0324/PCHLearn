#include "UI.h"
#include "BaseScene.h"
#include "Direct2D.h"
#include "SpriteComponent.h"

UI::UI(BaseScene* scene, int updateOrder)
	:Actor(scene, updateOrder)
{
	SpriteComponent* sprite = new SpriteComponent(this, m_updateOrder);
	ID2D1Bitmap* bitmap = GetScene()->GetDirect2D()->LoadImageFile(L"./Image/Moai01.png");
	if (bitmap) { sprite->SetBitmap(bitmap, 96, 320); }
}

void UI::UpdateActor(float deltaTime)
{
	UpdateComponent(deltaTime);
}