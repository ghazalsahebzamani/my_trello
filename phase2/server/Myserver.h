#ifndef __MyServer_H__
#define __MyServer_H__
#include <iostream>
#include <sstream>
#include "server.h"
#include "funcs.h"
using namespace std;
class MyServer : public Server {
public:
  MyServer(int port) : Server(port) {
  initialize(_trello);
  clear_file("temp3.txt");
  }
  void on_standard_input(string line);
  void on_new_connection(int identifier);
  void on_new_message(int identifier, string message);
  void on_terminated_connection(int identifier);
  void user_check(int& identifier,string& user);
  char bring_menu2(ostream& out);
  void start(stringstream& out,int identifier);
  void s_check_order(string message,int identifier);
  void s_check_username(string message,int identifier);
  void s_create_user(stringstream& out,string message,int identifier);
  void s_login(stringstream& out,string message,int identifier);
  void s_create_board(string message,int identifier);
  void s_show_boards(stringstream& out,int identifier);
  void s_enter_board(stringstream& out,string message,int identifier);
  void s_check_for_member(string message,int identifier);
  void s_add_member(string message,int identifier);
  void s_remove_user(stringstream& out,string message,int identifier);
  void s_check_access(int identifier);
  void s_remove_board(stringstream& out,string message,int identifier);
  void s_remove_list(stringstream& out,string message,int identifier);
  void s_add_list(string message,int identifier);
  void s_find_list(stringstream& out,string message,int identifier);
  void s_add_card(stringstream& out,string message,int identifier);
  void s_remove_card(stringstream& out,string message,int identifier);
  void s_move_card(stringstream& out,string message,int identifier);
  void s_find_card(stringstream& out,string message,int identifier);
  void s_rename_cards(stringstream& out,string message,int identifier);
  void s_edit_card_des(stringstream& out,string message,int identifier);
  void s_assign_user(stringstream& out,string message,int identifier);
  void s_remove_user_from_card(stringstream& out,string message,int identifier);
  void s_show_cards(stringstream& out,string message,int identifier);
  void s_filter(stringstream& out,string message,int identifier);
  void s_comment(stringstream& out,string message,int identifier);
  void s_get_name(string message,int identifier);
  void s_get_user(string message,int identifier);
  void s_get_pass(string message,int identifier);
protected:
  Trello _trello;
};
#endif