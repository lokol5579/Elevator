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
	int cx = GetSystemMetrics(SM_CXSCREEN);            /* 屏幕宽度 像素 */
	int cy = GetSystemMetrics(SM_CYSCREEN);            /* 屏幕高度 像素 */

	LONG l_WinStyle = GetWindowLong(hwnd, GWL_STYLE);   /* 获取窗口信息 */
	/* 设置窗口信息 最大化 取消标题栏及边框 */
	SetWindowLong(hwnd, GWL_STYLE, (l_WinStyle | WS_POPUP | WS_MAXIMIZE) & ~WS_CAPTION & ~WS_THICKFRAME & ~WS_BORDER);

	SetWindowPos(hwnd, HWND_TOP, 0, 0, cx, cy, 0);
}

void refresh(Elevator* elevator, int elevatorNum, int floorNum)
{
	system("cls");
	cout << "Start to simulate..." << endl;

	HANDLE handle_out = GetStdHandle(STD_OUTPUT_HANDLE);    //获得标准输出设备句柄
	CONSOLE_SCREEN_BUFFER_INFO csbi;                        //定义窗口缓冲区信息结构体
	GetConsoleScreenBufferInfo(handle_out, &csbi);          //获得窗口缓冲区信息

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
