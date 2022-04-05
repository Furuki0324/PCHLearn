#include "BaseScene.h"
#include "Application.h"

Direct2D* const BaseScene::GetDirect2D()
{
	return p_app->GetDirect2D();
}