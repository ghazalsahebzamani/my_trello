#include "entered_board_menu.h"
#include "ui_entered_board_menu.h"
#include "exp.h"
#include "funcs.h"
#include <QMessageBox>
#include "add_list.h"
#include "find_mem.h"
#include "remove_list.h"
using namespace std;
entered_board_menu::entered_board_menu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::entered_board_menu)
{
    ui->setupUi(this);
    add_ready=0;
    remove_ready=0;
    list_ready=0;
    rlist_ready=0;

}

entered_board_menu::~entered_board_menu()
{
    delete ui;
}

void entered_board_menu::on_pushButton_clicked()
{
    try
    {
        add_ready=1;
        string command="check access";
            ebcs->send(command);
            command=ebcs->receive();
            if(command=="BadAccess")
                throw BadAccess();
            find_mem* fm=new find_mem;
            fm->fcs=ebcs;
                fm->setModal(true);
                fm->eb=this;
                fm->show();
                hide();

//            entered_board_menu::find_user_interface();
//            string username=user;
//            command="add member"+username;
//            ebcs->send(command);
//            command=ebcs->receive();
//            find_exp(command);
//            write_to_file<string>(COMMAND,"7");
//            write_to_file<string>(COMMAND,username);
            }catch(MyException& exp)
            {
               QMessageBox::critical(0,"error",exp.what());
            }
}

void entered_board_menu::find_user_interface(){
//    string command="check access";
//    ebcs->send(command);
//    command=ebcs->receive();
//    if(command=="BadAccess")
//        throw BadAccess();
//    find_mem* fm=new find_mem;
//    fm->fcs=ebcs;
//    fm->setModal(true);
    //fm->eb=this;
//    fm->show();
//    hide();

}

void entered_board_menu::on_pushButton_2_clicked()
{
    try
        {

       remove_ready=1;
       string command="check access";
       ebcs->send(command);
       command=ebcs->receive();
       if(command=="BadAccess")
           throw BadAccess();
       find_mem* fm=new find_mem;
       fm->fcs=ebcs;
           fm->setModal(true);
           fm->eb=this;
           fm->show();
           hide();

    }catch(MyException& exp)
        {
           QMessageBox::critical(0,"error",exp.what());
        }
}



void entered_board_menu::on_pushButton_3_clicked()
{
    string command="logout";
    ebcs->send(command);

}

void entered_board_menu::on_buttonBox_accepted()
{
    try{
 if(added_user.size()>0){  entered_board_menu::find_user_interface();
   string username=added_user;
   string command="add member"+username;
   ebcs->send(command);
   command=ebcs->receive();
   find_exp(command);
   write_to_file<string>(COMMAND,"7");
   write_to_file<string>(COMMAND,username);
   added_user="";
   add_ready=0;
 }
 else if(removed_user.size()>0){
     string username=removed_user;
     string command="remove user"+username;
     ebcs->send(command);
     command=ebcs->receive();
     find_exp(command);
     write_to_file<string>(COMMAND,"8");
     write_to_file<string>(COMMAND,username);
     removed_user="";
     remove_ready=0;
 }
 else if(list.size()>0){
 string command="add list"+list;
 ebcs->send(command);
 command=ebcs->receive();
 write_to_file<string>(COMMAND,"n");
 write_to_file<string>(COMMAND,list);
 list="";
 list_ready=0;

 }
 else if(rlist.size()>0){
 string command="remove list"+rlist;
 ebcs->send(command);
 command=ebcs->receive();
 write_to_file<string>(COMMAND,"l");
 write_to_file<int>(COMMAND,Tools::mystoi(rlist));
 rlist="";
 remove_ready=0;

 }
    }catch(MyException& exp)
    {
       QMessageBox::critical(0,"error",exp.what());
    }

}


void entered_board_menu::on_pushButton_addlist_clicked()
{
    list_ready=1;
    add_list* al=new add_list;
    al->alcs=ebcs;
    al->show();
    hide();
}

void entered_board_menu::on_pushButton_4_clicked()
{
    rlist_ready=1;
    remove_list* rl=new remove_list;
    rl->rlcs=ebcs;
    rl->show();
    hide();

}
