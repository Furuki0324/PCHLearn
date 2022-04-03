#pragma once
#include "Component.h"

class SpriteComponent : public Component
{
public:
	SpriteComponent(Actor* owner, int updateOrder = 100);
	~SpriteComponent();
	void UpdateComponent(float deltaTime) override;

	int GetUpdateOrder() { return m_updateOrder; }

	void SetAnimation(bool isAnimation) { m_isAnimation = isAnimation; }

	/*
	Bitmap -> ‘fŞ‚ª‚Ğ‚Æ‚Ü‚Æ‚ß‚É‚³‚ê‚½‰æ‘œ
	Sprite -> Bitmap‚Ì’†‚ÅØ‚èo‚·‰æ‘œ‚¨‚æ‚Ñ‚»‚Ì”Ô†
	*/
	void SetBitmap(ID2D1Bitmap* bitmap, int spriteWidth, int spriteHeight);
	void SetSprite(int num);
	virtual void Render(ID2D1HwndRenderTarget* pRT);

private:

protected:
	int m_updateOrder;
	ID2D1Bitmap* m_bitmap;

	int m_currentSprite;
	int m_maxSprite;
	int m_spriteWidth;
	int m_spriteHeight;
	int m_numSpriteWidth;
	int m_numSpriteHeight;

	bool m_isAnimation;
	float wait;
};