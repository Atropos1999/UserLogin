#include <map>
#include "UserNode.h"

class AVLTree {
public:
	//      查找users中账户名为account的节点
	UserNode * search(string account);

	//      将用户节点插入到AVL树中
	bool insert(string account, string password);

	//      删除用户，需要输入用户名和密码，返回删除是否成功
	bool deleteUser(string account, string password);

	//      返回最大节点值
	string maxAccount();

	//      返回最小节点值
	string miniAccount();

	//      删除账户名为account的节点
	void remove(string account);

	//      从user.txt中获取所有user值，创建AVL树
	void getAllUser(AVLTree *users, string fileName);

	//      修改密码需要原有账户名，密码和新密码
	void changePassword(AVLTree *users, string account, string password, string newPassword);

	//      保存
	void save();

	//      树形打印AVL树
	void Output();

private:
	//析构函数
	~AVLTree(); 
	
	//      AVL树根节点
	UserNode *Root;
	
	//      AVL树的大小
	int treeSize;

	//与上次树形打印时相比，AVL树是否发生了变化
	bool change; 

	//      保存每一个节点的坐标(用于树形打印)
	map<UserNode*, pair<int, int> > indexes;

	//      获取树的高度
	int getHeight(UserNode *user);

	//      中序遍历(用于计算用户个数，用于树形打印)
	int inOrder();
	
	//      获取树的高度
	int getHeight();
	
	//      销毁AVL树
	void destroy(UserNode * &user);

	//      中序遍历AVL树(用于计算用户个数)
	void inOrder(UserNode *user);

	//      保存所有节点的坐标到map中(用于树形打印)
	void nodeIndex(UserNode* r, int layer);

	//      保存AVL树中的所有节点值到user.txt中
	void saveUser(UserNode *user, ofstream &outfile) const;
	
	//      销毁AVL树
	void destroy();

	//      查找users中键值为account的节点
	UserNode * search(UserNode * user, string account) const;

	//      右单旋转
	UserNode * rightRotation(UserNode *parent);

	//      左单旋转
	UserNode * leftRotation(UserNode *parent);

	//      左双旋转(先左旋再右旋)
	UserNode * leftRightRotation(UserNode *parent);

	//      右双旋转(先右旋再左旋)
	UserNode * rightLeftRotation(UserNode *parent);

	//      将用户节点(account,password)插入到AVL树中
	UserNode * insert(UserNode * &user, string account, string password);

	//      删除AVL树中的user节点，并返回被删除的节点
	UserNode * remove(UserNode * &user, string account);

	//      返回最小节点
	UserNode* miniAccount(UserNode *user);

	//      返回最大节点
	UserNode* maxiAccount(UserNode *user);
};
