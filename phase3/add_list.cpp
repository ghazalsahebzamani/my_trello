#include "add_list.h"
#include "ui_add_list.h"

add_list::add_list(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::add_list)
{
    ui->setupUi(this);
}

add_list::~add_list()
{
    delete ui;
}

void add_list::on_buttonBox_accepted()
{
  entered_board_menu* new_eb=new entered_board_menu;
    new_eb->list=ui->lineEdit ->text().toStdString();
    new_eb->ebcs=alcs;
    new_eb->show();
    hide();
}
