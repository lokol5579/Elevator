/********************
���ߣ�������
���䣺19281123@bjtu.edu.cn
����ʱ�䣺2021/7/19
�޸�ʱ�䣺2021/7/21
������������
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
	if (!writeSimulateInfo(elevator[elevatorId].getId())) return;
	while (people.getPeopleNum() != 0 || !elevator[elevatorId].peopleIsNULL())
	{
		{
			lock_guard<mutex> lock(mtx);
			refresh(elevator, elevatorNum, floorNum);
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
		refresh(elevator, elevatorNum, floorNum);
	}
}

int main()
{
	/*��ó������*/
	int floorNum(20), elevatorNum(3), elevatorWight(1000), peopleNum(100);
	double elevatorSpeed(1.0);
	cout << "***************��ӭʹ�õ���ģ����***************" << endl;
	//cout << "�����뽨��������"; cin >> floorNum;
	////cout << "�����뽨������������"; cin >> elevatorNum;
	//cout << "������������أ�"; cin >> elevatorWight;
	//cout << "����������ٶȣ�"; cin >> elevatorSpeed;
	//cout << "�������ʼ�ȴ�������"; cin >> peopleNum;

	/*��ʼ�����������ݼ��˿�*/
	Building building(floorNum, elevatorWight, elevatorSpeed);
	Human* human = new Human[peopleNum];
	People people(peopleNum, floorNum);
	Elevator* elevator = building.getElevator();
	for (int i(0); i < peopleNum; i++)
	{
		human[i].init(floorNum);
		people.insertVector(human[i]);
	}

	cout << "Start to simulate..." << endl;

	clock_t start = clock();

	/*���̵߳��ݹ���*/
	elevatorThread = new thread[elevatorNum];
	for (int i(0); i < elevatorNum; i++)
		elevatorThread[i] = thread(elevatorRun, ref(people), elevator, i, elevatorNum, floorNum);
	
	for (thread* iter = elevatorThread; iter <= &elevatorThread[elevatorNum - 1]; iter++)
		iter->join();

	clock_t end = clock();
	cout << "Time consuming: " << (end - start) / CLOCKS_PER_SEC << "s..." << endl;
	for (int i(0); i < elevatorNum; i++)
	{
		cout << "Total capacity of Elevator " << i + 1 << ": " << elevator[i].getTotalCapacity() << endl;
	}

	delete[]human;
	return 0;
}
