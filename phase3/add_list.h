#ifndef ADD_LIST_H
#define ADD_LIST_H

#include <QDialog>
#include "client_socket.h"
#include "entered_board_menu.h"
namespace Ui {
class add_list;
}

class add_list : public QDialog
{
    Q_OBJECT

public:
    explicit add_list(QWidget *parent = 0);
    ~add_list();
    ClientSocket* alcs;
    entered_board_menu* eb;


private slots:
    void on_buttonBox_accepted();

private:
    Ui::add_list *ui;
};

#endif // ADD_LIST_H
