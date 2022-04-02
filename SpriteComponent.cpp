#include "SpriteComponent.h"
#include "Actor.h"
#include "Game.h"
#include "Direct2D.h"

SpriteComponent::SpriteComponent(Actor* owner, int updateOrder)
	:Component(owner)
	,m_updateOrder(updateOrder)
{
	m_owner->GetGame()->GetDitect2DPtr()->AddSpriteComponent(this);
	wait = 0;
}

SpriteComponent::~SpriteComponent()
{
	m_owner->GetGame()->GetDitect2DPtr()->RemoveSpriteComponent(this);
}

void SpriteComponent::UpdateComponent(float deltaTime)
{
	wait += deltaTime;
	if (wait > 0.5f)
	{
		int next = m_currentSprite + 1;
		if (next >= m_maxSprite) { next = 0; }
		SetSprite(next);
		wait = 0;
	}
}

void SpriteComponent::Render(ID2D1HwndRenderTarget* pRT)
{
	if (m_bitmap)
	{
		Vector2 ownerLocation = m_owner->GetActorLocation();

		/*ビットマップの中から描画する部分を指定*/
		D2D1_RECT_F clippingRect = D2D1::RectF(
			m_spriteWidth * (m_currentSprite % m_numSpriteWidth),
			m_spriteHeight * (m_currentSprite / m_numSpriteWidth),
			m_spriteWidth * (m_currentSprite % m_numSpriteWidth) + m_spriteWidth,
			m_spriteHeight * (m_currentSprite / m_numSpriteWidth) + m_spriteHeight
		);

		pRT->DrawBitmap(
			m_bitmap,
			D2D1::RectF(
				ownerLocation.x,
				ownerLocation.y,
				ownerLocation.x + m_spriteWidth,
				ownerLocation.y + m_spriteHeight
			),
			1.0f,
			D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
			&clippingRect);
	}
}

void SpriteComponent::SetBitmap(ID2D1Bitmap* bitmap, int spriteWidth, int spriteHeight)
{
	m_bitmap = bitmap;
	m_spriteWidth = spriteWidth;
	m_spriteHeight = spriteHeight;
	m_currentSprite = 0;

	D2D1_SIZE_U size = m_bitmap->GetPixelSize();

	m_numSpriteWidth = size.width / spriteWidth;
	m_numSpriteHeight = size.height / spriteHeight;

	m_maxSprite = m_numSpriteWidth * m_numSpriteHeight;
}

void SpriteComponent::SetSprite(int num)
{
	if (num < m_maxSprite) { m_currentSprite = num; }
	else
	{
		std::cout << "Passed invalid num." << std::endl;
	}
}