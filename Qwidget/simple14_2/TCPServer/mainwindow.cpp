#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QHostInfo>
#include <QByteArray>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    labListen = new QLabel("监听状态: ");
    labListen->setMinimumWidth(200);
    ui->statusBar->addWidget(labListen);
    labSocketState = new QLabel("Socked状态: ");
    labSocketState->setMinimumWidth(200);
    ui->statusBar->addWidget(labSocketState);

    setWindowTitle("服务器: "+getLocalIP());

    tcpServer = new QTcpServer(this);

    connect(tcpServer,SIGNAL(newConnection()),this,SLOT(onNewConnected()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(tcpServer->isListening()){
        tcpServer->close();
    }
    event->accept();
}

QString MainWindow::getLocalIP()
{
    QString hostName =QHostInfo::localHostName();
    QHostInfo hostInfo = QHostInfo::fromName(hostName);
    QString localIP = "";
    QList<QHostAddress>addList= hostInfo.addresses();
    if(addList.isEmpty()) return localIP;
    foreach(auto aHost,addList){
        if(aHost.protocol()==QAbstractSocket::IPv4Protocol){
            localIP =aHost.toString();
            break;
        }
    }
    return localIP;
}

void MainWindow::onSocketReadyRead()
{
    while(tcpSocket->canReadLine()){
        ui->plainTextEdit->appendPlainText("[IN]"+tcpSocket->readLine());
    }
}

void MainWindow::onstateChanged(QAbstractSocket::SocketState state)
{
    switch (state) {
    case QAbstractSocket::UnconnectedState:
        labSocketState->setText("socket状态: UnconnectedState");break;
    case QAbstractSocket::HostLookupState:
        labSocketState->setText("socket状态: HostLookupState");break;
    case QAbstractSocket::ConnectingState:
        labSocketState->setText("socket状态: ConnectingState");break;
    case QAbstractSocket::ConnectedState:
        labSocketState->setText("socket状态: ConnectedState");break;
    case QAbstractSocket::BoundState:
        labSocketState->setText("socket状态: BoundState");break;
    case QAbstractSocket::ListeningState:
        labSocketState->setText("socket状态: ListeningState");break;
    case QAbstractSocket::ClosingState:
        labSocketState->setText("socket状态: ClosingState");break;
    default:
        break;
    }
}

void MainWindow::onClientDisConected()
{
     ui->plainTextEdit->appendPlainText("**client socket diconnected");
     tcpSocket->deleteLater();
}

void MainWindow::onClientConected()
{
    ui->plainTextEdit->appendPlainText("**client socket connected");
    ui->plainTextEdit->appendPlainText("**peer address: "+tcpSocket->peerAddress().toString());
    ui->plainTextEdit->appendPlainText("**peer port: "+QString::number(tcpSocket->peerPort()));
}

void MainWindow::onNewConnected()
{
    tcpSocket = tcpServer->nextPendingConnection();//获取socket
    connect(tcpSocket,SIGNAL(connected()),this,SLOT(onClientConected()));
    onClientConected();
    connect(tcpSocket,SIGNAL(disconected()),this,SLOT(onClientDisConected()));
    connect(tcpSocket,SIGNAL(stateChanged(QAbstractSocket::SocketState)),this,SLOT(onstateChanged(QAbstractSocket::SocketState)));
    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(onSocketReadyRead()));
    onstateChanged(tcpSocket->state());
}


void MainWindow::on_actStart_triggered()
{
    QString IP = ui->comboIP->currentText();
    int port = ui->spinPort->value();
    QHostAddress addr(IP);
    tcpServer->listen(addr,port);
    ui->plainTextEdit->appendPlainText("开始监听:");
    ui->plainTextEdit->appendPlainText("***服务器IP: "+tcpServer->serverAddress().toString());
    ui->plainTextEdit->appendPlainText("***服务器端口: "+QString::number(tcpServer->serverPort()));
    ui->actStart->setEnabled(false);
    ui->actStop->setEnabled(true);
    labListen->setText("监听状态: 正在监听");
}

void MainWindow::on_actStop_triggered()
{
    if(tcpServer->isListening()){
        tcpServer->close();
        ui->actStart->setEnabled(true);
        ui->actStop->setEnabled(false);
        labListen->setText("监听状态: closed");
    }
}

void MainWindow::on_actClear_triggered()
{
    ui->plainTextEdit->clear();
}

void MainWindow::on_btnSend_clicked()
{
    QString msg = ui->editMsg->text();
    ui->plainTextEdit->appendPlainText("[Out]: "+msg);
    ui->editMsg->clear();
    ui->editMsg->setFocus();

    QByteArray str= msg.toUtf8();
    str.append("\n");
    tcpSocket->write(str);
}
