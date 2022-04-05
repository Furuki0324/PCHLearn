#pragma once
#include "BaseScene.h"


class TitleScene : public BaseScene
{
public:
	TitleScene(Application* app);
	void RunLoop() override;

private:
};