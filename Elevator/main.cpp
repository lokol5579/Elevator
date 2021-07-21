/********************
作者：陈晗阳
邮箱：19281123@bjtu.edu.cn
创建时间：2021/7/19
修改时间：2021/7/20
描述：主程序
********************/

#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <Windows.h>
#include "parameter.h"
#include "human.h"
#include "people.h"
#include "elevator.h"
#include "building.h"

using namespace std;

thread* elevatorThread;
mutex mtx;

void elevatorRun(People& people, Elevator elevator)
{
	while (people.getPeopleNum() != 0 || elevator.getState() == State::WAIT)
	{
		int floor = elevator.getFloor();
		if (elevator.getState() == State::WAIT)
		{
			lock_guard<mutex> lock(mtx);
			int des = people.nearRequest(floor);
			if (des == floor) people.boarding(elevator);
			else des > floor ? elevator.setState(State::UP) : elevator.setState(State::DOWN);
			Sleep((DWORD)elevator.getTime());
		}
		else if (elevator.getState() == State::UP)
		{
			elevator.moveUp();
			elevator.getOff(floor);
			lock_guard<mutex> lock(mtx);
			int des = people.upRequest(floor);
			if (des == floor && elevator.peopleIsNULL()) { elevator.setState(State::WAIT); }
			else
			{
				people.boarding(elevator);
				Sleep((DWORD)elevator.getTime());
			}
		}
		else if (elevator.getState() == State::DOWN)
		{
			elevator.moveDown();
			elevator.getOff(floor);
			lock_guard<mutex> lock(mtx);
			int des = people.downRequest(floor);
			if (des == floor && elevator.peopleIsNULL()) { elevator.setState(State::WAIT); }
			else
			{
				people.boarding(elevator);
				Sleep((DWORD)elevator.getTime());
			}
		}
	}
}

int main()
{
	/*获得程序参数*/
	int floorNum(0), elevatorNum(0), elevatorWight(0), peopleNum(0);
	double elevatorSpeed(0.0);
	cout << "***************欢迎使用电梯模拟器***************" << endl;
	cout << "请输入建筑层数："; cin >> floorNum;
	//cout << "请输入建筑电梯数量："; cin >> elevatorNum;
	cout << "请输入电梯载重："; cin >> elevatorWight;
	cout << "请输入电梯速度："; cin >> elevatorSpeed;
	cout << "请输入初始等待人数："; cin >> peopleNum;

	/*初始化建筑、电梯及乘客*/
	Building building(floorNum, elevatorWight, HEIGHT / elevatorSpeed);
	Human* human = new Human[peopleNum];
	People people(peopleNum, floorNum);
	Elevator* elevator(building.getElevator());
	for (int i(0); i < peopleNum; i++)
	{
		human[i].init(floorNum);
		people.insertVector(human[i]);
	}

	/*多线程电梯构建*/
	elevatorThread = new thread[elevatorNum];
	for (int i(0); i < elevatorNum; i++)
		elevatorThread[i] = thread(elevatorRun, ref(people), elevator[i]);
	
	for (thread* iter = elevatorThread; iter <= &elevatorThread[elevatorNum]; iter++) iter->join();

	delete[]human;
	return 0;
}
