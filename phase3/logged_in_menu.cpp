#include "ui_logged_in_menu.h"
#include "QLabel"
#include "QTextBrowser"
#include "logged_in_menu.h"
#include "exp.h"
#include "funcs.h"
#include "dialog.h"
#include "find_mem.h"
using namespace std;
logged_in_menu::logged_in_menu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::logged_in_menu)
{
    ui->setupUi(this);
    create_board=new Dialog(this);
    sb=new show_boards(this);
    eb=new enter_board(this);
//    fm=new find_mem(this);

}

logged_in_menu::~logged_in_menu()
{
    delete ui;
}

void logged_in_menu::set_text(string s)
{
       ui->label_2->setText(QString::fromStdString(s)) ;
}

void logged_in_menu::on_pushButton_cb_clicked()
{

    create_board->dcs=lcs;
    create_board->setModal(true);
    create_board->show();
    hide();

}

void logged_in_menu::on_pushButton_clicked()
{
    string command="show boards";
    lcs->send(command);
    command=lcs->receive();
    //QString txt=QString::fromStdString(command);
    sb->set_text(command);
    sb->show();
    hide();
}

void logged_in_menu::on_pushButton_2_clicked()
{

  eb->ecs=lcs;
  eb->setModal(true);
   eb->show();
   hide();
}



