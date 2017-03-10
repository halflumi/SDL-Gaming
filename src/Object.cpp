#include "Object.h"
#include "Camera.h"

void Object::VisiableCheck()
{
	if (position.y - Camera::Inst()->getPosition().y < Main::Inst()->getRenderHeight() / 2)
	{
		if (position.x - Camera::Inst()->getPosition().x < Main::Inst()->getRenderWidth() / 2)
			visiable = true;
		else if (Camera::Inst()->getPosition().x - (position.x + width) < Main::Inst()->getRenderWidth() / 2)
			visiable = true;
		else
			visiable = false;
	}
	else if (Camera::Inst()->getPosition().y - (position.y + height) < Main::Inst()->getRenderHeight() / 2)
	{
		if (position.x - Camera::Inst()->getPosition().x < Main::Inst()->getRenderWidth() / 2)
			visiable = true;
		else if (Camera::Inst()->getPosition().x - (position.x + width) < Main::Inst()->getRenderWidth() / 2)
			visiable = true;
		else
			visiable = false;
	}
	else
		visiable = false;
}