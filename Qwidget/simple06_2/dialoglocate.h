#ifndef DIALOGLOCATE_H
#define DIALOGLOCATE_H

#include <QDialog>

namespace Ui {
class DialogLocate;
}

class DialogLocate : public QDialog
{
    Q_OBJECT

public:
    explicit DialogLocate(QWidget *parent = nullptr);
    ~DialogLocate();

private:
    Ui::DialogLocate *ui;
};

#endif // DIALOGLOCATE_H
