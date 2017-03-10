#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <map>

using namespace std;

class TextureLoader
{
private:
	TextureLoader() {}
	~TextureLoader() {}
	TextureLoader(const TextureLoader&);
	static TextureLoader* INSTANCE;

	map<string, SDL_Texture*> textureMap;
public:
	static TextureLoader* Inst()
	{
		if (INSTANCE == 0)
		{
			INSTANCE = new TextureLoader();
			return INSTANCE;
		}

		return INSTANCE;
	}

	map<string, SDL_Texture*>& getTextureMap() { return textureMap; }

	bool load(string fileName, string id);
	void clearTextureMap() { textureMap.clear(); }
	void clearFromTextureMap(string id);
	void draw(string id, int x, int y, int width, int height, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void drawEx(string id, int src_x, int src_y, int dest_x, int dest_y, int width, int height,  SDL_RendererFlip flip = SDL_FLIP_NONE);
	void drawEx2(string id, int x, int y, int src_width, int src_height, int dest_width, int dest_height, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void drawFrame(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame,  double angle, int alpha, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void drawFrameEx(std::string id, int x, int y, int src_width, int src_height, int dest_width, int dest_height, int currentRow, int currentFrame, double angle, int alpha, SDL_RendererFlip flip = SDL_FLIP_NONE);
};


