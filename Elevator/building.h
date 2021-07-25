/********************
���ߣ�������
���䣺19281123@bjtu.edu.cn
����ʱ�䣺2021/7/19
�޸�ʱ�䣺2021/7/20
������ģ�⽨��
********************/

#pragma once
#include <vector>
#include "elevator.h"
using namespace std;

class Elevator;

class Building
{
private:
	int floorNum;	//¥��
	Elevator elevator[10];	//����

public:
	Building(int floorNum, int elevatorTotalWight, double elevatorSpeed);	//��ʼ�������ò���
	inline int getFloorNum() { return floorNum; }	//���¥��
	inline Elevator* getElevator() { return elevator; }	//��õ��ݵ�ַ
};