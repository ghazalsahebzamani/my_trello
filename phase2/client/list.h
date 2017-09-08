#ifndef __LIST_H__
#define __LIST_H__
#include "card.h"
class List{
public:
	List(string _title,int _num):title(_title),num(_num){}
	void add_card(string title,int card_index,Member* admin);
	void remove_card(int number);
	void move_card();
	Card* find_card(int number);
	void delete_card(int number);
	void rename_card(int card_num,string new_title);
	void add_previously_created_card(Card* created_card);
	void edit_description(int card_num,vector<string> des);
	void show_member_cards(Member* user,string des_check,string cm_check,ostream& out);
	int get_num(){return num;}
	void filter_cards(vector<Member*> users,string des_check,string cm_check,ostream& out);
	void delete_all_cards();
	string get_title(){return title;}
	vector <Card*> get_cards(){return cards;}
private:
vector<Card*> cards;
int num;
string title;
};
#endif