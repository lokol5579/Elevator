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
	strftime(YMDTime, TIME_LENGTH, "%Y/%m/%d %X", localtime(&t));
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
	strftime(YMDTime, TIME_LENGTH, "%Y/%m/%d %X", localtime(&t));
	outFile << YMDTime << " " << "user" << human.getId() << " boarding | F" << human.getOrigin() << "->F" << human.getDestination() << endl;
}