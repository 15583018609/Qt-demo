#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_clicked()
{
    QString str = ui->editNum->text();
    int num = str.toInt();
    str = ui->editPrice->text();
    float price= str.toFloat();
    float total = num * price;
    str = str.setNum(total,'f',2);
    ui->editTotal ->setText(str);

}

void Widget::on_btnDec_clicked()
{
    QString str = ui->btnDec->text();
    int value = str.toInt();
    QString str1 =str.setNum(value,2);
    ui->editBin->setText(str1);
    str = str.setNum(value,16);
    ui->editHex->setText(str.toUpper());

}

void Widget::on_btnBin_clicked()
{
    QString str = ui->editBin->text();
    bool ok ;
    int value = str.toInt(&ok,2);
    str = str.setNum(value,2);
    ui->editDec->setText(QString::number(value));
    ui->editHex->setText(QString::number(value,16).toUpper());
}
