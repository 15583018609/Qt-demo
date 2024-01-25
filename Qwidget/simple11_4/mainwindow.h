#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include    <QLabel>
#include    <QString>

#include    <QtSql>
#include    <QDataWidgetMapper>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actOpenDB_triggered();

    void on_actFields_triggered();

    void on_actRecAppend_triggered();

    void on_actRecInsert_triggered();

    void on_actSubmit_triggered();

    void on_actRevert_triggered();

    void on_actRecDelete_triggered();

private:
    QSqlDatabase  DB; //数据库连接

    QSqlRelationalTableModel  *tabModel;//数据模型

    QItemSelectionModel *theSelection;//选择模型
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
