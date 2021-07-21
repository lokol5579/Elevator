#pragma once
#include <iostream>
#include <vector>
using namespace std;

class Human;
class Elevator;

class People
{
private:
	int peopleNum;
	vector<vector<Human>> peopleIn;
	vector<bool> peopleWaitIn;
public:
	People(int peopleNum, int floorNum) :peopleNum(peopleNum)
	{
		peopleIn.resize(floorNum);
		peopleWaitIn.resize(floorNum);
		for (int i(0); i < floorNum; peopleWaitIn[i - 1] = false);
	}
	inline int getPeopleNum() { return peopleNum; };
	void insertVector(Human& human);
	int nearRequest(int floor);
	int upRequest(int floor);
	int downRequest(int floor);
	void boarding(Elevator& elevator);
};