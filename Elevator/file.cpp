/********************
���ߣ�������
���䣺19281123@bjtu.edu.cn
����ʱ�䣺2021/7/22
�޸�ʱ�䣺2021/7/24
��������־��غ���ʵ��
********************/

#include <iostream>
#include <fstream>
#include <ctime>
#include <Windows.h>
#include <direct.h>
#include "file.h"
#include "human.h"
#define NAME_LENGTH 64
#define TIME_LENGTH 64
using namespace std;

bool writeSimulateInfo(int elevatorId)
{
	_mkdir(".\\log");
	char fileName[NAME_LENGTH];
	sprintf_s(fileName, ".\\log\\elevator%d.log", elevatorId);
	ofstream outFile;
	outFile.open(fileName, ios::app);
	time_t t = time(0);
	char YMDTime[TIME_LENGTH];
	strftime(YMDTime, TIME_LENGTH, "%Y/%m/%d %X", localtime(&t));
	outFile << YMDTime << " Start to simulate..." << endl;
	return true;
}

void writeBoardingInfo(Human human, int elevatorId)
{
	char fileName[NAME_LENGTH];
	sprintf_s(fileName, ".\\log\\elevator%d.log", elevatorId);
	ofstream outFile;
	outFile.open(fileName, ios::app);
	time_t t = time(0);
	char YMDTime[TIME_LENGTH];
	strftime(YMDTime, TIME_LENGTH, "%Y/%m/%d %X", localtime(&t));	//��õ���ʱ��
	outFile << YMDTime << " " << "user" << human.getId() << " boarding | F" << human.getOrigin() << "->F" << human.getDestination() << endl;
}

void writeOffInfo(Human human, int elevatorId)
{
	char fileName[NAME_LENGTH];
	sprintf_s(fileName, ".\\log\\elevator%d.log", elevatorId);
	ofstream outFile;
	outFile.open(fileName, ios::app);
	time_t t = time(0);
	char YMDTime[TIME_LENGTH];
	strftime(YMDTime, TIME_LENGTH, "%Y/%m/%d %X", localtime(&t));	//�������ʱ��
	outFile << YMDTime << " " << "user" << human.getId() << " boarding | F" << human.getOrigin() << "->F" << human.getDestination() << endl;
}

bool getTemporaryData(int& floorNum, int& elevatorNum, int& elevatorWight, int& peopleNum, double& elevatorSpeed)
{
	char fileName[NAME_LENGTH];
	sprintf_s(fileName, ".\\Elevator_Data");
	ifstream inFile;
	inFile.open(fileName);
	if (!inFile.is_open()) return false;
	inFile >> floorNum;
	inFile >> elevatorNum;
	inFile >> elevatorWight;
	inFile >> peopleNum;
	inFile >> elevatorSpeed;
	return true;
}