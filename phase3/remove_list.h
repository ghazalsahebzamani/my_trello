#ifndef REMOVE_LIST_H
#define REMOVE_LIST_H

#include <QDialog>
#include "client_socket.h"
#include "entered_board_menu.h"
namespace Ui {
class remove_list;
}

class remove_list : public QDialog
{
    Q_OBJECT

public:
    explicit remove_list(QWidget *parent = 0);
    ~remove_list();
    entered_board_menu* eb;
    ClientSocket* rlcs;

private slots:
    void on_buttonBox_accepted();

private:
    Ui::remove_list *ui;
};

#endif // REMOVE_LIST_H
