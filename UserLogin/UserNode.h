#include <string>
using namespace std;

class UserNode {
public:
	int height;      // ���ĸ߶�
	string account;   // �û���
	string password;  //����
	UserNode *left, *right; //�����ӽ��
	// ���캯��
	UserNode(string Account, string Password, UserNode *left = NULL, UserNode *right = NULL) :
		account(Account), password(Password), left(left), right(right){}
};
