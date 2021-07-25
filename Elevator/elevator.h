﻿/********************
作者：陈晗阳
邮箱：19281123@bjtu.edu.cn
创建时间：2021/7/19
修改时间：2021/7/21
描述：电梯属性定义
********************/

#pragma once
#include <vector>
#include <iostream>
#include "human.h"
#include "parameter.h"
using namespace std;

class Human;
class People;
extern int elevatorId;

class Elevator
{
private:
	/*电梯属性*/
	int id;
	int totalWight;	//电梯限重
	int totalCapacity; //电梯运送总人数
	double speed;	//电梯运行速度
	/*电梯实时状态*/
	int floor;	//电梯所处楼层
	int destination;	//目标楼层
	State state;	//电梯运动状态
	int peopleWight;	//电梯中的实时载重
	vector<Human> people;

public:
	Elevator() :totalWight(0), speed(0), floor(1), state(State::WAIT), peopleWight(0), destination(1), totalCapacity(0) { id = (++elevatorId); }
	Elevator(int totalWight, double speed) :totalWight(totalWight), peopleWight(0), speed(speed), floor(1), state(State::WAIT), destination(1), totalCapacity(0) { id = (++elevatorId); }
	inline void setState(State state) { this->state = state; }
	inline void setTotalWight(int wight) { this->totalWight = wight; }
	inline void setSpeed(double speed) { this->speed = speed; }
	inline void setDestination(int destination) { this->destination = destination; }
	inline void moveUp() { /*cout << "电梯" << this->getId() << "正在从" << floor << "楼向" << floor + 1 << "楼移动" << endl;*/  floor++; }
	inline void moveDown() { /*cout << "电梯" << this->getId() << "正在从" << floor << "楼向" << floor - 1 << "楼移动" << endl; */ floor--; }
	inline bool peopleIsNULL() { return people.empty(); }
	inline int getId() { return id; }
	inline int getPeopleWight() { return peopleWight; }
	inline int getTotalWight() { return totalWight; }
	inline int getTotalCapacity() { return totalCapacity; }
	inline int getFloor() { return floor; }
	inline int getDestination() { return destination; }
	inline int getPeopleNum() { return (int)people.size(); }
	inline double getTime() { return HEIGHT / speed; }
	inline State getState() { return state; }
	bool boarding(Human& human, People& waitingPeople);
	void getOff(int floor, People& waitingPeople);
};