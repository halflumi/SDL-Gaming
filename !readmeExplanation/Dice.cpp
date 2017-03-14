#include "Dice.h"

Dice* Dice::INSTANCE = 0;

int Dice::rand(int max)
{
	return random_generator() % max;
}