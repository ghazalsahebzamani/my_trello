#include "add_new_member.h"
#include "ui_add_new_member.h"

add_new_member::add_new_member(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::add_new_member)
{
    ui->setupUi(this);
}

add_new_member::~add_new_member()
{
    delete ui;
}
