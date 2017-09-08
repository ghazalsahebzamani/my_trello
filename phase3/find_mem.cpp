#include "find_mem.h"
#include "ui_find_mem.h"
#include <QLineEdit>
#include "funcs.h"
#include <QMessageBox>
#include "exp.h"
find_mem::find_mem(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::find_mem)
{
    ui->setupUi(this);
    found_user="";
}

find_mem::~find_mem()
{
    //delete ui;
}

void find_mem::on_buttonBox_accepted()
{

    try{
        QString qusername=ui->find->text();
        string username=qusername.toStdString();
        string command="check for member"+username;
        fcs->send(command);
        command=fcs->receive();
        //find_exp(command);
        if(command=="NotFound")
                throw NotFound();
        found_user=username;
        entered_board_menu* new_bm=new entered_board_menu;
        new_bm->ebcs=fcs;
        if(eb->add_ready==1){
        new_bm->added_user=username;
        }
        else if(eb->remove_ready==1)
            new_bm->removed_user=username;
        new_bm->show();
        hide();
        }
        catch(MyException& exp)
        {
            QMessageBox::critical(0,"error",exp.what());
            show();
        }

}
