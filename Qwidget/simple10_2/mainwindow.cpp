#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSplitter>
#include <QColorDialog>
void MainWindow::initGraph3D()
{
    graph3D =new Q3DScatter;
    //创建数据序列
    QScatterDataProxy *proxy =new QScatterDataProxy;
    QScatter3DSeries *series = new QScatter3DSeries(proxy);
    series->setMesh(QAbstract3DSeries::MeshCylinder);//mesh:计算机图形学最基础模型
    series->setItemLabelFormat("(@Rowlabel,@ColLabel:%.1f)");
    graph3D->addSeries(series);

    //添加数据
    int N=41;
    QScatterDataArray *dataArry = new QScatterDataArray;
    dataArry->resize(N*N);
    QScatterDataItem *item = &dataArry->first();

    //墨西哥草帽算法
    float x,y,z;
    x=-10;
    for(int i =1;i<=N;i++){
        y=-10;
        for(int j=1;j<=N;j++){
            z = qSqrt(x*x+y*y);
            if(z!=0)
                z=10*qSin(z)/z;
            else
                z=10;
            item->setPosition(QVector3D(x,z,y));
            item++;
            y+=0.5;
        }
        x+=0.5;
    }

    series->dataProxy()->resetArray(dataArry);


}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QSplitter *splitter=new QSplitter(Qt::Horizontal);
    splitter->addWidget(ui->groupBox);
    graph3D = new Q3DScatter;
    initGraph3D();
    splitter->addWidget(createWindowContainer(graph3D));
    setCentralWidget(splitter);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_comboCamera_activated(int index)
{
    graph3D->scene()->activeCamera()->setCameraPreset(Q3DCamera::CameraPreset(index));
}

void MainWindow::on_sliderH_valueChanged(int value)
{
    Q_UNUSED(value);
    int xRot = ui->sliderH->value();
    int yRot = ui->sliderV->value();
    int zoom = ui->sliderZoom->value();

    graph3D->scene()->activeCamera()->setCameraPosition(xRot,yRot,zoom);

}

void MainWindow::on_sliderV_valueChanged(int value)
{
    on_sliderH_valueChanged(value);
}

void MainWindow::on_sliderZoom_valueChanged(int value)
{
    on_sliderH_valueChanged(value);

}

void MainWindow::on_cBoxTheme_currentIndexChanged(int index)
{
    graph3D->activeTheme()->setType(Q3DTheme::Theme(index));
}

void MainWindow::on_cBoxBarStyle_currentIndexChanged(int index)
{
    QScatter3DSeries *series = graph3D->seriesList().at(0);
    series->setMesh(QAbstract3DSeries::Mesh(index));
}

void MainWindow::on_cBoxSelectionMode_currentIndexChanged(int index)
{
    graph3D->setSelectionMode(QAbstract3DGraph::SelectionFlags(index));
}

void MainWindow::on_spinFontSize_valueChanged(int arg1)
{
    QFont font= graph3D->activeTheme()->font();
    font.setPointSize(arg1);
    graph3D->activeTheme()->setFont(font);
}

void MainWindow::on_btnBarColor_clicked()
{
    QScatter3DSeries *series = graph3D->seriesList().at(0);
    QColor color = series->baseColor();
    color =QColorDialog::getColor(color);
    if(color.isValid())
        series->setBaseColor(color);
}

void MainWindow::on_chkBoxBackground_clicked(bool checked)
{
    graph3D->activeTheme()->setBackgroundEnabled(checked);
}

void MainWindow::on_chkBoxGrid_clicked(bool checked)
{
    graph3D->activeTheme()->setGridEnabled(checked);
}

void MainWindow::on_chkBoxSmooth_clicked(bool checked)
{
    QScatter3DSeries *series = graph3D->seriesList().at(0);
    series->setMeshSmooth(checked);
}

void MainWindow::on_chkBoxReflection_clicked(bool checked)
{
    graph3D->setReflection(checked);
}

void MainWindow::on_chkBoxReverse_clicked(bool checked)
{
    graph3D->axisY()->setReversed(checked);
}

void MainWindow::on_chkBoxItemLabel_clicked(bool checked)
{
    QScatter3DSeries *series = graph3D->seriesList().at(0);
    series->setItemLabelVisible(checked);
}

void MainWindow::on_chkBoxAxisTitle_clicked(bool checked)
{
    graph3D->axisY()->setTitleVisible(checked);
    graph3D->axisX()->setTitleVisible(checked);
    graph3D->axisZ()->setTitleVisible(checked);
}

void MainWindow::on_chkBoxAxisBackground_clicked(bool checked)
{
    graph3D->activeTheme()->setLabelBackgroundEnabled(checked);
}
