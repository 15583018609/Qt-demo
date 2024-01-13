#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDir>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    fileModel = new QFileSystemModel(this);
    fileModel->setRootPath(QDir::currentPath());
    ui->treeView->setModel(fileModel);
    ui->listView->setModel(fileModel);
    ui->tableView->setModel(fileModel);
    ui->tableView->verticalHeader()->setVisible(false);
    connect(ui->treeView,SIGNAL(clicked(QModelIndex)),ui->listView,SLOT(setRootIndex(QModelIndex)));
    connect(ui->treeView,SIGNAL(clicked(QModelIndex)),ui->tableView,SLOT(setRootIndex(QModelIndex)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_treeView_clicked(const QModelIndex &index)
{
    ui->labName->setText(fileModel->fileName(index));
    ui->labPath->setText(fileModel->filePath(index));
    ui->labType->setText(fileModel->type(index));
    unsigned size = fileModel->size(index)/1024;
    if(size<1024)
        ui->labSize->setText(QString::asprintf("%d KB",size));
    else
        ui->labSize->setText(QString::asprintf("%.2f MB",(float)size/1024));
    ui->checkBox->setChecked(fileModel->isDir(index));
}
