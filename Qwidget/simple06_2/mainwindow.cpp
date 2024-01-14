#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qdialogsetsize.h"
#include <QStringList>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    theModel = new QStandardItemModel(this);
    theSelection = new QItemSelectionModel(theModel);
    ui->tableView->setModel(theModel);
    ui->tableView->setSelectionModel(theSelection);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actTab_SetSize_triggered()
{
    QDialogSetSize *dig = new QDialogSetSize(this);
    dig->setRowsColums(theModel->rowCount(),theModel->columnCount());
    int ret = dig->exec();
    if(ret == QDialog::Accepted){
        int col = dig->columnCount();
        int row = dig->rowCount();
        theModel->setColumnCount(col);
        theModel->setRowCount(row);
    }
    delete dig;
}

void MainWindow::on_actTab_SetHeader_triggered()
{
    if(dialogHeader== NULL)
        dialogHeader = new DialogSetHeaders(this);
    if(dialogHeader->stringList().count()!=theModel->columnCount()){
        QStringList strList;
        for(int i=0;i<theModel->columnCount();i++){
            strList << theModel->headerData(i,Qt::Horizontal).toString();
        }
        dialogHeader->setStringList(strList);
    }
    int ret = dialogHeader->exec();
    if(ret ==QDialog::Accepted){
        QStringList strList = dialogHeader->stringList();
        theModel->setHorizontalHeaderLabels(strList);
    }
}
