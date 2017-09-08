#ifndef SIGNUP_H
#define SIGNUP_H

#include <QDialog>
#include <QLineEdit>
#include "client_socket.h"
namespace Ui {
class Signup;
}

class Signup : public QDialog
{
    Q_OBJECT

public:
    explicit Signup(QWidget *parent = 0);
    ~Signup();
     ClientSocket* cs;

private slots:
//    void on_lineEdit_cursorPositionChanged(int arg1, int arg2);


//    void on_lineEdit_name_returnPressed();

//    void on_lineEdit_2_cursorPositionChanged(int arg1, int arg2);

//    void on_lineEdit_3_returnPressed();

//    void on_buttonBox_accepted();

//    void on_signup_ok_clicked(QAbstractButton *button);



//    void on_lineEdit_name_editingFinished();

//    void on_lineEdit_2_editingFinished();

//    void on_lineEdit_3_editingFinished();

    void on_signup_ok_accepted();


    void on_Signup_rejected();

private:
    Ui::Signup *ui;
    QLineEdit* lineEdit_name;
    int fields_checked;
};

#endif // SIGNUP_H
