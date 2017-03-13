#include "Dialog.h"
#include "World.h"
#include "TextureLoader.h"

Dialog::Dialog()
{
	position.y = 400;
	Load();
}

void Dialog::Load()
{
	dialogText = new Textbox(position, "hey kiddo, I'm just writting this so you know that here are texts.", segoeui28, { 255,255,255 }, -1);
	width = 10;
	height = 10;
	next = NULL;
}

void Dialog::update()
{

}

void Dialog::draw()
{
	TextureLoader::Inst()->drawFrameEx(DialogBackground, position.x, position.y, width, height, World::Inst()->getWorldWidth(), 200, 0, 0, 0, 255);
	dialogText->draw();
}
