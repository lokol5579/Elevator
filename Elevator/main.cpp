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

using namespace std;

thread* elevatorThread;
mutex mtx;

void elevatorRun(People& people, Elevator elevator)
{
	writeSimulateInfo(elevator.getId());
	while (people.getPeopleNum() != 0 || !elevator.peopleIsNULL())
	{
		int floor = elevator.getFloor();
		if (elevator.getState() == State::WAIT)
		{
			{
				lock_guard<mutex> lock(mtx);
				people.nearRequest(elevator);
				if (elevator.getDestination() == floor)
					people.boarding(elevator);
				else elevator.getDestination() > floor ? elevator.setState(State::UP) : elevator.setState(State::DOWN);
			}
			Sleep((DWORD)(elevator.getTime() * 1000));
		}
		else if (elevator.getState() == State::UP)
		{
			elevator.moveUp(); floor++;
			elevator.getOff(floor, people);
			{
				lock_guard<mutex> lock(mtx);
				people.upRequest(elevator);
				if (elevator.getDestination() == floor && elevator.peopleIsNULL())
				{
					elevator.setState(State::WAIT);
					continue;
				}
				else people.boarding(elevator);
			}
			Sleep((DWORD)(elevator.getTime() * 1000));
		}
		else if (elevator.getState() == State::DOWN)
		{
			elevator.moveDown(); floor--;
			elevator.getOff(floor, people);
			lock_guard<mutex> lock(mtx);
			people.downRequest(elevator);
			if (elevator.getDestination() == floor && elevator.peopleIsNULL())
			{
				elevator.setState(State::WAIT);
				continue;
			}
			else people.boarding(elevator);
			Sleep((DWORD)(elevator.getTime() * 800));
		}
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
	Elevator* elevator(building.getElevator());
	for (int i(0); i < peopleNum; i++)
	{
		human[i].init(floorNum);
		people.insertVector(human[i]);
	}

	cout << "开始模拟！" << endl;

	clock_t start = clock();

	/*多线程电梯构建*/
	elevatorThread = new thread[elevatorNum];
	for (int i(0); i < elevatorNum; i++)
		elevatorThread[i] = thread(elevatorRun, ref(people), elevator[i]);
	
	for (thread* iter = elevatorThread; iter <= &elevatorThread[elevatorNum - 1]; iter++)
		iter->join();

	clock_t end = clock();
	cout << "模拟耗时" << (end - start) / CLOCKS_PER_SEC << "s..." << endl;

	delete[]human;
	return 0;
}
