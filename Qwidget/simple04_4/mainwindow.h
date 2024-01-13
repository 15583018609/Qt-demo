#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidgetItem>
#include <QPixmap>
#include <QLabel>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
//枚举类型treeItemType， 用于创建 QTreeWidgetItem 时作为节点的type, 自定义类型必须大于1000
//itTopItem 顶层节点;  itGroupItem 组节点； itImageItem 图片
    enum    treeItemType{itTopItem=1001,itGroupItem,itImageItem};
    //枚举类型，表示列号
    enum    treeColNum{colItem=0, colItemType=1}; //目录树列的编号定义

    QPixmap curPixmap;
    QLabel  labFileName;
    float pixRatio;

    void changeItemCaption(QTreeWidgetItem *item);

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actDockVisible_toggled(bool arg1);

    void on_actDockFloat_toggled(bool arg1);

    void on_dockWidget_topLevelChanged(bool topLevel);

    void on_dockWidget_visibilityChanged(bool visible);

    void on_actAddFolder_triggered();

    void on_actAddFiles_triggered();

    void on_treeWidget_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);

    void on_actZoomFitW_triggered();

    void on_actScanItems_triggered();


    void on_actDeleteItem_triggered();

    void on_actZoomFitH_triggered();

    void on_actZoomIn_triggered();

    void on_actZoomOut_triggered();

    void on_actZoomRealSize_triggered();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
