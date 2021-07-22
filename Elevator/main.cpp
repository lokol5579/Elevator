/********************
作者：陈晗阳
邮箱：19281123@bjtu.edu.cn
创建时间：2021/7/19
修改时间：2021/7/21
描述：主程序
********************/

#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <ctime>
#include <cstdlib>
#include <Windows.h>
#include "parameter.h"
#include "human.h"
#include "people.h"
#include "elevator.h"
#include "building.h"
#include "file.h"
#include "console.h"

using namespace std;

thread* elevatorThread;
mutex mtx;

void elevatorRun(People& people, Elevator *elevator, int elevatorId, int elevatorNum)
{
	if (!writeSimulateInfo(elevator[elevatorId].getId())) return;
	while (people.getPeopleNum() != 0 || !elevator[elevatorId].peopleIsNULL())
	{
		{
			lock_guard<mutex> lock(mtx);
			refresh(elevator, elevatorNum);
		}
		int floor = elevator[elevatorId].getFloor();
		if (elevator[elevatorId].getState() == State::WAIT)
		{
			{
				lock_guard<mutex> lock(mtx);
				people.nearRequest(elevator[elevatorId]);
				if (elevator[elevatorId].getDestination() == floor)
					people.boarding(elevator[elevatorId]);
				else elevator[elevatorId].getDestination() > floor ? elevator[elevatorId].setState(State::UP) : elevator[elevatorId].setState(State::DOWN);
			}
			Sleep((DWORD)(elevator[elevatorId].getTime() * 1000));
		}
		else if (elevator[elevatorId].getState() == State::UP)
		{
			elevator[elevatorId].moveUp(); floor++;
			elevator[elevatorId].getOff(floor, people);
			{
				lock_guard<mutex> lock(mtx);
				people.upRequest(elevator[elevatorId]);
				if (elevator[elevatorId].getDestination() == floor && elevator[elevatorId].peopleIsNULL())
				{
					elevator[elevatorId].setState(State::WAIT);
					continue;
				}
				else people.boarding(elevator[elevatorId]);
			}
			Sleep((DWORD)(elevator[elevatorId].getTime() * 1000));
		}
		else if (elevator[elevatorId].getState() == State::DOWN)
		{
			elevator[elevatorId].moveDown(); floor--;
			elevator[elevatorId].getOff(floor, people);
			lock_guard<mutex> lock(mtx);
			people.downRequest(elevator[elevatorId]);
			if (elevator[elevatorId].getDestination() == floor && elevator[elevatorId].peopleIsNULL())
			{
				elevator[elevatorId].setState(State::WAIT);
				continue;
			}
			else people.boarding(elevator[elevatorId]);
			Sleep((DWORD)(elevator[elevatorId].getTime() * 800));
		}
	}
	{
		lock_guard<mutex> lock(mtx);
		refresh(elevator, elevatorNum);
	}
}

int main()
{
	/*获得程序参数*/
	int floorNum(5), elevatorNum(3), elevatorWight(1000), peopleNum(100);
	double elevatorSpeed(1.0);
	cout << "***************欢迎使用电梯模拟器***************" << endl;
	//cout << "请输入建筑层数："; cin >> floorNum;
	////cout << "请输入建筑电梯数量："; cin >> elevatorNum;
	//cout << "请输入电梯载重："; cin >> elevatorWight;
	//cout << "请输入电梯速度："; cin >> elevatorSpeed;
	//cout << "请输入初始等待人数："; cin >> peopleNum;

	/*初始化建筑、电梯及乘客*/
	Building building(floorNum, elevatorWight, elevatorSpeed);
	Human* human = new Human[peopleNum];
	People people(peopleNum, floorNum);
	for (int i(0); i < peopleNum; i++)
	{
		human[i].init(floorNum);
		people.insertVector(human[i]);
	}

	cout << "Start to simulate..." << endl;

	clock_t start = clock();

	/*多线程电梯构建*/
	elevatorThread = new thread[elevatorNum];
	for (int i(0); i < elevatorNum; i++)
		elevatorThread[i] = thread(elevatorRun, ref(people), building.getElevator(), i, elevatorNum);
	
	for (thread* iter = elevatorThread; iter <= &elevatorThread[elevatorNum - 1]; iter++)
		iter->join();

	clock_t end = clock();
	cout << "Time consuming: " << (end - start) / CLOCKS_PER_SEC << "s..." << endl;

	delete[]human;
	return 0;
}
