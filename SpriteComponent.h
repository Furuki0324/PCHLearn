#pragma once
#include "Component.h"

class SpriteComponent : public Component
{
public:
	SpriteComponent(Actor* owner, int updateOrder = 100);
	~SpriteComponent();
	void UpdateComponent(float deltaTime) override;

	int GetUpdateOrder() { return m_updateOrder; }

	/*
	Bitmap -> �f�ނ��ЂƂ܂Ƃ߂ɂ��ꂽ�摜
	Sprite -> Bitmap�̒��Ő؂�o���摜����т��̔ԍ�
	*/
	void SetBitmap(ID2D1Bitmap* bitmap, int spriteWidth, int spriteHeight);
	void SetSprite(int num);
	void Render(ID2D1HwndRenderTarget* pRT);

private:

private:
	int m_updateOrder;
	ID2D1Bitmap* m_bitmap;

	int m_currentSprite;
	int m_maxSprite;
	int m_spriteWidth;
	int m_spriteHeight;
	int m_numSpriteWidth;
	int m_numSpriteHeight;

	float wait;
};