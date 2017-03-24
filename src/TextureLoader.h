#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <unordered_map>

using namespace std;

class TextureLoader
{
private:
	TextureLoader() {}
	~TextureLoader() {}
	TextureLoader(const TextureLoader&);
	static TextureLoader* INSTANCE;

	unordered_map<int, SDL_Texture*> textureMap;
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

	unordered_map<int, SDL_Texture*>& getTextureMap() { return textureMap; }

	bool load(string fileName, int id);
	void clearTextureMap() { textureMap.clear(); }
	void clearFromTextureMap(int id);
	void draw(int id, int x, int y, int width, int height, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void drawEx(int id, int src_x, int src_y, int dest_x, int dest_y, int width, int height,  SDL_RendererFlip flip = SDL_FLIP_NONE);
	void drawEx2(int id, int x, int y, int src_width, int src_height, int dest_width, int dest_height, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void drawFrame(int id, int x, int y, int width, int height, int currentRow, int currentFrame,  double angle, int alpha, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void drawFrameSp(int id, int x, int y, int width, int height, int currentRow, int currentFrame, double angle, int alpha, SDL_Color color, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void drawFrameEx(int id, int x, int y, int src_width, int src_height, int dest_width, int dest_height, int currentRow, int currentFrame, double angle, int alpha, SDL_RendererFlip flip = SDL_FLIP_NONE);
};


