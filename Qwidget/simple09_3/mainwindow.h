#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include<QMainWindow>
#include<QtCharts>
#include<QPointF>
#include<QStandardItemModel>
QT_CHARTS_USE_NAMESPACE
#define fixedColumnCount 5
#define initDataRowCount 10
#define colNoName 0
#define colNoMath 1
#define colNoChinese 2
#define colNoEnglish 3
#define colNoAverage 4

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void initData();
    void sureyData();
    void buildBarChartA();
    void initBarChart();

private slots:
    void on_actGenData_triggered();

    void on_actTongJi_triggered();

    void on_btnBuildBarChart_clicked();

private:
    QStandardItemModel *theModel;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
