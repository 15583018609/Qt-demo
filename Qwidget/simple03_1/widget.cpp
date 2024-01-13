#include "widget.h"
#include "ui_widget.h"
#include "qperson.h"
#include <QMetaProperty>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->spinBoxBoy->setProperty("isBoy",true);
    ui->spinBoxGirl->setProperty("isBoy",false);

    boy = new QPerson("王小明");
    boy->setProperty("score",95);
    boy->setProperty("age",10);
    boy->setProperty("sex","Boy");

    connect(boy,&QPerson::ageChanged,this,&Widget::on_ageChanged);

    girl=new QPerson("张小丽");
    girl->setProperty("score",81);
    girl->setProperty("age",20);
    girl->setProperty("sex","Girl");//动态属性
    connect(girl,&QPerson::ageChanged,this,&Widget::on_ageChanged);

    connect(ui->spinBoxBoy,SIGNAL(valueChanged(int)),this,
            SLOT(on_spin_valueChanged(int)));

    connect(ui->spinBoxGirl,SIGNAL(valueChanged(int)),this,
            SLOT(on_spin_valueChanged(int)));

}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_spin_valueChanged(int arg1)
{
    Q_UNUSED(arg1);
    QSpinBox *spinBox = qobject_cast<QSpinBox*>(sender());
    if(spinBox-property("isBoy").toBool())
        boy ->setAge(spinBox->value());
    else
        girl ->setAge(spinBox->value());
}

void Widget::on_ageChanged(int value)
{
    Q_UNUSED(value);
    QPerson *aPerson = qobject_cast<QPerson*>(sender());
    QString aName = aPerson->property("name").toString();
    QString aSex = aPerson->property("sex").toString();
    int aAge = aPerson->age();
    qDebug()<<"This is the aName"<< aName;
    ui->textEdit->appendPlainText(aName+","+aSex
                                  +QString::asprintf(",年龄=%d",aAge));

}

void Widget::on_btnBoyInc_clicked()
{
    qDebug()<<"Boy is click";
    boy->incAge();
}

void Widget::on_btnClassInfo_clicked()
{
    const QMetaObject *meta = girl ->metaObject();
    ui->textEdit->clear();
    ui->textEdit->appendPlainText("==元对象信息==\n");
    ui->textEdit->appendPlainText(
                QString ("类命令：%1\n").arg(meta->className()));
    ui->textEdit->appendPlainText("property\n");
    for(int i = meta->propertyOffset();i < meta->propertyCount();i++){
        QMetaProperty prop= meta->property(i);
        const char *proName = prop.name();
        QString propValue  = boy->property(proName).toString();
        ui->textEdit->appendPlainText(
                    QString("属性名称： %1,属性值：%2\n").arg(proName).arg(propValue));
    }

    ui->textEdit->appendPlainText("");
    ui->textEdit->appendPlainText("class info");

    for(int m=meta->classInfoOffset(); m < meta->classInfoCount();m++){
        QMetaClassInfo classinfo = meta->classInfo(m);
        ui->textEdit->appendPlainText(
                    QString( "Name= %1 value = %2")
                    .arg(classinfo.name()).arg(classinfo.value()));

    }

}

void Widget::on_btnGirInc_clicked()
{
    qDebug()<<"girl is click";
     girl->incAge();

}
