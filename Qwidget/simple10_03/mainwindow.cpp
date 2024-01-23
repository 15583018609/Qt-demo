#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    splitter=new QSplitter;
    init3DGraph();
    splitter->addWidget(ui->groupBox);
    splitter->addWidget(createWindowContainer(graph3D));
    setCentralWidget(splitter);

    QLinearGradient lgcolor(0,0,100,0);
    lgcolor.setColorAt(1.0,Qt::black);
    lgcolor.setColorAt(0.67,Qt::blue);
    lgcolor.setColorAt(0.33,Qt::red);
    lgcolor.setColorAt(0.0,Qt::yellow);
    QPixmap pm(160,20);
    QPainter painter(&pm);
    painter.setBrush(lgcolor);
    painter.drawRect(0,0,160,20);
    ui->btnGrad1->setIcon(QIcon(pm));
    ui->btnGrad1->setIconSize(QSize(160,20));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init3DGraph()
{
    graph3D = new Q3DSurface;
    graph3D->axisX()->setTitle("X轴");
    graph3D->axisX()->setTitleVisible(true);
    graph3D->axisX()->setRange(-11,11);
    graph3D->axisY()->setTitle("Y轴");
    graph3D->axisY()->setAutoAdjustRange(true);
    graph3D->axisY()->setTitleVisible(true);
    graph3D->axisZ()->setTitle("Z轴");
    graph3D->axisZ()->setRange(-11,11);
    graph3D->axisZ()->setTitleVisible(true);
    QSurfaceDataProxy *proxy=new QSurfaceDataProxy;
    series = new QSurface3DSeries;
    series->setItemLabelFormat("(@xLabel @yLabel @zLabel)");
    series->setMeshSmooth(true);
    graph3D->activeTheme()->setLabelBackgroundEnabled(false);
    series->setDrawMode(QSurface3DSeries::DrawSurfaceAndWireframe);
    graph3D->addSeries(series);
    series->setBaseColor(Qt::red);
    //创建数据, 墨西哥草帽
    int N=41;//-10:0.5:10, N个数据点
    QSurfaceDataArray *dataArray = new QSurfaceDataArray; //数组
    dataArray->reserve(N);

    float x=-10,y,z;
    int i,j;
    for (i =1 ; i <=N; i++)
    {
        QSurfaceDataRow *newRow = new QSurfaceDataRow(N); //一行的数据
        y=-10;
        int index=0;
        for (j = 1; j <=N; j++)
        {
            z=qSqrt(x*x+y*y);
            if (z!=0)
                z=10*qSin(z)/z;
            else
                z=10;
            (*newRow)[index++].setPosition(QVector3D(x, z, y));
            y=y+0.5;
        }
        x=x+0.5;
        *dataArray << newRow;
    }
  //  proxy->resetArray(dataArray);
    series->dataProxy()->resetArray(dataArray);

}


void MainWindow::on_comboDrawMode_currentIndexChanged(int index)
{
    series->setDrawMode(QSurface3DSeries::DrawFlags(index+1));
}

void MainWindow::on_btnGrad1_clicked()
{
    QLinearGradient gr;
    gr.setColorAt(0.0, Qt::black);
    gr.setColorAt(0.33, Qt::blue);
    gr.setColorAt(0.67, Qt::red);
    gr.setColorAt(1.0, Qt::yellow);

    series->setBaseGradient(gr);
    series->setColorStyle(Q3DTheme::ColorStyleRangeGradient);

}

void MainWindow::on_btnBarColor_clicked()
{
    QColor color = series->baseColor();
    color =QColorDialog::getColor(color);
    if (color.isValid())
    {
        series->setBaseColor(color);
        series->setColorStyle(Q3DTheme::ColorStyleUniform);
    }
}
