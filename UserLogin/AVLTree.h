#include <map>
#include "UserNode.h"

class AVLTree {
public:
	//      ����users���˻���Ϊaccount�Ľڵ�
	UserNode * search(string account);

	//      ���û��ڵ���뵽AVL����
	bool insert(string account, string password);

	//      ɾ���û�����Ҫ�����û��������룬����ɾ���Ƿ�ɹ�
	bool deleteUser(string account, string password);

	//      �������ڵ�ֵ
	string maxAccount();

	//      ������С�ڵ�ֵ
	string miniAccount();

	//      ɾ���˻���Ϊaccount�Ľڵ�
	void remove(string account);

	//      ��user.txt�л�ȡ����userֵ������AVL��
	void getAllUser(AVLTree *users, string fileName);

	//      �޸�������Ҫԭ���˻����������������
	void changePassword(AVLTree *users, string account, string password, string newPassword);

	//      ����
	void save();

	//      ���δ�ӡAVL��
	void Output();

private:
	//��������
	~AVLTree(); 
	
	//      AVL�����ڵ�
	UserNode *Root;
	
	//      AVL���Ĵ�С
	int treeSize;

	//���ϴ����δ�ӡʱ��ȣ�AVL���Ƿ����˱仯
	bool change; 

	//      ����ÿһ���ڵ������(�������δ�ӡ)
	map<UserNode*, pair<int, int> > indexes;

	//      ��ȡ���ĸ߶�
	int getHeight(UserNode *user);

	//      �������(���ڼ����û��������������δ�ӡ)
	int inOrder();
	
	//      ��ȡ���ĸ߶�
	int getHeight();
	
	//      ����AVL��
	void destroy(UserNode * &user);

	//      �������AVL��(���ڼ����û�����)
	void inOrder(UserNode *user);

	//      �������нڵ�����굽map��(�������δ�ӡ)
	void nodeIndex(UserNode* r, int layer);

	//      ����AVL���е����нڵ�ֵ��user.txt��
	void saveUser(UserNode *user, ofstream &outfile) const;
	
	//      ����AVL��
	void destroy();

	//      ����users�м�ֵΪaccount�Ľڵ�
	UserNode * search(UserNode * user, string account) const;

	//      �ҵ���ת
	UserNode * rightRotation(UserNode *parent);

	//      ����ת
	UserNode * leftRotation(UserNode *parent);

	//      ��˫��ת(������������)
	UserNode * leftRightRotation(UserNode *parent);

	//      ��˫��ת(������������)
	UserNode * rightLeftRotation(UserNode *parent);

	//      ���û��ڵ�(account,password)���뵽AVL����
	UserNode * insert(UserNode * &user, string account, string password);

	//      ɾ��AVL���е�user�ڵ㣬�����ر�ɾ���Ľڵ�
	UserNode * remove(UserNode * &user, string account);

	//      ������С�ڵ�
	UserNode* miniAccount(UserNode *user);

	//      �������ڵ�
	UserNode* maxiAccount(UserNode *user);
};
