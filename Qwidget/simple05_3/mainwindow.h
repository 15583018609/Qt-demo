#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QStandardItemModel>
#include <QItemSelectionModel>
#define FixedColumnCount 6
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    //用于状态栏的信息显示
        QLabel  *LabCurFile;  //当前文件
        QLabel  *LabCellPos;    //当前单元格行列号
        QLabel  *LabCellText;   //当前单元格内容

        QStandardItemModel  *theModel;//数据模型
        QItemSelectionModel *theSelection;//Item选择模型


private slots:
        void on_currentChanged(const QModelIndex &current,const QModelIndex &previous);
        void on_actOpen_triggered();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
