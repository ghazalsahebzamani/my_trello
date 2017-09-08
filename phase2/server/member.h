#ifndef __MEMBER_H__
#define __MEMBER_H__
#include <iostream>
#include <vector>
using namespace std;
class Member{
public:
	Member(string _name,string _user,string _pass):name(_name),user(_user),pass(_pass){}
	void remove_board(int board_num);
	void enter_board(int board_num);
	void show_my_cards();
	string get_user(){return user;};
	string get_pass(){return pass;};
	string get_name(){return name;};
private:
	string user;
	string name;
	string pass;
};
#endif