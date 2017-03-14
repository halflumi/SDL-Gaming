//2017.02.06

#include "Main.h"
#include "Dice.h"

const int FPS = 60;
const int DELAY_TIME = 1000.0f / FPS;

int main(int argc, char **argv)
{
	Uint32 frameStart, frameTime;

	cout << "Game initialization starts!" << endl;
	if (!Main::Inst()->Initialize("A Window!", 100, 100, 1024, 600, false))
	{
		cout << "Could not initialize!\n" << SDL_GetError() << endl;
		return -1;
	}
	else
	{
		std::cout << "Game initialization success!\n" << endl;
		while (Main::Inst()->running())
		{
			frameStart = SDL_GetTicks();

			Main::Inst()->handleEvents();
			Main::Inst()->updating();
			Main::Inst()->rendering();

			frameTime = SDL_GetTicks() - frameStart;

			if (frameTime < DELAY_TIME)
				SDL_Delay((int)(DELAY_TIME - frameTime));
			if (!Dice::Inst()->rand(20))
				cout << "FPS: " << 1000 / (SDL_GetTicks() - frameStart) << endl;
		}
	}
	cout << "Exit game now..." << endl;
	Main::Inst()->close();

	return 0;
}