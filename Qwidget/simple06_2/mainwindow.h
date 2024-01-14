#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QItemSelectionModel>
#include "dialogsetheaders.h"
#include "dialoglocate.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setActLocateEnable(bool enable);
    void  setDlgLocateNull();
    void  setAcellText(int row,int col,QString text);
private slots:
    void on_actTab_SetSize_triggered();

    void on_actTab_SetHeader_triggered();

    void on_actTab_Locate_triggered();

    void on_tableView_clicked(const QModelIndex &index);

private:
    QStandardItemModel *theModel;
    QItemSelectionModel *theSelection;
    DialogSetHeaders *dialogHeader=NULL;
    DialogLocate *dialogLocate=NULL;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
