#include <fstream>
#include "funcs.h"
#include "exp.h"
int main()
{
	Trello _trello;
	initialize(_trello);
	clear_file("temp3.txt");
	while(true){
		try{
			process(_trello,cin,cout);
		}
		catch(Quit){
			cout<<"Goodbye!"<<endl;
			clear_file("temp2.txt");
			return 0;
		}

	}
}
