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

//右单旋
UserNode *AVLTree::rightRotation(UserNode *parent) {
	//    父结点的左子结点
	UserNode * leftNode;

	leftNode = parent->left;
	parent->left = leftNode->right;//将左子节点的右子节点变成当前节点的左子节点 
	leftNode->right = parent;//将左子节点变成当前节点的父亲节点 

	parent->height = max(getHeight(parent->left), getHeight(parent->right)) + 1; //更新当前节点的高度
	leftNode->height = max(getHeight(leftNode->left), getHeight(leftNode->right)) + 1;//更新原左子节点高度
	return leftNode;//左结点为新的父节点
}

//左单旋
UserNode *AVLTree::leftRotation(UserNode *parent) {
	//    父结点的右子节点
	UserNode *rightNode;

	rightNode = parent->right;
	parent->right = rightNode->left;//将右子节点的左子节点变成当前节点的右子节点 
	rightNode->left = parent;//将右子节点变成当前节点的父亲节点

	parent->height = max(getHeight(parent->left), getHeight(parent->right)) + 1;//更新当前节点的高度
	rightNode->height = max(getHeight(rightNode->left), getHeight(rightNode->right)) + 1;//更新原右子节点高度
	return rightNode;//右节点为新的父节点
}

//左双旋
UserNode *AVLTree::leftRightRotation(UserNode *parent) {
	//    父节点的左子节点先左单旋，父节点再右单旋
	parent->left = leftRotation(parent->left);
	return rightRotation(parent);
}

//右双旋
UserNode *AVLTree::rightLeftRotation(UserNode *parent) {
	//    父节点的右节点先右单旋，父节点再左单旋
	parent->right = rightRotation(parent->right);
	return leftRotation(parent);
}

//获取树的最小节点
UserNode* AVLTree::miniAccount(UserNode *user) {
	if (user == NULL)
		return NULL;
	while (user->left != NULL)
		user = user->left;
	return user;
}

//获取整棵树的最小节点值
string AVLTree::miniAccount() {
	UserNode *p = miniAccount(Root);
	if (p != NULL)
		return p->account;
	return NULL;
}

//获取树的最大节点值
UserNode* AVLTree::maxiAccount(UserNode *user) {
	if (user == NULL)
		return NULL;
	while (user->right != NULL)
		user = user->right;
	return user;
}

//获取整棵树的最大节点值
string AVLTree::maxAccount() {
	UserNode *p = maxiAccount(Root);
	if (p != NULL)
		return p->account;
	return NULL;
}

//删除结点
UserNode *AVLTree::remove(UserNode *&user, string account) {
	change = true;
	//  根为空直接返回NULL。
	if (user == NULL)
		return NULL;
	//   第一种情况
	//  user有不多于一个子节点
	//  判断删除的节点在user的左子树还是右子树
	if (account < user->account){//待删除的结点在user左子树中
		user->left = remove(user->left, account);
		//      删除结点后，若AVL树失去平衡，则进行相应的调节(平衡因子变为2)
		if (getHeight(user->right) - getHeight(user->left) == 2){
			UserNode *rightNode = user->right;//user的右子树
			if (getHeight(rightNode->left) > getHeight(rightNode->right)){//左子树比右子树高
				user = rightLeftRotation(user);//删除节点在左子树，右子树的左子树深度大，采用先右旋再左旋操作
			}
			else{
				user = leftRotation(user);//除节点在左子树，右子树的右子树深度大，采用左旋操作
			}
		}
	}
	else if (account > user->account){//待删除的结点在user的右子树中
		user->right = remove(user->right, account);
		//      删除结点后，若AVL树失去平衡，则进行相应的调节(平衡因子变为2)
		if (getHeight(user->left) - getHeight(user->right) == 2){
			UserNode *leftNode = user->left;//user的左子树
			if (getHeight(leftNode->left) < getHeight(leftNode->right)){//若右子树比左子树高
				user = leftRightRotation(user);//删除节点在右子树，左子树的右子树深度大，采用先左旋再右旋操作
			}
			else{
				user = rightRotation(user);//删除节点在右子树，左子树的左子树深度大，采用右旋操作
			}
		}
	}
	else{
		//      第二种情况user为待删除的节点（因为account即不比user大又不比user小那肯定就是user本身了）
		if ((user->left != NULL) && (user->right != NULL)){//      user的左右子树均不为空
			//          如果user的左子树比右子树高
			if (getHeight(user->left) > getHeight(user->right)){
				//              找出user左子树中的最大节点
				UserNode *maxNode = maxiAccount(user->left);
				//              将maxNode的account和password赋值给user节点
				user->account = maxNode->account;
				user->password = maxNode->password;
				//              移除原maxNode节点
				user->left = remove(user->left, maxNode->account);
			}else{
				//              如果user的右子树比左子树高或者相等，找出user右子树中最小节点
				UserNode *minNode = miniAccount(user->right);
				//              将miniNode的account和password赋值给user节点
				user->account = minNode->account;
				user->password = minNode->password;
				//              移除原minNode节点
				user->right = remove(user->right, minNode->account);
			}
		}else{//          最多只有一子树情况，将子节点替换删除节点
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

//移除节点，外部可用
void AVLTree::remove(string account) {
	Root = remove(Root, account);
}


//插入节点
UserNode *AVLTree::insert(UserNode *&user, string account, string password) {
	if (user == NULL){
		//新建节点
		user = new UserNode(account, password, NULL, NULL);
	}else if (account < user->account){//当前节点小于上一个节点
		user->left = insert(user->left, account, password);//一直往左递归
		//        插入节点后，若AVL树失去平衡，则进行相应的调节。
		if (getHeight(user->left) - getHeight(user->right) == 2){
			//          和父节点比较
			if (account < user->left->account){
				user = rightRotation(user);//添加节点在左子树的左子树内，采用右旋操作 
			}
			else{
				user = leftRightRotation(user);//添加节点在左子树的右子树内，采用先左旋再右旋操作
			}
		}
	}
	else if (account > user->account){// 应该将account插入到user的右子树的情况
		user->right = insert(user->right, account, password);
		if (getHeight(user->right) - getHeight(user->left) == 2){
			//          和父节点比较
			if (account > user->right->account){
				user = leftRotation(user);//添加节点在右子树的右子树内，采用左旋操作 
			}
			else{
				user = rightLeftRotation(user);//加节点在右子树的左子树内，采用先右旋再左旋操作
			}
		}
	}
	//    平衡因子相应的发生改变
	user->height = max(getHeight(user->left), getHeight(user->right)) + 1;
	return user;
}

//外部使用的插入函数
bool AVLTree::insert(string account, string password) {
	change = true;
	insert(Root, account, password);
	//    将用户加入到user.txt文件中
	fstream users;
	 //写入的方式，同时是append模式的就不会覆盖掉前面的东西了。
	users.open("user.txt", ios::out | ios::app);
	users << account << " " << password << endl;
	users.close();
	return true;
}

//获取树的高度（小）
int AVLTree::getHeight(UserNode *user) {
	if (user != NULL)
		return user->height;
	return 0;
}

//获取整棵树的高度
int AVLTree::getHeight() {
	return getHeight(Root);
}

//将AVL中的user保存到user.txt文件中（重写）
void AVLTree::saveUser(UserNode *user, ofstream &outfile) const
{
	if (user != NULL)
	{
		saveUser(user->left, outfile);
		saveUser(user->right, outfile);
		outfile << user->account << " " << user->password << "\n"; //以空格为间隔写 x y
	}
}

//将AVL中的user保存到user.txt文件中（重写）
void AVLTree::save()
{
	ofstream outfile;
	outfile.open("user.txt", ios::out);
	saveUser(Root, outfile);
	outfile.close();
}

//搜索函数，返回找到的节点值
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

//外部使用的搜索函数
UserNode *AVLTree::search(string account) {
	return search(Root, account);
}



//将user.txt中的所有user值存入AVL树中
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
		//        用空格分割
		int index = message.find(" ");
		Account = message.substr(0, index);
		Password = message.substr(index + 1);
		users->insert(Root, Account, Password);
	}
	userFile.close();
}

//修改用户密码
void AVLTree::changePassword(AVLTree *users, string account, 
		string password, string newPassword) {
	UserNode *user = search(account);
	if (user->password == password){
		user->password = newPassword;
		//        修改之后重写user.txt
		users->save();
	}
}



//删除用户
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

//中序遍历
void AVLTree::inOrder(UserNode *user) {
	if (user != NULL){
		inOrder(user->left);
		treeSize++;
		inOrder(user->right);
	}
}
//外部使用
int AVLTree::inOrder() {
	inOrder(Root);
	return treeSize;
}

//摧毁树
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

//外部可使用的摧毁整棵树
void AVLTree::destroy() {
	destroy(Root);
}


//以下函数均为树形打印做准备
//将AVL树种每个结点的坐标值保存到map中
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

//树形打印AVL树
void AVLTree::Output() {
	nodeIndex(Root, 0);
	int row = getHeight();//行
	int col = inOrder();//列，一共有的子节点
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

	//    获取坐标值
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
