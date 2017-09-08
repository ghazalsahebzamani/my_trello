#include "board.h"
#include "exp.h"
void Board::add_user(Member* new_mem){
	board_members.push_back(new_mem);
}
void Board::filter_lists(vector<Member*> users,istream& in,ostream& out){
	for(int i=0;i<lists.size();i++)
		lists[i]->filter_cards(users,in,out);
}
void Board::remove_user_from_board(Member* user)
{
	for(int i=0;i<board_members.size();i++)
	{
		if(board_members[i]==user)
			board_members.erase(board_members.begin()+i);
		return;
	}
	throw NotFound();
}
void Board::show_member_lists(Member* user,istream& in,ostream& out){
	for(int i=0;i<lists.size();i++)
	{
		lists[i]->show_member_cards(user,in,out);
	}
}
void Board::add_list(string title,int list_num){
	List* new_list=new List(title,list_num);
	lists.push_back(new_list);
}
void Board::show_lists(ostream& out){
	if(lists.size()==0)
		out<<"no lists to show!"<<endl;
	for(int i=0;i<lists.size();i++)
		out<<"list number: "<<lists[i]->get_num()<<" title: "<<lists[i]->get_title()<<endl;
}
int Board::calc_newcard_index(){
	int max=0;
	for(int i=0;i<lists.size();i++)
	{
		for(int j=0;j<lists[i]->get_cards().size();j++)
		{
			if(lists[i]->get_cards()[j]->get_num()>max)
				max=lists[i]->get_cards()[j]->get_num();
		}
	}
	max++;
	return max;
}
void Board::show_cards(int list_num,ostream& out){
	for(int i=0;i<lists.size();i++)
	{
		if(lists[i]->get_num()==list_num)
		{
			if(lists[i]->get_cards().size()==0)
				out<<"no cards to show"<<endl;
			for(int j=0;j<lists[i]->get_cards().size();j++)
			{
				out<<"card number: "<<lists[i]->get_cards()[j]->get_num()<<" title: "<<lists[i]->get_cards()[j]->get_title()<<endl;
			}
			return;
		}
	}
	out<<"list not found!"<<endl;
}
void Board::delete_all_lists(){
	for(int i=0;i<lists.size();i++)
	{ 
		lists[i]->delete_all_cards();
		delete lists[i];
	}
}
void Board::remove_list(int list_num)
{
	for(int i=0;i<lists.size();i++)
	{
		if(lists[i]->get_num()==list_num)
		{
			delete lists[i];
			lists.erase(lists.begin()+i);
			return;
		}
	}
	throw NotFound();

}
List* Board::find_list(int number){
	for(int i=0;i<lists.size();i++)
	{
		if(lists[i]->get_num()==number)
			return lists[i];
	}
	throw NotFound();
}
void Board::move_card(List* first_list,List* second_list,int card_num){
	Card* moved=first_list->find_card(card_num);
	second_list->add_previously_created_card(moved);
	first_list->delete_card(card_num);
}
List* Board::find_the_list_containing_card(int card_num){
	for(int i=0;i<lists.size();i++){
		for(int j=0;j<lists[i]->get_cards().size();j++){
			if(lists[i]->get_cards()[j]->get_num()==card_num)
				return lists[i];
		}
	}
	throw NotFound();
}
