#ifndef __CARD_H__
#define __CARD_H__
#include "member.h"
#include "comment.h"
class Card{
public:
	Card(string _title,int _num):title(_title),num(_num){}
	void comment(Card* card,Member* composer,vector<string> des);
	void edit_des(vector<string> new_des){des=new_des;}
	void see_cms(ostream& out);
	string get_title(){return title;};
	void rename(string new_title){title=new_title;}
	int get_num(){return num;};
	void add_user(Member* user);
	void remove_user(string user);
	void show_card(string des_check,string cm_check,ostream& out);
	void delete_cms();
	void show_member_card(Member* user,string des_check,string cm_check,ostream& out);
	vector<Comment*> get_cms(){return comments;}
private:
	vector<Member*> mems;
	vector<Comment*> comments;
	int num;
	vector<string> des;
	string title;
};
#endif