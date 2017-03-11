#pragma once
#include <SDL_image.h>
#include "IDSheet.h"
#include "Entity.h"

class Textbox : public Entity
{
private:
	SDL_Texture* textTexture;
	string fontID;
	SDL_Color color;

	void Load();
	void drawText(SDL_RendererFlip flip = SDL_FLIP_NONE);
public:
	string text;

	Textbox();
	Textbox(Vector2D pos, string text, string fontID, SDL_Color color, int lastingTime);
	Textbox(Vector2D pos, float velocity_x, float velocity_y, string text, string fontID, SDL_Color color, int lastingTime);
	~Textbox() { SDL_DestroyTexture(textTexture); }
	void init(Vector2D* pos, string text, string fontID, SDL_Color color);
	void changeText(string& text);
	void changeFont(string fontID);
	void changeColor(SDL_Color color);

	string type() { return TypeTextbox; }
	void update();
	void draw();

	//bool checkMouseOver();
};