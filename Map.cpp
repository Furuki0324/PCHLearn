#include "Map.h"

#define STAGE_WIDTH			(640)
#define STAGE_HEIGHT		(320)
#define MAPCHIP_WIDTH		(32)
#define MAPCHIP_HEIGHT		(32)
#define NUM_MAPCHIP_WIDTH	(STAGE_WIDTH / MAPCHIP_WIDTH)
#define NUM_MAPCHIP_HEIGHT	(STAGE_HEIGHT / MAPCHIP_HEIGHT)

Map::Map()
{
	FILE* pFile;
	errno_t errorCode;
	errorCode = fopen_s(&pFile, "/CSV/mapchip.csv", "r");

	if (errorCode != 0)
	{
		DebugBreak();
	}
}