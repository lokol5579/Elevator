/********************
作者：陈晗阳
邮箱：19281123@bjtu.edu.cn
创建时间：2021/7/22
修改时间：2021/7/23
描述：控制台函数声明
********************/

class Elevator;

void userInterface(int& floorNum, int& elevatorNum, int& elevatorWight, int& peopleNum, double& elevatorSpeed);	//Console用户界面
void fullScreen();	//Console全屏
void refresh(Elevator* elevator, int elevatorNum, int floorNum);	//刷新界面
void setTextWhite();	//设置字体为白色