#include "mainwindow.h"
#include "ui_mainwindow.h"
#include    <QFileDialog>
#include    <QMessageBox>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setCentralWidget(ui->tableView);



    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectItems);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setAlternatingRowColors(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actOpenDB_triggered()
{
    QString aFile = QFileDialog::getOpenFileName(this,"打开数据库","","SQLITE数据(*.db *.db3)");
    if(aFile.isEmpty()) return;

    DB = QSqlDatabase::addDatabase("QSQLITE");
    DB.setDatabaseName(aFile);
    if(!DB.open()){
        QMessageBox::warning(this,"error","打开数据库失败");
        return;
    }

    tabModel = new QSqlRelationalTableModel(this,DB);
    tabModel->setTable("studInfo");
    tabModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    tabModel->setSort(0,Qt::AscendingOrder);
    tabModel->setHeaderData(0,Qt::Horizontal,"学号");
    tabModel->setHeaderData(1,Qt::Horizontal,"姓名");
    tabModel->setHeaderData(2,Qt::Horizontal,"性别");
    tabModel->setHeaderData(3,Qt::Horizontal,"学院");
    tabModel->setHeaderData(4,Qt::Horizontal,"专业");

    theSelection  = new QItemSelectionModel(tabModel);
    ui->tableView->setModel(tabModel);
    ui->tableView->setSelectionModel(theSelection);
    //建立联系
    tabModel->setRelation(3,
                          QSqlRelation("departments","departID","department"));
    tabModel->setRelation(4,
                          QSqlRelation("majors","majorID","major"));

    ui->tableView->setItemDelegate(new QSqlRelationalDelegate(ui->tableView));

    tabModel->select();



    ui->actOpenDB->setEnabled(false);
    ui->actRecAppend->setEnabled(true);
    ui->actRecDelete->setEnabled(true);
    ui->actRecInsert->setEnabled(true);
    ui->actFields->setEnabled(true);

}

void MainWindow::on_actFields_triggered()
{
    QSqlRecord emptyRec = tabModel->record();
    QString str;
    for(int i=0;i<emptyRec.count();i++){
        str = str+emptyRec.fieldName(i)+'\n';
    }
    QMessageBox::information(this,"所有字段名称",str);
}

void MainWindow::on_actRecAppend_triggered()
{
    //添加记录
    tabModel->insertRow(tabModel->rowCount(),QModelIndex()); //在末尾添加一个记录
    QModelIndex curIndex=tabModel->index(tabModel->rowCount()-1,1);//创建最后一行的ModelIndex
    theSelection->clearSelection();//清空选择项
    theSelection->setCurrentIndex(curIndex,QItemSelectionModel::Select);//设置刚插入的行为当前选择行
}

void MainWindow::on_actRecInsert_triggered()
{//插入记录
    QModelIndex curIndex=ui->tableView->currentIndex();
    tabModel->insertRow(curIndex.row(),QModelIndex());

    theSelection->clearSelection();//清除已有选择
    theSelection->setCurrentIndex(curIndex,QItemSelectionModel::Select);
}

void MainWindow::on_actSubmit_triggered()
{
    //保存修改
    bool res=tabModel->submitAll();
    if (!res)
        QMessageBox::information(this, "消息", "数据保存错误,错误信息\n"+tabModel->lastError().text(),
                                 QMessageBox::Ok,QMessageBox::NoButton);
    else
    {
        ui->actSubmit->setEnabled(false);
        ui->actRevert->setEnabled(false);
    }
}

void MainWindow::on_actRevert_triggered()
{//取消修改
    tabModel->revertAll();
    ui->actSubmit->setEnabled(false);
    ui->actRevert->setEnabled(false);
}

void MainWindow::on_actRecDelete_triggered()
{//删除当前记录
    tabModel->removeRow(theSelection->currentIndex().row());
    tabModel->submitAll(); //立即更新
}
