#pragma once
#include <SDL_image.h>
#include "IDSheet.h"
#include "Object.h"
#include "MyTimer.h"

class Textbox : public Object
{
private:
	MyTimer timer;
	SDL_Texture* textTexture;
	SDL_Color color;
	Vector2D velocity;
	int duration;

	void Load();
	void drawText(SDL_RendererFlip flip = SDL_FLIP_NONE);
public:
	int fontID;
	string text;

	Textbox();
	Textbox(Vector2D pos, string text, int fontID, SDL_Color color, int lastingTime);
	Textbox(Vector2D pos, float velocity_x, float velocity_y, string text, int fontID, SDL_Color color, int lastingTime);
	~Textbox() { SDL_DestroyTexture(textTexture); }
	void init(Vector2D pos, string text, int fontID, SDL_Color color);
	bool changeText(string text);
	void changeFont(int fontID);
	void changeColor(SDL_Color color);

	int type() { return TypeTextbox; }
	void update();
	void draw();
};