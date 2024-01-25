#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->Slider->setRange(0,100);
    ui->Slider->setValue(ui->battery->PowerLeve());
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_Slider_valueChanged(int value)
{
    ui->battery->setPowerLeve(value);
    ui->label->setText(QString::asprintf("当前电量:%d%%",value));
}
