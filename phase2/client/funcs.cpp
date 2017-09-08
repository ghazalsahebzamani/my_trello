#include <sstream>
#include <fstream>
#include "funcs.h"
#include "exp.h"
#define COMMAND "newcommand.txt"
#define LAST_COMMAND_FILE "command.txt"
void just_append_new_commands_to_previous(const char* prev_file,const char* newfile){
	ofstream out;
	out.open(prev_file);
	string s;
	ifstream in;
	in.open(newfile);
	while(getline(in,s)){
		out<<s<<endl;
	}
	in.close();
	ofstream out2;
	out2.open(newfile);
	out2.close();
}
void clear_file(const char* input){
	ofstream out;
	out.open(input);
	out.close();

}
void remove_line_from_file(const char* input,string data){
	ifstream infile;
	infile.open(input);
	ofstream tempfile;
	tempfile.open("temp2.txt");
	string s;
	while(getline(infile,s))
	{
		if(s!=data)
		{
			tempfile<<s<<endl;
		}
	}
	infile.close();
	tempfile.close();
	ofstream outfile;
	ifstream tmp2;
	tmp2.open("temp2.txt");
	outfile.open(input);
	while(getline(tmp2,s)){
		outfile<<s<<endl;
	}
	tmp2.close();
	outfile.close();
}
template<typename T>
void write_to_file(const char* file_name,T data){
    ofstream myfile;
    myfile.open (file_name,ios_base::app);
    myfile <<data<<endl;
    myfile.close();
}
char bring_menu(Trello &_trello,istream& in,ostream& out){
	string c;
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

	while(true)
	{
		try
		{
			in>>c;
			if(c=="")
				return c[0];
			write_to_file<string>(COMMAND,c);
			if((c.size()>1)||(c[0]!='1' && c[0]!='2' && c[0]!='q' && _trello.get_current()==NULL)|| (c[0]!='3' && c[0]!='q' && c[0]!='4' && c[0]!='5' && c[0]!='6' && c[0]!='r' && _trello.get_current()!=NULL && _trello.get_current_board()==NULL)||
				(c[0]!='7'&& c[0]!='8' && c[0]!='9'&& c[0]!='a' && c[0]!='h' && c[0]!='u' && c[0]!='g' && c[0]!='f' && c[0]!='c'&& c[0]!='d' && c[0]!='e' &&  c[0]!='m'&& c[0]!='b'&& c[0]!='r' && c[0]!='n' &&c[0]!='l' && c[0]!='q' && c[0]!='3' && c[0]!='4' && c[0]!='5' && c[0]!='6' && _trello.get_current_board()!=NULL && _trello.get_current()!=NULL))
				throw BadIO();
			return c[0];
		}
		catch(BadIO& exp)
		{
			out<<exp.what()<<endl;
		}
	}

}
void signup_interface(Trello& _trello,ostream& out,istream& in){
	string name,user,pass;
	while(true)
	{
			out<<"pls enter your name"<<endl;
			while(true)
			{
				try{	
					in>>name;
					write_to_file<string>(COMMAND,name);
					if(name.size()<3){
						throw ShortWord();
					}
					break;
				}catch(ShortWord& exp){
					out<<exp.what()<<endl;
				}
			}
			//write_to_file(signup_membernames,name);
			out<<"pls enter your username"<<endl;
			while(true)
			{
				try{
					in>>user;
					write_to_file<string>(COMMAND,user);
					if(user.size()<3){
						throw ShortWord();
					}
					for(int i=0;i<_trello.get_members().size();i++)
					{
						if(_trello.get_members()[i]->get_user()==user)
						{
							throw UserTaken();
						}

					}
					break;
				}catch(MyException& exp){
					out<<exp.what()<<endl;
				}
			}
			out<<"pls enter your password"<<endl;
			while(true)
			{
				try
				{
					in>>pass;
					write_to_file<string>(COMMAND,pass);
					if(pass.size()<6)
					{	
						throw WeakPass();
					}
					break;
				}catch(WeakPass& exp){
					out<<exp.what()<<endl;
				}
			}
			//write_to_file(signup_memberpass,pass)
			_trello.create_user(name,user,pass);
			return;
	}
}
void login_interface(Trello& _trello,istream& in,ostream& out){
	string user,pass;
	out<<"pls enter your user name and password"<<endl;
	while(true)
	{
		try
		{
			in>>user>>pass;
			write_to_file<string>(COMMAND,user);
			write_to_file<string>(COMMAND,pass);
			_trello.login(user,pass);
			out<<"Hello "<<_trello.get_current()->get_name()<<'!'<<endl;
			return;

		}
		catch(DoesntExist& exp)
		{	
			out<<exp.what()<<endl;
			string c;
			while(true)
			{
				try
				{
					in>>c;
					write_to_file<string>(COMMAND,c);
					if((c[0]!='t' && c[0]!='b' & c[0]!='r')|| c.size()>1)
					{
						throw BadIO();

					}
					else if(c[0]=='r')
					{
						signup_interface(_trello,out,in);
						return;
					}
					else if(c[0]=='b')
					{
						return;
					}
					else if(c[0]=='t')
					{
						break;
					}
				}
				catch(BadIO& exp){
					out<<exp.what()<<endl;
				}
			}
		}

	}

}
void create_board_interface(Trello &_trello,istream& in,ostream& out)
{
	out<<"pls enter a title for your board"<<endl;
	string title;
	in>>title;
	write_to_file<string>(COMMAND,title);
	_trello.create_board(title);
	return;


}
void enter_board_interface(Trello &_trello,istream& in,ostream& out){
	out<<"enter the number of the board you want to enter"<<endl;
	int num;
	try{
		in>>num;
		write_to_file<int>(COMMAND,num);
		if(in.fail())
		{
			throw NotaNumber();
		}

		for(int i=0;i<_trello.get_boards().size();i++)
		{
			if(_trello.get_boards()[i]->get_num()==num)
			{
				_trello.enter_board(num);
				return;
			}
		}
		throw NotFound();
	}catch(MyException& exp){
		out<<exp.what()<<endl;
	}
	
	return;


}
void add_user_interface(Trello &_trello,istream& in,ostream& out){
	try
	{
		if(_trello.get_current()!=_trello.get_current_board()->get_admin())
			throw BadAccess();
		Member* user=find_member_interface(_trello,in,out);
		_trello.get_current_board()->add_user(user);
		string s="board no:";
		int board_no=_trello.get_current_board()->get_num();
	}catch(MyException& exp)
	{
		out<<exp.what()<<endl;
	}

}
void remove_user_interface(Trello& _trello,istream& in,ostream& out){
	try
	{
		if(_trello.get_current()!=_trello.get_current_board()->get_admin())
		{
			throw BadAccess();
		}
		Member* user=find_member_interface(_trello,in,out);
		_trello.get_current_board()->remove_user_from_board(user);
		//remove_line_from_file(usernames_added_to_the_board,user->get_user());
	}
	catch(MyException& exp)
	{
		out<<exp.what()<<endl;
	}
}
void show_lists_interface(Trello& _trello,istream& in,ostream& out){
	_trello.get_current_board()->show_lists(out);

}
void remove_board_interface(Trello& _trello,istream& in,ostream& out){
	try{
		out<<"enter the number of the board you want to remove"<<endl;
		int n;
		in>>n;
		write_to_file<int>(COMMAND,n);
		if(in.fail())
			throw NotaNumber();
		_trello.remove_board(n);
	}catch(MyException& exp){
		out<<exp.what()<<endl;
	}
}
void remove_list_interface(Trello& _trello,istream& in,ostream& out){
	try{
		out<<"pls enter the number of the list you want to remove"<<endl;
		int n;
		in>>n;
		write_to_file<int>(COMMAND,n);
		if(in.fail())
			throw NotaNumber();
		_trello.get_current_board()->remove_list(n);

	}catch(MyException& exp){
		out<<exp.what()<<endl;
	}
}
void add_list_interface(Trello& _trello,istream& in,ostream& out){
	out<<"pls enter the title for the list you want to make"<<endl;
	string title;
	in>>title;
	write_to_file<string>(COMMAND,title);
	int list_num=_trello.calc_newlist_num();
	_trello.get_current_board()->add_list(title,list_num);
}
void add_card_interface(Trello& _trello,istream& in,ostream& out){
	out<<"pls enter the number of the list you want to add a new card to"<<endl;
	int list_num;
	string title;
	try{
		in>>list_num;
		write_to_file<int>(COMMAND,list_num);
		if(in.fail())
			throw NotaNumber();
		List* found_list=_trello.get_current_board()->find_list(list_num);
		int card_num=_trello.get_current_board()->calc_newcard_index();
		out<<"pls enter the card title"<<endl;
		in>>title;
		write_to_file<string>(COMMAND,title);
		found_list->add_card(title,card_num,_trello.get_current());
	}catch(MyException& exp){
		out<<exp.what()<<endl;
	}
}
void remove_card_interface(Trello& _trello,istream& in,ostream& out){
	int card_num;
	try{
		out<<"pls enter the card number"<<endl;
		in>>card_num;
		write_to_file<int>(COMMAND,card_num);
		List* found_list=_trello.get_current_board()->find_the_list_containing_card(card_num);
		if(in.fail())
			throw NotaNumber();
		found_list->remove_card(card_num);

		}
	catch(MyException& exp){
		out<<exp.what()<<endl;
	}
}
vector<string> get_description(istream& in,ostream& out){
	string s;
	vector<string> des;
	out<<"pls enter the txt below:"<<endl;
	do {
		in.clear();
	 	getline(in, s);
	 	des.push_back(s);
		} while (s.size() > 0);
		des.pop_back();
		for(int i=0;i<des.size();i++)
			write_to_file<string >(COMMAND,des[i]);
	return des;
}
void move_card_interface(Trello& _trello,istream& in,ostream& out){
	int first_list;
	int second_list;
	int card_num;
	try{
		out<<"pls enter the second list number"<<endl;
		in>>second_list;
		write_to_file<int>(COMMAND,second_list);
		if(in.fail())
			throw NotaNumber();
		List* secondlist=_trello.get_current_board()->find_list(second_list);
		out<<"pls enter the card number"<<endl;
		in>>card_num;
		write_to_file<int>(COMMAND,card_num);
		if(in.fail())
			throw NotaNumber();
		List* firstlist=_trello.get_current_board()->find_the_list_containing_card(card_num);
		_trello.get_current_board()->move_card(firstlist,secondlist,card_num);
	}catch(MyException& exp){
		out<<exp.what()<<endl;
	}
}
void edit_card_description_interface(Trello& _trello,istream& in,ostream& out){
	try{
		Card* found_card=edit_card_interface(_trello,in,out);
		in.ignore();
		vector<string> new_des=get_description(in,out);
		found_card->edit_des(new_des);
	}catch(MyException& exp){
		out<<exp.what()<<endl;
	}

}
Card* edit_card_interface(Trello& _trello,istream& in,ostream& out){
	int card_num;
	out<<"pls enter the number of the card you wish to edit"<<endl;
	in>>card_num;
	write_to_file<int>(COMMAND,card_num);
	if(in.fail())
		throw NotaNumber();
	List* found_list= _trello.get_current_board()->find_the_list_containing_card(card_num);
	return found_list->find_card(card_num);
}
void rename_card_interface(Trello& _trello,istream& in,ostream& out){
	try{
		Card* found_card=edit_card_interface(_trello,in,out);
		out<<"pls enter the new title for your card"<<endl;
		string title;
		in>>title;
		write_to_file<string>(COMMAND,title);
		found_card->rename(title);
	}catch(MyException& exp){
		out<<exp.what()<<endl;
	}
}
void assign_user_interface(Trello& _trello,istream& in,ostream& out){
	try
	{
		bool found=0;
		Card* found_card=edit_card_interface(_trello,in,out);		
		Member* user=find_member_interface(_trello,in,out);
		// get_board_members().size();j++)
		// 		if(boards[i]->get_board_members()[j]==current )
		for(int i=0;i<_trello.get_current_board()->get_board_members().size();i++)
			if(_trello.get_current_board()->get_board_members()[i]==user)
			{	found=1;
				break;
			}
		if(found==0)
			throw NotFound();	
		found_card->add_user(user);
	}catch(MyException& exp){
		out<<exp.what()<<endl;
	}
}
Member* find_member_interface(Trello& _trello,istream& in,ostream& out){
	string username;
	out<<"pls enter the user name of the member"<<endl;
	in>>username;
	write_to_file<string>(COMMAND,username);
	Member* user=_trello.find_member(username);
	return user;

}
void remove_user_from_card_interface(Trello& _trello,istream& in,ostream& out){
	string username;
	try{
		Card* found_card=edit_card_interface(_trello,in,out);
		Member* user=find_member_interface(_trello,in,out);
		found_card->remove_user(user->get_user());
	}catch(MyException& exp){
		out<<exp.what()<<endl;
	}
}
void filter_interface(Trello& _trello,istream& in,ostream& out){
	vector<Member*> users;
	out<<"pls enter the member usernames subsequently"<<endl;
	try
	{
		in.ignore();
		vector<string> usernames=get_description(in,out);
		for(int i=0;i<usernames.size();i++)
		{
			Member* found_member=_trello.find_member(usernames[i]);
			users.push_back(found_member);
		}
		string des_check,cm_check;
		out<<"show description?y/n"<<endl;
		in>>des_check;
		out<<"show comments?y/n"<<endl;
		in>>cm_check;	
	_trello.get_current_board()->filter_lists(users,des_check,cm_check,out);
	}catch(MyException& exp){
		out<<exp.what()<<endl;
	}	
}
void show_my_cards_interface(Trello& _trello,istream& in,ostream& out){
	try{
		string des_check,cm_check;
		out<<"show description?y/n"<<endl;
		in>>des_check;
		out<<"show comments?y/n"<<endl;
		in>>cm_check;
		Member* user=_trello.get_current();
		_trello.get_current_board()->show_member_lists(user,des_check,cm_check,out);
	}catch(MyException& exp){
		out<<exp.what()<<endl;
	}
}
void comment_interface(Trello&_trello,istream& in,ostream& out){
	try{
		Card* found_card=edit_card_interface(_trello,in,out);
		in.ignore();
		vector<string> des=get_description(in,out);
		found_card->comment(found_card,_trello.get_current(),des);
	}catch(MyException& exp){
		out<<exp.what()<<endl;
	}
}
void process(Trello& _trello,istream& in,ostream& out){
	_trello.show_current(out);
	_trello.show_current_board(out);
	char c;
	c=bring_menu(_trello,in,out);
	event_check(c,_trello,out,in);	
}
void initialize(Trello& _trello)
{
	ifstream in;
	ofstream out;
	int num_of_lines=0;
	in.open(LAST_COMMAND_FILE);
	out.open("temp3.txt");
	string s;
	while(getline(in,s))
	{
		
		num_of_lines++;
	}
	if(num_of_lines==0)
		return;
	in.close();
	in.open(LAST_COMMAND_FILE);
	int t=0;
	while(true)
	{
		process(_trello,in,out);
		if(in.eof())
		{
			in.close();
			out.close();
			return;
		}
	}

}

void event_check(char c,Trello& _trello,ostream& out,istream& in){
	switch(c)
	{
		case '1': signup_interface(_trello,out,in);
			break;
		case '2': login_interface(_trello,in,out);
			break;
		case '3': _trello.logout();
			break;
		case '4': create_board_interface(_trello,in,out);
			break;
		case '5':_trello.show_boards(out);
			break;
		case '6': enter_board_interface(_trello,in,out);
			break;
		case '7': add_user_interface(_trello,in,out);
			break;
		case '8' : remove_user_interface(_trello,in,out);
			break;
		case '9' : show_lists_interface(_trello,in,out);
			break;
		case 'r' : remove_board_interface(_trello,in,out);
			break;
		case 'l' : remove_list_interface(_trello,in,out);
			break;
		case 'n' : add_list_interface(_trello,in,out);
			break;
		case 'a' : add_card_interface(_trello,in,out);
			break;
		case 'b' : remove_card_interface(_trello,in,out);
			break;
		case 'm' : move_card_interface(_trello,in,out);
			break;
		case 'c' : rename_card_interface(_trello,in,out);
			break;
		case 'd' : edit_card_description_interface(_trello,in,out);
			break;
		case 'u' : assign_user_interface(_trello,in,out);
			break;
		case 'f' : remove_user_from_card_interface(_trello,in,out);
			break;
		case 'e' : show_my_cards_interface(_trello,in,out);
			break;
		case 'g' : filter_interface(_trello,in,out);
			break;
		case 'h' : comment_interface(_trello,in,out);
			break;															
		case 'q': remove_line_from_file(COMMAND,"q");
		
		// if(_trello.get_current()!=NULL)
		// {
		// 	write_to_file(COMMAND,"3") ;///logout!
		// }
		 just_append_new_commands_to_previous(LAST_COMMAND_FILE,COMMAND);
		 throw Quit();
	}
}