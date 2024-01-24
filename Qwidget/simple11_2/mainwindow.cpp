#include "mainwindow.h"
#include "ui_mainwindow.h"
#include    <QFileDialog>
#include    <QMessageBox>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setCentralWidget(ui->splitter);
    qryModel = new QSqlQueryModel(this);
    theSelection = new QItemSelectionModel(qryModel);
    ui->tableView->setModel(qryModel);
    ui->tableView->setSelectionModel(theSelection);

    dataMapper = new QDataWidgetMapper;
    dataMapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);
    dataMapper->setModel(qryModel);

    //选择行变化时
    connect(theSelection,SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
                this,SLOT(onCurrentrowchanged(QModelIndex,QModelIndex)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onCurrentrowchanged(const QModelIndex &current, const QModelIndex &previous)
{
    Q_UNUSED(previous);
    if (!current.isValid())
    {
        ui->dbLabPhoto->clear();
        return;
    }
    dataMapper->setCurrentModelIndex(current);
    bool first=(current.row()==0); //是否首记录
    bool last=(current.row()==qryModel->rowCount()-1);//是否尾记录

    ui->actRecFirst->setEnabled(!first); //更新使能状态
    ui->actRecPrevious->setEnabled(!first);
    ui->actRecNext->setEnabled(!last);
    ui->actRecLast->setEnabled(!last);

    int curRecNo=theSelection->currentIndex().row();
    QSqlRecord curRec = qryModel->record(curRecNo);
    int empNo = curRec.value("EmpNo").toInt();
    QSqlQuery query; //查询当前empNo的Memo和Photo字段的数据
    query.prepare("select EmpNo, Memo, Photo from employee where EmpNo = :ID");
    query.bindValue(":ID",empNo);
    query.exec();
    query.first();//回到第一条记录
    QVariant    va=query.value("Photo");//
    if (!va.isValid())  //图片字段内容为空
       ui->dbLabPhoto->clear();
    else{//显示照片
        QPixmap pic;
        QByteArray data = va.toByteArray();
        pic.loadFromData(data);
        ui->dbLabPhoto->setPixmap(pic.scaledToWidth(ui->dbLabPhoto->size().width()));
    }
    QVariant va2 = query.value("Memo");//显示备注
    ui->dbEditMemo->setPlainText(va2.toString());


}

void MainWindow::refreshTableView()
{
    int index =dataMapper->currentIndex();
    QModelIndex curIndex=qryModel->index(index,1);
    theSelection->clearSelection();
    theSelection->setCurrentIndex(curIndex,QItemSelectionModel::Select);
}


void MainWindow::on_actOpenDB_triggered()
{
    QString aFile = QFileDialog::getOpenFileName(this,"打开数据库","","数据库文件(*.db *.db3)");
    if(aFile.isEmpty()) return;
    DB=QSqlDatabase::addDatabase("QSQLITE");
    DB.setDatabaseName(aFile);
    if(!DB.open()){
        QMessageBox::warning(this,"错误","打开数据库失败");
        return;
    }
    qryModel->setQuery("SELECT EmpNo,Name,Gender,Height,Birthday,Mobile,Province,City,Department,"
                       "Education,Salary FROM employee ORDER BY EmpNo");
    if(qryModel->lastError().isValid()){
        QMessageBox::critical(this, "错误", "数据表查询错误,错误信息\n"+qryModel->lastError().text(),
                                 QMessageBox::Ok,QMessageBox::NoButton);
        return;
    }
    qryModel->setHeaderData(0,Qt::Horizontal,"工号");
    qryModel->setHeaderData(1,Qt::Horizontal,"姓名");
    qryModel->setHeaderData(2,Qt::Horizontal,"性别");
    qryModel->setHeaderData(3,Qt::Horizontal,"身高");
    qryModel->setHeaderData(4,Qt::Horizontal,"出生日期");
    qryModel->setHeaderData(5,Qt::Horizontal,"手机");
    qryModel->setHeaderData(6,Qt::Horizontal,"省份");
    qryModel->setHeaderData(7,Qt::Horizontal,"城市");
    qryModel->setHeaderData(8,Qt::Horizontal,"部门");
    qryModel->setHeaderData(9,Qt::Horizontal,"学历");
    qryModel->setHeaderData(10,Qt::Horizontal,"工资");

    //创建数据映射
    dataMapper->addMapping(ui->dbSpinEmpNo,0);//"empNo";
    dataMapper->addMapping(ui->dbEditName,1);//"Name";
    dataMapper->addMapping(ui->dbComboSex,2);//"Gender";

    dataMapper->addMapping(ui->dbSpinHeight,3);//"Height";
    dataMapper->addMapping(ui->dbEditBirth,4);//"Birthday";
    dataMapper->addMapping(ui->dbEditMobile,5);//"Mobile";

    dataMapper->addMapping(ui->dbComboProvince,6);//"Province";
    dataMapper->addMapping(ui->dbEditCity,7);//"City";
    dataMapper->addMapping(ui->dbComboDep,8);//"Department";

    dataMapper->addMapping(ui->dbComboEdu,9);//"Education";
    dataMapper->addMapping(ui->dbSpinSalary,10);//"Salary";

    dataMapper->toFirst();

    ui->actOpenDB->setEnabled(false);


}

void MainWindow::on_actRecFirst_triggered()
{
    //首记录
    dataMapper->toFirst();
    refreshTableView();
}

void MainWindow::on_actRecPrevious_triggered()
{//前一条记录
    dataMapper->toPrevious();
    refreshTableView();
}

void MainWindow::on_actRecNext_triggered()
{//后一条记录
    dataMapper->toNext();
    refreshTableView();
}

void MainWindow::on_actRecLast_triggered()
{//最后一条记录
    dataMapper->toLast();
    refreshTableView();
}
