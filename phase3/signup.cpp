#include "signup.h"
#include "ui_signup.h"
#include "dialog.h"
#include "funcs.h"
#include "exp.h"
#include "mainwindow.h"
#include <QMessageBox>
Signup::Signup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Signup)
{
    ui->setupUi(this);
}

Signup::~Signup()
{
    delete ui;
}
//void Signup::on_lineEdit_name_editingFinished()
//{
//    QString name=ui->lineEdit_name->text();
//    string sname=name.toStdString();
//    if(sname.size() <3){
//       // QMessageBox* box;
//        QMessageBox::critical(0,"Error","Too short name.It should contain at least 3 charachters");
//        show();
//    }
//}

//void Signup::on_lineEdit_2_editingFinished()
//{
//    QString quser=ui->lineEdit_2->text();
//    string user=quser.toStdString();
//    try{

//        write_to_file<string>(COMMAND,user);
//        if(user.size()<3 && lineEdit_name->text().toStdString().size()>3)
//        {
//            throw ShortWord();
//        }
//        string command="check my username"+user;
//        cs->send(command);
//        string response=cs->receive();
//            if(response=="UserTaken()")
//            {
//                throw UserTaken();
//            }
//        }catch(MyException& exp){
//            QMessageBox::critical(0,"Error",exp.what());
//           show();
//    }
//}

//void Signup::on_lineEdit_3_editingFinished()
//{
//    QString qpass=ui->lineEdit_3->text();
//    string pass=qpass.toStdString();
//    if(pass.size() <6 && ui->lineEdit_2->text().toStdString().size()>3 && ui->lineEdit_name->text().toStdString().size()>3){
//       QMessageBox::critical(0,"Error","week pass.It should contain at least 6 charachters");
//       show();
//    }

//}

void Signup::on_signup_ok_accepted()
{
    QString name=ui->lineEdit_name->text();
    string sname=name.toStdString();
    QString quser=ui->lineEdit_2->text();
    string user=quser.toStdString();
    string pass=ui->lineEdit_3->text().toStdString();
    if(sname.size() <3){
       // QMessageBox* box;
        QMessageBox::critical(0,"Error","Too short name.It should contain at least 3 charachters");
        show();
   }
    if(user.size() <3){
       // QMessageBox* box;
        QMessageBox::critical(0,"Error","Too short username.It should contain at least 3 charachters");
        show();
    }
    if(pass.size() <6){
       // QMessageBox* box;
        QMessageBox::critical(0,"Error","Too week password.It should contain at least 6 charachters");
        show();
   }
    else if(ui->lineEdit_name->text().toStdString().size()>2 && ui->lineEdit_2->text().toStdString().size()>2 && ui->lineEdit_3->text().toStdString().size()>5)
    {

try{
    string command="check my username"+user;
    cs->send(command);
    string response=cs->receive();
    if(response=="UserTaken()")
       {
           throw UserTaken();
       }
    command="my name:"+sname;
    cs->send(command);
    cs->receive();
    command="my user:"+user;
    cs->send(command);
    command=cs->receive();
    command="my pass:"+pass;
    cs->send(command);
    cs->receive();
    command="create user.name:"+sname+"user:"+user+"pass:"+pass;
    cs->send(command);
    cs->receive();
    MainWindow* w=new MainWindow;
    w->mcs=cs;
    w->show();
    hide();
    write_to_file<string>(COMMAND,"1");
    write_to_file<string>(COMMAND,sname);
    write_to_file<string>(COMMAND,user);
    write_to_file<string>(COMMAND,pass);
    return;
        }catch(MyException& exp){
                QMessageBox::critical(0,"Error",exp.what());
               show();
        }


    }
}

void Signup::on_Signup_rejected()
{
    MainWindow* w=new MainWindow;
    w->mcs=cs;
    w->show();
    hide();
}
