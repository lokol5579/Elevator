/********************
作者：陈晗阳
邮箱：19281123@bjtu.edu.cn
创建时间：2021/7/19
修改时间：2021/7/21
描述：人的属性定义
********************/

#pragma once
#include <iostream>
#include "parameter.h"

extern int humanId;

class Human
{
private:
	int id;
	int wight;	//体重
	int origin;	//所在楼层
	int destination;	//目标楼层
	State state;	//去往状态

public:
	Human() :wight(0), origin(0), destination(0), state(State::WAIT) { id = (++humanId); }	//初始化人，并获得ID
	void init(int floorNum);	//初始化人
	inline int getId() { return id; }	//获得ID
	inline int getWight() { return wight; }	//获得体重
	inline int getOrigin() { return origin; }	//获得所在楼层
	inline int getDestination() { return destination; }	//获得目标楼层
	inline State getState() { return state; }	//获得所去方向
};