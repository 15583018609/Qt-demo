#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    QObject::connect(ui->rBtnBlack, SIGNAL(clicked()), this, SLOT(setTextFontColor()));
    QObject::connect(ui->rBtnRed, SIGNAL(clicked()), this, SLOT(setTextFontColor()));
    QObject::connect(ui->rBtnBlue, SIGNAL(clicked()), this, SLOT(setTextFontColor()));
}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::on_checkBoxUderline_clicked(bool checked)
{
    QFont font = ui ->plainTextEdit ->font();
    font.setUnderline(checked);
    ui->plainTextEdit->setFont(font);
}

void Dialog::on_checkBoxItalic_clicked(bool checked)
{
    QFont font = ui ->plainTextEdit ->font();
    font.setItalic(checked);
    ui->plainTextEdit->setFont(font);
}


void Dialog::on_checkBoxBold_clicked(bool checked)
{
    QFont font = ui ->plainTextEdit ->font();
    font.setBold(checked);
    ui->plainTextEdit->setFont(font);
}

void Dialog::setTextFontColor()
{
    QPalette plet= ui->plainTextEdit->palette();
    if (ui->rBtnBlack->isChecked())
        plet.setColor(QPalette::Text,Qt::black);
    else if(ui->rBtnBlue->isChecked())
        plet.setColor(QPalette::Text,Qt::blue);
    else if(ui->rBtnRed->isChecked())
        plet.setColor(QPalette::Text,Qt::red);
    else
        plet.setColor(QPalette::Text,Qt::black);
    ui->plainTextEdit->setPalette(plet);
}
