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
	/*��ó������*/
	int floorNum(5), elevatorNum(3), elevatorWight(1000), peopleNum(100);
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
	Elevator* elevator(building.getElevator());
	for (int i(0); i < peopleNum; i++)
	{
		human[i].init(floorNum);
		people.insertVector(human[i]);
	}

	cout << "��ʼģ�⣡" << endl;

	clock_t start = clock();

	/*���̵߳��ݹ���*/
	elevatorThread = new thread[elevatorNum];
	for (int i(0); i < elevatorNum; i++)
		elevatorThread[i] = thread(elevatorRun, ref(people), elevator[i]);
	
	for (thread* iter = elevatorThread; iter <= &elevatorThread[elevatorNum - 1]; iter++)
		iter->join();

	clock_t end = clock();
	cout << "ģ���ʱ" << (end - start) / CLOCKS_PER_SEC << "s..." << endl;

	delete[]human;
	return 0;
}
