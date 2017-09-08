#ifndef FIND_MEM_H
#define FIND_MEM_H

#include <QDialog>
#include "entered_board_menu.h"
#include "client_socket.h"
using namespace std;
namespace Ui {
class find_mem;
}

class find_mem : public QDialog
{
    Q_OBJECT

public:
    explicit find_mem(QWidget *parent = 0);
    ~find_mem();
    ClientSocket* fcs;
    string found_user;
   entered_board_menu* eb;


private slots:
    void on_buttonBox_accepted();

private:
    Ui::find_mem *ui;
};

#endif // FIND_MEM_H
