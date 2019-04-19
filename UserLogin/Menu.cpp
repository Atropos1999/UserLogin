#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <string>
#include <conio.h>
#include "menu.h"

//构造函数
//从文件读入初始数据，放入平衡树里
Menu::Menu()
{
	user = new AVLTree();
	user->getAllUser(user, "user.txt");

}

//光标跳转到坐标为x，y位置（欢迎界面的辅助工具）
void Menu::gotoXY(int x, int y)
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);//句柄
	HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
	COORD po = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
	SetConsoleCursorPosition(hOut, po);
}

//欢迎界面
void  Menu::welcome(){
	//利用gotoXY函数，可以实现走马灯效果
	gotoXY(26, 6);
	cout << "·   -  —" << string(6, ' ') << "—  -   ·";
	gotoXY(37, 6);
	Sleep(100);

	gotoXY(26, 6);
	cout << "·   -  — W       —  -   ·";
	gotoXY(38, 6);
	Sleep(100);

	gotoXY(26, 6);
	cout << "·   -  — WE      —  -   ·";
	gotoXY(39, 6);
	Sleep(100);

	gotoXY(26, 6);
	cout << "·   -  — WEL     —  -   ·";
	gotoXY(40, 6);
	Sleep(100);
	gotoXY(26, 6);
	cout << "·   -  — WELC    —  -   ·";
	gotoXY(41, 6);
	Sleep(100);
	gotoXY(26, 6);
	cout << "·   -  — WELCO   —  -   ·";
	gotoXY(42, 6);
	Sleep(100);
	gotoXY(26, 6);
	cout << "·   -  — WELCOM  —  -   ·";
	gotoXY(43, 6);
	Sleep(100);
	gotoXY(26, 6);
	cout << "·   -  — WELCOME —  -   ·";
	cout << endl << endl << endl;
}


//主界面
void Menu::mainMenu() {
	//无限循环，一次又一次执行
	//作用是在其他菜单退回主界面的时候还可以保证输出这些内容以及继续执行switch分支
	//这样可以实现更好的用户界面（很重要！）
	while (true) {
		system("cls");//清屏
		welcome();

		cout << "                           >>>>>>>用户登录系统<<<<<<<" << endl;
		cout << "           ____________________________________________________________" << endl;;
		cout << "          |                    『1』.登录账号                           |" << endl;
		cout << "          |                    『2』.注册账户                           |" << endl;
		cout << "          |                    『3』.修改密码                           |" << endl;
		cout << "          |                    『4』.注销账号                           |" << endl;
		cout << "          |                    『5』.树形打印                           |" << endl;
		cout << "          |                    『6』.退出                               |" << endl;
		cout << "           -----------------------------------------------------------" << endl;
		cout << "                               请输入序号以实现对应操作。\n";
		gotoXY(26, 19);
		
		//原来用int，出现频闪
		string n;
		cin >> n;
		int size = n.length();
		if ((size > 1) || (n[0]>'6' && n[0] <'1')){
			gotoXY(26, 20);
			cout << "输入不合法！请重新输入！" << endl;
			system("pause");
			continue;
		}
		else{
			switch (n[0]){
				case '1':
					Login();continue;
				case '2':
					Register();continue;
				case '3':
					change();continue;
				case '4':
					cancel();continue;
				case '5':
					printUser();continue;
				case '6':
					system("pause");
					exit(0);
				default:
					system("pause");
					break;
			}
		}	
		
	}
}

//登陆
void Menu::Login()
{
	string account, password;
	while (true){
		system("cls");
		gotoXY(26, 5);
		cout << "================   登录账号   ================" << endl;
		gotoXY(26, 6);
		cout << "账号：";
		cin >> account;
		if (!user->search(account)){
			gotoXY(26, 7);
			cout << "账户不存在请重新输入！" << endl;
			system("pause");
		}else{
			gotoXY(26, 7);
			cout << "密码： ";
			cin >> password;
			if (user->search(account)->password == password){
				gotoXY(30, 8);
				cout << "登录成功！" << endl;
				system("pause");
				break;
			}
			else{
				gotoXY(30, 8);
				cout << "用户密码错误，请重新输入！" << endl;
				system("pause");
			}
		}
	}
}
//注册
void Menu::Register()
{
	string account, password;
	while (true) {
		system("cls");
		gotoXY(26, 5);
		cout << "================   注册账号   ================" << endl;
		gotoXY(26, 6);
		cout << "账户:";
		cin >> account;
		bool flag = true;
		for (int i = 0; account[i] != '\0'; i++) {
			if (!((account[i] >= '0' && account[i] <= '9') || (account[i] >= 'a' && account[i] <= 'z' || account[i] >= 'A' && account[i] <= 'Z'))) {
				gotoXY(30, 7);
				cout << "非法输入！账户名只能是字母和数字。" << endl;
				flag = false;
				system("pause");
				continue;
			}
		}
		if (flag){
			if (user->search(account)){
				gotoXY(26, 7);
				cout << "该账户已存在！" << endl;
				system("pause");
				continue;
			}
			else{
				gotoXY(26, 7);
				cout << "请输入密码:";
				cin >> password;
				user->insert(account, password);
				gotoXY(30, 8);
				cout << "注册成功！" << endl;
				system("pause");   break;
			}
		}
	}
}

//删除
void Menu::cancel()
{
	string account, password;
	while (true)
	{
		system("cls");
		gotoXY(26, 5);
		cout << "================   注销账号   ================" << endl;
		gotoXY(26, 6);
		cout << "账户：";
		cin >> account;
		if (user->search(account)) {
			gotoXY(26, 7);
			cout << "密码：";
			cin >> password;
			if (user->search(account)->password == password){
				user->deleteUser(account, password);
				gotoXY(30, 8);
				cout << "删除成功！" << endl;
				system("pause");
				break;
			}else{
				gotoXY(30, 8);
				cout << "密码错误请重新输入！" << endl;
				system("pause");
				continue;
			}
		}else{
			gotoXY(30, 7);
			cout << "账户不存在！" << endl;
			gotoXY(26, 8);
			cout << "1.继续注销账户\n";
			gotoXY(26, 9);
			cout << "2.退出当前页面\n";
			string k;
			gotoXY(26, 10);
			cin >> k;
			if (k[0] == '1' && k.length()==1){
				system("pause");
				continue;
			}else if (k[0] == '2' && k.length() == 1){
				break;
			}else{
				gotoXY(26, 11);
				cout << "输入不合法！默认为退出当前程序！";
				system("pause");
				break;
			}
		}
	}
	

}

void Menu::change() {
	
	string account, password, newPassword;
	while (true){
		system("cls");
		gotoXY(26, 5);
		cout << "================   修改密码   ================" << endl;
		gotoXY(26, 6);
		cout << "账号：";
		cin >> account;
		if (!user->search(account)){
			gotoXY(26, 7);
			cout << "用户不存在,请重新输入！\n";
			system("pause");
			continue;
		}else{
			gotoXY(26, 7);
			cout << "密码：";
			cin >> password;
			if (user->search(account)->password == password){
				gotoXY(26, 8);
				cout << "新密码：";
				cin >> newPassword;
				user->changePassword(user, account, password, newPassword);
				gotoXY(26, 9);
				cout << "用户密码修改成功！\n";
				system("pause");
				break;
			}else{
				gotoXY(26, 8);
				cout << "密码错误请重新输入！\n";
				system("pause");
			}
		}	
	}
}

//打印树
void Menu::printUser()
{
	system("cls");
	cout << "================   树形打印   ================" << endl;
	user->Output();
	system("pause");
}
