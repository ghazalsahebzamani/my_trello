#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
using namespace std;
void getfolan(istream& in,ostream& out){
	string kooft;
	int dard;
	in>>kooft>>dard;
	out<<kooft<<dard<<endl;

}
void signup_interface(ostream& out,istream& in){
	string name,user,pass;
	while(true)
	{
			out<<"pls enter your name"<<endl;	
					in>>name;
					break;
	}
			out<<"pls enter your password"<<endl;
			while(true)
			{
					in>>pass;
					break;
			}
			return;
}
void client_show_my_cards_interface(istream& in,ostream& out){
	out<<"show comments?y/n"<<endl;
	string s1,s2;
	while(true)
	{
		try
		{	
			in>>s1;
			cerr<<"s1:"<<s1<<endl;
			in>>s2;
			cerr<<"s2:"<<s2<<endl;
			if(s1.size()>1 ||(s1[0]!='y' && s1[0]!='n')) 
				throw "BadIO()";
			if(s2.size()>1 ||(s2[0]!='y' && s2[0]!='n')) 
				throw "BadIO()";
			break;
		}catch(string& exp)
		{
			out<<"exp.what()"<<endl;
		}
	}	
}

int main(){
	string s1="y";
	string s2="n";
	ofstream outfile;
	outfile.open("tmpp.txt");
	outfile<<s1<<endl;
	outfile<<s2<<endl;
	outfile.close();
	ifstream in;

	in.open("tmpp.txt");

	client_show_my_cards_interface(in,cout);
	in.close();
	outfile.open("tmpp.txt");
	outfile.close();

	//client_show_my_cards_interface(in,cout);
      //   //_trello.login(user,pass);
      //   //out<<"Hello "<<_trello.get_current()->get_name()<<'!'<<endl;
      //   //send(identifier,out.str());
      //   cerr<<out.str();
      // }
      // catch(DoesntExist& exp)
      // { 
      // send(identifier,"DoesntExist");

      // }

}