#include <iostream>
#include "AVLTree.h"

using namespace std;
class Menu {
public:
	Menu();
	AVLTree *user;//储存用户
	void gotoXY(int x, int y);//光标移动
	void welcome();//欢迎界面
	void mainMenu();//主页面
	void Login();//登录界面
	void Register();//注册界面
	void cancel();//注销用户界面
	void change();//修改密码界面
	void printUser();//树形打印界面
};