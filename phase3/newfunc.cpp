#include "newfuncs.h"
#include <sstream>
#include <fstream>
#include "exp.h"
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
void call_write(string c){
    write_to_file(COMMAND,c);
}
void client_signup_interface(ClientSocket& socket,ostream& out,istream& in){
    string name,user,pass,command;
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
            out<<"pls enter your username"<<endl;
            while(true)
            {
                try{
                    in>>user;
                    write_to_file<string>(COMMAND,user);
                    if(user.size()<3){
                        throw ShortWord();
                    }
                    command="check my username"+user;
                    socket.send(command);
                    string response=socket.receive();
                        if(response=="UserTaken()")
                        {
                            throw UserTaken();
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
            command="my name:"+name;
            socket.send(command);
            socket.receive();
            command="my user:"+user;
            socket.send(command);
            socket.receive();
            command="my pass:"+pass;
            socket.send(command);
            socket.receive();
            command="create user.name:"+name+"user:"+user+"pass:"+pass;
            socket.send(command);
            socket.receive();
            return;
    }
}
void client_login_interface(ClientSocket& socket,istream& in,ostream& out){
    string user,pass;
    out<<"pls enter your user name and password"<<endl;
    while(true){
        try
        {
            string command;
            in>>user>>pass;
            write_to_file<string>(COMMAND,user);
            write_to_file<string>(COMMAND,pass);
            command="login/user:"+user+"pass:"+pass;
            socket.send(command);
            command=socket.receive();
            find_exp(command);
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
                        client_signup_interface(socket,out,in);
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

void client_logout(ClientSocket& socket,istream& in,ostream& out){
    string command="logout";
    socket.send(command);
}
void client_create_board_interface(ClientSocket& socket,istream& in,ostream& out){
    out<<"pls enter a title for your board"<<endl;
    string title;
    in>>title;
    write_to_file<string>(COMMAND,title);
    string command="create board"+title;
    socket.send(command);
    return;
}
void client_show_boards(ClientSocket& socket,istream& in,ostream& out){
    string command="show boards";
    socket.send(command);
    command=socket.receive();
    cout<<command;
}
void find_exp(string errorcode){
        if(errorcode=="You don't have the permission to access the following")
            throw BadAccess();
        if(errorcode=="invalid input!try again.")
            throw BadIO();
        if(errorcode=="already taken.choose a different one")
            throw UserTaken();
        if(errorcode=="input should conain at least 3 carachters.try again.")
            throw ShortWord();
        if(errorcode=="week password.It should contain at least 6 characters.try again.")
            throw WeakPass();
        if(errorcode=="invalid login.user/pass doesnt exist.try again:t back to menu:b register:r")
            throw DoesntExist();
        if(errorcode=="the desired was not found")
            throw NotFound();
        if(errorcode=="not a number!")
            throw NotaNumber();
}
void  client_enter_board_interface(ClientSocket& socket,istream& in,ostream& out){
    out<<"enter the number of the board you want to enter"<<endl;
    int num;
    try{
        in>>num;
        write_to_file<int>(COMMAND,num);
        if(in.fail())
        {
            throw NotaNumber();
        }
        string command="enter board"+Tools::itos(num);
        socket.send(command);
        command=socket.receive();
        find_exp(command);
    }catch(MyException& exp){
        out<<exp.what()<<endl;
    }

    return;
}
void  client_add_user_interface(ClientSocket& socket,istream& in,ostream& out){
    string command="check access";
    socket.send(command);
    command=socket.receive();
    try
    {
        if(command=="BadAccess")
            throw BadAccess();
    string username=client_find_member_interface(socket,in,out);
    command="add member"+username;
    socket.send(command);
    command=socket.receive();
    find_exp(command);
    }catch(MyException& exp)
    {
        out<<exp.what()<<endl;
    }

}
string client_find_member_interface(ClientSocket& socket,istream& in,ostream& out){
    string username;
    out<<"pls enter the user name of the member"<<endl;
    in>>username;
    write_to_file<string>(COMMAND,username);
    string command="check for member"+username;
    socket.send(command);
    command=socket.receive();
    if(command=="NotFound")
        throw NotFound();
    return username;

}
void client_remove_user_interface(ClientSocket& socket,istream& in,ostream& out){

    try
    {
        string command="check access";
        socket.send(command);
        command=socket.receive();
        if (command=="BadAccess")
            throw BadAccess();
        string user=client_find_member_interface(socket,in,out);
        command="remove user"+user;
        socket.send(command);
        command=socket.receive();
        find_exp(command);
    }
    catch(MyException& exp)
    {
        out<<exp.what()<<endl;
    }

}
void  client_show_lists_interface(ClientSocket& socket,istream& in,ostream& out){
    string command="show lists";
    socket.send(command);
    command=socket.receive();
    out<<command;

}
void client_remove_board_interface(ClientSocket& socket,istream& in,ostream& out){
    try{
        out<<"enter the number of the board you want to remove"<<endl;
        int n;
        in>>n;
        write_to_file<int>(COMMAND,n);
        if(in.fail())
            throw NotaNumber();
        string s_num=Tools::itos(n);
        string command="remove board"+s_num;
        socket.send(command);
        command=socket.receive();
        find_exp(command);
    }catch(MyException& exp){
        out<<exp.what()<<endl;
    }
}
void client_remove_list_interface(ClientSocket& socket,istream& in,ostream& out){
    try{
        out<<"pls enter the number of the list you want to remove"<<endl;
        int n;
        in>>n;
        write_to_file<int>(COMMAND,n);
        if(in.fail())
            throw NotaNumber();
        string snum=Tools::itos(n);
        string command="remove list"+snum;
        socket.send(command);
        command=socket.receive();
        find_exp(command);
    }catch(MyException& exp){
        out<<exp.what()<<endl;
    }
}
void client_add_list_interface(ClientSocket& socket,istream& in,ostream& out){
    out<<"pls enter the title for the list you want to make"<<endl;
    string title;
    in>>title;
    write_to_file<string>(COMMAND,title);
    string command="add list"+title;
    socket.send(command);
    socket.receive();
}
void client_find_list(ClientSocket& socket,int list_num){
        string command="find list";
        string snum=Tools::itos(list_num);
        command=command+snum;
        socket.send(command);
        command=socket.receive();
        find_exp(command);
    }
void client_add_card_interface(ClientSocket& socket,istream& in,ostream& out){
    out<<"pls enter the number of the list you want to add a new card to"<<endl;
    int list_num;
    string title;
    try{
        in>>list_num;
        write_to_file<int>(COMMAND,list_num);
        if(in.fail())
            throw NotaNumber();
        client_find_list(socket,list_num);
        out<<"pls enter the card title"<<endl;
        in>>title;
        write_to_file<string>(COMMAND,title);
        string command="add card"+Tools::itos(list_num)+"title:"+title;
        socket.send(command);
        command=socket.receive();
        find_exp(command);
    }catch(MyException& exp){
        out<<exp.what()<<endl;
    }

}
void client_remove_card_interface(ClientSocket& socket,istream& in,ostream& out){
    int card_num;
    string command="remove card";
    try{
        out<<"pls enter the card number"<<endl;
        in>>card_num;
        write_to_file<int>(COMMAND,card_num);
        if(in.fail())
            throw NotaNumber();
        command=command+Tools::itos(card_num);
        socket.send(command);
        command=socket.receive();
        find_exp(command);
        }
    catch(MyException& exp){
        out<<exp.what()<<endl;
    }
}
void client_move_card_interface(ClientSocket& socket,istream& in,ostream& out){
    int first_list;
    int second_list;
    int card_num;
    try{
        out<<"pls enter the second list number"<<endl;
        in>>second_list;
        write_to_file<int>(COMMAND,second_list);
        if(in.fail())
            throw NotaNumber();
        client_find_list(socket,second_list);
        out<<"pls enter the card number"<<endl;
        in>>card_num;
        write_to_file<int>(COMMAND,card_num);
        if(in.fail())
            throw NotaNumber();
        string command="move card.2list:"+Tools::itos(second_list)+"cardnum:"+Tools::itos(card_num);
        socket.send(command);
        command=socket.receive();
        find_exp(command);
    }catch(MyException& exp){
        out<<exp.what()<<endl;
    }
}
string client_edit_card_interface(ClientSocket& socket,istream& in,ostream& out){
        int card_num;
        out<<"pls enter the number of the card you wish to edit"<<endl;
        in>>card_num;
        write_to_file<int>(COMMAND,card_num);
        if(in.fail())
            throw NotaNumber();
        string command="find card"+Tools::itos(card_num);
        socket.send(command);
        command=socket.receive();
        find_exp(command);
        return Tools::itos(card_num);
}
void client_rename_card_interface(ClientSocket& socket,istream& in,ostream& out){
try{
        string s_card_num=client_edit_card_interface(socket,in,out);
        out<<"pls enter the new title for your card"<<endl;
        string title;
        in>>title;
        write_to_file<string>(COMMAND,title);
        string command="rename card.cardnum:"+s_card_num+"title"+title;
        socket.send(command);
        command=socket.receive();
        find_exp(command);
    }catch(MyException& exp){
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
void client_edit_card_description_interface(ClientSocket& socket,istream& in,ostream& out){
    try{
        string found_card=client_edit_card_interface(socket,in,out);
        in.ignore();
        vector<string> new_des=get_description(in,out);
        string command="edit card des.card num:"+found_card;
        command=command+"des:";
        for(int i=0;i<new_des.size();i++){
            command=command+new_des[i];
            command.push_back('$');
        }
        socket.send(command);
        command=socket.receive();
        find_exp(command);
    }catch(MyException& exp){
        out<<exp.what()<<endl;
    }
}
void client_assign_user_interface(ClientSocket& socket,istream& in,ostream& out){
    try
    {
        string found_card=client_edit_card_interface(socket,in,out);
        string user=client_find_member_interface(socket,in,out);
        string command="assign user.cardnum:"+found_card+"user:"+user;
        socket.send(command);
        command=socket.receive();
        find_exp(command);
    }catch(MyException& exp){
        out<<exp.what()<<endl;
    }
}
void client_remove_user_from_card_interface(ClientSocket& socket,istream& in,ostream& out){
    string username;
    try{
        string found_card=client_edit_card_interface(socket,in,out);
        string user=client_find_member_interface(socket,in,out);
        string command="remove user from card.cardnum:"+found_card+"user:"+user;
        socket.send(command);
        command=socket.receive();
        find_exp(command);
    }catch(MyException& exp){
        out<<exp.what()<<endl;
    }
}
string client_show_cms_des_interface(istream& in,ostream& out){
    string s;
    while(true)
    {
        try
        {
            in>>s;
            if(s.size()>1 ||(s[0]!='y' && s[0]!='n'))
                throw BadIO();
            return s;
        }catch(MyException& exp)
        {
            out<<exp.what()<<endl;
        }
    }
}
void client_show_my_cards_interface(ClientSocket& socket,istream& in,ostream& out){
try{
        out<<"show description?y/n"<<endl;
        string s_des=client_show_cms_des_interface(in,out);
        out<<"show comments?y/n"<<endl;
        string s_cms=client_show_cms_des_interface(in,out);
        socket.send("show cards.des?"+s_des+"cms?"+s_cms);
        string command=socket.receive();
        find_exp(command);
        cout<<command;
    }catch(MyException& exp){
        out<<exp.what()<<endl;
    }
}
void client_filter_interface(ClientSocket& socket,istream& in,ostream& out){
    out<<"pls enter the member usernames subsequently"<<endl;
    try
    {
        in.ignore();
        vector<string> usernames=get_description(in,out);
        //out<<"show description?y/n"<<endl;
        out<<"show comments?y/n"<<endl;
        string s=client_show_cms_des_interface(in,out);
        //out<<"show comments?y/n"<<endl;
        //string s_cms=client_show_cms_des_interface(in,out);
        string command="filter"+s+"users:";
        for(int i=0;i<usernames.size();i++)
        {
            command=command+usernames[i];
            command.push_back('$');
        }
        socket.send(command);
        command=socket.receive();
        find_exp(command);
        cout<<command;
    }catch(MyException& exp){
        out<<exp.what()<<endl;
    }
}
void comment_interface(ClientSocket& socket,istream& in,ostream& out){
try{
        string found_card=client_edit_card_interface(socket,in,out);
        string command="comment.cardnum:"+found_card+"content:";
        in.ignore();
        vector<string> des=get_description(in,out);
        for(int i=0;i<des.size();i++){
            command=command+des[i];
            command.push_back('^');
        }
        socket.send(command);
        command=socket.receive();
        find_exp(command);
    }catch(MyException& exp){
        out<<exp.what()<<endl;
    }
}
void client_event_check(char c,ClientSocket& socket,ostream& out,istream& in){
    switch(c)
    {
        case '1': client_signup_interface(socket,out,in);
            break;
        case '2': client_login_interface(socket,in,out);
            break;
        case '3': client_logout(socket,in,out);
            break;
        case '4': client_create_board_interface(socket,in,out);
            break;
        case '5': client_show_boards(socket,in,out);
            break;
        case '6': client_enter_board_interface(socket,in,out);
            break;
        case '7': client_add_user_interface(socket,in,out);
            break;
        case '8' : client_remove_user_interface(socket,in,out);
            break;
        case '9' : client_show_lists_interface(socket,in,out);
            break;
        case 'r' : client_remove_board_interface(socket,in,out);
            break;
        case 'l' : client_remove_list_interface(socket,in,out);
            break;
        case 'n' : client_add_list_interface(socket,in,out);
            break;
        case 'a' : client_add_card_interface(socket,in,out);
            break;
        case 'b' : client_remove_card_interface(socket,in,out);
            break;
        case 'm' : client_move_card_interface(socket,in,out);
            break;
        case 'c' : client_rename_card_interface(socket,in,out);
            break;
        case 'd' : client_edit_card_description_interface(socket,in,out);
            break;
        case 'u' : client_assign_user_interface(socket,in,out);
            break;
        case 'f' : client_remove_user_from_card_interface(socket,in,out);
            break;
        case 'e' : client_show_my_cards_interface(socket,in,out);
            break;
        case 'g' : client_filter_interface(socket,in,out);
            break;
        case 'h' : comment_interface(socket,in,out);
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
