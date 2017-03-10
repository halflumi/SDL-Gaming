#include "Dice.h"

Dice* Dice::INSTANCE = 0;

int Dice::rand(int max)
{
	return random_generator() % max;
}

int Dice::rand(int min, int max)
{
	if (min == max)
		return min;
	return random_generator() % (max - min) + min;
}

int Dice::randInverse(int max)
{
	return random_generator() % max - max;
}