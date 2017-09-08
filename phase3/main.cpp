#include <QApplication>
#include <QCoreApplication>
#include <QtCore>
#include "mainwindow.h"
#include "client_socket.h"
//#include "tools.h"
#include "funcs.h"
#include <QDebug>
#include <iostream>
using namespace std;
int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    ClientSocket* socket=new ClientSocket("127.0.0.1",8787);
    socket->send("start");
    string c=socket->receive();
    MainWindow* w=new MainWindow;
    w->mcs=socket;

         w->show();
//             w->show();
//         else
//         w->hide();
    //QString qc = QString::fromStdString(c);
    //qDebug()<<qc;
    return a.exec();
}
