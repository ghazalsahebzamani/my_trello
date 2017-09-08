#ifndef LOGGED_IN_MENU_H
#define LOGGED_IN_MENU_H

#include <QDialog>
#include "client_socket.h"
#include "dialog.h"
#include "enter_board.h"
#include "find_mem.h"
#include "show_boards.h"
using namespace std;
namespace Ui {
class logged_in_menu;
}

class logged_in_menu : public QDialog
{
    Q_OBJECT

public:
    explicit logged_in_menu(QWidget *parent = 0);
    ~logged_in_menu();
    ClientSocket* lcs;
    Dialog* create_board;
    show_boards* sb;
    enter_board* eb;
    find_mem* fm;
    void set_text(string s);
private slots:

    void on_pushButton_cb_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();


private:
//public:
    Ui::logged_in_menu *ui;
};

#endif // LOGGED_IN_MENU_H
