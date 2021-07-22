/********************
作者：陈晗阳
邮箱：19281123@bjtu.edu.cn
创建时间：2021/7/19
修改时间：2021/7/21
描述：人的功能实现
********************/

#include <iostream>
#include <cstdlib>
#include "parameter.h"
#include "human.h"

int humanId = 0;
bool setSeed = false;

void Human::init(int floorNum)
{
	if (!setSeed)
	{
		srand((unsigned)time(NULL));
		setSeed = true;
	}
	wight = (rand() % 101) + 80; //体重范围80-180kg
	origin = (rand() % floorNum) + 1;
	while ((destination = (rand() % floorNum + 1)) == origin);
	(origin - destination) > 0 ? (state = State::DOWN) : (state = State::UP);
}