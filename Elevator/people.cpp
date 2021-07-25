/********************
作者：陈晗阳
邮箱：19281123@bjtu.edu.cn
创建时间：2021/7/20
修改时间：2021/7/21
描述：人群功能模拟
********************/

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

int People::nearRequest(Elevator& elevator)
{
	int high(elevator.getFloor()), low(elevator.getFloor());

	/*获得电梯所在楼层以上的最近请求*/
	for (; high <= (int)peopleWaitIn.size(); high++)
	{
		if (peopleWaitIn[high - 1] && !this->requestState[high - 1]) break;
	}

	/*获得电梯所在楼层以下的最近请求*/
	for (; low >= 1; low--)
	{
		if (peopleWaitIn[low - 1] && !this->requestState[low - 1]) break;
	}

	/*根据最近请求更改响应状态*/
	if (high > peopleWaitIn.size() && low >= 1)
	{
		if (elevator.getDestination() > low)
		{
			this->requestState[elevator.getDestination() - 1] = false;
			this->requestState[low - 1] = true;
			elevator.setDestination(low);
		}
		return low;
	}
	else if (high <= peopleWaitIn.size() && low < 1)
	{
		if (elevator.getDestination() < high)
		{
			this->requestState[elevator.getDestination() - 1] = false;
			this->requestState[high - 1] = true;
			elevator.setDestination(high);
		}
		return high;
	}
	else if (high > peopleWaitIn.size() && low < 1) return -1;
	else
	{
		if ((high - elevator.getFloor()) > (low - elevator.getFloor()))
		{
			if (elevator.getDestination() > low)
			{
				this->requestState[elevator.getDestination() - 1] = false;
				this->requestState[low - 1] = true;
				elevator.setDestination(low);
			}
			return low;
		}
		else
		{
			if (elevator.getDestination() < high)
			{
				this->requestState[elevator.getDestination() - 1] = false;
				this->requestState[high - 1] = true;
				elevator.setDestination(high);
			}
			return high;
		}
	}
}

int People::upRequest(Elevator& elevator)
{
	int high((int)peopleWaitIn.size());

	/*获得电梯所在楼层以上最远请求*/
	for (; high > elevator.getFloor(); high--)
	{
		if (peopleWaitIn[high - 1] && !this->requestState[high - 1]) break;
	}

	/*根据最近请求更改响应状态*/
	if (elevator.getDestination() < high)
	{
		this->requestState[elevator.getDestination() - 1] = false;
		this->requestState[high - 1] = true;
		elevator.setDestination(high);
	}
	return high;
}

int People::downRequest(Elevator& elevator)
{
	int low(1);
	/*获得电梯所在楼层以下最远请求*/
	for (; low < elevator.getFloor(); low++)
	{
		if (peopleWaitIn[low - 1] && !this->requestState[low - 1]) break;
	}
	/*根据最近请求更改响应状态*/
	if (elevator.getDestination() > low)
	{
		this->requestState[elevator.getDestination() - 1] = false;
		this->requestState[low - 1] = true;
		elevator.setDestination(low);
	}
	return low;
}

void People::boarding(Elevator& elevator)
{
	int floor(elevator.getFloor()), totalWight(elevator.getTotalWight());
	if (peopleWaitIn[floor - 1])	//该楼层是否有人等待
	{
		/*遍历获得需上电梯的人*/
		for (vector<Human>::iterator iter(peopleIn[floor - 1].begin()); iter != peopleIn[floor - 1].end();)
		{
			if (elevator.getState() == State::WAIT && iter->getState() == State::UP && elevator.boarding(*iter, *this))
			{
				iter = peopleIn[floor - 1].erase(iter);
				elevator.setState(State::UP); peopleNum--;
				continue;
			}
			else if (elevator.getState() == State::WAIT && iter->getState() == State::DOWN && elevator.boarding(*iter, *this))
			{
				iter = peopleIn[floor - 1].erase(iter);
				elevator.setState(State::DOWN); peopleNum--;
				continue;
			}
			else if (elevator.getState() == State::UP && iter->getState() == State::UP && elevator.boarding(*iter, *this))
			{
				iter = peopleIn[floor - 1].erase(iter); peopleNum--;
				continue;
			}
			else if (elevator.getState() == State::DOWN && iter->getState() == State::DOWN&& elevator.boarding(*iter, *this))
			{
				iter = peopleIn[floor - 1].erase(iter); peopleNum--;
				continue;
			}
			iter++;
		}
	}
	if (peopleIn[floor - 1].empty()) peopleWaitIn[floor - 1] = false;	//若无人等待，则更改设置标志
}
