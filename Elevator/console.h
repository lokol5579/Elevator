/********************
作者：陈晗阳
邮箱：19281123@bjtu.edu.cn
创建时间：2021/7/22
修改时间：2021/7/23
描述：控制台函数声明
********************/

class Elevator;

void userInterface(int& floorNum, int& elevatorNum, int& elevatorWight, int& peopleNum, double& elevatorSpeed);
void fullScreen();
void refresh(Elevator* elevator, int elevatorNum, int floorNum);
void setTextWhite();