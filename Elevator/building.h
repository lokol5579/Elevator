/********************
作者：陈晗阳
邮箱：19281123@bjtu.edu.cn
创建时间：2021/7/19
修改时间：2021/7/20
描述：模拟建筑
********************/

#pragma once
#include <vector>
#include "elevator.h"
using namespace std;

class Elevator;

class Building
{
private:
	int floorNum;	//楼层
	Elevator elevator[10];	//电梯

public:
	Building(int floorNum, int elevatorTotalWight, double elevatorSpeed);	//初始化并设置参数
	inline int getFloorNum() { return floorNum; }	//获得楼层
	inline Elevator* getElevator() { return elevator; }	//获得电梯地址
};