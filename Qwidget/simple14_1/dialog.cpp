#include "dialog.h"
#include "ui_dialog.h"
Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::lookUpHostInfo(const QHostInfo &host)
{
   QList<QHostAddress> addList = host.addresses();
   if(addList.isEmpty()) return;
   foreach(auto aHost,addList){
       bool show;
       if(ui->chkOnlyIPv4->isChecked())
           show = (aHost.protocol()==QAbstractSocket::IPv4Protocol);
       else
           show = true;
       if(show){
           ui->plainTextEdit->appendPlainText("协议: "+protecolName(aHost.protocol()));
           ui->plainTextEdit->appendPlainText("IP地址: "+aHost.toString());
           ui->plainTextEdit->appendPlainText("");
       }
   }
}


void Dialog::on_btnGetHostInfo_clicked()
{
    QString hostName = QHostInfo::localHostName();
    ui->plainTextEdit->appendPlainText(hostName);
    QHostInfo hostInfo = QHostInfo::fromName(hostName);
    QList<QHostAddress> addList = hostInfo.addresses();
    if(addList.isEmpty()) return;
    foreach(auto aHost,addList){
        bool show;
        if(ui->chkOnlyIPv4->isChecked())
            show = (aHost.protocol()==QAbstractSocket::IPv4Protocol);
        else
            show = true;
        if(show){
            ui->plainTextEdit->appendPlainText("协议: "+protecolName(aHost.protocol()));
            ui->plainTextEdit->appendPlainText("本机IP地址: "+aHost.toString());
            ui->plainTextEdit->appendPlainText("");
        }
    }
}

QString Dialog::protecolName(QAbstractSocket::NetworkLayerProtocol protocol)
{
    switch (protocol) {
        case QAbstractSocket::IPv4Protocol:
            return "IPv4 protocol";
        case QAbstractSocket::IPv6Protocol:
            return "IPv6 protocol";
        case QAbstractSocket::AnyIPProtocol:
            return "Any protocol";
        default:
            return "Unkonwn NetWork protocol";
    }
}

void Dialog::on_btnClear_clicked()
{
    ui->plainTextEdit->clear();
}

void Dialog::on_btnLookup_clicked()
{
    //异步方式
    QString hostName = ui->editHost->text();
    ui->plainTextEdit->appendPlainText("正在查询的主机信息: "+hostName);
    QHostInfo::lookupHost(hostName,this,SLOT(lookUpHostInfo(QHostInfo)));
}

void Dialog::on_btnDetail_clicked()
{
     QList<QHostAddress> addList = QNetworkInterface::allAddresses();
     if(addList.isEmpty()) return;
     foreach(auto aHost,addList){
         bool show;
         if(ui->chkOnlyIPv4->isChecked())
             show = (aHost.protocol()==QAbstractSocket::IPv4Protocol);
         else
             show = true;
         if(show){
             ui->plainTextEdit->appendPlainText("协议: "+protecolName(aHost.protocol()));
             ui->plainTextEdit->appendPlainText("本机IP地址: "+aHost.toString());
             ui->plainTextEdit->appendPlainText("");
         }
     }

}

void Dialog::on_btnALLInterface_clicked()
{
    QList<QNetworkInterface> list=QNetworkInterface::allInterfaces();
    foreach(auto aInterface,list){
        if(!aInterface.isValid()) continue;
        ui->plainTextEdit->appendPlainText("设备名称: "+aInterface.humanReadableName());
        ui->plainTextEdit->appendPlainText("MAC地址: "+aInterface.hardwareAddress());
        QList<QNetworkAddressEntry> entryList = aInterface.addressEntries();
        foreach(auto aEntry ,entryList){
            ui->plainTextEdit->appendPlainText(" IP地址: "+aEntry.ip().toString());
            ui->plainTextEdit->appendPlainText(" 子网掩码: "+aEntry.netmask().toString());
            ui->plainTextEdit->appendPlainText(" 广播地址: "+aEntry.broadcast().toString());
        }
        ui->plainTextEdit->appendPlainText("");
    }
}
