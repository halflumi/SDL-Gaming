#pragma once
#include <SDL.h>
#include <string>
#include "Vector2D.h"

using namespace std;

class Object
{
protected:
	Object() : position(0, 0), width(0), height(0), currentRow(0), currentFrame(0), numFrames(1), angle(0), alpha(255), visiable(false), active(true) {}
	//Object(int x, int y, string id) : position(x, y), uniqueID(id) {}
	Vector2D position;

	int width;
	int height;

	int currentRow;
	int currentFrame;
	int numFrames;
	string uniqueID;
	string textureFile;

	double angle;
	int alpha;
	bool visiable;

	virtual void load() = 0;
public:
	bool active;

	virtual ~Object() {}

	virtual string type() = 0;
	Vector2D& getPosition() { return position; }
	int getWidth() { return width; }
	int getHeight() { return height; }

	virtual void update() = 0;
	virtual void draw() = 0;
	//virtual void clean() = 0;
	//virtual void collision() = 0;
};

