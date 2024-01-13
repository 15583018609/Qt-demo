#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->statusBar->addWidget(&labFileName);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actDockVisible_toggled(bool arg1)
{
    ui->dockWidget->setVisible(arg1);
}

void MainWindow::on_actDockFloat_toggled(bool arg1)
{
    ui->dockWidget->setFloating(arg1);
}

void MainWindow::on_dockWidget_topLevelChanged(bool topLevel)
{
    ui->actDockFloat->setChecked(topLevel);
}

void MainWindow::on_dockWidget_visibilityChanged(bool visible)
{
    ui->actDockVisible->setChecked(visible);
}

void MainWindow::on_actAddFolder_triggered()
{
    QString fullname = QFileDialog::getExistingDirectory();
    if(fullname.isEmpty()) return;

    QString dir = fullname.right(fullname.length()-fullname.lastIndexOf("/")-1);

    if(!ui->treeWidget->currentIndex().isValid()) return;

    QTreeWidgetItem *parItem = ui->treeWidget->currentItem();
    QTreeWidgetItem *item = new QTreeWidgetItem(itGroupItem);



    QIcon icon(":/images/icons/open3.bmp");
    item->setIcon(colItem,icon);
    item->setText(colItem,dir);
    item->setText(colItemType,"type:group");
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsAutoTristate
                   |Qt::ItemIsEnabled|Qt::ItemIsUserCheckable);

    item->setCheckState(colItem,Qt::Checked);
    parItem->addChild(item);
}

void MainWindow::on_actAddFiles_triggered()
{
    QStringList files = QFileDialog::getOpenFileNames(this,"选择一个或者多个文件","","Images(*.jpg)");
    if(files.isEmpty()) return;
    QTreeWidgetItem *parItem ;
    QTreeWidgetItem *item = ui->treeWidget->currentItem();
    if(item->type() == itImageItem)
        parItem = item->parent();
    else
        parItem = item->parent();
    foreach(auto file,files){
        item = new QTreeWidgetItem(itImageItem);
        QString str = file.right(file.length()-file.lastIndexOf("/")-1);
        QIcon icon(":/images/icons/31.ico");
        item->setIcon(colItem,icon);
        item->setText(colItem,str);
        item->setText(colItemType,"type:imageFile");
        item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsAutoTristate
                   |Qt::ItemIsEnabled|Qt::ItemIsUserCheckable);
        item->setData(colItem,Qt::UserRole,file);
        item->setCheckState(colItem,Qt::Checked);
        parItem->addChild(item);
    }
}

void MainWindow::on_treeWidget_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
     Q_UNUSED(previous);
    if(current == NULL) return;
    int var = current->type();
    switch (var) {
        case itTopItem:
            ui->actAddFiles->setEnabled(true);
            ui->actAddFolder->setEnabled(true);
            ui->actDeleteItem->setEnabled(false);
        break;
    case itGroupItem:
        ui->actAddFiles->setEnabled(true);
        ui->actAddFolder->setEnabled(true);
        ui->actDeleteItem->setEnabled(true);
        break;
    case itImageItem:
        ui->actAddFiles->setEnabled(true);
        ui->actAddFolder->setEnabled(false);
        ui->actDeleteItem->setEnabled(true);
        labFileName.setText(current->data(colItem,Qt::UserRole).toString());
        curPixmap.load(current->data(colItem,Qt::UserRole).toString());
        on_actZoomFitW_triggered();
        ui->actZoomFitH->setEnabled(true);
        ui->actZoomFitW->setEnabled(true);
        ui->actZoomIn->setEnabled(true);
        ui->actZoomOut->setEnabled(true);
        ui->actZoomRealSize->setEnabled(true);
        break;
    default:
        break;
    }
}

void MainWindow::on_actZoomFitW_triggered()
{
    int w = ui->scrollArea->width();
    int realW =curPixmap.width();
    pixRatio= (float)w/realW;
    QPixmap pix = curPixmap.scaledToWidth(w-30);\
    ui->label->setPixmap(pix);
}

void MainWindow::on_actScanItems_triggered()
{
    for(int i=0;i<ui->treeWidget->topLevelItemCount();i++){
        QTreeWidgetItem *item = ui->treeWidget->topLevelItem(i);
        changeItemCaption(item);
    }
}

void MainWindow::changeItemCaption(QTreeWidgetItem *item)
{
    QString str = "*"+item->text(colItem);
    item->setText(colItem,str);
    for(int i=0;i<item->childCount();i++){
        changeItemCaption(item->child(i));
    }
}

void MainWindow::on_actDeleteItem_triggered()
{
    QTreeWidgetItem *item = ui->treeWidget->currentItem();
    QTreeWidgetItem *parItem =item->parent();
    parItem->removeChild(item);
    delete  item;
}

void MainWindow::on_actZoomFitH_triggered()
{
    int H = ui->scrollArea->height();
    int realH =curPixmap.height();
    pixRatio= (float)H/realH;
    QPixmap pix = curPixmap.scaledToHeight(H-30);\
    ui->label->setPixmap(pix);
}

void MainWindow::on_actZoomIn_triggered()
{
    pixRatio*=1.2;
    int w = pixRatio*curPixmap.width();
    int h = pixRatio*curPixmap.height();
    QPixmap pix= curPixmap.scaled(w,h);
    ui->label->setPixmap(pix);
}

void MainWindow::on_actZoomOut_triggered()
{
    pixRatio/=1.2;
    int w = pixRatio*curPixmap.width();
    int h = pixRatio*curPixmap.height();
    QPixmap pix= curPixmap.scaled(w,h);
    ui->label->setPixmap(pix);
}

void MainWindow::on_actZoomRealSize_triggered()
{
    pixRatio =1;
    ui->label->setPixmap(curPixmap);
}
