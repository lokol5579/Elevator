/********************
���ߣ�������
���䣺19281123@bjtu.edu.cn
����ʱ�䣺2021/7/19
�޸�ʱ�䣺2021/7/20
������������
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
	cout << "����" << &elevator << "�������У�" << endl;
	while (people.getPeopleNum() != 0 || !elevator.peopleIsNULL() || elevator.getState() == State::WAIT)
	{
		int floor = elevator.getFloor();
		if (elevator.getState() == State::WAIT)
		{
			{
				lock_guard<mutex> lock(mtx);
				int des = people.nearRequest(floor);
				if (des == -1) break;
				if (des == floor) people.boarding(elevator);
				else des > floor ? elevator.setState(State::UP) : elevator.setState(State::DOWN);
			}
			Sleep((DWORD)elevator.getTime());
		}
		else if (elevator.getState() == State::UP)
		{
			elevator.moveUp(); floor++;
			elevator.getOff(floor);
			{
				lock_guard<mutex> lock(mtx);
				int des = people.upRequest(floor);
				if (des == floor && elevator.peopleIsNULL())
				{
					elevator.setState(State::WAIT);
					continue;
				}
				else people.boarding(elevator);
			}
			Sleep((DWORD)elevator.getTime());
		}
		else if (elevator.getState() == State::DOWN)
		{
			elevator.moveDown(); floor--;
			elevator.getOff(floor);
			lock_guard<mutex> lock(mtx);
			int des = people.downRequest(floor);
			if (des == floor && elevator.peopleIsNULL())
			{
				elevator.setState(State::WAIT);
				continue;
			}
			else people.boarding(elevator);
			Sleep((DWORD)elevator.getTime());
		}
	}
}

int main()
{
	/*��ó������*/
	int floorNum(10), elevatorNum(2), elevatorWight(1000), peopleNum(10);
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

	/*���̵߳��ݹ���*/
	elevatorThread = new thread[elevatorNum];
	for (int i(0); i < elevatorNum; i++)
		elevatorThread[i] = thread(elevatorRun, ref(people), elevator[i]);
	
	for (thread* iter = elevatorThread; iter <= &elevatorThread[elevatorNum - 1]; iter++)
		iter->join();

	delete[]human;
	return 0;
}
