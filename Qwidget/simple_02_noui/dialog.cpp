#include "dialog.h"
#include <QHBoxLayout>
#include <QVBoxLayout>

void Dialog::initUI()
{
    checkBoxUnderline = new QCheckBox(tr("Underline"));
    checkBoxItalic = new QCheckBox(tr("Italic"));
    checkBoxBlod = new QCheckBox(tr("Blod"));

    QHBoxLayout *HLayout1 = new QHBoxLayout;
    HLayout1->addWidget(checkBoxUnderline);
    HLayout1->addWidget(checkBoxItalic);
    HLayout1->addWidget(checkBoxBlod);

    rBtnRed = new QRadioButton(tr("Red"));
    rBtnBlue = new QRadioButton(tr("Blue"));
    rBtnBlack = new QRadioButton(tr("Black"));

    QHBoxLayout *HLayout2 = new QHBoxLayout;
    HLayout2->addWidget(rBtnRed);
    HLayout2->addWidget(rBtnBlue);
    HLayout2->addWidget(rBtnBlack);

    plainTextEdit = new QPlainTextEdit();
    QFont font = plainTextEdit->font();
    font.setPointSize(20);
    plainTextEdit->setFont(font);
    plainTextEdit->setPlainText("Hello World!\n\nThis is a Demo!");


    btnOK = new QPushButton(tr("确认"));
    btnCancel = new QPushButton(tr("取消"));
    btnClose = new QPushButton(tr("退出"));

    QHBoxLayout *HLayout3 = new QHBoxLayout;
    HLayout3->addStretch();
    HLayout3->addWidget(btnOK);
    HLayout3->addWidget(btnCancel);
    HLayout3->addStretch();
    HLayout3->addWidget(btnClose);

    QVBoxLayout *VLayout = new QVBoxLayout;
    VLayout->addLayout(HLayout1);
    VLayout->addLayout(HLayout2);
    VLayout->addWidget(plainTextEdit);
    VLayout->addLayout(HLayout3);
    setLayout(VLayout);

}

void Dialog::iniSignalSlots()
{
    connect(btnOK,SIGNAL(clicked()),this,SLOT(accpet()));
    connect(btnCancel,SIGNAL(clicked()),this,SLOT(rejcet()));
    connect(btnClose,SIGNAL(clicked()),this,SLOT(close()));

    connect(checkBoxUnderline,SIGNAL(clicked(bool)),this,SLOT(on_checkUnderline(bool)));
    connect(checkBoxItalic,SIGNAL(clicked(bool)),this,SLOT(on_checkItalic(bool)));
    connect(checkBoxBlod,SIGNAL(clicked(bool)),this,SLOT(on_checkBlod(bool)));

    connect(rBtnBlack,SIGNAL(clicked()),this,SLOT(setTextFontColor()));
    connect(rBtnBlue,SIGNAL(clicked()),this,SLOT(setTextFontColor()));
    connect(rBtnRed,SIGNAL(clicked()),this,SLOT(setTextFontColor()));

}

void Dialog::on_checkUnderline(bool checked)
{
    QFont font = plainTextEdit->font();
    font.setUnderline(checked);
    plainTextEdit->setFont(font);
}

void Dialog::on_checkItalic(bool checked)
{
    QFont font = plainTextEdit->font();
    font.setItalic(checked);
    plainTextEdit->setFont(font);
}

void Dialog::on_checkBlod(bool checked)
{
    QFont font = plainTextEdit->font();
    font.setBold(checked);
    plainTextEdit->setFont(font);
}

void Dialog::setTextFontColor()
{
    QPalette pelt = plainTextEdit->palette();
    if(rBtnBlack->isChecked())
        pelt.setColor(QPalette::Text,Qt::black);
    else if(rBtnBlue->isChecked())
        pelt.setColor(QPalette::Text,Qt::blue);
    else if(rBtnRed->isChecked())
        pelt.setColor(QPalette::Text,Qt::red);
    else
        pelt.setColor(QPalette::Text,Qt::black);
    plainTextEdit->setPalette(pelt);
}

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
{
    initUI();
    iniSignalSlots();
}

Dialog::~Dialog()
{
}

