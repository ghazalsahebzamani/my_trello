#include "card.h"
#include "exp.h"
void Card::add_user(Member* user){
	mems.push_back(user);
	cerr<<"size?:"<<mems.size()<<endl;
}
void Card::remove_user(string user){
	for(int i=0;i<mems.size();i++)
	{
		if(mems[i]->get_user()==user)
		{
			mems.erase(mems.begin()+i);
			return;
		}
	}
	throw NotFound();
}
void Card::show_card(string des_check,string cm_check,ostream& out){
	string s;
	out<<"card number: "<<num<<" title: "<<title<<endl;
	//out<<"see description?y/n"<<endl;
	while(true)
	{
		try
		{	
			// in>>s;
			if(des_check.size()>1 ||(des_check[0]!='y' && des_check[0]!='n')) 
				throw BadIO();
			break;
		}catch(MyException& exp)
		{
			out<<exp.what()<<endl;
		}
	}
		switch(des_check[0])
		{
			case 'y':
			out<<"description: "<<endl;
			for(int i=0;i<des.size();i++)
				out<<des[i]<<endl;
			break;
		}
		//out<<"see comments?y/n"<<endl;
		while(true)
		{
			try
			{	
				// in>>s;
				if(cm_check.size()>1 ||(cm_check[0]!='y' && cm_check[0]!='n')) 
					throw BadIO();
				break;
			}catch(MyException& exp)
			{
				out<<exp.what()<<endl;
			}
		}
		switch(cm_check[0])
		{
			case 'y':see_cms(out);
			break;
		}
}
void Card::delete_cms(){
	for(int i=0;i<comments.size();i++)
		delete comments[i];

}
void Card::see_cms(ostream& out){
	for(int i=0;i<comments.size();i++)
	{
		out<<"comment number "<<i+1<<" :"<<endl;
		comments[i]->show_comment(out);
	}
}
void Card::comment(Card* card,Member* composer,vector<string> des){
	Comment* new_comment=new Comment(composer,des);
	comments.push_back(new_comment);
}
void Card::show_member_card(Member* user,string des_check,string cm_check,ostream& out){
	bool found=0;
	for(int i=0;i<mems.size();i++)
	{
		if(mems[i]==user){
			show_card(des_check,cm_check,out);
			found=1;		
		}
	}
	if(found==0)
		throw NoMemFound();
}