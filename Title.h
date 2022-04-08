#pragma once
#include "BaseScene.h"


class TitleScene : public BaseScene
{
public:
	TitleScene(Application* app);
	bool InitScene() override;
	void RunLoop() override;
	void ExitScene() override;

private:
};