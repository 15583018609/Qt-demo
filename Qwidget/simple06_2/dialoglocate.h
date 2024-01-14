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

    void setRange(int rows,int cols);
    void setValue(int rows,int cols);
    void closeEvent(QCloseEvent *event);

private slots:
    void on_btnSetText_clicked();

private:
    Ui::DialogLocate *ui;
};

#endif // DIALOGLOCATE_H
