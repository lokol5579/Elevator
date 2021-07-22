/********************
作者：陈晗阳
邮箱：19281123@bjtu.edu.cn
创建时间：2021/7/20
修改时间：2021/7/21
描述：电梯功能实现
********************/

#include <iostream>
#include "elevator.h"
#include "human.h"
#include "people.h"
#include "parameter.h"
using namespace std;

int elevatorId = 0;

bool Elevator::boarding(Human& human, People& waitingPeople)
{
	if (peopleWight + human.getWight() < totalWight)
	{
		peopleWight += human.getWight();
		cout << "用户" << human.getId() << "登上了电梯" << this->getId() << "..." << endl;
		switch (human.getState())
		{
		case State::DOWN:
		{
			if (destination > human.getDestination())
			{
				waitingPeople.setRequestState(human.getDestination(), false);
				destination = human.getDestination();
				waitingPeople.setRequestState(destination, true);
			}
			break;
		}
		case State::UP: 
		{
			if (destination < human.getDestination())
			{
				waitingPeople.setRequestState(human.getDestination(), false);
				destination = human.getDestination();
				waitingPeople.setRequestState(destination, true);
			}
			break;
		}
		}
		people.push_back(human);
		return true;
	}
	else return false;
}

void Elevator::getOff(int floor, People& waitingPeople)
{
	if (!people.empty())
	{
		for (vector<Human>::iterator iter(people.begin()); iter != people.end();)
		{
			if (iter->getDestination() == floor)
			{
				peopleWight -= iter->getWight();
				cout << "用户" << iter->getId() << "下了电梯" << this->getId() << "..." << endl;
				iter = people.erase(iter);
			}
			else iter++;
		}
	}
	if (waitingPeople.getRequestState(floor)) waitingPeople.setRequestState(floor, false);
}