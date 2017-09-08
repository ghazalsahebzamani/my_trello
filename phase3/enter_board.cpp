#include "enter_board.h"
#include "ui_enter_board.h"
#include "tools.h"
#include "logged_in_menu.h"
#include "exp.h"
#include "funcs.h"
#include <QMessageBox>
using namespace std;
enter_board::enter_board(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::enter_board)
{
    ui->setupUi(this);
    err=new QMessageBox(this);
    bm=new entered_board_menu(this);
}

enter_board::~enter_board()
{
//    delete err;
    delete ui;
}
void enter_board::on_buttonBox_accepted()
{
    string snum=ui->lineEdit->text().toStdString();
       try{
            for(int i=0;i<snum.size();i++)
            {
                if(snum[i]>57 || snum[i]<48 || (snum[i]==48 && snum.size()>1) )
                    {
                    throw NotaNumber();
                    }
            }
            int num=Tools::mystoi(snum);
            string command="enter board"+snum;
            ecs->send(command);
            command=ecs->receive();
            find_exp(command);
            write_to_file<string>(COMMAND,"6");
            write_to_file<int>(COMMAND,num);
            bm->setModal(true);
            bm->ebcs=ecs;
            bm->show();
            hide();
        }catch(MyException& exp){
            QMessageBox::critical(0,"Error",exp.what());
            show();

        }

        return;

}

void enter_board::on_enter_board_rejected()
{
    logged_in_menu* lm=new logged_in_menu;
    lm->lcs=ecs;
    lm->set_text("menu:");
    lm->setModal(true);
    lm->show();
    hide();
}
