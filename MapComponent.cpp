#include "MapComponent.h"
#include "Actor.h"
#include "Game.h"
#include "Direct2D.h"

#define MAP_WIDTH		(640)
#define MAP_HEIGHT		(480)
#define CHIP_WIDTH		(16)
#define CHIP_HEIGHT		(16)
#define NUM_CHIP_WIDTH	(MAP_WIDTH / CHIP_WIDTH)
#define NUM_CHIP_HEIGHT	(MAP_HEIGHT / CHIP_HEIGHT)

MapComponent::MapComponent(Actor* owner, const char* csvPath, int drawOrder)
	:SpriteComponent(owner, drawOrder)
{
	p_mapData = new int[NUM_CHIP_WIDTH * NUM_CHIP_HEIGHT];

	std::ifstream ifs(csvPath);
	if (!ifs)
	{
		std::cout << "No CSV file found." << std::endl;
	}
	else
	{
		std::cout << "Load CSV file." << std::endl;
		SplitCSVData(ifs);
	}

	SetAnimation(false);
	ID2D1Bitmap* bitmap = m_owner->GetGame()->GetDitect2DPtr()->LoadImageFile(L"./Image/base.png");
	if (bitmap) { SetBitmap(bitmap, 16, 16); }
}

MapComponent::~MapComponent()
{
	delete p_mapData;
}

void MapComponent::SplitCSVData(std::ifstream& ifs)
{
	int count = 0;
	std::string line;
	while (std::getline(ifs, line))
	{
		size_t pos;
		size_t offset = 0;
		std::string substr;

		for (int i = 0; i < NUM_CHIP_WIDTH; ++i)
		{
			pos = line.find_first_of(",", offset);
			if (i == 39 && pos == std::string::npos)
			{
				pos = line.length();
			}
			substr = line.substr(offset, pos - offset);
			p_mapData[count] = std::stoi(substr);

			offset = pos + 1;
			++count;
		}
	}
}

void MapComponent::Render(ID2D1HwndRenderTarget* pRT)
{
	for (int height = 0; height < NUM_CHIP_HEIGHT; ++height)
	{
		for (int width = 0; width < NUM_CHIP_WIDTH; ++width)
		{
			int index = p_mapData[height * NUM_CHIP_WIDTH + width];
			/*値が0の場合はスキップ*/
			if (index == 0) { continue; }
			/*もし範囲外を指定していた場合は明らかに間違ってる画像を表示*/
			if (index > m_maxSprite) { index = 0; }

			/*ビットマップの中から描画する部分を指定*/
			D2D1_RECT_F clippingRect = D2D1::RectF(
				static_cast<float>(m_spriteWidth * (index % m_numSpriteWidth)),
				static_cast<float>(m_spriteHeight * (index / m_numSpriteWidth)),
				static_cast<float>(m_spriteWidth * (index % m_numSpriteWidth) + m_spriteWidth),
				static_cast<float>(m_spriteHeight * (index / m_numSpriteWidth) + m_spriteHeight)
			);		

			pRT->DrawBitmap(
				m_bitmap,
				D2D1::RectF(
					static_cast<float>(m_ownerLocation.x + CHIP_WIDTH * width),
					static_cast<float>(m_ownerLocation.y + CHIP_HEIGHT * height),
					static_cast<float>(m_ownerLocation.x + CHIP_WIDTH * (width + 1)),
					static_cast<float>(m_ownerLocation.y + CHIP_HEIGHT * (height + 1))
				),
				1.0f,
				D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
				clippingRect
			);
		}
	}
}