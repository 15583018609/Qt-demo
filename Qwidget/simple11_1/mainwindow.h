#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include    <QLabel>
#include    <QString>

#include    <QtSql>
#include    <QDataWidgetMapper>

#include    "qwcomboboxdelegate.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QSqlDatabase  DB;//数据库连接
    QSqlTableModel  *tabModel;  //数据模型
    QItemSelectionModel *theSelection; //选择模型
    QDataWidgetMapper   *dataMapper; //数据映射
    QWComboBoxDelegate   delegateSex; //自定义数据代理，性别
    QWComboBoxDelegate   delegateDepart; //自定义数据代理，部门

    void openTab();//打开数据库
    void getFileNames();//获取字段名称
    void getFieldNames();
    Ui::MainWindow *ui;
private slots:
    void on_currentChanged(const QModelIndex &current,const QModelIndex &previous);
    void on_currentRowChanged(const QModelIndex &current,const QModelIndex &previous);
    void on_actOpenDB_triggered();
    void on_actRecAppend_triggered();
    void on_actRecInsert_triggered();
    void on_actRecDelete_triggered();
    void on_actSubmit_triggered();
    void on_actRevert_triggered();
    void on_actPhotoClear_triggered();
    void on_actPhoto_triggered();
    void on_actScan_triggered();
    void on_comboFields_currentIndexChanged(int index);
    void on_radioBtnAscend_clicked(bool checked);
    void on_radioBtnDescend_clicked(bool checked);
    void on_radioBtnMan_clicked(bool checked);
    void on_radioBtnWoman_clicked(bool checked);
    void on_radioBtnBoth_clicked(bool checked);
};
#endif // MAINWINDOW_H
