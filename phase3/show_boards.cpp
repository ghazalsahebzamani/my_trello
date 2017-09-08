#include "show_boards.h"
#include "ui_show_boards.h"

show_boards::show_boards(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::show_boards)
{
    ui->setupUi(this);
}
void show_boards::set_text(string s){
    QString txt=QString::fromStdString(s);
    ui->mg->setText(txt);
}
show_boards::~show_boards()
{
    delete ui;
}
