#include "login.h"
#include "ui_login.h"
#include "funcs.h"
#include "newfuncs.h"
#include "exp.h"
#include <QMessageBox>
#include "logged_in_menu.h"
#include "mainwindow.h"
Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    menu=new logged_in_menu(this);
}

Login::~Login()
{
//    delete menu;
    delete ui;
}

void Login::on_buttonBox_accepted()
{
    try
        {
            string command;
            QString quser=ui->lineEdit->text();
            string user=quser.toStdString();
            QString qpass =ui->lineEdit_2->text();
            string pass=qpass.toStdString();
            command="login/user:"+user+"pass:"+pass;
            socket->send(command);
            command=socket->receive();
            find_exp(command);
             write_to_file(COMMAND,"2");
             write_to_file<string>(COMMAND,user);
             write_to_file<string>(COMMAND,pass);
             menu->lcs=socket;
             menu->set_text(command);
             menu->setModal(true);
             menu->show();
             hide();
            return;
    }
    catch(DoesntExist& exp)
            {
                 QMessageBox* box=new QMessageBox(this);
                 box->critical(0,"Error",exp.what());
                 box->setFixedSize(500,200);
                string c;
            }
    
}

void Login::on_Login_finished(int result)
{
    MainWindow* w=new MainWindow;
    w->mcs =socket;
    w->show();
    hide();
}
