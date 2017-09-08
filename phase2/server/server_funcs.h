#ifndef __SERVER_FUNCS_H__
#define __SERVER_FUNCS_H__
#include <iostream>
#include <sstream>
#include "trello.h"
using namespace std;
char bring_menu2(Trello &_trello,ostream& out,int identifier);
void start(Trello &_trello,stringstream& out,int identifier);
void s_check_order(Trello &_trello,string message,int identifier);
void s_check_username(string message,int identifier);
void s_create_user(Trello &_trello,stringstream& out,string message,int identifier);
void s_login(Trello& _trello,stringstream& out,string message,int identifier);
void s_create_board(Trello& _trello,string message,int identifier);
void s_show_boards(Trello& _trello,stringstream& out,int identifier);
void s_enter_board(Trello& _trello,stringstream& out,string message,int identifier);
void s_check_for_member(Trello& _trello,string message,int identifier);
void s_add_member(Trello& _trello,string message,int identifier);
void s_remove_user(Trello& _trello,stringstream& out,string message,int identifier);
void s_check_access(Trello& _trello,int identifier);
void s_remove_board(Trello& _trello,stringstream& out,string message,int identifier);
void s_remove_list(Trello& _trello,stringstream& out,string message,int identifier);
void s_add_list(Trello& _trello,string message,int identifier);
void s_find_list(Trello& _trello,stringstream& out,string message,int identifier);
void s_add_card(Trello& _trello,stringstream& out,string message,int identifier);
void s_remove_card(Trello& _trello,stringstream& out,string message,int identifier);
void s_move_card(Trello& _trello,stringstream& out,string message,int identifier);
void s_find_card(Trello& _trello,stringstream& out,string message,int identifier);
void s_rename_cards(Trello& _trello,stringstream& out,string message,int identifier);
void s_edit_card_des(Trello& _trello,stringstream& out,string message,int identifier);
void s_assign_user(Trello& _trello,stringstream& out,string message,int identifier);
void s_remove_user_from_card(Trello& _trello,stringstream& out,string message,int identifier);
void s_show_cards(Trello& _trello,stringstream& out,string message,int identifier);
void s_filter(Trello& _trello,stringstream& out,string message,int identifier);
void s_comment(Trello& _trello,stringstream& out,string message,int identifier);
void s_get_name(string message,int identifier);
void s_get_user(string message,int identifier);
void s_get_pass(string message,int identifier);
#endif