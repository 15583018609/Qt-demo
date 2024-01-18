#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLinearGradient>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setPalette(QPalette(Qt::white));
    setAutoFillBackground(true);
    resize(300,300);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    int W = width();
    int H = height();
    int side = qMin(W,H);

    QRect rect((W-side)/2,(H-side)/2,side,side);
    painter.drawRect(rect);
    painter.setViewport(rect);
    painter.setWindow(-100,-100,200,200);

    QLinearGradient linGradient(0,0,100,0);
    linGradient.setColorAt(0,Qt::yellow);
    linGradient.setColorAt(1,Qt::green);
    linGradient.setSpread(QGradient::PadSpread);

    painter.setCompositionMode(QPainter::RasterOp_NotSourceXorDestination);

    painter.setBrush(linGradient);

    for(int i =0;i<36;i++){
        painter.drawEllipse(QPoint(50,0),50,50);
        painter.rotate(10);
    }

}

