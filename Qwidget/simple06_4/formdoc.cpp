#include "formdoc.h"
#include "ui_formdoc.h"
#include <QTextStream>
#include <QFileInfo>
#include <QFontDialog>
FormDoc::FormDoc(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormDoc)
{
    ui->setupUi(this);
}

FormDoc::~FormDoc()
{
    delete ui;
}

bool FormDoc::isFileOpened()
{
    return mFileOpened;
}

void FormDoc::loadFromFile(QString fileName)
{
    QFile file(fileName);
    if(file.open(QIODevice::ReadOnly|QIODevice::Text)){
        QTextStream stream(&file);
        ui->plainTextEdit->clear();
        ui->plainTextEdit->setPlainText(stream.readAll());
        file.close();
        mCurrentFileName = fileName;
        QFileInfo fileInfo(fileName);
        QString str=fileInfo.fileName();
        setWindowTitle(str);
        mFileOpened = true;

    }
}

QString FormDoc::getCurFileName()
{
    return mCurrentFileName;
}

void FormDoc::setTextFont()
{
    QFont font = ui->plainTextEdit->font();
    bool ok;
    font = QFontDialog::getFont(&ok,font);
    ui->plainTextEdit->setFont(font);

}

void FormDoc::textCopy()
{
    ui->plainTextEdit->copy();
}

void FormDoc::textPaste()
{
    ui->plainTextEdit->paste();
}

void FormDoc::textCut()
{
    ui->plainTextEdit->cut();
}
