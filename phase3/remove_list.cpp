#include "remove_list.h"
#include "ui_remove_list.h"
#include <QLineEdit>
remove_list::remove_list(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::remove_list)
{
    ui->setupUi(this);
}

remove_list::~remove_list()
{
    delete ui;
}

void remove_list::on_buttonBox_accepted()
{
    entered_board_menu* new_eb=new entered_board_menu;
    new_eb->ebcs=rlcs;
    new_eb->rlist=ui->lineEdit->text().toStdString();
    new_eb->remove_ready=1;
    new_eb->show();
    hide();
}
