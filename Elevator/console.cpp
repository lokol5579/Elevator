#include <stdio.h>
#include <Windows.h>
#include <iomanip>
#include <conio.h>
#include "elevator.h"
#include "parameter.h"
using namespace std;

void fullScreen()
{
	HWND hwnd = GetForegroundWindow();
	int cx = GetSystemMetrics(SM_CXSCREEN);            /* ��Ļ��� ���� */
	int cy = GetSystemMetrics(SM_CYSCREEN);            /* ��Ļ�߶� ���� */

	LONG l_WinStyle = GetWindowLong(hwnd, GWL_STYLE);   /* ��ȡ������Ϣ */
	/* ���ô�����Ϣ ��� ȡ�����������߿� */
	SetWindowLong(hwnd, GWL_STYLE, (l_WinStyle | WS_POPUP | WS_MAXIMIZE) & ~WS_CAPTION & ~WS_THICKFRAME & ~WS_BORDER);

	SetWindowPos(hwnd, HWND_TOP, 0, 0, cx, cy, 0);
}

void refresh(Elevator* elevator, int elevatorNum, int floorNum)
{
	system("cls");
	cout << "Start to simulate..." << endl;

	HANDLE handle_out = GetStdHandle(STD_OUTPUT_HANDLE);    //��ñ�׼����豸���
	CONSOLE_SCREEN_BUFFER_INFO csbi;                        //���崰�ڻ�������Ϣ�ṹ��
	GetConsoleScreenBufferInfo(handle_out, &csbi);          //��ô��ڻ�������Ϣ

	for (int i(0); i < elevatorNum; i++)
	{
		//displayScreen(elevator[i]);
		cout << "Elevator " << i + 1 << " :" << endl;
		cout << "\t" << "Wight: " << elevator[i].getPeopleWight() << "Kg  People: " << elevator[i].getPeopleNum() << "  State: ";
		switch (elevator[i].getState())
		{
		case State::WAIT: cout << "WAIT"; break;
		case State::UP: cout << "UP"; break;
		case State::DOWN: cout << "DOWN"; break;
		}
		cout << "  Floor: " << elevator[i].getFloor() << endl;
	}
	cout << "\n      ";
	for (int i(0); i < elevatorNum; i++)
	{
		cout << "Elevator " << i + 1 << "    ";
	}
	cout << "\n\n";
	for (int i(0); i < floorNum; i++)
	{
		cout << "F" << setw(3) << floorNum - i << "  ";
		for (int j(0); j < elevatorNum; j++)
		{
			if (elevator[j].getFloor() == floorNum - i)
			{
				SetConsoleTextAttribute(handle_out, BACKGROUND_BLUE | BACKGROUND_RED);
				cout << " ";
				SetConsoleTextAttribute(handle_out, FOREGROUND_RED | FOREGROUND_GREEN);
				cout <<"   ";
				SetConsoleTextAttribute(handle_out, BACKGROUND_BLUE);
				cout << "  ";
				SetConsoleTextAttribute(handle_out, FOREGROUND_RED | FOREGROUND_GREEN);
				cout << "   ";
				SetConsoleTextAttribute(handle_out, BACKGROUND_BLUE | BACKGROUND_RED);
				cout << " ";
				SetConsoleTextAttribute(handle_out, FOREGROUND_RED | FOREGROUND_GREEN);
				cout << "    ";
			}
			else
			{
				SetConsoleTextAttribute(handle_out, BACKGROUND_BLUE | BACKGROUND_RED);
				cout << " ";
				SetConsoleTextAttribute(handle_out, FOREGROUND_BLUE | FOREGROUND_GREEN);
				cout << "   ||   ";
				SetConsoleTextAttribute(handle_out, BACKGROUND_BLUE | BACKGROUND_RED);
				cout << " ";
				SetConsoleTextAttribute(handle_out, FOREGROUND_RED | FOREGROUND_GREEN);
				cout << "    ";
			}
		}
		cout << endl;
	}
}
