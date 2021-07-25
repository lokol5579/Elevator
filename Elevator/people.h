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
	int peopleNum;	//�ȴ���Ⱥ����
	vector<vector<Human>> peopleIn;	//ÿ��¥�ĵȴ���Ⱥ
	vector<bool> peopleWaitIn;	//ÿ��¥�Ƿ��еȴ���Ⱥ
	vector<bool> requestState;	//��Ӧ״̬
public:
	People(int peopleNum, int floorNum) :peopleNum(peopleNum)	//��ʼ����Ⱥ
	{
		peopleIn.resize(floorNum);
		peopleWaitIn.resize(floorNum);
		requestState.resize(floorNum);
	}
	inline void setRequestState(int floor, bool requestState) { this->requestState[floor - 1] = requestState; }	//������Ӧ״̬
	inline int getPeopleNum() { return peopleNum; }	//��õȴ�����
	inline bool getRequestState(int floor) { return requestState[floor - 1]; }	//�����Ӧ״̬
	void insertVector(Human& human);	//�����ɵ��˼�����Ӧ��Ⱥ
	int nearRequest(Elevator& elevator);	//�����������������
	int upRequest(Elevator& elevator);	//��õ�������¥��������Զ������
	int downRequest(Elevator& elevator);	//��õ�������¥��������Զ������
	void boarding(Elevator& elevator);	//����
};