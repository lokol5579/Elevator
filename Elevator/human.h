/********************
���ߣ�������
���䣺19281123@bjtu.edu.cn
����ʱ�䣺2021/7/19
�޸�ʱ�䣺2021/7/20
������ģ����
********************/

#pragma once
#include <iostream>
#include "parameter.h"


class Human
{
private:
	int wight;	//����
	int origin;	//����¥��
	int destination;	//Ŀ��¥��
	State state;	//ȥ��״̬

public:
	Human() :wight(0), origin(0), destination(0), state(State::WAIT) { ; }
	void init(int floorNum);
	int getWight() { return wight; }
	int getOrigin() { return origin; }
	int getDestination() { return destination; }
	State getState() { return state; }
};