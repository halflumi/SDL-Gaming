#include "Camera.h"

Camera* Camera::INSTANCE = new Camera();

void Camera::Focus(Player* _target)
{
	if (target)
		target->removeFocused();
	target = _target;
}