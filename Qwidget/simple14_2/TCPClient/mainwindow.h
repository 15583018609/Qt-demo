#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QLabel>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actClear_triggered();
    void onSocketReadyRead();
    void onstateChanged(QAbstractSocket::SocketState state);
    void onDisConected();
    void onConected();
    void on_actConnect_triggered();

    void on_actDisconnect_triggered();

    void on_btnSend_clicked();

private:

    QLabel *labSocketState;
    QTcpSocket *tcpSocket;
    QString getLocalIP();
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
