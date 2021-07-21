#include <vector>
#include "building.h"
#include "elevator.h"
using namespace std;

Building::Building(int floorNum, int elevatorTotalWight, double elevatorSpeed) :floorNum(floorNum)
{
	for (int i(0); i < 3; i++)
	{
		elevator[i].setTotalWight(elevatorTotalWight);
		elevator[i].setSpeed(elevatorSpeed);
	}
}