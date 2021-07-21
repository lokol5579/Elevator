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
		cout << "�û�" << &human << "�����˵���..." << endl;
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
				cout << "�û�" << &iter << "���˵���..." << endl;
				iter = people.erase(iter);
			}
			else iter++;
		}
	}
}