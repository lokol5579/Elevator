/********************
���ߣ�������
���䣺19281123@bjtu.edu.cn
����ʱ�䣺2021/7/20
�޸�ʱ�䣺2021/7/21
���������ݹ���ʵ��
********************/

#include "elevator.h"
#include "human.h"
#include "people.h"
#include "parameter.h"
#include "file.h"
using namespace std;

int elevatorId = 0;

bool Elevator::boarding(Human& human, People& waitingPeople)
{
	if (peopleWight + human.getWight() < totalWight)	//�Ƿ���
	{
		peopleWight += human.getWight();
		writeBoardingInfo(human, this->getId());	//д����־

		/*������ȥ�ķ��򼰵���״̬�ж��Ƿ��ϵ���*/
		switch (human.getState())
		{
		case State::DOWN:
		{
			if (destination > human.getDestination())
			{
				waitingPeople.setRequestState(human.getDestination(), false);
				destination = human.getDestination();
				waitingPeople.setRequestState(destination, true);
			}
			break;
		}
		case State::UP: 
		{
			if (destination < human.getDestination())
			{
				waitingPeople.setRequestState(human.getDestination(), false);
				destination = human.getDestination();
				waitingPeople.setRequestState(destination, true);
			}
			break;
		}
		}
		people.push_back(human);
		this->totalCapacity++;
		return true;
	}
	else return false;
}

void Elevator::getOff(int floor, People& waitingPeople)
{
	if (!people.empty())	//�ж��Ƿ����
	{
		/*�����Ƿ��е���Ŀ��¥�����*/
		for (vector<Human>::iterator iter(people.begin()); iter != people.end();)
		{
			if (iter->getDestination() == floor)
			{
				peopleWight -= iter->getWight();
				writeOffInfo(*iter, this->getId());
				iter = people.erase(iter);
			}
			else iter++;
		}
	}
	if (waitingPeople.getRequestState(floor)) waitingPeople.setRequestState(floor, false);
}