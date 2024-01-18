#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QtMath>
#include <QPainterPath>
#include <QFont>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setPalette(QPalette(Qt::white)); //设置窗口背景色
    setAutoFillBackground(true);
    resize(600,300); //固定初始化窗口大小
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPen pen;
    pen.setStyle(Qt::SolidLine);
    painter.setPen(pen);
    painter.setRenderHint(QPainter::Antialiasing);
    QBrush brush;
    brush.setColor(Qt::yellow);
    brush.setStyle(Qt::SolidPattern);
    painter.setBrush(brush);

    qreal deg = 3.1415926*(360/5)/180;
    qreal R = 100;
    QPoint points[5]={QPoint(R,0),
                     QPoint(R*std::cos(deg),-R*std::sin(deg)),
                     QPoint(R*std::cos(2*deg),-R*std::sin(2*deg)),
                     QPoint(R*std::cos(3*deg),-R*std::sin(3*deg)),
                     QPoint(R*std::cos(4*deg),-R*std::sin(4*deg))};

    QFont font;
    font.setPointSize(12);

  //  painter.drawPolygon(points,5);
    QPainterPath starPath;
    starPath.moveTo(points[3]);
    starPath.lineTo(points[1]);
    starPath.lineTo(points[4]);
    starPath.lineTo(points[2]);
    starPath.lineTo(points[0]);
    starPath.closeSubpath();

    starPath.addText(points[0],font,"0");
    starPath.addText(points[1],font,"1");
    starPath.addText(points[2],font,"2");
    starPath.addText(points[3],font,"3");
    starPath.addText(points[4],font,"4");

    painter.setFont(font);
    painter.save();

    painter.translate(100,120);
    painter.drawPath(starPath);
    painter.drawText(0,0,"s1");

    painter.restore();
    painter.translate(300,120);
    painter.rotate(90);
    painter.scale(0.7,0.7);
    painter.drawPath(starPath);
    painter.drawText(0,0,"s2");


    painter.resetTransform();
    painter.translate(500,120);
    painter.rotate(-90);
    painter.scale(1.7,0.7);
    painter.drawPath(starPath);
    painter.drawText(0,0,"s3");
}

