#ifndef ADD_NEW_MEMBER_H
#define ADD_NEW_MEMBER_H

#include <QDialog>

namespace Ui {
class add_new_member;
}

class add_new_member : public QDialog
{
    Q_OBJECT

public:
    explicit add_new_member(QWidget *parent = 0);
    ~add_new_member();

private:
    Ui::add_new_member *ui;
};

#endif // ADD_NEW_MEMBER_H
