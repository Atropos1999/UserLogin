#include <iostream>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <stdio.h>
#include <vector>
#include "AVLTree.h"
using namespace std;

AVLTree::~AVLTree()
{
	destroy(Root);
}

//�ҵ���
UserNode *AVLTree::rightRotation(UserNode *parent) {
	//    ���������ӽ��
	UserNode * leftNode;

	leftNode = parent->left;
	parent->left = leftNode->right;//�����ӽڵ�����ӽڵ��ɵ�ǰ�ڵ�����ӽڵ� 
	leftNode->right = parent;//�����ӽڵ��ɵ�ǰ�ڵ�ĸ��׽ڵ� 

	parent->height = max(getHeight(parent->left), getHeight(parent->right)) + 1; //���µ�ǰ�ڵ�ĸ߶�
	leftNode->height = max(getHeight(leftNode->left), getHeight(leftNode->right)) + 1;//����ԭ���ӽڵ�߶�
	return leftNode;//����Ϊ�µĸ��ڵ�
}

//����
UserNode *AVLTree::leftRotation(UserNode *parent) {
	//    ���������ӽڵ�
	UserNode *rightNode;

	rightNode = parent->right;
	parent->right = rightNode->left;//�����ӽڵ�����ӽڵ��ɵ�ǰ�ڵ�����ӽڵ� 
	rightNode->left = parent;//�����ӽڵ��ɵ�ǰ�ڵ�ĸ��׽ڵ�

	parent->height = max(getHeight(parent->left), getHeight(parent->right)) + 1;//���µ�ǰ�ڵ�ĸ߶�
	rightNode->height = max(getHeight(rightNode->left), getHeight(rightNode->right)) + 1;//����ԭ���ӽڵ�߶�
	return rightNode;//�ҽڵ�Ϊ�µĸ��ڵ�
}

//��˫��
UserNode *AVLTree::leftRightRotation(UserNode *parent) {
	//    ���ڵ�����ӽڵ������������ڵ����ҵ���
	parent->left = leftRotation(parent->left);
	return rightRotation(parent);
}

//��˫��
UserNode *AVLTree::rightLeftRotation(UserNode *parent) {
	//    ���ڵ���ҽڵ����ҵ��������ڵ�������
	parent->right = rightRotation(parent->right);
	return leftRotation(parent);
}

//��ȡ������С�ڵ�
UserNode* AVLTree::miniAccount(UserNode *user) {
	if (user == NULL)
		return NULL;
	while (user->left != NULL)
		user = user->left;
	return user;
}

//��ȡ����������С�ڵ�ֵ
string AVLTree::miniAccount() {
	UserNode *p = miniAccount(Root);
	if (p != NULL)
		return p->account;
	return NULL;
}

//��ȡ�������ڵ�ֵ
UserNode* AVLTree::maxiAccount(UserNode *user) {
	if (user == NULL)
		return NULL;
	while (user->right != NULL)
		user = user->right;
	return user;
}

//��ȡ�����������ڵ�ֵ
string AVLTree::maxAccount() {
	UserNode *p = maxiAccount(Root);
	if (p != NULL)
		return p->account;
	return NULL;
}

//ɾ�����
UserNode *AVLTree::remove(UserNode *&user, string account) {
	change = true;
	//  ��Ϊ��ֱ�ӷ���NULL��
	if (user == NULL)
		return NULL;
	//   ��һ�����
	//  user�в�����һ���ӽڵ�
	//  �ж�ɾ���Ľڵ���user������������������
	if (account < user->account){//��ɾ���Ľ����user��������
		user->left = remove(user->left, account);
		//      ɾ��������AVL��ʧȥƽ�⣬�������Ӧ�ĵ���(ƽ�����ӱ�Ϊ2)
		if (getHeight(user->right) - getHeight(user->left) == 2){
			UserNode *rightNode = user->right;//user��������
			if (getHeight(rightNode->left) > getHeight(rightNode->right)){//����������������
				user = rightLeftRotation(user);//ɾ���ڵ���������������������������ȴ󣬲�������������������
			}
			else{
				user = leftRotation(user);//���ڵ���������������������������ȴ󣬲�����������
			}
		}
	}
	else if (account > user->account){//��ɾ���Ľ����user����������
		user->right = remove(user->right, account);
		//      ɾ��������AVL��ʧȥƽ�⣬�������Ӧ�ĵ���(ƽ�����ӱ�Ϊ2)
		if (getHeight(user->left) - getHeight(user->right) == 2){
			UserNode *leftNode = user->left;//user��������
			if (getHeight(leftNode->left) < getHeight(leftNode->right)){//������������������
				user = leftRightRotation(user);//ɾ���ڵ���������������������������ȴ󣬲�������������������
			}
			else{
				user = rightRotation(user);//ɾ���ڵ���������������������������ȴ󣬲�����������
			}
		}
	}
	else{
		//      �ڶ������userΪ��ɾ���Ľڵ㣨��Ϊaccount������user���ֲ���userС�ǿ϶�����user�����ˣ�
		if ((user->left != NULL) && (user->right != NULL)){//      user��������������Ϊ��
			//          ���user������������������
			if (getHeight(user->left) > getHeight(user->right)){
				//              �ҳ�user�������е����ڵ�
				UserNode *maxNode = maxiAccount(user->left);
				//              ��maxNode��account��password��ֵ��user�ڵ�
				user->account = maxNode->account;
				user->password = maxNode->password;
				//              �Ƴ�ԭmaxNode�ڵ�
				user->left = remove(user->left, maxNode->account);
			}else{
				//              ���user�����������������߻�����ȣ��ҳ�user����������С�ڵ�
				UserNode *minNode = miniAccount(user->right);
				//              ��miniNode��account��password��ֵ��user�ڵ�
				user->account = minNode->account;
				user->password = minNode->password;
				//              �Ƴ�ԭminNode�ڵ�
				user->right = remove(user->right, minNode->account);
			}
		}else{//          ���ֻ��һ������������ӽڵ��滻ɾ���ڵ�
			UserNode *tmp = user;
			if (user->left != NULL){
				user = user->left;
			}else{
				user = user->right;
			}
			delete  tmp;
		}
	}if (user != NULL)
	{
		user->height = max(getHeight(user->left), getHeight(user->right)) + 1;
	}
	return user;
}

//�Ƴ��ڵ㣬�ⲿ����
void AVLTree::remove(string account) {
	Root = remove(Root, account);
}


//����ڵ�
UserNode *AVLTree::insert(UserNode *&user, string account, string password) {
	if (user == NULL){
		//�½��ڵ�
		user = new UserNode(account, password, NULL, NULL);
	}else if (account < user->account){//��ǰ�ڵ�С����һ���ڵ�
		user->left = insert(user->left, account, password);//һֱ����ݹ�
		//        ����ڵ����AVL��ʧȥƽ�⣬�������Ӧ�ĵ��ڡ�
		if (getHeight(user->left) - getHeight(user->right) == 2){
			//          �͸��ڵ�Ƚ�
			if (account < user->left->account){
				user = rightRotation(user);//��ӽڵ������������������ڣ������������� 
			}
			else{
				user = leftRightRotation(user);//��ӽڵ������������������ڣ���������������������
			}
		}
	}
	else if (account > user->account){// Ӧ�ý�account���뵽user�������������
		user->right = insert(user->right, account, password);
		if (getHeight(user->right) - getHeight(user->left) == 2){
			//          �͸��ڵ�Ƚ�
			if (account > user->right->account){
				user = leftRotation(user);//��ӽڵ������������������ڣ������������� 
			}
			else{
				user = rightLeftRotation(user);//�ӽڵ������������������ڣ���������������������
			}
		}
	}
	//    ƽ��������Ӧ�ķ����ı�
	user->height = max(getHeight(user->left), getHeight(user->right)) + 1;
	return user;
}

//�ⲿʹ�õĲ��뺯��
bool AVLTree::insert(string account, string password) {
	change = true;
	insert(Root, account, password);
	//    ���û����뵽user.txt�ļ���
	fstream users;
	 //д��ķ�ʽ��ͬʱ��appendģʽ�ľͲ��Ḳ�ǵ�ǰ��Ķ����ˡ�
	users.open("user.txt", ios::out | ios::app);
	users << account << " " << password << endl;
	users.close();
	return true;
}

//��ȡ���ĸ߶ȣ�С��
int AVLTree::getHeight(UserNode *user) {
	if (user != NULL)
		return user->height;
	return 0;
}

//��ȡ�������ĸ߶�
int AVLTree::getHeight() {
	return getHeight(Root);
}

//��AVL�е�user���浽user.txt�ļ��У���д��
void AVLTree::saveUser(UserNode *user, ofstream &outfile) const
{
	if (user != NULL)
	{
		saveUser(user->left, outfile);
		saveUser(user->right, outfile);
		outfile << user->account << " " << user->password << "\n"; //�Կո�Ϊ���д x y
	}
}

//��AVL�е�user���浽user.txt�ļ��У���д��
void AVLTree::save()
{
	ofstream outfile;
	outfile.open("user.txt", ios::out);
	saveUser(Root, outfile);
	outfile.close();
}

//���������������ҵ��Ľڵ�ֵ
UserNode *AVLTree::search(UserNode *user, string account) const {
	if (user == NULL || user->account == account){
		return user;
	}
	if (account < user->account){
		return search(user->left, account);
	}
	else{
		return search(user->right, account);
	}
}

//�ⲿʹ�õ���������
UserNode *AVLTree::search(string account) {
	return search(Root, account);
}



//��user.txt�е�����userֵ����AVL����
void AVLTree::getAllUser(AVLTree *users, string fileName){
	ifstream userFile;
	userFile.open(fileName, ios::in);
	string message;
	if (!userFile.is_open()){
		exit(0);
	}
	while (getline(userFile, message)){
		string Account;
		string Password;
		//        �ÿո�ָ�
		int index = message.find(" ");
		Account = message.substr(0, index);
		Password = message.substr(index + 1);
		users->insert(Root, Account, Password);
	}
	userFile.close();
}

//�޸��û�����
void AVLTree::changePassword(AVLTree *users, string account, 
		string password, string newPassword) {
	UserNode *user = search(account);
	if (user->password == password){
		user->password = newPassword;
		//        �޸�֮����дuser.txt
		users->save();
	}
}



//ɾ���û�
bool AVLTree::deleteUser(string account, string password) {
	if (search(account)->password == password){
		remove(account);
		save();
		return true;
	}
	else{
		return false;
	}
}

//�������
void AVLTree::inOrder(UserNode *user) {
	if (user != NULL){
		inOrder(user->left);
		treeSize++;
		inOrder(user->right);
	}
}
//�ⲿʹ��
int AVLTree::inOrder() {
	inOrder(Root);
	return treeSize;
}

//�ݻ���
void AVLTree::destroy(UserNode *&user) {
	if (user == NULL){
		return;
	}
	if (user->left != NULL){
		destroy(user->left);
	}
	if (user->right != NULL){
		destroy(user->right);
	}
	delete user;
}

//�ⲿ��ʹ�õĴݻ�������
void AVLTree::destroy() {
	destroy(Root);
}


//���º�����Ϊ���δ�ӡ��׼��
//��AVL����ÿ����������ֵ���浽map��
void AVLTree::nodeIndex(UserNode* r, int layer) {
	if (r != NULL) {
		static int col;
		if (layer == 0) {
			col = 0;
		}
		nodeIndex(r->left, layer + 1);
		indexes[r] = make_pair(layer, col++);
		nodeIndex(r->right, layer + 1);
	}
}

//���δ�ӡAVL��
void AVLTree::Output() {
	nodeIndex(Root, 0);
	int row = getHeight();//��
	int col = inOrder();//�У�һ���е��ӽڵ�
	int len = 6;
	vector<vector<string> > chart(row, vector<string>(col));
	if (change) {
		indexes.clear();
		nodeIndex(Root, 0);
		change = false;
	}

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			chart[i][j] = string(len, ' ');
		}
	}

	//    ��ȡ����ֵ
	map<UserNode*, pair<int, int> >::iterator i;
	i = indexes.begin();

	while (i != indexes.end()) {
		int curr_row = i->second.first;
		int curr_col = i->second.second;
		string curr_key = i->first->account;
		if (curr_key.length()>len)
		{
			string curr_str = curr_key.substr(0, len - 2) + '.';
			chart[curr_row][curr_col] = curr_str;
		}else{
			int blank_num = len - curr_key.size();
			string curr_str(blank_num, ' ');
			curr_str += curr_key;
			chart[curr_row][curr_col] = curr_str;
		}
		
		i++;
	}
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			cout << chart[i][j];
		}
		cout << endl;
	}
}
