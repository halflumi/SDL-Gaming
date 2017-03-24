#pragma once
#include <random>

using namespace std;

class Dice
{
private:
	static Dice* INSTANCE;
	Dice() {};
	Dice(const Dice&);
    
	random_device random_generator;
public:
	static Dice* Inst()
	{
		if (INSTANCE == 0)
		{
			INSTANCE = new Dice();
			return INSTANCE;
		}
		return INSTANCE;
	}

	int rand(int max);
	int rand(int min, int max);
	int randInverse(int max);
};
