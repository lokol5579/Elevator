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
	for (; !peopleWaitIn[high] && high <= (int)peopleWaitIn.size(); high++);
	for (; !peopleWaitIn[low] && low >= 1; low++);
	return (high - floor) > (low - floor) ? low : high;
}

int People::upRequest(int floor)
{
	int high((int)peopleWaitIn.size());
	for (; !peopleWaitIn[high] && high >= floor; high--);
	return high;
}

int People::downRequest(int floor)
{
	int low(0);
	for (; !peopleWaitIn[low] && low <= floor; low++);
	return low;
}

void People::boarding(Elevator& elevator)
{
	State state(elevator.getState());
	int floor(elevator.getFloor()), totalWight(elevator.getTotalWight());
	if (peopleWaitIn[floor - 1])
	{
		for (vector<Human>::iterator iter(peopleIn[floor - 1].begin()); elevator.getPeopleWight() < totalWight;)
		{
			if (elevator.getState() == State::WAIT && iter->getState() == State::UP && elevator.boarding(*iter))
			{
				iter = peopleIn[floor - 1].erase(iter);
				elevator.setState(State::UP);
				continue;
			}
			else if (elevator.getState() == State::WAIT && iter->getState() == State::DOWN && elevator.boarding(*iter))
			{
				iter = peopleIn[floor - 1].erase(iter);
				elevator.setState(State::DOWN);
				continue;
			}
			else if (elevator.getState() == State::UP && iter->getState() == State::UP && elevator.boarding(*iter))
			{
				iter = peopleIn[floor - 1].erase(iter);
				continue;
			}
			else if (elevator.getState() == State::DOWN && iter->getState() == State::DOWN && elevator.boarding(*iter))
			{
				iter = peopleIn[floor - 1].erase(iter);
				continue;
			}
			iter++;
		}
	}
	if (peopleIn[floor - 1].empty()) peopleWaitIn[floor - 1] = false;
}
