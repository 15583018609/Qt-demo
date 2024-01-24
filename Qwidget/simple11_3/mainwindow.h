#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include    <QLabel>
#include <QString>
#include <QtSql>
#include <QDataWidgetMapper>
#include "dialogdata.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void    openTable();//打开数据表
    void    updateRecord(int recNo); //更新记录
private slots:
    void on_actOpenDB_triggered();

    void on_actRecInsert_triggered();

    void on_actRecDelete_triggered();

    void on_actScan_triggered();

    void on_actRecEdit_triggered();

    void on_tableView_doubleClicked(const QModelIndex &index);
private:
    QSqlDatabase  DB; //数据库

    QSqlQueryModel  *qryModel; //数据库模型

    QItemSelectionModel *theSelection; //选择模型
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
