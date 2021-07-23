/********************
作者：陈晗阳
邮箱：19281123@bjtu.edu.cn
创建时间：2021/7/20
修改时间：2021/7/21
描述：建筑功能实现
********************/

#include <vector>
#include "building.h"
#include "elevator.h"
using namespace std;

Building::Building(int floorNum, int elevatorTotalWight, double elevatorSpeed) :floorNum(floorNum)
{
	for (int i(0); i < 10; i++)
	{
		elevator[i].setTotalWight(elevatorTotalWight);
		elevator[i].setSpeed(elevatorSpeed);
	}
}