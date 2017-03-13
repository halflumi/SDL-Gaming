#include <SDL_image.h>
#include <iostream>
#include "TextureLoader.h"
#include "Main.h"


TextureLoader* TextureLoader::INSTANCE = 0;

bool TextureLoader::load(string fileName, string id)
{
	//Avoid reloading the same texture
	if (textureMap[id])
		return true;

	SDL_Surface* tempSurface = IMG_Load(fileName.c_str());

	if (tempSurface == 0)
	{
		printf("SDL_IMAGE_ERROR loading image from file: %s\n", fileName.c_str(), IMG_GetError());
		return false;
	}

	SDL_Texture* newTexture = SDL_CreateTextureFromSurface(Main::Inst()->getRenderer(), tempSurface);

	SDL_FreeSurface(tempSurface);

	if (newTexture != 0)
	{
		textureMap[id] = newTexture;
		return true;
	}

	return false;
}

void TextureLoader::draw(string id, int x, int y, int width, int height, SDL_RendererFlip flip)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;

	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = x;
	destRect.y = y;

	SDL_RenderCopyEx(Main::Inst()->getRenderer(), textureMap[id], &srcRect, &destRect, 0, 0, flip);
}

void TextureLoader::drawEx(string id, int src_x, int src_y, int dest_x, int dest_y, int width, int height, SDL_RendererFlip flip)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;

	srcRect.x = src_x;
	srcRect.y = src_y;
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = dest_x;
	destRect.y = dest_y;

	SDL_RenderCopyEx(Main::Inst()->getRenderer(), textureMap[id], &srcRect, &destRect, 0, 0, flip);
}

void TextureLoader::drawFrame(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame, double angle, int alpha,  SDL_RendererFlip flip)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;

	srcRect.x = width * currentFrame;
	srcRect.y = height * currentRow;
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = x;
	destRect.y = y;

	SDL_RenderCopyEx(Main::Inst()->getRenderer(), textureMap[id], &srcRect, &destRect, angle, NULL, flip);
}