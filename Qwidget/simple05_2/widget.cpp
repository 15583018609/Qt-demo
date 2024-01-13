#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    theModel = new QStringListModel(this);
    QStringList strlist;
    strlist <<"Item1"<<"Item2"<<"Item3"<<"Item4";
    theModel->setStringList(strlist);
    ui->listView->setModel(theModel);

    ui->listView->setEditTriggers(QAbstractItemView::DoubleClicked|
                                  QAbstractItemView::SelectedClicked);


}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_btnTextClear_clicked()
{
    ui->plainTextEdit->clear();
}

void Widget::on_btnTextImport_clicked()
{
    QStringList strlisr = theModel->stringList();
    foreach(auto str,strlisr){
            ui->plainTextEdit->appendPlainText(str);
    }
}

void Widget::on_btnIniList_clicked()
{
    QStringList strlist;
    strlist <<"Item1"<<"Item2"<<"Item3"<<"Item4";
    theModel->setStringList(strlist);
    ui->listView->setModel(theModel);
}

void Widget::on_btnListDelete_clicked()
{
    theModel->removeRow(ui->listView->currentIndex().row());
}

void Widget::on_btnListClear_clicked()
{
    theModel->removeRows(0,theModel->rowCount());
}

void Widget::on_btnListAppend_clicked()
{
    theModel->insertRow(theModel->rowCount());
    QModelIndex index = theModel->index(theModel->rowCount()-1,0);
    theModel->setData(index,"new Item",Qt::DisplayRole);
    ui->listView->setCurrentIndex(index);
}

void Widget::on_btnListInsert_clicked()
{
    theModel->insertRow(ui->listView->currentIndex().row());
    QModelIndex index = theModel->index(ui->listView->currentIndex().row()-1,0);
    theModel->setData(index,"insert Item",Qt::DisplayRole);
    ui->listView->setCurrentIndex(index);
}

void Widget::on_listView_clicked(const QModelIndex &index)
{
    ui->label->setText(QString::asprintf("行: %d , 列： %d",index.row(),index.column()));
}
