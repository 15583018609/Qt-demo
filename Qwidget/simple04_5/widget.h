#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QDate>
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

private:
    //  自定义单元格Type的类型，在创建单元格的Item时使用
        enum    CellType{ctName=1000,ctSex,ctBirth,ctNation,ctPartyM,ctScore}; //各单元格的类型

    //  各字段在表格中的列号
        enum    FieldColNum{colName=0, colSex,colBirth,colNation,colScore,colPartyM};

public:
    Widget(QWidget *parent = nullptr);

    void    createItemsARow(int rowNo,QString Name,QString Sex,QDate birth,
                            QString Nation,bool isPM,int score); //为某一行创建items

    ~Widget();

private slots:
    void on_btnSetHeader_clicked();

    void on_btnSetRows_clicked();

    void on_chkBoxRowColor_clicked(bool checked);

    void on_btnIniData_clicked();

    void on_btnInsertRow_clicked();

    void on_btnAppendRow_clicked();

    void on_btnDelCurRow_clicked();

    void on_btnAutoHeght_clicked();

    void on_btnAutoWidth_clicked();

    void on_btnReadToEdit_clicked();

    void on_chkBoxTabEditable_clicked(bool checked);

    void on_chkBoxHeaderH_clicked(bool checked);

    void on_chkBoxHeaderV_clicked(bool checked);


    void on_rBtnSelectRow_clicked();

    void on_rBtnSelectItem_clicked();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
