#pragma once
#include <SDL.h>
#include <string>
#include "Vector2D.h"

using namespace std;

class Object
{
protected:
	Object() 
	: position(0, 0), uniqueID(-1), name(""), width(0), height(0), currentRow(0), currentFrame(0), numFrames(1), animatedSpeed(12), angle(0), alpha(255), visiable(false), active(true) 
	{}
	int uniqueID;

	int currentFrame;
	int currentRow;
	int numFrames;
	int animatedSpeed;
	double angle;
	int alpha;

	virtual void Load() = 0;
	void VisiableCheck();
public:
	string name;
	Vector2D position;
	int width;
	int height;
	bool visiable;
	bool active;

	virtual int type() = 0;
	int getUniqueID() { return uniqueID; }
	void setUniqueID(int id) { uniqueID = id; }
	void setPosition(float x, float y) { position.set(x, y); }
	void setPosition(Vector2D pos) { position = pos; }
	void setPosition(Vector2D* pos) { position = *pos; }
	void addPosition(Vector2D shift) { position += shift; }

	virtual void update() = 0;
	virtual void draw() = 0;
};

