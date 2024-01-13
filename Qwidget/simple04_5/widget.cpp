#include "widget.h"
#include "ui_widget.h"
#include <QDate>
#include <QTableWidgetItem>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

void Widget::createItemsARow(int rowNo, QString Name, QString Sex, QDate birth, QString Nation, bool isPM, int score)
{
    QTableWidgetItem *item;
    unsigned StudID = 20202020;
    //Name
    item = new QTableWidgetItem(Name,ctName);
    item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    item->setData(Qt::UserRole,StudID++);
    ui->tableInfo->setItem(rowNo,colName,item);

    //Sex
    item = new QTableWidgetItem(Sex,ctSex);
    QIcon icon;
    if(Sex == "男")
        icon.addFile(":/images/icons/boy.ico");
    else
        icon.addFile(":/images/icons/girl.ico");
    item->setIcon(icon);
    item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ui->tableInfo->setItem(rowNo,colSex,item);

    //birth
    item = new QTableWidgetItem(birth.toString("yyyy-MM-dd"),ctBirth);
    item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ui->tableInfo->setItem(rowNo,colBirth,item);

    //Nation
    item = new QTableWidgetItem(Nation,ctNation);
    item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ui->tableInfo->setItem(rowNo,colNation,item);

    //isParty
    item = new QTableWidgetItem("党员",ctPartyM);
    if(isPM)
        item->setCheckState(Qt::Checked);
    else
        item->setCheckState(Qt::Unchecked);
    item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    item->setBackgroundColor(Qt::yellow);
    ui->tableInfo->setItem(rowNo,colPartyM,item);

    //Score
    item = new QTableWidgetItem(QString::number(score),ctScore);
    item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ui->tableInfo->setItem(rowNo,colScore,item);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_btnSetHeader_clicked()
{
    QTableWidgetItem *headerItem;
    QStringList headerText;
    headerText<<"姓 名"<<"性 别"<<"出生日期"<<"民 族"<<"分 数"<<"是否党员";
    ui->tableInfo->setColumnCount(headerText.count());
    for(int i=0;i<ui->tableInfo->columnCount();i++){
        headerItem = new QTableWidgetItem(headerText.at(i));
        QFont   font = ui->tableInfo->font();
        font.setBold(true);
        font.setPointSize(12);
        headerItem->setFont(font);
        headerItem->setTextColor(Qt::red);
        ui->tableInfo->setHorizontalHeaderItem(i,headerItem);
    }
}

void Widget::on_btnSetRows_clicked()
{
    ui->tableInfo->setRowCount(ui->spinRowCount->value());
    ui->tableInfo->setAlternatingRowColors(ui->chkBoxRowColor->isChecked());

}

void Widget::on_chkBoxRowColor_clicked(bool checked)
{
    ui->tableInfo->setAlternatingRowColors(checked);
}

void Widget::on_btnIniData_clicked()
{
    QString strName,strSex;
    bool  isParty = false;
    QDate birth;
    birth.setDate(1997,8,06);
    ui->tableInfo->clearContents();
    for(int i=0;i<ui->tableInfo->rowCount();i++){
        strName =QString::asprintf("学生%d",i);
        i%2 == 0 ? strSex = "男" : strSex = "女";
        createItemsARow(i,strName,strSex,birth,"汉族",isParty,80);
        birth = birth.addDays(20);
        isParty = !isParty;
    }
}

void Widget::on_btnInsertRow_clicked()
{
    int row = ui->tableInfo->currentRow();
    ui->tableInfo->insertRow(row);
    createItemsARow(row,"新学生","男",QDate::fromString("1990-11-23","yyyy-MM-dd"),"苗族",true,90);
}

void Widget::on_btnAppendRow_clicked()
{
    int row = ui->tableInfo->rowCount();
    ui->tableInfo->insertRow(row);
    createItemsARow(row,"新学生","女",QDate::fromString("2000-11-23","yyyy-MM-dd"),"苗族",true,90);
}

void Widget::on_btnDelCurRow_clicked()
{
    ui->tableInfo->removeRow(ui->tableInfo->currentRow());
}

void Widget::on_btnAutoHeght_clicked()
{
    ui->tableInfo->resizeRowsToContents();
}

void Widget::on_btnAutoWidth_clicked()
{
    ui->tableInfo->resizeColumnsToContents();
}

void Widget::on_btnReadToEdit_clicked()
{
    ui->plainTextEdit->clear();
    QTableWidgetItem *celltem;
    QString str;
    for(int i=0;i<ui->tableInfo->rowCount();i++){
        for(int j= 0;j<ui->tableInfo->columnCount()-1;j++){
            celltem = ui->tableInfo->item(i,j);
            str = str+celltem->text()+" ";
        }
        celltem = ui->tableInfo->item(i,colPartyM);
        if(celltem->checkState() == Qt::Checked)
            str = str +"党员";
        else
            str = str +"群众";
        ui->plainTextEdit->appendPlainText(str);
        str = "";

    }
}


void Widget::on_chkBoxTabEditable_clicked(bool checked)
{
    if(checked)
        ui->tableInfo->setEditTriggers(QAbstractItemView::DoubleClicked
                                       |QAbstractItemView::SelectedClicked);
    else
        ui->tableInfo->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void Widget::on_chkBoxHeaderH_clicked(bool checked)
{
    ui->tableInfo->horizontalHeader()->setVisible(checked);
}

void Widget::on_chkBoxHeaderV_clicked(bool checked)
{
    ui->tableInfo->verticalHeader()->setVisible(checked);
}



void Widget::on_rBtnSelectRow_clicked()
{
    ui->tableInfo->setSelectionBehavior(QAbstractItemView::SelectRows);
}

void Widget::on_rBtnSelectItem_clicked()
{
    ui->tableInfo->setSelectionBehavior(QAbstractItemView::SelectItems);
}
