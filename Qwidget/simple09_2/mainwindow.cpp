#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QValueAxis>
#include <QTime>
#include <QtMath>
#include <QChart>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    creatChart();

    prepareData();

    updataFromChart();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::creatChart()
{
    QChart *chart = new QChart();
    chart->setTitle("简单的曲线");
    ui->chartView->setChart(chart);
    ui->chartView->setRenderHint(QPainter::Antialiasing);

    QLineSeries *series0 = new QLineSeries;
    QLineSeries *series1 = new QLineSeries;
    series0->setName("Sin曲线");
    series1->setName("Cos曲线");

    curSeries = series0;

    QPen pen;
    pen.setStyle(Qt::DotLine);
    pen.setWidth(2);
    pen.setColor(Qt::red);
    series0->setPen(pen);
    pen.setStyle(Qt::SolidLine);
    pen.setColor(Qt::blue);
    series1->setPen(pen);

    chart->addSeries(series0);
    chart->addSeries(series1);

    QValueAxis *axisX = new QValueAxis;
    QValueAxis *axisY = new QValueAxis;
    curAxis = axisX;

    axisX->setRange(0,10);
    axisY->setLabelFormat("%.1f");
    axisX->setTickCount(11);
    axisX->setMinorTickCount(4);
    axisX->setTitleText("times(secs)");

    axisY->setRange(-1.5,1.5);
    axisY->setTickCount(3);
    axisY->setMinorTickCount(4);
    axisY->setTitleText("value");

    chart->setAxisX(axisX,series0);
    chart->setAxisX(axisX,series1);
    chart->setAxisY(axisY,series0);
    chart->setAxisY(axisY,series1);


}

void MainWindow::prepareData()
{
    QLineSeries *series0 =(QLineSeries*) ui->chartView->chart()->series().at(0);
    QLineSeries *series1 =(QLineSeries*) ui->chartView->chart()->series().at(1);

    int cnt=100 ;
    series0->clear();
    series1->clear();
    qsrand(QTime::currentTime().second());
    qreal t=0,y1,y2,intv=0.1;
    qreal rd;
    for(int i=0;i<cnt;i++){
        rd = (rand()%10)-5;
        y1 = qSin(t)+rd/50;
        series0->append(t,y1);
        y2 = qCos(t)+rd/50;
        series1->append(t,y2);
        t+=intv;
    }
}

void MainWindow::updataFromChart()
{
    QChart *chart = ui->chartView->chart();
    ui->editTitle->setText(chart->title());
    QMargins mg=chart->margins();
    ui->spinMarginBottom->setValue(mg.bottom());
    ui->spinMarginLeft->setValue(mg.left());
    ui->spinMarginTop->setValue(mg.top());
    ui->spinMarginRight->setValue(mg.right());
}


void MainWindow::on_actZoomOut_triggered()
{
    //缩小
    ui->chartView->chart()->zoom(0.8);//zoomOut();
}

void MainWindow::on_actZoomIn_triggered()
{
    //放大
    ui->chartView->chart()->zoom(1.2);//zoomIn();
}

void MainWindow::on_actZoomReset_triggered()
{
    //复位
    ui->chartView->chart()->zoomReset();
}

void MainWindow::on_actDraw_triggered()
{
    prepareData();
}

void MainWindow::on_btnSetTitle_clicked()
{
    QChart *chart = ui->chartView->chart();
    chart->setTitle(ui->editTitle->text());
}

void MainWindow::on_btnSetTitleFont_clicked()
{
    QFont  font = ui->chartView->chart()->titleFont();
    bool ok = false;
    font = QFontDialog::getFont(&ok,font);
    if(ok){
        ui->chartView->chart()->setTitleFont(font);
    }
}

void MainWindow::on_radioButton_clicked(bool checked)
{
    if(checked)
        ui->chartView->chart()->legend()->setAlignment(Qt::AlignTop);
}

void MainWindow::on_radioButton_2_clicked(bool checked)
{
    if(checked)
        ui->chartView->chart()->legend()->setAlignment(Qt::AlignBottom);
}

void MainWindow::on_radioButton_3_clicked(bool checked)
{
    if(checked)
        ui->chartView->chart()->legend()->setAlignment(Qt::AlignLeft);
}

void MainWindow::on_radioButton_4_clicked(bool checked)
{
    if(checked)
        ui->chartView->chart()->legend()->setAlignment(Qt::AlignRight);
}

void MainWindow::on_chkLegendVisible_clicked(bool checked)
{
    ui->chartView->chart()->legend()->setVisible(checked);
}

void MainWindow::on_chkBoxLegendBackground_clicked(bool checked)
{
    ui->chartView->chart()->legend()->setBackgroundVisible(checked);
}

void MainWindow::on_btnLegendFont_clicked()
{
    QFont  font = ui->chartView->chart()->legend()->font();
    bool ok = false;
    font = QFontDialog::getFont(&ok,font);
    if(ok){
        ui->chartView->chart()->legend()->setFont(font);
    }
}

void MainWindow::on_btnLegendlabelColor_clicked()
{
    QColor  color = ui->chartView->chart()->legend()->labelColor();
    color = QColorDialog::getColor(color);
    if(color.isValid()){
        ui->chartView->chart()->legend()->setLabelColor(color);
    }
}

void MainWindow::on_btnSetMargin_clicked()
{
    QMargins mgs;
    mgs.setBottom(ui->spinMarginBottom->value());
    mgs.setLeft(ui->spinMarginLeft->value());
    mgs.setTop(ui->spinMarginTop->value());
    mgs.setRight(ui->spinMarginRight->value());

    ui->chartView->chart()->setMargins(mgs);
}

void MainWindow::on_cBoxAnimation_currentIndexChanged(int index)
{
    ui->chartView->chart()->setAnimationOptions((QChart::AnimationOption)index);
}

void MainWindow::on_cBoxTheme_currentIndexChanged(int index)
{
    ui->chartView->chart()->setTheme(QChart::ChartTheme(index));
}

void MainWindow::on_radioSeries0_clicked(bool checked)
{
    if(ui->radioSeries0->isChecked())
        curSeries =(QLineSeries*) ui->chartView->chart()->series().at(0);
    else
        curSeries =(QLineSeries*) ui->chartView->chart()->series().at(1);

    ui->editSeriesName->setText(curSeries->name());
    ui->chkSeriesVisible->setChecked(curSeries->isVisible());
    ui->chkPointVisible->setChecked(curSeries->pointsVisible());
    ui->sliderSeriesOpacity->setValue(curSeries->opacity()*10);
    ui->chkPointLabelVisible->setChecked(curSeries->pointLabelsVisible());
}

void MainWindow::on_radioSeries1_clicked(bool checked)
{
    on_radioSeries0_clicked(checked);
}

void MainWindow::on_btnSeriesName_clicked()
{
   curSeries->setName(ui->editSeriesName->text());
}

void MainWindow::on_chkSeriesVisible_clicked(bool checked)
{
    curSeries->setVisible(ui->chkSeriesVisible->isChecked());
}

void MainWindow::on_chkPointVisible_clicked(bool checked)
{
    curSeries->setPointsVisible(ui->chkPointVisible->isChecked());
}

void MainWindow::on_btnSeriesColor_clicked()
{
    QColor color = curSeries->color();
    color=QColorDialog::getColor(color);

    if(color.isValid()){
        curSeries->setColor(color);
    }
}

void MainWindow::on_btnSeriesPen_clicked()
{
    bool ok = false;
    QPen pen = curSeries->pen();
    DialogPen::getPen(pen,ok);
    if(ok){
        curSeries->setPen(pen);
    }
}

void MainWindow::on_sliderSeriesOpacity_valueChanged(int value)
{
    curSeries->setOpacity(value/10.0);
}

void MainWindow::on_chkPointLabelVisible_clicked(bool checked)
{
    curSeries->setPointLabelsVisible(checked);
}

void MainWindow::on_btnSeriesLabColor_clicked()
{
    QColor color = curSeries->pointLabelsColor();
    color=QColorDialog::getColor(color);

    if(color.isValid()){
        curSeries->setPointLabelsColor(color);
    }
}

void MainWindow::on_btnSeriesLabFont_clicked()
{
    QFont font = curSeries->pointLabelsFont();
    bool ok = false;
    font = QFontDialog::getFont(&ok,font);
    if(ok){
        curSeries->setPointLabelsFont(font);
    }

}

void MainWindow::on_radioSeriesLabFormat0_clicked(bool checked)
{
    curSeries->setPointLabelsFormat("@yPoint");
}

void MainWindow::on_radioSeriesLabFormat1_clicked(bool checked)
{
    curSeries->setPointLabelsFormat("(@xPoint,@yPoint)");
}

void MainWindow::on_radioX_clicked()
{
    //获取当前坐标轴
    // 在Qt 5.12.1中编译时提示 QChart::axisX()和QChart::axisY()函数过时，应使用 QChart::axes()函数
    //    if (ui->radioX->isChecked())
    //        curAxis=(QValueAxis*)ui->chartView->chart()->axisX();
    //    else
    //        curAxis=(QValueAxis*)ui->chartView->chart()->axisY();

    //  下面是针对Qt 5.12.1修改的代码
        QList<QAbstractAxis*> axes;
        if (ui->radioX->isChecked())
            axes=ui->chartView->chart()->axes(Qt::Horizontal);
        else
            axes=ui->chartView->chart()->axes(Qt::Vertical);
        curAxis=(QValueAxis*)axes[0];


    //获取坐标轴的各种属性，显示到界面上
        ui->spinAxisMin->setValue(curAxis->min());
        ui->spinAxisMax->setValue(curAxis->max());

        ui->editAxisTitle->setText(curAxis->titleText());
        ui->chkBoxAxisTitle->setChecked(curAxis->isTitleVisible());

        ui->editAxisLabelFormat->setText(curAxis->labelFormat());
        ui->chkBoxLabelsVisible->setChecked(curAxis->labelsVisible());

        ui->chkGridLineVisible->setChecked(curAxis->isGridLineVisible());
        ui->chkAxisLineVisible->setChecked(curAxis->isLineVisible());

        ui->spinTickCount->setValue(curAxis->tickCount());
        ui->chkAxisLineVisible->setChecked(curAxis->isLineVisible());

        ui->spinMinorTickCount->setValue(curAxis->minorTickCount());
        ui->chkMinorTickVisible->setChecked(curAxis->isMinorGridLineVisible());
}

void MainWindow::on_radioY_clicked()
{
    on_radioX_clicked();
}

void MainWindow::on_chkBoxVisible_clicked(bool checked)
{
    //坐标轴是否可见
     curAxis->setVisible(checked);
}

void MainWindow::on_btnSetAxisRange_clicked()
{
    curAxis->setRange(ui->spinAxisMin->value(),ui->spinAxisMax->value());

}

void MainWindow::on_btnAxisSetTitle_clicked()
{
    curAxis->setTitleText(ui->editAxisTitle->text());
}

void MainWindow::on_chkBoxAxisTitle_clicked(bool checked)
{//轴标题是否可见
    curAxis->setTitleVisible(checked);
}

void MainWindow::on_btnAxisSetTitleFont_clicked()
{ //设置坐标轴的标题的字体
    QFont   font=curAxis->titleFont();

    bool    ok=false;
    font=QFontDialog::getFont(&ok,font);
    if (ok)
       curAxis->setTitleFont(font);

}

void MainWindow::on_pushButton_clicked()
{//设置坐标轴刻度标签的文字格式
    curAxis->setLabelFormat(ui->editAxisLabelFormat->text());
}

void MainWindow::on_btnAxisLabelColor_clicked()
{//设置坐标轴刻度标签的文字颜色
    QColor   color=curAxis->labelsColor();

    color=QColorDialog::getColor(color);
    if (color.isValid())
       curAxis->setLabelsColor(color);
}

void MainWindow::on_btnAxisLabelFont_clicked()
{//设置坐标轴刻度标签的文字字体
    QFont   font=curAxis->labelsFont();

    bool    ok=false;
    font=QFontDialog::getFont(&ok,font);
    if (ok)
       curAxis->setLabelsFont(font);
}

void MainWindow::on_chkBoxLabelsVisible_clicked(bool checked)
{//轴的刻度标签是否可见
    curAxis->setLabelsVisible(checked);
}

void MainWindow::on_chkGridLineVisible_clicked(bool checked)
{ //轴的网格线是否可见
    curAxis->setGridLineVisible(checked);
}

void MainWindow::on_btnGridLineColor_clicked()
{//网格线的颜色设置
    QColor   color=curAxis->gridLineColor();

    color=QColorDialog::getColor(color);
    if (color.isValid())
       curAxis->setGridLineColor(color);
}

void MainWindow::on_pushButton_10_clicked()
{//网格线的Pen设置
    QPen    pen;
    pen=curAxis->gridLinePen();

    bool    ok=false;
    pen=DialogPen::getPen(pen,ok);

    if (ok)
      curAxis->setGridLinePen(pen);
}

void MainWindow::on_chkMinorTickVisible_clicked(bool checked)
{ //次级刻度是否可见
    curAxis->setMinorGridLineVisible(checked);
}

void MainWindow::on_spinTickCount_valueChanged(int arg1)
{
   curAxis->setTickCount(arg1);
}

void MainWindow::on_btnAxisLinePen_clicked()
{
    QPen    pen;
    pen=curAxis->linePen();

    bool    ok=false;
    pen=DialogPen::getPen(pen,ok);

    if (ok)
      curAxis->setLinePen(pen);
}

void MainWindow::on_btnAxisLinePenColor_clicked()
{
    QColor   color=curAxis->linePenColor();

    color=QColorDialog::getColor(color);
    if (color.isValid())
       curAxis->setLinePenColor(color);
}

void MainWindow::on_chkAxisLineVisible_clicked(bool checked)
{
    //刻度是否可见
    curAxis->setLineVisible(checked);
}

void MainWindow::on_spinMinorTickCount_valueChanged(int arg1)
{
    curAxis->setMinorTickCount(arg1);
}

void MainWindow::on_btnMinorColor_clicked()
{//次级刻度网格线颜色
    QColor   color=curAxis->minorGridLineColor();

    color=QColorDialog::getColor(color);
    if (color.isValid())
       curAxis->setMinorGridLineColor(color);
}

void MainWindow::on_btnMinorPen_clicked()
{//次级刻度线Pen设置
    QPen    pen;
    pen=curAxis->minorGridLinePen();

    bool    ok=false;
    pen=DialogPen::getPen(pen,ok);

    if (ok)
      curAxis->setMinorGridLinePen(pen);
}
