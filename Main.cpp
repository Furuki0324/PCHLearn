#include "Game.h"

int main()
{
	Game game(640, 480);

	HRESULT hr = game.Initialize();
	if (hr == S_OK)
	{
		game.RunLoop();
	}
	else
	{
		std::cout << std::system_category().message(hr);
	}

	return 0;
}
