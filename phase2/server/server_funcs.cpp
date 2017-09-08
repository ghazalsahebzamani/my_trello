#include <iostream>
#include "server_funcs.h"
#include "Myserver.h"
#include "tools.h"
#include "funcs.h"
using namespace std;
char bring_menu2(Trello &_trello,ostream& out){
  if(_trello.get_current()==NULL)
  {
    out<<"what do you want to do?"<<endl;
    out<<"sign up:1"<<endl;
    out<<"log in:2"<<endl;
  }
  else{
    out<<"logout: 3"<<endl;
    out<<"create board: 4"<<endl;
    out<<"show boards: 5"<<endl;
    out<<"enter_board: 6"<<endl;
    out<<"remove board: r"<<endl;
  }
  if(_trello.get_current_board()!=NULL)
  {
    out<<"add user: 7"<<endl;
    out<<"remove user from board: 8"<<endl;
    out<<"show lists: 9"<<endl;
    out<<"add new list: n"<<endl;
    out<<"remove list: l"<<endl;
    out<<"add card to a list: a"<<endl;
    out<<"remove a card from a list: b"<<endl;
    out<<"move a card from one list to another: m"<<endl;
    out<<"rename a card: c"<<endl;
    out<<"edit a card description: d"<<endl;
    out<<"assign user to a card: u"<<endl;
    out<<"remove a user from a card:f"<<endl;
    out<<"show my cards: e"<<endl;
    out<<"filter cards by member names: g"<<endl;
    out<<"comment a card: h"<<endl;
  }
  out<<"quit: q"<<endl;
}
void start(Trello &_trello,stringstream& out,int identifier){
  _trello.show_current(out);
  _trello.show_current_board(out);
  bring_menu2(_trello,out);
  send(identifier,out.str());
}
void s_check_order(Trello &_trello,string message,int identifier){
  string c=message;
  if((c[14]!='1' && c[14]!='2' && c[14]!='q' && _trello.get_current()==NULL)|| (c[14]!='3' && c[14]!='q' && c[14]!='4' && c[14]!='5' && c[14]!='6' && c[14]!='r' && _trello.get_current()!=NULL && _trello.get_current_board()==NULL)||
      (c[14]!='7'&& c[14]!='8' && c[14]!='9'&& c[14]!='a' && c[14]!='h' && c[14]!='u' && c[14]!='g' && c[14]!='f' && c[14]!='c'&& c[14]!='d' && c[14]!='e' &&  c[14]!='m'&& c[14]!='b'&& c[14]!='r' && c[14]!='n' &&c[14]!='l' && c[14]!='q' && c[14]!='3' && c[14]!='4' && c[14]!='5' && c[14]!='6' && _trello.get_current_board()!=NULL && _trello.get_current()!=NULL))
  {
    send(identifier,"BadIO error!");
  }
  else
  send(identifier,"ok");
}
void s_get_name(string message,int identifier){
  size_t pos=message.find("my name:");
  string name=message.substr(pos+8);
  send(identifier,"ok");
}
void s_get_user(string message,int identifier){
  size_t pos=message.find("my user:");
  string user=message.substr(pos+8);
  send(identifier,"ok");
}
void s_get_pass(string message,int identifier){
  size_t pos=message.find("my pass:");
  string pass=message.substr(pos+8);
  send(identifier,"ok");
}
void s_check_username(string message,int identifier){
  size_t pos=message.find("check my username");
  string user=message.substr(pos+17);
  user_check(identifier,user);
  send(identifier,"ok");
}
void s_create_user(Trello &_trello,stringstream& out,string message,int identifier){
  size_t pos1=message.find("user:");
  name=message.substr(17,pos1-17);
  size_t pos2=message.find("pass:");
  user=message.substr(pos1+5,pos2-pos1-5);
  pass=message.substr(pos2+5);
  _trello.create_user(name,user,pass);
}
void s_login(Trello& _trello,stringstream& out,string message,int identifier){
  string user,pass;
  size_t pos1=message.find("login/user:");
  string userpass=message.substr(pos1+11);
  size_t pos2=userpass.find("pass:");
  pass=userpass.substr(pos2+5);
  user=userpass.substr(0,pos2);
  try{
    _trello.login(user,pass);
    out<<"Hello "<<_trello.get_current()->get_name()<<'!'<<endl;
    send(identifier,out.str());
  }
  catch(DoesntExist& exp)
  { 
   out<<exp.what(); 
  send(identifier,out.str());
  }
}
void s_create_board(Trello& _trello,string message,int identifier){
  string title=message.substr(12);
  _trello.create_board(title);
  send(identifier,"ok");
  }
void s_show_boards(Trello& _trello,stringstream& out,int identifier){
  _trello.show_boards(out);
 send(identifier,out.str());
}
void s_enter_board(Trello& _trello,stringstream& out,string message,int identifier){
  string snum=message.substr(11);
  int num=Tools::mystoi(snum);
  try
  {
    for(int i=0;i<_trello.get_boards().size();i++)
    {
      if(_trello.get_boards()[i]->get_num()==num)
      {
        _trello.enter_board(num);
        Msend(identifier,"ok");
        return;
      }
    }
    throw NotFound();
  }
  catch(MyException& exp){
    out<<exp.what();
    send(identifier,out.str());
  }
}
void s_check_for_member(Trello& _trello,string message,int identifier){
  try
    {
    string username=message.substr(16);
    _trello.find_member(username);
    send(identifier,"ok");
    }
  catch(NotFound& exp){
    MyServer::send(identifier,"NotFound");
  }
}
void s_add_member(Trello& _trello,string message,int identifier){
  string username=message.substr(10);
  Member* user=_trello.find_member(username);
  _trello.get_current_board()->add_user(user);
  send(identifier,"ok");
}
void s_remove_user(Trello& _trello,stringstream& out,string message,int identifier){
 try
  {
    string username=message.substr(11);
    Member* user=_trello.find_member(username);
    _trello.get_current_board()->remove_user_from_board(user);
    send(identifier,"ok");
  }
  catch(MyException& exp)
  {
    out<<exp.what()<<endl;
    send(identifier,out.str());
  }
}
void s_check_access(Trello& _trello,int identifier){
 if(_trello.get_current()!=_trello.get_current_board()->get_admin())
      send(identifier,"BadAccess");
  else
    send(identifier,"ok"); 
}
void s_remove_board(Trello& _trello,stringstream& out,string message,int identifier){
  try{
      string s_num=message.substr(12);
      int num=Tools::mystoi(s_num);
      _trello.remove_board(num);
      send(identifier,"ok");
    }catch(MyException& exp){
      out<<exp.what();
      send(identifier,out.str());
    }
}
void s_remove_list(Trello& _trello,stringstream& out,string message,int identifier){
try{
    string snum=message.substr(11);
    int n=Tools::mystoi(snum);
    _trello.get_current_board()->remove_list(n);
    send(identifier,"ok");
  }catch(MyException& exp)
  {
    out<<exp.what();
    send(identifier,out.str());
  }
}
void s_add_list(Trello& _trello,string message,int identifier){
  string title=message.substr(8);
  int list_num=_trello.calc_newlist_num();
  _trello.get_current_board()->add_list(title,list_num); 
  send(identifier,"ok"); 
}
void s_find_list(Trello& _trello,stringstream& out,string message,int identifier){
  try
   { 
    string s_num=message.substr(9);
    int list_num=Tools::mystoi(s_num);
    _trello.get_current_board()->find_list(list_num);
    send(identifier,"ok");
    }catch(MyException& exp){
      out<<exp.what();
      send(identifier,out.str());
  }
}
void s_add_card(Trello& _trello,stringstream& out,string message,int identifier){
  try{
      size_t pos1=message.find("title");
      string title=message.substr(pos1+5);
      string s_num=message.substr(8,pos1-8);
      int list_num=Tools::mystoi(s_num);
      List* found_list=_trello.get_current_board()->find_list(list_num);
      int card_num=_trello.get_current_board()->calc_newcard_index();
      found_list->add_card(title,card_num,_trello.get_current());
      send(identifier,"ok");
    }catch(MyException& exp){
      out<<exp.what();
      send(identifier,out.str());
  }
}
void s_remove_card(Trello& _trello,stringstream& out,string message,int identifier){
  try
  {
    string snum=message.substr(11);
    int card_num=Tools::mystoi(snum);
    List* found_list=_trello.get_current_board()->find_the_list_containing_card(card_num);
    found_list->remove_card(card_num);
    send(identifier,"ok");
  }catch(MyException& exp){
    out<<exp.what();
    send(identifier,out.str());
  }
}
void s_move_card(Trello& _trello,stringstream& out,string message,int identifier){
 try
 {
    size_t pos1=message.find("cardnum:");
    string snum=message.substr(16,pos1-16);
    int second_list=Tools::mystoi(snum);
    string s_cardnum=message.substr(pos1+8);
    int card_num=Tools::mystoi(s_cardnum);
    List* secondlist=_trello.get_current_board()->find_list(second_list);
    List* firstlist=_trello.get_current_board()->find_the_list_containing_card(card_num);
    _trello.get_current_board()->move_card(firstlist,secondlist,card_num);
    send(identifier,"ok");
  }catch(MyException& exp){
    out<<exp.what();
    send(identifier,out.str());
  } 
}
void s_find_card(Trello& _trello,stringstream& out,string message,int identifier){
  try
  { 
    string snum=message.substr(9);
    int card_num=Tools::mystoi(snum);
     _trello.get_current_board()->find_the_list_containing_card(card_num);
    send(identifier,"ok");
  }
  catch(MyException& exp){
    out<<exp.what();
    send(identifier,out.str());
  }
}
void s_rename_cards(Trello& _trello,stringstream& out,string message,int identifier){
  try
  {
    size_t pos1=message.find("title");
    string s_cardnum=message.substr(20,pos1-20);
    int card_num=Tools::mystoi(s_cardnum);
    string title=message.substr(pos1+5);
    List* found_list= _trello.get_current_board()->find_the_list_containing_card(card_num);
    Card* found_card=found_list->find_card(card_num);
    found_card->rename(title);
    send(identifier,"ok");
  }
  catch(MyException& exp){
    out<<exp.what();
    send(identifier,out.str());
  }
}
void s_edit_card_des(Trello& _trello,stringstream& out,string message,int identifier){
  try
  {
    size_t pos1=message.find("des:");
    string s_cardnum=message.substr(23,pos1-23);
    int card_num=Tools::mystoi(s_cardnum);
    List* found_list= _trello.get_current_board()->find_the_list_containing_card(card_num);
    Card* found_card=found_list->find_card(card_num);
    string des_data=message.substr(pos1+4);
    vector<string> new_des;
    new_des=Tools::split(des_data,'$');
    found_card->edit_des(new_des);
    send(identifier,"ok");
  }
  catch(MyException& exp){
    out<<exp.what();
    send(identifier,out.str());
  }
}
void s_assign_user(Trello& _trello,stringstream& out,string message,int identifier){
  size_t pos1=message.find("user:");
  string s_cardnum=message.substr(20,pos1);
  int card_num=Tools::mystoi(s_cardnum);
  string username=message.substr(pos1+5);
  try
  {
    Member* user=_trello.find_member(username);
    bool found=0;
    for(int i=0;i<_trello.get_current_board()->get_board_members().size();i++)
      if(_trello.get_current_board()->get_board_members()[i]==user)
      { found=1;
        break;
        }
    if(found==0)
      throw NotFound();
    List* found_list=_trello.get_current_board()->find_the_list_containing_card(card_num);
    Card* found_card=found_list->find_card(card_num);   
    found_card->add_user(user);
    send(identifier,"ok");
  }catch(MyException& exp){
    out<<exp.what();
    send(identifier,out.str());
  } 
}
void s_remove_user_from_card(Trello& _trello,stringstream& out,string message,int identifier){
  size_t pos1=message.find("user:");
  string s_cardnum=message.substr(30,pos1);
  int card_num=Tools::mystoi(s_cardnum);
  string username=message.substr(pos1+5);
  try
  {
    List* found_list=_trello.get_current_board()->find_the_list_containing_card(card_num);
    Card* found_card=found_list->find_card(card_num);   
    Member* user=_trello.find_member(username);
    found_card->remove_user(user->get_user());
    send(identifier,"ok");
  }catch(MyException& exp){
    out<<exp.what();
    send(identifier,out.str());
  } 
}
void s_show_cards(Trello& _trello,stringstream& out,string message,int identifier){
  size_t pos1=message.find("cms?");
  string s_des=message.substr(15,pos1-15);
  string s_cms=message.substr(pos1+4);
  try{
    Member* user=_trello.get_current();
    _trello.get_current_board()->show_member_lists(user,s_des,s_cms,out);
    send(identifier,out.str());
  }catch(MyException& exp){
    out<<exp.what();
    send(identifier,out.str());
  } 
}
void s_filter(Trello& _trello,stringstream& out,string message,int identifier){
  size_t pos1=message.find("users:");
  string s=message.substr(6,pos1-6);
  string usernames_line=message.substr(pos1+6);
  vector<string> usernames=Tools::split(usernames_line,'$');
  vector<Member*> users;
  try
  {
    for(int i=0;i<usernames.size();i++)
    {
      Member* found_member=_trello.find_member(usernames[i]);
      users.push_back(found_member);
    }
    _trello.get_current_board()->filter_lists(users,"y",s,out);
    send(identifier,out.str());
  }catch(MyException& exp){
    out<<exp.what();
    send(identifier,out.str());
  }
}
void s_comment(Trello& _trello,stringstream& out,string message,int identifier){
  try{
      size_t pos1=message.find("content:");
      string s_cardnum=message.substr(16,pos1-16);
      int card_num=Tools::mystoi(s_cardnum);
      List* found_list=_trello.get_current_board()->find_the_list_containing_card(card_num);
      Card* found_card=found_list->find_card(card_num);
      string comment_line=message.substr(pos1+8);
      vector<string> des=Tools::split(comment_line,'^');
      found_card->comment(found_card,_trello.get_current(),des);
      send(identifier,"ok");
    }catch(MyException& exp){
      out<<exp.what();
      send(identifier,out.str());
  }
}