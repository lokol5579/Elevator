#include <iostream>
#include <ctime>
#include "parameter.h"
#include "human.h"

void Human::init(int floorNum)
{
	srand((unsigned)time(NULL));
	wight = (rand() % 101) + 80; //ÌåÖØ·¶Î§80-180kg
	origin = (rand() % floorNum) + 1;
	while ((destination = (rand() % floorNum + 1)) == origin);
	(origin - destination) > 0 ? (state = State::DOWN) : (state = State::UP);
}