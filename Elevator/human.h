/********************
作者：陈晗阳
邮箱：19281123@bjtu.edu.cn
创建时间：2021/7/19
修改时间：2021/7/20
描述：模拟人
********************/

#pragma once
#include <iostream>
#include "parameter.h"


class Human
{
private:
	int wight;	//体重
	int origin;	//所在楼层
	int destination;	//目标楼层
	State state;	//去往状态

public:
	Human() :wight(0), origin(0), destination(0), state(State::WAIT) { ; }
	void init(int floorNum);
	int getWight() { return wight; }
	int getOrigin() { return origin; }
	int getDestination() { return destination; }
	State getState() { return state; }
};