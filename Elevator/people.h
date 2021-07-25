/********************
作者：陈晗阳
邮箱：19281123@bjtu.edu.cn
创建时间：2021/7/20
修改时间：2021/7/21
描述：人群功能实现
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
	int peopleNum;	//等待人群数量
	vector<vector<Human>> peopleIn;	//每层楼的等待人群
	vector<bool> peopleWaitIn;	//每层楼是否有等待人群
	vector<bool> requestState;	//响应状态
public:
	People(int peopleNum, int floorNum) :peopleNum(peopleNum)	//初始化人群
	{
		peopleIn.resize(floorNum);
		peopleWaitIn.resize(floorNum);
		requestState.resize(floorNum);
	}
	inline void setRequestState(int floor, bool requestState) { this->requestState[floor - 1] = requestState; }	//设置响应状态
	inline int getPeopleNum() { return peopleNum; }	//获得等待人数
	inline bool getRequestState(int floor) { return requestState[floor - 1]; }	//获得响应状态
	void insertVector(Human& human);	//将生成的人加入相应人群
	int nearRequest(Elevator& elevator);	//获得离电梯最近的请求
	int upRequest(Elevator& elevator);	//获得电梯所在楼层以上最远的请求
	int downRequest(Elevator& elevator);	//获得电梯所在楼层以下最远的请求
	void boarding(Elevator& elevator);	//登梯
};