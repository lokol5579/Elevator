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

void elevatorRun(People& people, Elevator *elevator, int elevatorId, int elevatorNum, int floorNum)
{
	if (!writeSimulateInfo(elevator[elevatorId - 1].getId())) return;
	while (people.getPeopleNum() != 0 || !elevator[elevatorId - 1].peopleIsNULL())
	{
		{
			lock_guard<mutex> lock(mtx);
			refresh(elevator, elevatorNum, floorNum);
		}
		int floor = elevator[elevatorId - 1].getFloor();
		if (elevator[elevatorId - 1].getState() == State::WAIT)
		{
			{
				lock_guard<mutex> lock(mtx);
				people.nearRequest(elevator[elevatorId - 1]);
				if (elevator[elevatorId - 1].getDestination() == floor)
					people.boarding(elevator[elevatorId - 1]);
				else elevator[elevatorId - 1].getDestination() > floor ? elevator[elevatorId - 1].setState(State::UP) : elevator[elevatorId - 1].setState(State::DOWN);
			}
			//Sleep((DWORD)(elevator[elevatorId].getTime() * 1000));
		}
		else if (elevator[elevatorId - 1].getState() == State::UP)
		{
			elevator[elevatorId - 1].moveUp(); floor++;
			elevator[elevatorId - 1].getOff(floor, people);
			{
				lock_guard<mutex> lock(mtx);
				people.upRequest(elevator[elevatorId - 1]);
				if (elevator[elevatorId - 1].getDestination() == floor && elevator[elevatorId - 1].peopleIsNULL())
				{
					elevator[elevatorId - 1].setState(State::WAIT);
					continue;
				}
				else people.boarding(elevator[elevatorId - 1]);
			}
			//Sleep((DWORD)(elevator[elevatorId].getTime() * 1000));
		}
		else if (elevator[elevatorId - 1].getState() == State::DOWN)
		{
			elevator[elevatorId - 1].moveDown(); floor--;
			elevator[elevatorId - 1].getOff(floor, people);
			lock_guard<mutex> lock(mtx);
			people.downRequest(elevator[elevatorId - 1]);
			if (elevator[elevatorId - 1].getDestination() == floor && elevator[elevatorId - 1].peopleIsNULL())
			{
				elevator[elevatorId - 1].setState(State::WAIT);
				continue;
			}
			else people.boarding(elevator[elevatorId - 1]);
			//Sleep((DWORD)(elevator[elevatorId].getTime() * 800));
		}
	}
	{
		lock_guard<mutex> lock(mtx);
		refresh(elevator, elevatorNum, floorNum);
	}
}

int main(int argc, char* argv[])
{
	fullScreen();
	/*获得程序参数*/
	int floorNum(10), elevatorNum(3), elevatorWight(1000), peopleNum(1000);
	double elevatorSpeed(1.0);
	if (!getTemporaryData(floorNum, elevatorNum, elevatorWight, peopleNum, elevatorSpeed))
	{
		cout << "Temporary file lost..." << endl;
		system("pause");
		exit(-1);
	}
	//userInterface(floorNum, elevatorNum, elevatorWight, peopleNum, elevatorSpeed);

	/*初始化建筑、电梯及乘客*/
	Building building(floorNum, elevatorWight, elevatorSpeed);
	Human* human = new Human[peopleNum];
	People people(peopleNum, floorNum);
	Elevator* elevator = building.getElevator();
	for (int i(0); i < peopleNum; i++)
	{
		human[i].init(floorNum);
		people.insertVector(human[i]);
	}
	setTextWhite();
	cout << "Start to simulate..." << endl;

	clock_t start = clock();

	/*多线程电梯构建*/
	elevatorThread = new thread[elevatorNum];
	for (int i(0); i < elevatorNum; i++)
		elevatorThread[i] = thread(elevatorRun, ref(people), elevator, i + 1, elevatorNum, floorNum);
	
	for (thread* iter = elevatorThread; iter <= &elevatorThread[elevatorNum - 1]; iter++)
		iter->join();

	clock_t end = clock();
	setTextWhite();
	cout << "Time consuming: " << (end - start) / CLOCKS_PER_SEC << "s..." << endl;
	for (int i(0); i < elevatorNum; i++)
	{
		cout << "Total capacity of Elevator " << i + 1 << ": " << elevator[i].getTotalCapacity() << endl;
	}

	delete[]human;
	system("pause");
	system("exit");
	return 0;
}
