/********************
���ߣ�������
���䣺19281123@bjtu.edu.cn
����ʱ�䣺2021/7/22
�޸�ʱ�䣺2021/7/24
��������־��غ�������
********************/
class Human;

bool writeSimulateInfo(int elevatorId);	//д�뿪ʼģ�����
void writeBoardingInfo(Human human, int elevatorId);	//д����ݼ�¼
void writeOffInfo(Human human, int elevatorId);	//д�����ݼ�¼
bool getTemporaryData(int& floorNum, int& elevatorNum, int& elevatorWight, int& peopleNum, double& elevatorSpeed);	//��ȡ��ʱ�ļ�