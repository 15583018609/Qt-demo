#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QItemSelectionModel>
#include "dialogsetheaders.h"
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
    void on_actTab_SetSize_triggered();

    void on_actTab_SetHeader_triggered();

private:
    QStandardItemModel *theModel;
    QItemSelectionModel *theSelection;
    DialogSetHeaders *dialogHeader=NULL;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
