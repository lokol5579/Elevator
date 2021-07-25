/********************
作者：陈晗阳
邮箱：19281123@bjtu.edu.cn
创建时间：2021/7/22
修改时间：2021/7/24
描述：日志相关函数声明
********************/
class Human;

bool writeSimulateInfo(int elevatorId);	//写入开始模拟语句
void writeBoardingInfo(Human human, int elevatorId);	//写入登梯记录
void writeOffInfo(Human human, int elevatorId);	//写入下梯记录
bool getTemporaryData(int& floorNum, int& elevatorNum, int& elevatorWight, int& peopleNum, double& elevatorSpeed);	//读取临时文件