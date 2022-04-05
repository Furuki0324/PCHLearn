#include "Game.h"
#include "Application.h"

int main()
{
	Application app(640,480);
	app.Run();

	//Game game(640, 480);

	//HRESULT hr = game.Initialize();
	//if (hr == S_OK)
	//{
	//	game.RunLoop();
	//}
	//else
	//{
	//	std::cout << std::system_category().message(hr);
	//}

	return 0;
}
