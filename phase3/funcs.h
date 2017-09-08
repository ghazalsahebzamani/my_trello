#ifndef __FUNCS_H__
#define __FUNCS_H__
#include "trello.h"
#include <fstream>
#define COMMAND "newcommand.txt"
char bring_menu(Trello& _trello,istream& in,ostream& out);
void signup_interface(Trello& _trello,ostream& out,istream& in);
void login_interface(Trello& _trello,istream& in,ostream& out);
void event_check(char c,Trello& _trello,ostream& out,istream& in);
void create_board_interface(Trello& _trello);
void enter_board_interface(Trello& _trello,istream& in,ostream& out);
void add_user_interface(Trello& _trello,istream& in,ostream& out);
void remove_user_interface(Trello& _trello,istream& in,ostream& out);
void show_lists_interface(Trello& _trello,istream& in,ostream& out);
void remove_board_interface(Trello& _trello,istream& in,ostream& out);
void remove_list_interface(Trello& _trello,istream& in,ostream& out);
void add_list_interface(Trello& _trello,istream& in,ostream& out);
void add_card_interface(Trello& _trello,istream& in,ostream& out);
void remove_list_interface(Trello& _trello,istream& in,ostream& out);
void move_card_interface(Trello& _trello,istream& in,ostream& out);
void show_my_cards_interface(Trello& _trello,istream& in,ostream& out);
void rename_card_interface(Trello& _trello,istream& in,ostream& out);
void edit_card_description_interface(Trello& _trello,istream& in,ostream& out);
void remove_user_from_a_card_interface(Trello& _trello,istream& in,ostream& out);
void filter_interface(Trello& _trello,istream& in,ostream& out);
void comment_interface(Trello&_trello,istream& in,ostream& out);
void process(Trello& _trello,istream& in,ostream& out);
void initialize(Trello& _trello);
void clear_file(const char* input);
void call_write(string c);
void find_exp(string errorcode);
template<typename T>
void write_to_file(const char* file_name,T data){
    ofstream myfile;
    myfile.open (file_name,ios_base::app);
    myfile <<data<<endl;
    myfile.close();
}
void remove_line_from_file(const char* input,string data);
vector<string> get_description(istream& in,ostream& out);
Card* edit_card_interface(Trello& _trello,istream& in,ostream& out);
Member* find_member_interface(Trello& _trello,istream& in,ostream& out);
#endif
