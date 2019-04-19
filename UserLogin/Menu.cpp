#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <string>
#include <conio.h>
#include "menu.h"

//���캯��
//���ļ������ʼ���ݣ�����ƽ������
Menu::Menu()
{
	user = new AVLTree();
	user->getAllUser(user, "user.txt");

}

//�����ת������Ϊx��yλ�ã���ӭ����ĸ������ߣ�
void Menu::gotoXY(int x, int y)
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);//���
	HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
	COORD po = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
	SetConsoleCursorPosition(hOut, po);
}

//��ӭ����
void  Menu::welcome(){
	//����gotoXY����������ʵ�������Ч��
	gotoXY(26, 6);
	cout << "��   -  ��" << string(6, ' ') << "��  -   ��";
	gotoXY(37, 6);
	Sleep(100);

	gotoXY(26, 6);
	cout << "��   -  �� W       ��  -   ��";
	gotoXY(38, 6);
	Sleep(100);

	gotoXY(26, 6);
	cout << "��   -  �� WE      ��  -   ��";
	gotoXY(39, 6);
	Sleep(100);

	gotoXY(26, 6);
	cout << "��   -  �� WEL     ��  -   ��";
	gotoXY(40, 6);
	Sleep(100);
	gotoXY(26, 6);
	cout << "��   -  �� WELC    ��  -   ��";
	gotoXY(41, 6);
	Sleep(100);
	gotoXY(26, 6);
	cout << "��   -  �� WELCO   ��  -   ��";
	gotoXY(42, 6);
	Sleep(100);
	gotoXY(26, 6);
	cout << "��   -  �� WELCOM  ��  -   ��";
	gotoXY(43, 6);
	Sleep(100);
	gotoXY(26, 6);
	cout << "��   -  �� WELCOME ��  -   ��";
	cout << endl << endl << endl;
}


//������
void Menu::mainMenu() {
	//����ѭ����һ����һ��ִ��
	//�������������˵��˻��������ʱ�򻹿��Ա�֤�����Щ�����Լ�����ִ��switch��֧
	//��������ʵ�ָ��õ��û����棨����Ҫ����
	while (true) {
		system("cls");//����
		welcome();

		cout << "                           >>>>>>>�û���¼ϵͳ<<<<<<<" << endl;
		cout << "           ____________________________________________________________" << endl;;
		cout << "          |                    ��1��.��¼�˺�                           |" << endl;
		cout << "          |                    ��2��.ע���˻�                           |" << endl;
		cout << "          |                    ��3��.�޸�����                           |" << endl;
		cout << "          |                    ��4��.ע���˺�                           |" << endl;
		cout << "          |                    ��5��.���δ�ӡ                           |" << endl;
		cout << "          |                    ��6��.�˳�                               |" << endl;
		cout << "           -----------------------------------------------------------" << endl;
		cout << "                               �����������ʵ�ֶ�Ӧ������\n";
		gotoXY(26, 19);
		
		//ԭ����int������Ƶ��
		string n;
		cin >> n;
		int size = n.length();
		if ((size > 1) || (n[0]>'6' && n[0] <'1')){
			gotoXY(26, 20);
			cout << "���벻�Ϸ������������룡" << endl;
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

//��½
void Menu::Login()
{
	string account, password;
	while (true){
		system("cls");
		gotoXY(26, 5);
		cout << "================   ��¼�˺�   ================" << endl;
		gotoXY(26, 6);
		cout << "�˺ţ�";
		cin >> account;
		if (!user->search(account)){
			gotoXY(26, 7);
			cout << "�˻����������������룡" << endl;
			system("pause");
		}else{
			gotoXY(26, 7);
			cout << "���룺 ";
			cin >> password;
			if (user->search(account)->password == password){
				gotoXY(30, 8);
				cout << "��¼�ɹ���" << endl;
				system("pause");
				break;
			}
			else{
				gotoXY(30, 8);
				cout << "�û�����������������룡" << endl;
				system("pause");
			}
		}
	}
}
//ע��
void Menu::Register()
{
	string account, password;
	while (true) {
		system("cls");
		gotoXY(26, 5);
		cout << "================   ע���˺�   ================" << endl;
		gotoXY(26, 6);
		cout << "�˻�:";
		cin >> account;
		bool flag = true;
		for (int i = 0; account[i] != '\0'; i++) {
			if (!((account[i] >= '0' && account[i] <= '9') || (account[i] >= 'a' && account[i] <= 'z' || account[i] >= 'A' && account[i] <= 'Z'))) {
				gotoXY(30, 7);
				cout << "�Ƿ����룡�˻���ֻ������ĸ�����֡�" << endl;
				flag = false;
				system("pause");
				continue;
			}
		}
		if (flag){
			if (user->search(account)){
				gotoXY(26, 7);
				cout << "���˻��Ѵ��ڣ�" << endl;
				system("pause");
				continue;
			}
			else{
				gotoXY(26, 7);
				cout << "����������:";
				cin >> password;
				user->insert(account, password);
				gotoXY(30, 8);
				cout << "ע��ɹ���" << endl;
				system("pause");   break;
			}
		}
	}
}

//ɾ��
void Menu::cancel()
{
	string account, password;
	while (true)
	{
		system("cls");
		gotoXY(26, 5);
		cout << "================   ע���˺�   ================" << endl;
		gotoXY(26, 6);
		cout << "�˻���";
		cin >> account;
		if (user->search(account)) {
			gotoXY(26, 7);
			cout << "���룺";
			cin >> password;
			if (user->search(account)->password == password){
				user->deleteUser(account, password);
				gotoXY(30, 8);
				cout << "ɾ���ɹ���" << endl;
				system("pause");
				break;
			}else{
				gotoXY(30, 8);
				cout << "����������������룡" << endl;
				system("pause");
				continue;
			}
		}else{
			gotoXY(30, 7);
			cout << "�˻������ڣ�" << endl;
			gotoXY(26, 8);
			cout << "1.����ע���˻�\n";
			gotoXY(26, 9);
			cout << "2.�˳���ǰҳ��\n";
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
				cout << "���벻�Ϸ���Ĭ��Ϊ�˳���ǰ����";
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
		cout << "================   �޸�����   ================" << endl;
		gotoXY(26, 6);
		cout << "�˺ţ�";
		cin >> account;
		if (!user->search(account)){
			gotoXY(26, 7);
			cout << "�û�������,���������룡\n";
			system("pause");
			continue;
		}else{
			gotoXY(26, 7);
			cout << "���룺";
			cin >> password;
			if (user->search(account)->password == password){
				gotoXY(26, 8);
				cout << "�����룺";
				cin >> newPassword;
				user->changePassword(user, account, password, newPassword);
				gotoXY(26, 9);
				cout << "�û������޸ĳɹ���\n";
				system("pause");
				break;
			}else{
				gotoXY(26, 8);
				cout << "����������������룡\n";
				system("pause");
			}
		}	
	}
}

//��ӡ��
void Menu::printUser()
{
	system("cls");
	cout << "================   ���δ�ӡ   ================" << endl;
	user->Output();
	system("pause");
}
