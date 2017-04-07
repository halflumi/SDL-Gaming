//2017.02.06

#include "Main.h"
#include "Dice.h"
#include "XmlParser.h"

const int FPS = 60;
const int DELAY_TIME = 1000.0f / FPS;

int main(int argc, char **argv)
{
	Uint32 frameStart, frameTime;

	//temporary xml loading here
	XmlParser::Inst()->load();

	cout << "Game initialization starts!" << endl;
	if (!Main::Inst()->initialize("A Window!", XmlParser::Inst()->window_x, XmlParser::Inst()->window_y, XmlParser::Inst()->window_w, XmlParser::Inst()->window_h))
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
			//if (!Dice::Inst()->rand(100))
			//	cout << "FPS: " << 1000 / (SDL_GetTicks() - frameStart) << endl;
		}
	}
	cout << "Exit game now..." << endl;
	Main::Inst()->close();

	return 0;
}