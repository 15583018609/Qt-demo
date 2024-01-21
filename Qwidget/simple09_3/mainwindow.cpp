#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qsrand(QTime::currentTime().second());
    theModel = new QStandardItemModel(initDataRowCount,fixedColumnCount,this);
    ui->tableView->setModel(theModel);
    initBarChart();
    buildBarChartA();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initData()
{
    QStringList headerList;
    headerList <<"姓名"<<"数学"<<"语文"<<"英语"<<"平均分";
    theModel->setHorizontalHeaderLabels(headerList);

    for(int i=0;i<theModel->rowCount();i++){
        QString stuName= QString::asprintf("学生%2d",i+1);
        QStandardItem *aitem= new QStandardItem(stuName);
        aitem->setTextAlignment(Qt::AlignHCenter);
        theModel->setItem(i,colNoName,aitem);
        qreal avgScore=0;
        for(int j =colNoMath;j<=colNoEnglish;j++){
            qreal score = 50.0+qrand()%50;
            avgScore+=score;
            aitem =new QStandardItem(QString::asprintf("%.0f",score));
            aitem->setTextAlignment(Qt::AlignHCenter);
            theModel->setItem(i,j,aitem);

        }
        aitem=new QStandardItem(QString::asprintf("%.1f",avgScore/3));
        aitem->setTextAlignment(Qt::AlignHCenter);
        aitem->setFlags(aitem->flags()&!Qt::ItemIsEditable);
        theModel->setItem(i,colNoAverage,aitem);
    }
}

void MainWindow::sureyData()
{
    //数据统计
        int cnt50,cnt60,cnt70,cnt80,cnt90;

        qreal   sumV,minV,maxV;
        qreal   val;
        QTreeWidgetItem *item; //节点

        int i,j;
        for(i=colNoMath;i<=colNoAverage;i++)
        {
            sumV=0;
            cnt50=0;
            cnt60=0;
            cnt70=0;
            cnt80=0;
            cnt90=0;

            for(j=0;j<theModel->rowCount();j++)
            {
                val=theModel->item(j,i)->text().toDouble();
                ////////////////////////////
                if (j==0)
                {
                    minV=val;
                    maxV=val;
                }
                if (val<minV)
                    minV=val;
                if (val>maxV)
                    maxV=val;
                //////////////////////////
                sumV+=val;

                if (val<60)
                    cnt50++;
                else if ((val>=60) && (val<70))
                    cnt60++;
                else if ((val>=70) && (val<80))
                    cnt70++;
                else if ((val>=80) && (val<90))
                    cnt80++;
                else
                    cnt90++;
            }
            //////////
            item=ui->treeWidget->topLevelItem(0); //<60
            item->setText(i,QString::number(cnt50));
            item->setTextAlignment(i,Qt::AlignHCenter);

            item=ui->treeWidget->topLevelItem(1); //60
            item->setText(i,QString::number(cnt60));
            item->setTextAlignment(i,Qt::AlignHCenter);

            item=ui->treeWidget->topLevelItem(2); //70
            item->setText(i,QString::number(cnt70));
            item->setTextAlignment(i,Qt::AlignHCenter);

            item=ui->treeWidget->topLevelItem(3); //80
            item->setText(i,QString::number(cnt80));
            item->setTextAlignment(i,Qt::AlignHCenter);

            item=ui->treeWidget->topLevelItem(4); //90
            item->setText(i,QString::number(cnt90));
            item->setTextAlignment(i,Qt::AlignHCenter);

            item=ui->treeWidget->topLevelItem(5); //average
            item->setText(i,QString::number(sumV/theModel->rowCount()));
            item->setTextAlignment(i,Qt::AlignHCenter);

            item=ui->treeWidget->topLevelItem(6); //max
            item->setText(i,QString::number(maxV));
            item->setTextAlignment(i,Qt::AlignHCenter);

            item=ui->treeWidget->topLevelItem(7); //min
            item->setText(i,QString::number(minV));
            item->setTextAlignment(i,Qt::AlignHCenter);
        }
}

void MainWindow::buildBarChartA()
{
    QChart *chart = ui->chartViewBar->chart();
    chart->removeAllSeries();
    if(chart->axisX()!= NULL){
        chart->removeAxis(chart->axisX());
        chart->removeAxis(chart->axisY());
    }


    //数据集
    QBarSet *setMath=new QBarSet(theModel->horizontalHeaderItem(colNoMath)->text());
    QBarSet *setChinese=new QBarSet(theModel->horizontalHeaderItem(colNoChinese)->text());
    QBarSet *setEnglish=new QBarSet(theModel->horizontalHeaderItem(colNoEnglish)->text());
    QLineSeries *Line=new QLineSeries();
    Line->setName(theModel->horizontalHeaderItem(colNoAverage)->text());
    QPen pen;
    pen.setColor(Qt::red);
    pen.setWidth(2);
    Line->setPen(pen);
    for(int i =0;i<theModel->rowCount();i++){
        setMath->append(theModel->item(i,colNoMath)->text().toInt());
        setChinese->append(theModel->item(i,colNoChinese)->text().toInt());
        setEnglish->append(theModel->item(i,colNoEnglish)->text().toInt());
        Line->append(QPointF(i,theModel->item(i,colNoAverage)->text().toFloat()));
    }
    //序列
    QBarSeries *series = new QBarSeries();
    series->append(setMath);
    series->append(setChinese);
    series->append(setEnglish);

    chart->addSeries(series);
    chart->addSeries(Line);
    QStringList catagories;
    for(int i=0;i<theModel->rowCount();i++){
        catagories<<theModel->item(i,colNoName)->text();
    }
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
   // axisX->setCategories(catagories);
    axisX->append(catagories); //添加横坐标文字列表
//    chart->setAxisX(axisX,series);
//    chart->setAxisX(axisX,Line);
    chart->addAxis(axisX, Qt::AlignLeft);
   // axisX->setRange(categories.at(0), categories.at(categories.count()-1)); //这只坐标轴范围
    QValueAxis *axisY = new QValueAxis;
    axisY->setRange(0,100);
    axisY->setTitleText("分数");
    axisY->setTickCount(6);//11
    axisY->setLabelFormat("%.0f"); //标签格式
    //chart->setAxisY(axisY,series);
    chart->addAxis(axisY, Qt::AlignLeft);
    chart->legend()->setAlignment(Qt::AlignBottom);

    series->attachAxis(axisX);
    series->attachAxis(axisY);

    Line->attachAxis(axisX);
    Line->attachAxis(axisY);
}

void MainWindow::initBarChart()
{
    QChart *chart=new QChart();
    chart->setTitle("Bar演示");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    ui->chartViewBar->setChart(chart);
    ui->chartViewBar->setRenderHint(QPainter::Antialiasing);

}


void MainWindow::on_actGenData_triggered()
{
    initData();
}

void MainWindow::on_actTongJi_triggered()
{
    sureyData();
}

void MainWindow::on_btnBuildBarChart_clicked()
{
    buildBarChartA();
}
