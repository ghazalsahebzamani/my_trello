#include "comment.h"
void Comment::show_comment(ostream& out){
	out<<"composer: "<<composer->get_name()<<endl;
	out<<"script:"<<endl;
	for(int i=0;i<text.size();i++)
		out<<text[i]<<endl;
}