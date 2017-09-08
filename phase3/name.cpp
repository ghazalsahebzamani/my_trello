#include "name.h"
#include "ui_name.h"

name::name(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::name)
{
    ui->setupUi(this);
}

name::~name()
{
    delete ui;
}
