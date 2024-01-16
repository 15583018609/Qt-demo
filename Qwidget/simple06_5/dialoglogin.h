#ifndef DIALOGLOGIN_H
#define DIALOGLOGIN_H

#include <QDialog>
#include <QMouseEvent>
namespace Ui {
class DialogLogin;
}

class DialogLogin : public QDialog
{
    Q_OBJECT

public:
    explicit DialogLogin(QWidget *parent = nullptr);
    ~DialogLogin();

private slots:
    void on_btnOK_clicked();

private:
    Ui::DialogLogin *ui;
    QString m_user;
    QString m_pswd;
    int m_tryCount = 0;
    bool m_moving = false;
    QPoint m_lastPos;

    void writeSettings();
    void readSettings();
    QString encrypt(const QString &str);

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

};

#endif // DIALOGLOGIN_H
