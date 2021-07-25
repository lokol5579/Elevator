/********************
作者：陈晗阳
邮箱：19281123@bjtu.edu.cn
创建时间：2021/7/20
修改时间：2021/7/21
描述：电梯功能实现
********************/

#include "elevator.h"
#include "human.h"
#include "people.h"
#include "parameter.h"
#include "file.h"
using namespace std;

int elevatorId = 0;

bool Elevator::boarding(Human& human, People& waitingPeople)
{
	if (peopleWight + human.getWight() < totalWight)	//是否超重
	{
		peopleWight += human.getWight();
		writeBoardingInfo(human, this->getId());	//写入日志

		/*根据人去的方向及电梯状态判断是否上电梯*/
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
		this->totalCapacity++;
		return true;
	}
	else return false;
}

void Elevator::getOff(int floor, People& waitingPeople)
{
	if (!people.empty())	//判断是否空载
	{
		/*遍历是否有到达目标楼层的人*/
		for (vector<Human>::iterator iter(people.begin()); iter != people.end();)
		{
			if (iter->getDestination() == floor)
			{
				peopleWight -= iter->getWight();
				writeOffInfo(*iter, this->getId());
				iter = people.erase(iter);
			}
			else iter++;
		}
	}
	if (waitingPeople.getRequestState(floor)) waitingPeople.setRequestState(floor, false);
}