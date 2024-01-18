#include "widget.h"
#include "ui_widget.h"
#include <QPainter>
#include <QBrush>
#include <QRect>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setPalette(QPalette(Qt::white));
    setAutoFillBackground(true);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    int W = this->width();
    int H = this->height();
    //painter.setRenderHint(QPainter::Antialiasing);
    //painter.setRenderHint(QPainter::TextAntialiasing);
    QPen pen;
    pen.setWidth(20);
    pen.setColor(Qt::green);
    pen.setStyle(Qt::DashDotLine);
    pen.setJoinStyle(Qt::RoundJoin);
    QRect rect(W/4,H/4,W/2,H/2);
    painter.setPen(pen);

    QBrush brush;
    brush.setColor(Qt::red);
    brush.setStyle(Qt::Dense5Pattern);
    painter.setBrush(brush);

    QPoint point[]={QPoint(W/3,H/3),QPoint(W/2,H/2),QPoint(W/2,H/2)};
    painter.drawPolyline(point,3);

//    QImage image(":images/images/qt.jpg");
//    painter.drawImage(rect,image);
//    QFont font;
//    font.setPointSize(20);
//    painter.setFont(font);
//    painter.drawText(rect,"Hello Qt");
  //  painter.drawRect(rect);
}

