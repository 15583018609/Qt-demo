#include "dialog.h"
#include "ui_dialog.h"
#include <QFileDialog>
#include <QColorDialog>
#include <QFontDialog>
#include <QInputDialog>
#include <QMessageBox>
Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::on_btnClearText_2_clicked()
{
    ui->plainTextEdit->clear();
}

void Dialog::on_btnOpen_2_clicked()
{
    QString curPath = QDir::currentPath();
    QString digTitle = "选择对话框";
    QString filter = "文本文件(*,txt);;图片文件(*.jpg *.gig);;所有格式(*.*)";
    QString fileName = QFileDialog::getOpenFileName(this,digTitle,curPath,filter);
    if(fileName.isEmpty()) return;
    ui->plainTextEdit->appendPlainText(fileName);
}

void Dialog::on_btnOpenMulti_2_clicked()
{
    QString curPath = QDir::currentPath();
    QString digTitle = "选择对话框";
    QString filter = "文本文件(*,txt);;图片文件(*.jpg *.gig);;所有格式(*.*)";
    QStringList fileNames = QFileDialog::getOpenFileNames(this,digTitle,curPath,filter);
    if(fileNames.count()== 0) return;
    foreach(auto str,fileNames){
        ui->plainTextEdit->appendPlainText(str);
    }
}

void Dialog::on_btnSelDir_2_clicked()
{
    QString curPath = QDir::currentPath();
    QString digTitle = "选择对话框";
    QString selectedDir = QFileDialog::getExistingDirectory(this,digTitle,curPath,QFileDialog::ShowDirsOnly);
    if(selectedDir.isEmpty()) return;
    ui->plainTextEdit->appendPlainText(selectedDir);
}

void Dialog::on_btnSave_2_clicked()
{
    QString curPath = QCoreApplication::applicationDirPath();
    QString digTitle = "选择对话框";
    QString filter = "文本文件(*,txt);;图片文件(*.jpg *.gig);;所有格式(*.*)";
    QString fileName = QFileDialog::getSaveFileName(this,digTitle,curPath,filter);
    if(fileName.count()== 0) return;
    ui->plainTextEdit->appendPlainText(fileName);
}

void Dialog::on_btnColor_2_clicked()
{
    QPalette pal = ui->plainTextEdit->palette();
    QColor initColor =pal.color(QPalette::Text);
    QColor color = QColorDialog::getColor(initColor,this,"选择颜色");
    if(!color.isValid()) return;
    pal.setColor(QPalette::Text,color);
    ui->plainTextEdit->setPalette(pal);

}

void Dialog::on_btnFont_2_clicked()
{
    bool ok = false;
    QFont initFont = ui->plainTextEdit->font();
    QFont font=QFontDialog::getFont(&ok,initFont,this,"选择字体");
    if(!ok) return;
    ui->plainTextEdit->setFont(font);
}

void Dialog::on_btnInputString_2_clicked()
{
    QString digTitle = "输入文字对话框";
    QString texLabel = "请输入文件名";
    QString defaultInput = "xxx.txt";
    QLineEdit::EchoMode echoMode = QLineEdit::Normal;
    bool ok = false;
    QString str = QInputDialog::getText(this,digTitle,texLabel,echoMode,defaultInput,&ok);
    if(!ok) return;
    ui->plainTextEdit->appendPlainText(str);
}

void Dialog::on_btnInputInt_2_clicked()
{
    QString digTitle = "输入整数对话框";
    QString texLabel = "请输入整数";
    int defaultValue = ui->plainTextEdit->font().pointSize();
    int minValue = 0,maxValue = 100;
    bool ok = false;
    int value = QInputDialog::getInt(this,digTitle,texLabel,defaultValue,minValue,maxValue,1,&ok);
    if(!ok) return;
    QFont font = ui->plainTextEdit->font();
    font.setPointSize(value);
    ui->plainTextEdit->setFont(font);
    ui->plainTextEdit->appendPlainText(QString::asprintf("输入了一个整数：%d",value));
}

void Dialog::on_btnInputFloat_2_clicked()
{
    QString digTitle = "输入浮点数对话框";
    QString texLabel = "请输入浮点数";
    float defaultValue = 15.0;
    float minValue = 0.0,maxValue = 100.0;
    bool ok = false;
    float value = QInputDialog::getDouble(this,digTitle,texLabel,defaultValue,minValue,maxValue,2,&ok);
    if(!ok) return;
    ui->plainTextEdit->appendPlainText(QString::asprintf("输入了一个整数：%.2f",value));
}

void Dialog::on_btnInputItem_2_clicked()
{
    QStringList items;
    items <<"优秀" <<"良好"<<"及格"<<"不及格";
    QString digTitle = "输入条目对话框";
    QString texLabel = "请选择条目";
    bool ok = false;
    QString text = QInputDialog::getItem(this,digTitle,texLabel,items,0,true,&ok);
    if(!ok||text.isEmpty()) return;
    ui->plainTextEdit->appendPlainText(text);
}

void Dialog::on_btnMsgQuestion_2_clicked()
{
    QString digTitle = "Question消息框";
    QString texLabel = "文件已被修改，是否保存？";
    QMessageBox::StandardButtons result;
    result = QMessageBox::question(this,digTitle,texLabel,QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel,QMessageBox::NoButton);
    QString str;
    if(result == QMessageBox::Yes)
        str = "Question消息框: yes 被选中";
    else if(result == QMessageBox::No)
        str = "Question消息框: no 被选中";
    else if(result == QMessageBox::Cancel)
        str = "Question消息框: cancel 被选中";
    else
        str = "";
    ui->plainTextEdit->appendPlainText(str);
}

void Dialog::on_btnMsgInformation_2_clicked()
{
    QMessageBox::information(this,"Title","text",QMessageBox::Ok);
}

void Dialog::on_btnMsgWarning_2_clicked()
{
    QMessageBox::warning(this,"Title","text",QMessageBox::Ok);
}

void Dialog::on_btnMsgCritical_2_clicked()
{
     QMessageBox::critical(this,"Title","text",QMessageBox::Ok);
}

void Dialog::on_btnMsgAbout_2_clicked()
{
    QMessageBox::about(this,"Title","text");
}

void Dialog::on_btnMsgAboutQt_2_clicked()
{
    QMessageBox::aboutQt(this,"Title");

}
