#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
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

protected:
    void closeEvent(QCloseEvent *event);
private:

    QLabel *labListen;
    QLabel *labSocketState;
    QTcpServer *tcpServer;
    QTcpSocket *tcpSocket;

    QString getLocalIP();

    Ui::MainWindow *ui;
private slots:
    void onSocketReadyRead();
    void onstateChanged(QAbstractSocket::SocketState state);
    void onClientDisConected();
    void onClientConected();
    void onNewConnected();
    void on_actStart_triggered();
    void on_actStop_triggered();
    void on_actClear_triggered();
    void on_btnSend_clicked();
};
#endif // MAINWINDOW_H
