#include "trello.h"
#include "exp.h"
void Trello::create_user(string name,string user,string pass){
		Member* new_mem=new Member(name,user,pass);
		members.push_back(new_mem);
}
void Trello::show_current_board(ostream& out){
	if(current_board!=NULL)
		out<<"entered in board :"<<current_board->get_title()<<" with board number: "<<current_board->get_num()<<endl;
}
void Trello::login(string user,string pass){
	bool found=0;
		for(int i=0;i<members.size();i++)
		{
			if(members[i]->get_user()==user && members[i]->get_pass()==pass)
			{
				found=1;
				current=members[i];
				return;
			}
	}
	if(found==0)
		throw DoesntExist();
}
int Trello::calc_newlist_num(){
	int max=0;
	for(int i=0;i<boards.size();i++)
	{
		for(int j=0;j<boards[i]->get_lists().size();j++)
			{
				if(boards[i]->get_lists()[j]->get_num()>max)
					max=boards[i]->get_lists()[j]->get_num();
			}
	}
	max++;
	return max;
}
Trello::~Trello(){
	for(int i=0;i<boards.size();i++)
	{
		boards[i]->delete_all_lists();
		delete boards[i];
	}
	for(int i=0;i<members.size();i++)
		delete members[i];
}
Trello::Trello(const Trello& obj){
	for(int i=0;i<obj.members.size();i++)
	{
		Member* new_mem=new Member(obj.members[i]->get_name(),obj.members[i]->get_user(),obj.members[i]->get_pass());
		members.push_back(new_mem);
	}
	for(int i=0;i<obj.boards.size();i++)
	{
		Board* new_board=new Board(obj.boards[i]->get_title(),obj.boards[i]->get_num());
		new_board=obj.boards[i];
		boards.push_back(new_board);
	}
	for(int i=0;i<members.size();i++)
	{
		if(members[i]->get_user()==obj.current->get_user())
			current=members[i];
		break;
	}
}
void Trello::show_current(ostream& out){
	if(current!=NULL)
	out<<"logged in as: "<<current->get_user()<<endl;
}
void Trello::logout(){
	current=NULL;
	current_board=NULL;
}
void Trello::show_boards(ostream& out)
{
	bool found=0;
	for(int i=0;i<boards.size();i++)
	{
		for(int j=0;j<boards[i]->get_board_members().size();j++)
		{
			if(boards[i]->get_board_members()[j]==current)
			{
				out<<"board title: "<<boards[i]->get_title()<<"board number: "<<boards[i]->get_num()<<endl;
				found=1;
			}
		}
		if(boards[i]->get_admin()==current)
		{
			out<<"board title: "<<boards[i]->get_title()<<" board number: "<<boards[i]->get_num()<<endl;
			found=1;
		}
	}
	if(found==0)
	{
		out<<"no boards to show!"<<endl;
	}
}
void Trello::create_board(string title){
	int num=boards.size()+1;
	Board* new_board=new Board(title,num);
	new_board->set_admin(current);
	boards.push_back(new_board);
}
void Trello::remove_board(int board_number){
	for(int i=0;i<boards.size();i++)
	{
		if(boards[i]->get_num()==board_number)
		{
			if(current!=boards[i]->get_admin())
				throw BadAccess();
			boards.erase(boards.begin()+i);
			return;
		}
	}
	throw NotFound();
}
void Trello::enter_board(int n){
	for(int i=0;i<boards.size();i++)
	{

		if(boards[i]->get_num()==n)
		{
			for(int j=0;j<boards[i]->get_board_members().size();j++)
				if(boards[i]->get_board_members()[j]==current )
			{
				current_board=boards[i];
				return;
			}
			if(boards[i]->get_admin()==current)
			{
				current_board=boards[i];
				return;
			}
			throw BadAccess();
		}
	}
}
Member* Trello::find_member(string user){
	for(int i=0;i<members.size();i++){
		if(members[i]->get_user()==user)
			return members[i];
	}
	throw NotFound();

}
