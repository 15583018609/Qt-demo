#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>


void MainWindow::on_currentChanged(const QModelIndex &current,const QModelIndex &previous)
{
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
                                                    currentPath,"");

}
