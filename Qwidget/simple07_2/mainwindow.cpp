#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->tabWidget);
    theModel=new QStandardItemModel(this);
    theSelection = new QItemSelectionModel(theModel);
    ui->tableView->setModel(theModel);
    QStringList headerList;
    headerList<<"Depth"<<"Measured Depth"<<"Direction"<<"Offset"<<"Quality"<<"Sampled";
    theModel->setHorizontalHeaderLabels(headerList);
    resetTable(5);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actTabReset_triggered()
{
    resetTable(10);
}

void MainWindow::resetTable(int rows)
{
    theModel->removeRows(0,theModel->rowCount());
    theModel->setRowCount(rows);
    QString str =theModel->headerData(theModel->columnCount()-1,Qt::Horizontal,Qt::DisplayRole).toString();
    for(int i=0;i<rows;i++){
        QModelIndex index = theModel->index(i,theModel->columnCount()-1);
        QStandardItem *item = theModel->itemFromIndex(index);
        item->setData(str,Qt::DisplayRole);
        item->setCheckable(true);
        item->setEditable(false);
    }
}

void MainWindow::on_actOpen_triggered()
{
    QString curPath = QCoreApplication::applicationDirPath();
    QString title = "打开一个文件";
    QString filter = "Qt预定义编码格式(*.stm)";
    QString fileName =QFileDialog::getOpenFileName(this,title,curPath,filter);
    if(fileName.isEmpty()) return;
    QFile file(fileName);
    if(file.open(QIODevice::ReadOnly)){
        QDataStream stream(&file);
        stream.setVersion(QDataStream::Qt_5_14);
        qint16 rowCount,colCount;
        stream>>rowCount;
        stream>>colCount;
        //headerList<<"Depth"<<"Measured Depth"<<"Direction"<<"Offset"<<"Quality"<<"Sampled";
        resetTable(rowCount);
        QString str;
        for(int i=0;i<colCount;i++)
            stream>>str;
        //数据区域
        qint16 Depth;
        qreal  MeasuredDepth,Direction,Offset;
        QString Quality;
        bool Sampled;
        QStandardItem *item;
        QModelIndex index;
        for(int i=0;i<rowCount;i++){
            stream>>Depth;
            index = theModel->index(i,0);
            item = theModel->itemFromIndex(index);
            item->setData(Depth,Qt::DisplayRole);\

            stream>>MeasuredDepth;
            index = theModel->index(i,1);
            item = theModel->itemFromIndex(index);
            item->setData(MeasuredDepth,Qt::DisplayRole);

            stream>>Direction;
            index = theModel->index(i,2);
            item = theModel->itemFromIndex(index);
            item->setData(Direction,Qt::DisplayRole);

            stream>>Offset;
            index = theModel->index(i,3);
            item = theModel->itemFromIndex(index);
            item->setData(Offset,Qt::DisplayRole);

            stream>>Quality;
            index = theModel->index(i,4);
            item = theModel->itemFromIndex(index);
            item->setData(Quality,Qt::DisplayRole);

            stream>>Sampled;
            index = theModel->index(i,5);
            item = theModel->itemFromIndex(index);
            if(Sampled)
                item->setCheckState(Qt::Checked);
            else
                item->setCheckState(Qt::Unchecked);
        }
        file.close();
    }
}

void MainWindow::on_actSave_triggered()
{
    QString curPath = QCoreApplication::applicationDirPath();
    QString title = "保存一个文件";
    QString filter = "Qt预定义编码格式(*.stm)";
    QString fileName =QFileDialog::getSaveFileName(this,title,curPath,filter);
    if(fileName.isEmpty()) return;
    QFile file(fileName);
    if(file.open(QIODevice::WriteOnly|QIODevice::Truncate)){
        QDataStream stream(&file);
        stream.setVersion(QDataStream::Qt_5_14);
        qint16 rowCount=theModel->rowCount();
        qint16 colCount=theModel->columnCount();
        stream<<rowCount;
        stream<<colCount;
        //headerList<<"Depth"<<"Measured Depth"<<"Direction"<<"Offset"<<"Quality"<<"Sampled";
        for(int i=0;i<colCount;i++)
            stream << theModel->horizontalHeaderItem(i)->text();

        //数据区域
        qint16 Depth;
        qreal  MeasuredDepth,Direction,Offset;
        QString Quality;
        bool Sampled;
        for(int i=0;i<rowCount;i++){
            Depth = theModel->item(i,0)->data(Qt::DisplayRole).toInt();
            stream<<Depth;

            MeasuredDepth = theModel->item(i,1)->data(Qt::DisplayRole).toFloat();
            stream<<MeasuredDepth;

            Direction = theModel->item(i,2)->data(Qt::DisplayRole).toFloat();
            stream<<Direction;

            Offset = theModel->item(i,3)->data(Qt::DisplayRole).toFloat();
            stream<<Offset;

            Quality = theModel->item(i,4)->data(Qt::DisplayRole).toString();
            stream<<Quality;

            Sampled =(theModel->item(i,5)->checkState()==Qt::Checked);
            stream<<Sampled;
        }
        file.close();
    }

}

void MainWindow::on_actOpenBin_triggered()
{
    QString curPath = QCoreApplication::applicationDirPath();
    QString title = "打开一个文件";
    QString filter = "Qt标准编码格式(*.dat)";
    QString fileName =QFileDialog::getOpenFileName(this,title,curPath,filter);
    if(fileName.isEmpty()) return;
    QFile file(fileName);
    if(file.open(QIODevice::ReadOnly)){
        QDataStream stream(&file);
        stream.setByteOrder(QDataStream::LittleEndian);
        qint16 rowCount,colCount;
        stream.readRawData((char*)&rowCount,sizeof(qint16));
        stream.readRawData((char*)&colCount,sizeof(qint16));
        //headerList<<"Depth"<<"Measured Depth"<<"Direction"<<"Offset"<<"Quality"<<"Sampled";
        resetTable(rowCount);
        char* buf;
        uint strlen;
        for(int i=0;i<colCount;i++)
            stream.readBytes(buf,strlen);
        //QString str = QString::fromLocal8Bit(buf,strlen);
        //数据区域
        qint16 Depth;
        qreal  MeasuredDepth,Direction,Offset;
        QString Quality;
        qint8 Sampled;
        QStandardItem *item;
        QModelIndex index;
        for(int i=0;i<rowCount;i++){
            stream.readRawData((char*)&Depth,sizeof(qint16));
            index = theModel->index(i,0);
            item = theModel->itemFromIndex(index);
            item->setData(Depth,Qt::DisplayRole);

            stream.readRawData((char*)&MeasuredDepth,sizeof(qreal));
            index = theModel->index(i,1);
            item = theModel->itemFromIndex(index);
            item->setData(MeasuredDepth,Qt::DisplayRole);

            stream.readRawData((char*)&Direction,sizeof(qreal));
            index = theModel->index(i,2);
            item = theModel->itemFromIndex(index);
            item->setData(Direction,Qt::DisplayRole);

            stream.readRawData((char*)&Offset,sizeof(qreal));
            index = theModel->index(i,3);
            item = theModel->itemFromIndex(index);
            item->setData(Offset,Qt::DisplayRole);

            stream.readBytes(buf,strlen);
            QString Quality = QString::fromLocal8Bit(buf,strlen);
            item = theModel->itemFromIndex(index);
            item->setData(Quality,Qt::DisplayRole);

            stream.readRawData((char*)&Sampled,sizeof(qint8));
            index = theModel->index(i,5);
            item = theModel->itemFromIndex(index);
            if(Sampled==1)
                item->setCheckState(Qt::Checked);
            else
                item->setCheckState(Qt::Unchecked);
        }
        file.close();
    }
}

void MainWindow::on_actSaveBin_triggered()
{
    QString curPath = QCoreApplication::applicationDirPath();
    QString title = "保存一个文件";
    QString filter = "Qt预定义编码格式(*.dat)";
    QString fileName =QFileDialog::getSaveFileName(this,title,curPath,filter);
    if(fileName.isEmpty()) return;
    QFile file(fileName);
    if(file.open(QIODevice::WriteOnly|QIODevice::Truncate)){
        QDataStream stream(&file);
        stream.setByteOrder(QDataStream::LittleEndian);
        stream.setVersion(QDataStream::Qt_5_14);
        qint16 rowCount=theModel->rowCount();
        qint16 colCount=theModel->columnCount();
        stream.writeRawData((char*)&rowCount,sizeof(qint16));
        stream.writeRawData((char*)&colCount,sizeof(qint16));
        //headerList<<"Depth"<<"Measured Depth"<<"Direction"<<"Offset"<<"Quality"<<"Sampled";
        QByteArray btArry;

        for(int i=0;i<colCount;i++){
           QString str=theModel->horizontalHeaderItem(i)->text();
           btArry= str.toUtf8();
           stream.writeBytes(btArry,btArry.length());
        }
          //  stream << theModel->horizontalHeaderItem(i)->text();

        //数据区域
        qint16 Depth;
        qreal  MeasuredDepth,Direction,Offset;
        QString Quality;
        bool Sampled;
        for(int i=0;i<rowCount;i++){
            Depth = theModel->item(i,0)->data(Qt::DisplayRole).toInt();
            stream.writeRawData((char*)&Depth,sizeof(qint16));

            MeasuredDepth = theModel->item(i,1)->data(Qt::DisplayRole).toFloat();
            stream.writeRawData((char*)&MeasuredDepth,sizeof(qreal));

            Direction = theModel->item(i,2)->data(Qt::DisplayRole).toFloat();
            stream.writeRawData((char*)&Direction,sizeof(qreal));

            Offset = theModel->item(i,3)->data(Qt::DisplayRole).toFloat();
            stream.writeRawData((char*)&Offset,sizeof(qreal));

            Quality = theModel->item(i,4)->data(Qt::DisplayRole).toString();
            btArry= Quality.toUtf8();
            stream.writeBytes(btArry,btArry.length());


            Sampled =(theModel->item(i,5)->checkState()==Qt::Checked);
            qint8 yes=1,no=0;
            if(Sampled)
                stream.writeRawData((char*)&yes,sizeof(qint8));
            else
                stream.writeRawData((char*)&no,sizeof(qint8));
        }
        file.close();
    }
}
