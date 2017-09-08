#ifndef __TRELLO_H__
#define __TRELLO_H__
#include "board.h"
class Trello{
    friend class Board;
public:
    Trello()
    {
         current=new Member("","","");
         current=NULL;
         current_board=NULL;
    }
 void create_user(string name,string user,string pass);
 void remove_board(int board_number);
 void show_current(ostream& out);
 int calc_newlist_num();
 void login(string user,string pass);
 void logout();
 void show_current_board(ostream& out);
 void enter_board(int n);
 void show_boards(ostream& out);
 void create_board(string title);
 Member* find_member(string user);
 Board* find_board();
 Member* get_current(){return current;}
 Board* get_current_board(){return current_board;}
 vector<Board*> get_boards(){return boards;}
 vector<Member*> get_members(){return members;}
 Trello(const Trello& obj);
 ~Trello();
private:
    vector<Member*> members;
    vector<Board*> boards;
    Member* current;
    Board* current_board;
};
#endif
