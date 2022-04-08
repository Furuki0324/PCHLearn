#pragma once
#include "Actor.h"

class BaseScene;

class UI : public Actor
{
public:
	//UI以外のアクターが更新されてからUIが更新されるようにupdateOrderのデフォルトを設定
	UI(BaseScene* scene, int updateOrder = 200);
	//~UI();

	void UpdateActor(float deltaTime) override;
};
