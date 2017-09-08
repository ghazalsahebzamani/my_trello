#ifndef LOGIN_H
#define LOGIN_H
#include <QDialog>
#include "client_socket.h"
#include "logged_in_menu.h"
namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();
    ClientSocket* socket;
    logged_in_menu* menu;

private slots:
    void on_buttonBox_accepted();
    
    void on_Login_finished(int result);

private:
    Ui::Login *ui;
};

#endif // LOGIN_H
