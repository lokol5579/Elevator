/********************
���ߣ�������
���䣺19281123@bjtu.edu.cn
����ʱ�䣺2021/7/20
�޸�ʱ�䣺2021/7/21
��������������ʵ��
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