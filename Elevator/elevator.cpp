#include "elevator.h"
#include "human.h"
#include "parameter.h"
using namespace std;

bool Elevator::boarding(Human& human)
{
	if (peopleWight + human.getWight() < totalWight)
	{
		peopleWight += human.getWight();
		people.push_back(human);
		return true;
	}
	else return false;
}

void Elevator::getOff(int floor)
{
	if (!people.empty())
	{
		for (int i(0); i < (int)people.size(); i++)
		{
			if (people[i].getDestination() == floor)
			{
				peopleWight -= people[i].getWight();
				people.erase(people.begin() + i);
			}
		}
	}
}