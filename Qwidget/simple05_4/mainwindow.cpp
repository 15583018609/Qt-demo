#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QTextStream>

void MainWindow::initModelFromStringList(QStringList &fileContent)
{

    theModel->setRowCount(fileContent.count()-1);
    //设置表头
    QString header = fileContent.at(0);
    QStringList headerlist = header.split(QRegExp("\\s+"),QString::SkipEmptyParts);
    theModel->setHorizontalHeaderLabels(headerlist);
    //设置表格数据
    int j;
    QStandardItem *item;
    for(int i=1;i<fileContent.count();i++){
        QString linText = fileContent.at(i);
        QStringList tmplist = linText.split(QRegExp("\\s+"),QString::SkipEmptyParts);
        for(j = 0;j<FixedColumnCount-1;j++){
            item =new QStandardItem(tmplist.at(j));
            theModel->setItem(i-1,j,item);
        }
        item =new QStandardItem(headerlist.at(j));
        if(tmplist.at(j) == "1")
            item->setCheckState(Qt::Checked);
        else
            item->setCheckState(Qt::Unchecked);
        theModel->setItem(i-1,j,item);
    }
}



void MainWindow::on_currentChanged(const QModelIndex &current,const QModelIndex &previous)
{
    Q_UNUSED(previous);
    if(current.isValid()){
        LabCellPos->setText(QString::asprintf("当前单元格: %d行，%d列",current.row(),current.column()));

        QStandardItem *item = theModel->itemFromIndex(current);

        this->LabCellText->setText("单元内容"+item->text());

        QFont font = item->font();
        ui->actFontBold->setChecked(font.bold());
    }
    else
        return;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    LabCurFile = new QLabel("当前文件",this) ;  //当前文件
    LabCellPos = new QLabel("当前单元格",this);    //当前单元格行列号
    LabCellText= new QLabel("单元内容",this);   //当前单元格内容

    theModel = new QStandardItemModel(10,FixedColumnCount,this);//数据模型
    theSelection = new QItemSelectionModel(theModel);//Item选择模型

    ui->tableView->setModel(theModel);
    ui->tableView->setSelectionModel(theSelection);

    LabCurFile->setMinimumWidth(200);
    LabCellPos->setMinimumWidth(150);

    ui->statusbar->addWidget(LabCurFile);
    ui->statusbar->addWidget(LabCellPos);
    ui->statusbar->addWidget(LabCellText);

    ui->tableView->setItemDelegateForColumn(0,&intspinDelegate);



    connect(theSelection,SIGNAL(currentChanged(QModelIndex,QModelIndex)),this,SLOT(on_currentChanged(QModelIndex,QModelIndex)));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actOpen_triggered()
{
    QString currentPath= QCoreApplication::applicationDirPath();
    QString fileName = QFileDialog::getOpenFileName(this,"打开一个文件",
                                                    currentPath,"井数据文件(*.txt);;所有文件(*)");
    if(fileName.isEmpty()) return;
    QStringList fileContent;
    QFile file(fileName);
    if(file.open(QIODevice::ReadOnly|QIODevice::Text)){
        QTextStream stream(&file);
        ui->plainTextEdit->clear();
        while(!stream.atEnd()){
            QString str = stream.readLine();
            ui->plainTextEdit->appendPlainText(str);
            fileContent.append(str);
        }
        file.close();
        this->LabCurFile->setText("当前文件: "+fileName);
        initModelFromStringList(fileContent);
        ui->tableView->resizeRowsToContents();
        ui->actSave->setEnabled(true);
        ui->actAppend->setEnabled(true);
        ui->actDelete->setEnabled(true);
        ui->actInsert->setEnabled(true);
    }
}

void MainWindow::on_actSave_triggered()
{
    QString currentPath= QCoreApplication::applicationDirPath();
    QString fileName = QFileDialog::getSaveFileName(this,"选择一个文件",
                                                    currentPath,"井数据文件(*.txt);;所有文件(*)");
    if(fileName.isEmpty()) return;
    QFile file(fileName);
    if(!file.open(QIODevice::ReadWrite|QIODevice::Text|QIODevice::Truncate)) return;

    QTextStream stream(&file);

    QString str;
    ui->plainTextEdit->clear();
    QStandardItem *item;
    //获取表头文字
    for(int i=0;i<theModel->columnCount();i++){
        item = theModel->horizontalHeaderItem(i);
        str = str+item->text()+"\t\t";
    }
    stream<<str<<"\n";
    ui->plainTextEdit->appendPlainText(str);
    int j;
    for(int i=0;i<theModel->rowCount();i++){
        str="";
        for(j=0;j<theModel->columnCount()-1;j++){
            item =theModel->item(i,j);
            str=str+item->text()+"\t\t";
        }
        item =theModel->item(i,j);
        if(item->checkState()==Qt::Checked)
            str=str+"1";
        else
            str = str+"0";
        stream<<str<<"\n";
        ui->plainTextEdit->appendPlainText(str);
    }
}


void MainWindow::on_actModelData_triggered()
{
    QString str;
    ui->plainTextEdit->clear();
    QStandardItem *item;
    //获取表头文字
    for(int i=0;i<theModel->columnCount();i++){
        item = theModel->horizontalHeaderItem(i);
        str = str+item->text()+"\t";
    }
    ui->plainTextEdit->appendPlainText(str);
    int j;
    for(int i=0;i<theModel->rowCount();i++){
        str="";
        for(j=0;j<theModel->columnCount()-1;j++){
            item =theModel->item(i,j);
            str=str+item->text()+"\t";
        }
        item =theModel->item(i,j);
        if(item->checkState()==Qt::Checked)
            str=str+"1";
        else
            str = str+"0";
        ui->plainTextEdit->appendPlainText(str);
    }
}

void MainWindow::on_actAppend_triggered()
{
    QList<QStandardItem*> itemList;
    QStandardItem *item;
    for(int i =0;i<FixedColumnCount-1;i++){
        item=new QStandardItem("0");
        itemList<<item;
    }
    QString str=theModel->headerData(theModel->columnCount()-1,
                                     Qt::Horizontal,Qt::DisplayRole).toString();
    item =new QStandardItem(str);
    item->setCheckState(Qt::Checked);
    itemList<<item;
    theModel->appendRow(itemList);

    theSelection->clearSelection();
    QModelIndex index=theModel->index(theModel->rowCount()-1,0);
    theSelection->setCurrentIndex(index,QItemSelectionModel::Select);
}

void MainWindow::on_actInsert_triggered()
{
    QList<QStandardItem*> itemList;
    QStandardItem *item;
    for(int i =0;i<FixedColumnCount-1;i++){
        item=new QStandardItem("0");
        itemList<<item;
    }
    QString str=theModel->headerData(theModel->columnCount()-1,
                                     Qt::Horizontal,Qt::DisplayRole).toString();
    item =new QStandardItem(str);
    item->setCheckState(Qt::Checked);
    itemList<<item;
    int row = theSelection->currentIndex().row();
    theModel->insertRow(row,itemList);
    theSelection->clearSelection();
    QModelIndex index=theModel->index(row,0);
    theSelection->setCurrentIndex(index,QItemSelectionModel::Select);
}

void MainWindow::on_actDelete_triggered()
{
    QModelIndex index = theSelection->currentIndex();
    if(index.row() == theModel->rowCount()-1)
        theModel->removeRow(index.row());
    else{
        theModel->removeRow(index.row());
        theSelection->setCurrentIndex(index,QItemSelectionModel::Select);
    }

}

void MainWindow::on_actAlignLeft_triggered()
{
    on_actAlign_triggered(Qt::AlignLeft);
}

void MainWindow::on_actAlign_triggered(Qt::Alignment atextAlignment)
{
    if(!theSelection->hasSelection()) return;
    auto selectedIndexes = theSelection->selectedIndexes();
    for(int i=0;i<selectedIndexes.count();i++){
        auto index = selectedIndexes.at(i);
        QStandardItem *item =theModel->itemFromIndex(index);
        item->setTextAlignment(atextAlignment);
    }
}

void MainWindow::on_actAlignCenter_triggered()
{
    on_actAlign_triggered(Qt::AlignCenter);
}

void MainWindow::on_actAlignRight_triggered()
{
    on_actAlign_triggered(Qt::AlignRight);
}

void MainWindow::on_actFontBold_triggered(bool checked)
{
    if(!theSelection->hasSelection()) return;
    auto selectedIndexes = theSelection->selectedIndexes();
    for(int i=0;i<selectedIndexes.count();i++){
        auto index = selectedIndexes.at(i);
        QStandardItem *item =theModel->itemFromIndex(index);
        QFont font = item->font();
        font.setBold(checked);
        item->setFont(font);
    }
}
