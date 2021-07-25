/********************
作者：陈晗阳
邮箱：19281123@bjtu.edu.cn
创建时间：2021/7/22
修改时间：2021/7/23
描述：控制台函数实现
********************/

#include <stdio.h>
#include <Windows.h>
#include <iomanip>
#include <conio.h>
#include "elevator.h"
#include "parameter.h"
using namespace std;

bool print(false);

void userInterface(int& floorNum, int& elevatorNum, int& elevatorWight, int& peopleNum, double& elevatorSpeed)
{
	HANDLE handle_out = GetStdHandle(STD_OUTPUT_HANDLE);    //获得标准输出设备句柄
	SetConsoleTextAttribute(handle_out, BACKGROUND_INTENSITY);
	cout << "\n\n";
	for (int i(0); i < 9; i++)
		cout << "\t\t                                                  " << endl;
	{
		COORD pos = { 0, 3 };
		SetConsoleCursorPosition(handle_out, pos);
	}
	SetConsoleTextAttribute(handle_out, 31);
	cout << "\t                                                    " << endl;
	cout << "\t                       Welcome!                     " << endl;
	cout << "\t                                                    " << endl;
	cout << "\t          Number of Floors:                         " << endl;
	cout << "\t       Number of Elevators:                         " << endl;
	cout << "\t     Capacity of Elevators:       kg                " << endl;
	cout << "\t        Speed of Elevators:       m/s               " << endl;
	cout << "\t  Number of Waiting People:                         " << endl;
	cout << "\t                                                    " << endl;
	SetConsoleTextAttribute(handle_out, 31);
	{
		COORD pos = { 36, 6 };
		SetConsoleCursorPosition(handle_out, pos);
	}
	cin >> floorNum;
	{
		COORD pos = { 36, 7 };
		SetConsoleCursorPosition(handle_out, pos);
	}
	cin >> elevatorNum;
	{
		COORD pos = { 36, 8 };
		SetConsoleCursorPosition(handle_out, pos);
	}
	cin >> elevatorWight;
	{
		COORD pos = { 36, 9 };
		SetConsoleCursorPosition(handle_out, pos);
	}
	cin >> elevatorSpeed;
	{
		COORD pos = { 36, 10 };
		SetConsoleCursorPosition(handle_out, pos);
	}
	cin >> peopleNum;
	system("cls");
	SetConsoleTextAttribute(handle_out, 15);
}

void fullScreen()
{
	HWND hwnd = GetForegroundWindow();
	int cx = GetSystemMetrics(SM_CXSCREEN);            /* 屏幕宽度 像素 */
	int cy = GetSystemMetrics(SM_CYSCREEN);            /* 屏幕高度 像素 */

	LONG l_WinStyle = GetWindowLong(hwnd, GWL_STYLE);   /* 获取窗口信息 */
	/* 设置窗口信息 最大化 取消标题栏及边框 */
	SetWindowLong(hwnd, GWL_STYLE, (l_WinStyle | WS_POPUP | WS_MAXIMIZE) & ~WS_CAPTION & ~WS_THICKFRAME & ~WS_BORDER);

	SetWindowPos(hwnd, HWND_TOP, 0, 0, cx, cy, 0);
	system("cls");
}

void refresh(Elevator* elevator, int elevatorNum, int floorNum)
{
	if (!print)
	{
		system("cls");
		cout << "Start to simulate..." << endl;
	}

	HANDLE handle_out = GetStdHandle(STD_OUTPUT_HANDLE);    //获得标准输出设备句柄

	for (int i(0); i < elevatorNum; i++)
	{
		if (!print)
		{
			cout << "Elevator " << i + 1 << " :" << endl;
			cout << "\t" << "Wight:    Kg  People:       State:       Floor: ";
		}
		{
			COORD pos = { 15, (i + 1) * 2 };
			SetConsoleCursorPosition(handle_out, pos);
			cout << setw(3) << elevator[i].getPeopleWight();
		}
		{
			COORD pos = { 30, (i + 1) * 2 };
			SetConsoleCursorPosition(handle_out, pos);
			cout << setw(4) << elevator[i].getPeopleNum();
		}
		{
			COORD pos = { 42, (i + 1) * 2 };
			SetConsoleCursorPosition(handle_out, pos);
			switch (elevator[i].getState())
			{
			case State::WAIT: cout << "WAIT"; break;
			case State::UP: cout << setw(4) << "UP"; break;
			case State::DOWN: cout << "DOWN"; break;
			}
		}
		{
			COORD pos = { 55, (i + 1) * 2 };
			SetConsoleCursorPosition(handle_out, pos);
			cout << setw(3) << elevator[i].getFloor() << endl;
		}
	}
	if (!print)
	{
		cout << "\n      ";
		for (int i(0); i < elevatorNum; i++)
		{
			cout << "Elevator " << i + 1 << "    ";
		}
		cout << "\n\n";
		for (int i(floorNum); i > 0; i--)
		{
			SetConsoleTextAttribute(handle_out, 15);
			cout << "F" << setw(3) << i << "  ";
			for (int j(0); j < elevatorNum; j++)
			{
				SetConsoleTextAttribute(handle_out, BACKGROUND_BLUE | BACKGROUND_RED);
				cout << " ";
				SetConsoleTextAttribute(handle_out, FOREGROUND_BLUE | FOREGROUND_GREEN);
				cout << "        ";
				SetConsoleTextAttribute(handle_out, BACKGROUND_BLUE | BACKGROUND_RED);
				cout << " ";
				SetConsoleTextAttribute(handle_out, FOREGROUND_RED | FOREGROUND_GREEN);
				cout << "    ";
			}
			cout << endl;
		}
	}
	for (int i(floorNum); i > 0; i--)
	{
		for (int j(0); j < elevatorNum; j++)
		{
			COORD pos = { 10 + j * 14, (elevatorNum + 2) * 2 + floorNum - i };
			SetConsoleCursorPosition(handle_out, pos);
			if (elevator[j].getFloor() == i)
			{
				SetConsoleTextAttribute(handle_out, BACKGROUND_BLUE);
				cout << "  ";
			}
			else
			{
				SetConsoleTextAttribute(handle_out, FOREGROUND_BLUE | FOREGROUND_GREEN);
				cout << "||";
			}
			SetConsoleTextAttribute(handle_out, FOREGROUND_RED | FOREGROUND_GREEN);
		}
	}
	print = true;
	{
		COORD pos = { 0, (elevatorNum + 2) * 2 + floorNum + 1 };
		SetConsoleCursorPosition(handle_out, pos);
	}
}

void setTextWhite()
{
	HANDLE handle_out = GetStdHandle(STD_OUTPUT_HANDLE);    //获得标准输出设备句柄
	SetConsoleTextAttribute(handle_out, 15);
}