#include <iostream>
#include <Windows.h>
#include "elevator.h"
#include "parameter.h"
using namespace std;

void refresh(Elevator* elevator, int elevatorNum)
{
	system("cls");
	cout << "Start to simulate..." << endl;
	for (int i(0); i < elevatorNum; i++)
	{
		cout << "Elevator " << i + 1 << " :" << endl;
		cout << "\t" << "Wight: " << elevator[i].getPeopleWight() << "Kg  People: " << elevator[i].getPeopleNum() << endl;
		cout << "\t" << "State: ";
		switch (elevator[i].getState())
		{
		case State::WAIT: cout << "WAIT"; break;
		case State::UP: cout << "UP"; break;
		case State::DOWN: cout << "DOWN"; break;
		}
		cout << "  Floor: " << elevator[i].getFloor() << endl;
	}
}
