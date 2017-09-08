#include "list.h"
#include "exp.h"
void List::add_card(string title,int card_index,Member* admin){
    Card* new_card=new Card(title,card_index);
    new_card->add_user(admin);
    cards.push_back(new_card);
}
void List::remove_card(int number){

    Card* deleted=find_card(number);
    delete deleted;
    delete_card(number);
}
void List::filter_cards(vector<Member*> users,string des_check,string cm_check,ostream& out){
    cerr<<"ok2?dc:"<<des_check<<"cc:"<<cm_check<<endl;
    int num_of_mems_not_found=0;
    for(int i=0;i<users.size();i++){
        try{
            show_member_cards(users[i],des_check,cm_check,out);}
            catch(NoMemFound& exp){
                num_of_mems_not_found++;
            }
    }
    if(num_of_mems_not_found==users.size())
        throw NoCardsFound();
}
void List::delete_card(int number){
    for(int i=0;i<cards.size();i++)
    {
        if(cards[i]->get_num()==number)
            cards.erase(cards.begin()+i);
    }
}
void List::delete_all_cards(){
    for(int i=0;i<cards.size();i++)
        {
            cards[i]->delete_cms();
            delete cards[i];
        }
}
void List::add_previously_created_card(Card* created_card){
    cards.push_back(created_card);

}
void List::rename_card(int card_num,string new_title){
    Card* found_card=find_card(card_num);
    found_card->rename(new_title);
}
Card* List::find_card(int number)
{
    for(int i=0;i<cards.size();i++)
    {
        if(cards[i]->get_num()==number)
            return cards[i];
    }
    throw NotFound();
}
void List::show_member_cards(Member* user,string des_check,string cm_check,ostream& out)
{
    int mem_not_found=0;
    for(int i=0;i<cards.size();i++)
    {
        try{
            cards[i]->show_member_card(user,des_check,cm_check,out);
        }catch(MyException& exp){
            mem_not_found++;
        }
    }
    if(mem_not_found==cards.size())
        throw NoMemFound();
}
