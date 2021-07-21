#include <iostream>
#include <vector>
#include "elevator.h"
#include "human.h"
#include "people.h"
#include "parameter.h"
using namespace std;

void People::insertVector(Human& human)
{
	peopleIn[human.getOrigin() - 1].push_back(human);
	peopleWaitIn[human.getOrigin() - 1] = true;
}

int People::nearRequest(int floor)
{
	int high(floor), low(floor);
	for (; high <= (int)peopleWaitIn.size() && !peopleWaitIn[high - 1]; high++);
	for (; low >= 1 && !peopleWaitIn[low - 1]; low--);
	if (high > peopleWaitIn.size() && low >= 1) return low;
	else if (high <= peopleWaitIn.size() && low < 1) return high;
	else if (high > peopleWaitIn.size() && low < 1) return -1;
	else return (high - floor) > (low - floor) ? low : high;
}

int People::upRequest(int floor)
{
	int high((int)peopleWaitIn.size());
	for (; !peopleWaitIn[high - 1] && high > floor; high--);
	return high;
}

int People::downRequest(int floor)
{
	int low(1);
	for (; !peopleWaitIn[low - 1] && low < floor; low++);
	return low;
}

void People::boarding(Elevator& elevator)
{
	int floor(elevator.getFloor()), totalWight(elevator.getTotalWight());
	if (peopleWaitIn[floor - 1])
	{
		for (vector<Human>::iterator iter(peopleIn[floor - 1].begin()); !peopleIn[floor - 1].empty();)
		{
			if (elevator.getState() == State::WAIT && iter->getState() == State::UP)
			{
				if (!elevator.boarding(*iter)) break;
				iter = peopleIn[floor - 1].erase(iter);
				elevator.setState(State::UP); peopleNum--;
				continue;
			}
			else if (elevator.getState() == State::WAIT && iter->getState() == State::DOWN)
			{
				if (!elevator.boarding(*iter)) break;
				iter = peopleIn[floor - 1].erase(iter);
				elevator.setState(State::DOWN); peopleNum--;
				continue;
			}
			else if (elevator.getState() == State::UP && iter->getState() == State::UP)
			{
				if (!elevator.boarding(*iter)) break;
				iter = peopleIn[floor - 1].erase(iter); peopleNum--;
				continue;
			}
			else if (elevator.getState() == State::DOWN && iter->getState() == State::DOWN)
			{
				if (!elevator.boarding(*iter)) break;
				iter = peopleIn[floor - 1].erase(iter); peopleNum--;
				continue;
			}
			iter++;
		}
	}
	if (peopleIn[floor - 1].empty()) peopleWaitIn[floor - 1] = false;
}
