#ifndef NAME_H
#define NAME_H

#include <QWidget>

namespace Ui {
class name;
}

class name : public QWidget
{
    Q_OBJECT

public:
    explicit name(QWidget *parent = 0);
    ~name();

private:
    Ui::name *ui;
};

#endif // NAME_H
