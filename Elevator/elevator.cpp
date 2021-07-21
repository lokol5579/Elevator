#include <iostream>
#include "elevator.h"
#include "human.h"
#include "parameter.h"
using namespace std;

bool Elevator::boarding(Human& human)
{
	if (peopleWight + human.getWight() < totalWight)
	{
		peopleWight += human.getWight();
		cout << "用户" << &human << "登上了电梯..." << endl;
		people.push_back(human);
		return true;
	}
	else return false;
}

void Elevator::getOff(int floor)
{
	if (!people.empty())
	{
		for (vector<Human>::iterator iter(people.begin()); iter != people.end();)
		{
			if (iter->getDestination() == floor)
			{
				peopleWight -= iter->getWight();
				cout << "用户" << &iter << "下了电梯..." << endl;
				iter = people.erase(iter);
			}
			else iter++;
		}
	}
}