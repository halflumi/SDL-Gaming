#include <SDL_image.h>
#include <iostream>
#include "TextureLoader.h"
#include "Main.h"

TextureLoader* TextureLoader::INSTANCE = 0;

void TextureLoader::clearFromTextureMap(int id)
{
	SDL_DestroyTexture(textureMap[id]);
	textureMap[id] = NULL;
}

bool TextureLoader::load(string fileName, int id)
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
	
	if (newTexture == NULL)
		printf("SDL_ERROR creating texture from rendered surface: %s\n", SDL_GetError());

	SDL_FreeSurface(tempSurface);

	if (newTexture != 0)
	{
		textureMap[id] = newTexture;
		return true;
	}

	return false;
}

void TextureLoader::draw(int id, int x, int y, int width, int height, SDL_RendererFlip flip)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;

	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = x;
	destRect.y = y;

	SDL_RenderCopyEx(Main::Inst()->getRenderer(), textureMap[id], &srcRect, &destRect, 0, NULL, flip);
}

void TextureLoader::drawEx(int id, int src_x, int src_y, int dest_x, int dest_y, int width, int height, SDL_RendererFlip flip)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;

	srcRect.x = src_x;
	srcRect.y = src_y;
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = dest_x;
	destRect.y = dest_y;

	SDL_RenderCopyEx(Main::Inst()->getRenderer(), textureMap[id], &srcRect, &destRect, 0, NULL, flip);
}

void TextureLoader::drawEx2(int id, int x, int y, int src_width, int src_height, int dest_width, int dest_height, SDL_RendererFlip flip)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;

	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = src_width;
	srcRect.h = src_height;
	destRect.w = dest_width;
	destRect.h = dest_height;
	destRect.x = x;
	destRect.y = y;

	SDL_RenderCopyEx(Main::Inst()->getRenderer(), textureMap[id], &srcRect, &destRect, 0, NULL, flip);
}

void TextureLoader::drawFrame(int id, int x, int y, int width, int height, int currentRow, int currentFrame, double angle, int alpha,  SDL_RendererFlip flip)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;

	srcRect.x = width * currentFrame;
	srcRect.y = height * currentRow;
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = x;
	destRect.y = y;

	SDL_SetTextureAlphaMod(textureMap[id], alpha);
	SDL_RenderCopyEx(Main::Inst()->getRenderer(), textureMap[id], &srcRect, &destRect, angle, NULL, flip);
}

void TextureLoader::drawFrameEx(int id, int x, int y, int src_width, int src_height, int dest_width, int dest_height, int currentRow, int currentFrame, double angle, int alpha, SDL_RendererFlip flip)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;

	srcRect.x = src_width * currentFrame;
	srcRect.y = src_height * currentRow;
	srcRect.w = src_width;
	srcRect.h = src_height;
	destRect.w = dest_width;
	destRect.h = dest_height;
	destRect.x = x;
	destRect.y = y;

	SDL_SetTextureAlphaMod(textureMap[id], alpha);
	SDL_RenderCopyEx(Main::Inst()->getRenderer(), textureMap[id], &srcRect, &destRect, angle, NULL, flip);
}

void TextureLoader::drawFrameSp(int id, int x, int y, int width, int height, int currentRow, int currentFrame, double angle, int alpha, SDL_Color color, SDL_RendererFlip flip)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;

	srcRect.x = width * currentFrame;
	srcRect.y = height * currentRow;
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = x;
	destRect.y = y;

	SDL_SetTextureColorMod(textureMap[id], color.r, color.g, color.b);
	SDL_SetTextureAlphaMod(textureMap[id], alpha);
	SDL_RenderCopyEx(Main::Inst()->getRenderer(), textureMap[id], &srcRect, &destRect, angle, NULL, flip);
}