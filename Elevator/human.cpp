/********************
���ߣ�������
���䣺19281123@bjtu.edu.cn
����ʱ�䣺2021/7/19
�޸�ʱ�䣺2021/7/21
�������˵Ĺ���ʵ��
********************/

#include <iostream>
#include <ctime>
#include "parameter.h"
#include "human.h"

int humanId = 0;

void Human::init(int floorNum)
{
	srand((unsigned)time(NULL));
	wight = (rand() % 101) + 80; //���ط�Χ80-180kg
	origin = (rand() % floorNum) + 1;
	while ((destination = (rand() % floorNum + 1)) == origin);
	(origin - destination) > 0 ? (state = State::DOWN) : (state = State::UP);
}