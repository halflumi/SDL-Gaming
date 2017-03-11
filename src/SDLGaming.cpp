//2017.02.06

#include "Main.h"
#include "Dice.h"

const int FPS = 60;
const int DELAY_TIME = 1000.0f / FPS;
const int WINDOW_POS_X = 100;
const int WINDOW_POS_Y = 100;
const int WINDOW_WIDTH = 1024;
const int WINDOW_HEIGHT = 768;

int main(int argc, char **argv)
{
	Uint32 frameStart, frameTime;

	cout << "Game initialization starts!" << endl;
	if (!Main::Inst()->initialize("A Window!", WINDOW_POS_X, WINDOW_POS_Y, WINDOW_WIDTH, WINDOW_HEIGHT))
	{
		cout << "Could not initialize!\n" << SDL_GetError() << endl;
		return -1;
	}
	else
	{
		std::cout << "Game initialization success!\n" << endl;
		while (Main::Inst()->isRunning())
		{
			frameStart = SDL_GetTicks();

			Main::Inst()->prossessing();

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