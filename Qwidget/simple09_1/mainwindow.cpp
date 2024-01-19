#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtMath>
#include <QValueAxis>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    creatChartView();//创建图表
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::creatChartView()
{
    QChartView* chartView = new QChartView(this);
    QChart * chart = new QChart();
    chart->setTitle("简单函数曲线");
    chartView->setChart(chart);
    setCentralWidget(chartView);

    QLineSeries *series0 = new QLineSeries;
    QLineSeries *series1 = new QLineSeries;
    series0->setName("Sin曲线");
    series1->setName("Cos曲线");
    chart->addSeries(series0);
    chart->addSeries(series1);
    int cnt =100;
    qreal y0,y1,t=0,intV = 0.1;
    for(int i=0;i<cnt;i++){
        y0 = qSin(t);
        series0->append(t,y0);
        y1 = qCos(t);
        series1->append(t,y1);
        t+=intV;
    }
    //创建坐标轴
    QValueAxis *axisX = new QValueAxis;
    axisX->setRange(0,10);
    chart->setAxisX(axisX,series0);
    chart->setAxisX(axisX,series1);
    QValueAxis *axisY = new QValueAxis;
    axisY->setRange(-1,1);
    chart->setAxisY(axisY,series0);
    chart->setAxisY(axisY,series1);


}



