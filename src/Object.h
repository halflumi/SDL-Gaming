#pragma once
#include <SDL.h>
#include <string>
#include "Vector2D.h"

using namespace std;

class Object
{
protected:
	Object() : position(0, 0), width(0), height(0), currentRow(0), currentFrame(0), numFrames(1), animatedSpeed(250), uniqueID(""), angle(0), alpha(255), visiable(false), active(true) {}
	Vector2D position;

	int width;
	int height;

	int numFrames;
	int animatedSpeed;
	string uniqueID;

	double angle;
	int alpha;

	virtual void Load() = 0;
	void VisiableCheck();
public:
	int currentFrame;
	int currentRow;
	bool visiable;
	bool active;

	virtual string type() = 0;
	string getUniqueID() { return uniqueID; }
	Vector2D& getPosition() { return position; }
	int getWidth() { return width; }
	int getHeight() { return height; }
	void setUniqueID(string id) { uniqueID = id; }
	void setPosition(int x, int y) { position.set(x, y); }
	void setPosition(Vector2D pos) { position = pos; }
	void setPosition(Vector2D* pos) { position = *pos; }
	void addPosition(Vector2D* shift) { position += *shift; }

	virtual void update() = 0;
	virtual void draw() = 0;
};

