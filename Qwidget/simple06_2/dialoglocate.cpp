#include "dialoglocate.h"
#include "ui_dialoglocate.h"

DialogLocate::DialogLocate(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogLocate)
{
    ui->setupUi(this);
}

DialogLocate::~DialogLocate()
{
    delete ui;
}
