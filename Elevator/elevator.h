/********************
作者：陈晗阳
邮箱：19281123@bjtu.edu.cn
创建时间：2021/7/19
修改时间：2021/7/20
描述：模拟电梯
********************/

#pragma once
#include <vector>
#include <iostream>
#include "human.h"
#include "parameter.h"
using namespace std;

class Human;

class Elevator
{
private:
	/*电梯属性*/
	int totalWight;	//电梯限重
	double speed;	//电梯运行速度
	/*电梯实时状态*/
	int floor;	//电梯所处楼层
	State state;	//电梯运动状态
	int peopleWight;	//电梯中的实时载重
	//int peopleNum;	//电梯中的实时人数
	vector<Human> people;

public:
	Elevator() :totalWight(0), speed(0), floor(1), state(State::WAIT), peopleWight(0) { ; }
	Elevator(int totalWight, double speed) :totalWight(totalWight), peopleWight(0), speed(speed), floor(1), state(State::WAIT) { ; }
	inline void setState(State state) { this->state = state; }
	inline void setTotalWight(int wight) { this->totalWight = wight; }
	inline void setSpeed(double speed) { this->speed = speed; }
	inline void moveUp() { floor++; }
	inline void moveDown() { floor--; }
	inline bool peopleIsNULL() { return people.empty(); }
	inline int getPeopleWight() { return peopleWight; }
	inline int getTotalWight() { return totalWight; }
	inline int getFloor() { return floor; }
	inline double getTime() { return HEIGHT / speed; }
	inline State getState() { return state; }
	bool boarding(Human& human);
	void getOff(int floor);
};

