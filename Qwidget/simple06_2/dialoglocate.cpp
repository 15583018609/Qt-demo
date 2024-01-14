#include "dialoglocate.h"
#include "ui_dialoglocate.h"
#include <QMessageBox>
#include <mainwindow.h>
DialogLocate::DialogLocate(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogLocate)
{
    ui->setupUi(this);
}

DialogLocate::~DialogLocate()
{
    QMessageBox::information(this,"提示","单元格定位对话框被删除");
    delete ui;
}

void DialogLocate::setRange(int rows,int cols)
{
    ui->spinBoxRow->setRange(0,rows-1);
    ui->spinBoxColumn->setRange(0,cols-1);
}

void DialogLocate::setValue(int rows, int cols)
{
    ui->spinBoxRow->setValue(rows);
    ui->spinBoxColumn->setValue(cols);
}

void DialogLocate::closeEvent(QCloseEvent *event)
{
    MainWindow *parW = (MainWindow*)parentWidget();
    parW->setActLocateEnable(true);
    parW->setDlgLocateNull();
}

void DialogLocate::on_btnSetText_clicked()
{
    int row = ui->spinBoxRow->value();
    int col = ui->spinBoxColumn->value();
    MainWindow *parW = (MainWindow*)parentWidget();
    parW->setAcellText(row,col,ui->edtCaption->text());
    if(ui->chkBoxRow->isChecked())
        ui->spinBoxRow->setValue(ui->spinBoxRow->value()+1);
    if(ui->chkBoxColumn->isChecked())
        ui->spinBoxColumn->setValue(ui->spinBoxColumn->value()+1);
}
