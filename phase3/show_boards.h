#ifndef SHOW_BOARDS_H
#define SHOW_BOARDS_H

#include <QDialog>
using namespace std;
namespace Ui {
class show_boards;
}

class show_boards : public QDialog
{
    Q_OBJECT

public:
    explicit show_boards(QWidget *parent = 0);
    void set_text(string s);
    ~show_boards();

private:
    Ui::show_boards *ui;
};

#endif // SHOW_BOARDS_H
