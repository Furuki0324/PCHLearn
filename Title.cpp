#include "Title.h"
#include "Application.h"

TitleScene::TitleScene(Application* app)
	:BaseScene(app)
{
	std::cout << "Create Title." << std::endl;
}

bool TitleScene::InitScene()
{
	return true;
}

void TitleScene::RunLoop()
{
	BYTE key[256];
	GetKeyboardState(key);

	if (key[VK_Y] & 0x80)
	{
		p_app->Quit();
	}
	if (key[VK_RETURN] & 0x80)
	{
		p_app->ChangeScene(Application::Scene::game);
	}
}

void TitleScene::ExitScene()
{

}