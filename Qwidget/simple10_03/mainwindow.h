#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSplitter>
#include <QColorDialog>
#include <QtDataVisualization>
using namespace QtDataVisualization;
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void init3DGraph();
private slots:
    void on_comboDrawMode_currentIndexChanged(int index);

    void on_btnGrad1_clicked();

    void on_btnBarColor_clicked();

private:
    QSplitter *splitter;
    Q3DSurface *graph3D;
    QSurface3DSeries *series;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
