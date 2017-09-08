#ifndef ENTERED_BOARD_MENU_H
#define ENTERED_BOARD_MENU_H

#include <QDialog>
#include "client_socket.h"
using namespace std;
namespace Ui {
class entered_board_menu;
}

class entered_board_menu : public QDialog
{
    Q_OBJECT

public:
    explicit entered_board_menu(QWidget *parent = 0);
    ~entered_board_menu();
    ClientSocket* ebcs;
    string added_user;
    string removed_user;
    string list;
    string rlist;
    bool add_ready;
    bool remove_ready;
    bool list_ready;
    bool rlist_ready;


private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void find_user_interface();

    void on_buttonBox_accepted();
    void on_pushButton_addlist_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::entered_board_menu *ui;
};

#endif // ENTERED_BOARD_MENU_H
