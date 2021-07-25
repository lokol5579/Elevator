/********************
作者：陈晗阳
邮箱：19281123@bjtu.edu.cn
创建时间：2021/7/22
修改时间：2021/7/22
描述：日志相关函数声明
********************/
class Human;

bool writeSimulateInfo(int elevatorId);
void writeBoardingInfo(Human human, int elevatorId);
void writeOffInfo(Human human, int elevatorId);
bool getTemporaryData(int& floorNum, int& elevatorNum, int& elevatorWight, int& peopleNum, double& elevatorSpeed);