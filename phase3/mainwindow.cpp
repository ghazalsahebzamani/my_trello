#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "signup.h"
#include "funcs.h"
#include <QDialog>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ss=new Signup(this);
    l=new Login;
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
//    delete s;
//    delete l;
    delete ui;
}



void MainWindow::on_pushButton_3_clicked()
{

    l->socket=mcs;
    l->setModal(true);
    l->show();
    hide();

}

void MainWindow::on_su_clicked()
{
    ss->cs=mcs;
    ss->setModal(true);
    ss->show();
    hide();


}

