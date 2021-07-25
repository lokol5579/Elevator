/********************
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
	vector<Human> people;	//电梯中的人

public:
	Elevator() :totalWight(0), speed(0), floor(1), state(State::WAIT), peopleWight(0), destination(1), totalCapacity(0) { id = (++elevatorId); }	//初始化电梯参数
	inline void setState(State state) { this->state = state; }	//设置电梯状态
	inline void setTotalWight(int wight) { this->totalWight = wight; }	//设置电梯承重
	inline void setSpeed(double speed) { this->speed = speed; }	//设置电梯运行速度
	inline void setDestination(int destination) { this->destination = destination; }	//设置电梯目标楼层
	inline void moveUp() { floor++; }	//向上移动一层
	inline void moveDown() { floor--; }	//向下移动一层
	inline bool peopleIsNULL() { return people.empty(); }	//判断电梯是否空载
	inline int getId() { return id; }	//获得电梯ID
	inline int getPeopleWight() { return peopleWight; }	//获得电梯实时载重
	inline int getTotalWight() { return totalWight; }	//获得电梯承重
	inline int getTotalCapacity() { return totalCapacity; }	//获得电梯总运载量
	inline int getFloor() { return floor; }	//获得电梯所在楼层
	inline int getDestination() { return destination; }	//获得电梯目标楼层
	inline int getPeopleNum() { return (int)people.size(); }	//获得电梯所载人数
	inline double getTime() { return HEIGHT / speed; }	//获得电梯运行一层所需时间
	inline State getState() { return state; }	//获得电梯运行状态
	bool boarding(Human& human, People& waitingPeople);	//上电梯
	void getOff(int floor, People& waitingPeople);	//下电梯
};