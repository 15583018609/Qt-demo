#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QHostInfo>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    labSocketState = new QLabel("Socked状态: ");
    labSocketState->setMinimumWidth(200);
    ui->statusbar->addWidget(labSocketState);

    setWindowTitle("客户端: "+getLocalIP());

    tcpSocket= new QTcpSocket(this);
    connect(tcpSocket,SIGNAL(connected()),this,SLOT(onConected()));
    connect(tcpSocket,SIGNAL(disconected()),this,SLOT(onDisConected()));
    connect(tcpSocket,SIGNAL(stateChanged(QAbstractSocket::SocketState)),this,SLOT(onstateChanged(QAbstractSocket::SocketState)));
    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(onSocketReadyRead()));

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

void MainWindow::onDisConected()
{
     ui->plainTextEdit->appendPlainText("**socket diconnected");
     ui->actConnect->setEnabled(true);
     ui->actDisconnect->setEnabled(false);
}

void MainWindow::onConected()
{
    ui->plainTextEdit->appendPlainText("**socket connected");
    ui->plainTextEdit->appendPlainText("**peer address: "+tcpSocket->peerAddress().toString());
    ui->plainTextEdit->appendPlainText("**peer port: "+QString::number(tcpSocket->peerPort()));
    ui->actConnect->setEnabled(false);
    ui->actDisconnect->setEnabled(true);
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

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actClear_triggered()
{
    ui->plainTextEdit->clear();
}

void MainWindow::on_actConnect_triggered()
{
    QString addr = ui->comboServer->currentText();
    int port = ui->spinPort->value();
    tcpSocket->connectToHost(addr,port);
}

void MainWindow::on_actDisconnect_triggered()
{
    if(tcpSocket->state()==QAbstractSocket::ConnectedState)
        tcpSocket->disconnectFromHost();
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
