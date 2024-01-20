#ifndef DIALOGPEN_H
#define DIALOGPEN_H
#include <QPen>
#include <QDialog>

namespace Ui {
class DialogPen;
}

class DialogPen : public QDialog
{
    Q_OBJECT

public:
    explicit DialogPen(QWidget *parent = nullptr);
    ~DialogPen();

    QPen getPen();
    void setPen(const QPen &pen);

    static QPen getPen(QPen initPen,bool &ok);
private slots:
    void on_btnColor_clicked();

private:

    QPen m_pen;
    Ui::DialogPen *ui;
};

#endif // DIALOGPEN_H
