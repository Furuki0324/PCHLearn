#include "SpriteComponent.h"
#include "Actor.h"
#include "Game.h"
#include "Direct2D.h"

SpriteComponent::SpriteComponent(Actor* owner, int updateOrder)
	:Component(owner)
	,m_updateOrder(updateOrder)
	,m_currentSprite(0)
	,m_isAnimation(false)
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
	m_ownerLocation = m_owner->GetActorScreenLocation();

	if (m_isAnimation)
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
}

void SpriteComponent::Render(ID2D1HwndRenderTarget* pRT)
{
	if (m_bitmap)
	{
		/*ビットマップの中から描画する部分を指定*/
		D2D1_RECT_F clippingRect = D2D1::RectF(
			static_cast<float>(m_spriteWidth * (m_currentSprite % m_numSpriteWidth)),
			static_cast<float>(m_spriteHeight * (m_currentSprite / m_numSpriteWidth)),
			static_cast<float>(m_spriteWidth * (m_currentSprite % m_numSpriteWidth) + m_spriteWidth),
			static_cast<float>(m_spriteHeight * (m_currentSprite / m_numSpriteWidth) + m_spriteHeight)
		);

		/*アクターの座標がスプライトの中心になるように調節して描画*/
		pRT->DrawBitmap(
			m_bitmap,
			D2D1::RectF(
				m_ownerLocation.x - static_cast<float>(m_spriteWidth / 2.0f),
				m_ownerLocation.y - static_cast<float>(m_spriteHeight / 2.0f),
				m_ownerLocation.x + static_cast<float>(m_spriteWidth / 2.0f),
				m_ownerLocation.y + static_cast<float>(m_spriteHeight / 2.0f)
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

	std::cout << "Size:" << m_spriteWidth << " Max:" << m_maxSprite << std::endl;
}

void SpriteComponent::SetSprite(int num)
{
	if (num < m_maxSprite) { m_currentSprite = num; }
	else
	{
		std::cout << "Passed invalid num." << std::endl;
	}
}