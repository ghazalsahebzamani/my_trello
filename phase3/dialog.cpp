#include "dialog.h"
#include "ui_dialog.h"
#include "funcs.h"
#include "logged_in_menu.h"
#include "exp.h"
using namespace std;
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}
void Dialog::on_pushButton_clicked()
{
    try{
    string title=ui->lineEdit->text().toStdString();
    write_to_file<string>(COMMAND,"4");
    write_to_file<string>(COMMAND,title);
    string command="create board"+title;
    dcs->send(command);
    logged_in_menu* lm=new logged_in_menu;
    lm->lcs=dcs;
    lm->set_text("menu:");
    lm->setModal(true);
    lm->show();
    hide();
    return;
    }catch(MyException& exp){

    }

}
