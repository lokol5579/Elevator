/********************
���ߣ�������
���䣺19281123@bjtu.edu.cn
����ʱ�䣺2021/7/19
�޸�ʱ�䣺2021/7/21
�������˵Ĺ���ʵ��
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
	wight = (rand() % 101) + 80; //���������أ����ط�Χ80-180kg
	origin = (rand() % floorNum) + 1;	//����������¥��
	/*���������¥�㲻ͬ��Ŀ��¥��*/
	while ((destination = (rand() % floorNum + 1)) == origin);
	(origin - destination) > 0 ? (state = State::DOWN) : (state = State::UP);
}