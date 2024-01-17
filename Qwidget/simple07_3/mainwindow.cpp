#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_117_clicked()
{
    QString curPath =QDir::currentPath();
    QString fileName = QFileDialog::getOpenFileName(this,"",curPath,"(*.*)");
    ui->editFile->setText(fileName);
}

void MainWindow::on_pushButton_118_clicked()
{
    QString curPath =QDir::currentPath();
    QString dirName = QFileDialog::getExistingDirectory(this,"",curPath);
    ui->editDir->setText(dirName);
}

void MainWindow::on_pushButton_119_clicked()
{
    ui->plainTextEdit->clear();
}

void MainWindow::on_pushButton_5_clicked()
{

    getBtnInfo(sender());
    ui->plainTextEdit->appendPlainText(QCoreApplication::applicationDirPath());

}

void MainWindow::getBtnInfo(QObject *btn)
{
    QPushButton* btn2 = static_cast<QPushButton*>(btn);
    ui->plainTextEdit->appendPlainText(btn2->text());
    ui->plainTextEdit->appendPlainText(btn2->toolTip());
}

void MainWindow::on_pushButton_67_clicked()
{
    getBtnInfo(sender());
    QString sours = ui->editFile->text();
    QFileInfo info(sours);
    QString dest =info.path()+"/"+info.fileName()+"副本"+info.suffix();
    QFile::copy(sours,dest);
    ui->plainTextEdit->appendPlainText("源文件："+sours);
    ui->plainTextEdit->appendPlainText("副本"+dest+"\n");
}
