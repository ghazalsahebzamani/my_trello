#ifndef __NEWFUNCS_H__
#define __NEWFUNCS_H__
#include "trello.h"
#include "client_socket.h"
#define COMMAND "newcommand.txt"
#define LAST_COMMAND_FILE "command.txt"
template<typename T>
void write_to_file(const char* file_name,T data);
void client_signup_interface(ClientSocket& socket,ostream& out,istream& in);
void client_event_check(char c,ClientSocket& socket,ostream& out,istream& in);
void call_write(string c);
void clear_file(const char* input);
void client_login_interface(ClientSocket& socket,istream& in,ostream& out);
void client_logout(ClientSocket& socket,istream& in,ostream& out);
void client_create_board_interface(ClientSocket& socket,istream& in,ostream& out);
void client_show_boards(ClientSocket& socket,istream& in,ostream& out);
void  client_enter_board_interface(ClientSocket& socket,istream& in,ostream& out);
void  client_add_user_interface(ClientSocket& socket,istream& in,ostream& out);
string client_find_member_interface(ClientSocket& socket,istream& in,ostream& out);
void client_remove_user_interface(ClientSocket& socket,istream& in,ostream& out);
void client_remove_board_interface(ClientSocket& socket,istream& in,ostream& out);
void client_remove_list_interface(ClientSocket& socket,istream& in,ostream& out);
void find_exp(string errorcode);
void client_add_list_interface(ClientSocket& socket,istream& in,ostream& out);
void client_add_card_interface(ClientSocket& socket,istream& in,ostream& out);
void client_find_list(ClientSocket& socket,int list_num);
void client_remove_card_interface(ClientSocket& socket,istream& in,ostream& out);
void client_move_card_interface(ClientSocket& socket,istream& in,ostream& out);
void client_rename_card_interface(ClientSocket& socket,istream& in,ostream& out);
string client_edit_card_interface(ClientSocket& socket,istream& in,ostream& out);
void client_edit_card_description_interface(ClientSocket& socket,istream& in,ostream& out);
vector<string> get_description(istream& in,ostream& out);
void client_assign_user_interface(ClientSocket& socket,istream& in,ostream& out);
void client_remove_user_from_card_interface(ClientSocket& socket,istream& in,ostream& out);
void client_show_my_cards_interface(ClientSocket& socket,istream& in,ostream& out);
void client_filter_interface(ClientSocket& socket,istream& in,ostream& out);
string client_show_cms_des_interface(istream& in,ostream& out);
void comment_interface(ClientSocket& socket,istream& in,ostream& out);
void remove_line_from_file(const char* input,string data);
void just_append_new_commands_to_previous(const char* prev_file,const char* newfile);
#endif