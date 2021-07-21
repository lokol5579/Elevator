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
#include "parameter.h"
using namespace std;

int elevatorId = 0;

bool Elevator::boarding(Human& human)
{
	if (peopleWight + human.getWight() < totalWight)
	{
		peopleWight += human.getWight();
		cout << "用户" << human.getId() << "登上了电梯" << this->getId() << "..." << endl;
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
				cout << "用户" << iter->getId() << "下了电梯" << this->getId() << "..." << endl;
				iter = people.erase(iter);
			}
			else iter++;
		}
	}
}