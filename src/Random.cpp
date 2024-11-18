#include "Random.h"
#include <cstdlib>
#include <ctime>

namespace Random
{
	void init()
	{
		std::srand(std::time(0));
	}

	int getRandomInt(int stari, int endi)
	{
		return stari + rand() % ((endi + 1) - stari);
	}
}