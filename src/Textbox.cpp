#include "Textbox.h"
#include "Main.h"
#include "TextureLoader.h"
#include "Camera.h"

bool operator==(SDL_Color& color, SDL_Color& _color)
{
	if (color.r == _color.r && color.g == _color.g && color.b == _color.b)
		return true;
	return false;
}

Textbox::Textbox() : textTexture(NULL)
{
	duration = -2;
}

Textbox::Textbox(Vector2D pos, string _text, int _fontID, SDL_Color _color, int lastingTime) : timer(true)
{
	textTexture = NULL;
	position = pos;
	text = _text;
	fontID = _fontID;
	color = _color;
	duration = lastingTime;
	Load();
}

Textbox::Textbox(Vector2D pos, float velocity_x, float velocity_y, string _text, int _fontID, SDL_Color _color, int lastingTime) : timer(true)
{
	textTexture = NULL;
	position = pos;
	velocity.x = velocity_x;
	velocity.y = velocity_y;
	text = _text;
	fontID = _fontID;
	color = _color;
	duration = lastingTime;
	Load();
}

void Textbox::init(Vector2D pos, string _text, int _fontID, SDL_Color _color) 
{
	position = pos;
	text = _text;
	fontID = _fontID;
	color = _color;
	Load();
}

bool Textbox::changeText(string _text)
{
	if (text == _text)
		return false;
	text = _text;
	Load();
	return true;
}

void Textbox::changeFont(int _fontID)
{
	if (fontID == _fontID)
		return;
	fontID = _fontID;
	Load();
}

void Textbox::changeColor(SDL_Color _color)
{
	if (color == _color)
		return;
	color = _color;
	Load();
}

void Textbox::Load()
{
	SDL_Surface* textSurface = TTF_RenderText_Blended(Main::Inst()->getFont(fontID), text.c_str(), color);
	if (textSurface == NULL)
	{
		printf("SDL_TTF_ERROR rendering text surface: %s\n", TTF_GetError());
	}
	else
	{
		textTexture = SDL_CreateTextureFromSurface(Main::Inst()->getRenderer(), textSurface);

		if (textTexture == NULL)
			printf("SDL_ERROR creating texture from rendered text: %s\n", SDL_GetError());
		else
		{
			width = textSurface->w;
			height = textSurface->h;
		}

		SDL_FreeSurface(textSurface);
	}
}

void Textbox::update()
{
	if (duration < 0) // UI text
		return;

	VisiableCheck();

	if (timer.getTicks() > duration)
	{
		active = false;
		return;
	}
	/// upfloat for 0.8 sec
	if (timer.getTicks() < 48)
		position += velocity;
	else
		alpha -= 10;
}

void Textbox::draw()
{
	if (active)
	{
		drawText();
	}
}

void Textbox::drawText(SDL_RendererFlip flip)
{
	SDL_Rect destRect;

	if (duration != -1)
	{
		destRect.x = position.x - Camera::Inst()->getPosition().x + Main::Inst()->getRenderWidth() / 2;
		destRect.y = position.y - Camera::Inst()->getPosition().y + Main::Inst()->getRenderHeight() / 2;
	}
	else
	{
		destRect.x = position.x;
		destRect.y = position.y;
	}
	destRect.w = width;
	destRect.h = height;

	SDL_SetTextureAlphaMod(textTexture, alpha);
	SDL_RenderCopyEx(Main::Inst()->getRenderer(), textTexture, NULL, &destRect, angle, 0, flip);
}