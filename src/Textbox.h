#pragma once
#include <SDL_image.h>
#include "IDSheet.h"
#include "Entity.h"

class Textbox : public Entity
{
private:
	SDL_Texture* textTexture;
	int fontID;
	SDL_Color color;
	bool messageBox;

	void Load();
	void drawText(SDL_RendererFlip flip = SDL_FLIP_NONE);
public:
	string text;

	Textbox();
	Textbox(Vector2D pos, string text, int fontID, SDL_Color color, int lastingTime, bool messageBox = false);
	Textbox(Vector2D pos, float velocity_x, float velocity_y, string text, int fontID, SDL_Color color, int lastingTime);
	~Textbox() { SDL_DestroyTexture(textTexture); }
	void init(Vector2D pos, string text, int fontID, SDL_Color color);
	bool changeText(string text);
	void changeFont(int fontID);
	void changeColor(SDL_Color color);

	int type() { return TypeTextbox; }
	void update();
	void draw();

	//bool checkMouseOver();
};