#ifndef ENTER_BOARD_H
#define ENTER_BOARD_H

#include <QDialog>
#include "client_socket.h"
#include <QMessageBox>
#include "entered_board_menu.h"
namespace Ui {
class enter_board;
}

class enter_board : public QDialog
{
    Q_OBJECT

public:
    explicit enter_board(QWidget *parent = 0);
    ~enter_board();
    ClientSocket* ecs;

    entered_board_menu* bm;


private slots:
    void on_buttonBox_accepted();

    void on_enter_board_rejected();

private:
    Ui::enter_board *ui;
    QMessageBox* err;
};

#endif // ENTER_BOARD_H
