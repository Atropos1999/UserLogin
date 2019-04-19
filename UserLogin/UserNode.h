#include <string>
using namespace std;

class UserNode {
public:
	int height;      // 树的高度
	string account;   // 用户名
	string password;  //密码
	UserNode *left, *right; //左右子结点
	// 构造函数
	UserNode(string Account, string Password, UserNode *left = NULL, UserNode *right = NULL) :
		account(Account), password(Password), left(left), right(right){}
};
