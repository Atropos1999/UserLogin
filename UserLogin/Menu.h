#include <iostream>
#include "AVLTree.h"

using namespace std;
class Menu {
public:
	Menu();
	AVLTree *user;//�����û�
	void gotoXY(int x, int y);//����ƶ�
	void welcome();//��ӭ����
	void mainMenu();//��ҳ��
	void Login();//��¼����
	void Register();//ע�����
	void cancel();//ע���û�����
	void change();//�޸��������
	void printUser();//���δ�ӡ����
};