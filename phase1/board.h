#ifndef __BOARD_H__
#define __BOARD_H__
#include "list.h"
class Board{
public:
	Board(string _title,int _num): title(_title),num(_num){}
	string get_title(){return title;}
	void add_user(Member* new_mem);
	void remove_user_from_board(Member* new_mem);
	void show_lists(ostream& out);
	void show_cards(int list_num,ostream& out);
	void add_list(string title,int list_num);
	void remove_list(int list_num);
	void move_card(List* first_list,List* second_list,int card_num);
	void filter_cards(vector<string>users);
	void show_member_lists(Member* user,istream& in,ostream& out);
	void filter_lists(vector<Member*> users,istream& in,ostream& out);
	void delete_all_lists();
	int get_num(){return num;}
	void set_admin(Member* _admin){admin=_admin;}
	List* find_the_list_containing_card(int card_num);
	Member* get_admin(){return admin;}
	int calc_newcard_index();
	List* find_list(int num);
	vector<Member*> get_board_members(){return board_members;}
	vector<List*> get_lists(){return lists;}
private:
	Member* admin;
	vector<Member*> board_members;
	vector<List*> lists;
	string title;
	int num;
};
#endif