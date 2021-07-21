/********************
���ߣ�������
���䣺19281123@bjtu.edu.cn
����ʱ�䣺2021/7/20
�޸�ʱ�䣺2021/7/21
��������Ⱥ����ʵ��
********************/

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
	vector<bool> requestState;
public:
	People(int peopleNum, int floorNum) :peopleNum(peopleNum)
	{
		peopleIn.resize(floorNum);
		peopleWaitIn.resize(floorNum);
		requestState.resize(floorNum);
		//for (int i(0); i < floorNum; peopleWaitIn[i] = false);
	}
	inline void setRequestState(int floor, bool requestState) { this->requestState[floor] = requestState; }
	inline int getPeopleNum() { return peopleNum; }
	inline bool getRequestState(int floor) { return requestState[floor]; }
	void insertVector(Human& human);
	int nearRequest(int floor);
	int upRequest(int floor);
	int downRequest(int floor);
	void boarding(Elevator& elevator);
};