/********************
���ߣ�������
���䣺19281123@bjtu.edu.cn
����ʱ�䣺2021/7/19
�޸�ʱ�䣺2021/7/21
�������˵����Զ���
********************/

#pragma once
#include <iostream>
#include "parameter.h"

extern int humanId;

class Human
{
private:
	int id;
	int wight;	//����
	int origin;	//����¥��
	int destination;	//Ŀ��¥��
	State state;	//ȥ��״̬

public:
	Human() :wight(0), origin(0), destination(0), state(State::WAIT) { id = (++humanId); }
	void init(int floorNum);
	inline int getId() { return id; }
	inline int getWight() { return wight; }
	inline int getOrigin() { return origin; }
	inline int getDestination() { return destination; }
	inline State getState() { return state; }
};