#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "formdoc.h"
#include <QMdiSubWindow>
#include <QFileDialog>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->mdiArea);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actDoc_New_triggered()
{
    FormDoc *formDoc = new FormDoc(this);
//    formDoc->setAttribute(Qt::WA_DeleteOnClose);
    ui->mdiArea->addSubWindow(formDoc);
    formDoc->show();
    ui->actCut->setEnabled(true);
    ui->actCopy->setEnabled(true);
    ui->actPaste->setEnabled(true);
    ui->actFont->setEnabled(true);
}

void MainWindow::on_actDoc_Open_triggered()
{
    bool needNew = false;
    FormDoc *formDoc ;
    if(ui->mdiArea->subWindowList().count()>0){
        formDoc=(FormDoc *)ui->mdiArea->activeSubWindow()->widget();
        needNew=formDoc->isFileOpened();
    }else{
        needNew = true;
    }
    if(needNew){
        formDoc = new FormDoc(this);
        ui->mdiArea->addSubWindow(formDoc);
    }
    QString fileName = QFileDialog::getOpenFileName(this,"open","","C程序文件(.h *cpp);;所有文件(*.*)");
    formDoc->loadFromFile(fileName);
    formDoc->show();
}

void MainWindow::on_actCloseALL_triggered()
{
    ui->mdiArea->closeAllSubWindows();
}

void MainWindow::on_actFont_triggered()
{
    FormDoc *formDoc =(FormDoc *)ui->mdiArea->activeSubWindow()->widget();
    formDoc->setTextFont();
}

void MainWindow::on_actCut_triggered()
{
    FormDoc *formDoc =(FormDoc *)ui->mdiArea->activeSubWindow()->widget();
    formDoc->textCut();
}

void MainWindow::on_actCopy_triggered()
{
    FormDoc *formDoc =(FormDoc *)ui->mdiArea->activeSubWindow()->widget();
    formDoc->textCopy();
}

void MainWindow::on_actPaste_triggered()
{
    FormDoc *formDoc =(FormDoc *)ui->mdiArea->activeSubWindow()->widget();
    formDoc->textPaste();
}

void MainWindow::on_actViewMode_triggered(bool checked)
{
    if(checked){
        ui->mdiArea->setViewMode(QMdiArea::TabbedView);
        ui->mdiArea->setTabsClosable(true);
        ui->actCascade->setEnabled(false);
        ui->actTile->setEnabled(false);
    }else{
        ui->mdiArea->setViewMode(QMdiArea::SubWindowView);
        ui->actCascade->setEnabled(true);
        ui->actTile->setEnabled(true);
    }
}

void MainWindow::on_actCascade_triggered()
{
    ui->mdiArea->cascadeSubWindows();
}

void MainWindow::on_actTile_triggered()
{
    ui->mdiArea->tileSubWindows();
}

void MainWindow::on_mdiArea_subWindowActivated(QMdiSubWindow *arg1)
{
    Q_UNUSED(arg1)
    if(ui->mdiArea->subWindowList().count()==0){
        ui->actCut->setEnabled(false);
        ui->actCopy->setEnabled(false);
        ui->actPaste->setEnabled(false);
        ui->actFont->setEnabled(false);
        ui->statusbar->clearMessage();
    }else{
        FormDoc *formDoc =(FormDoc *)ui->mdiArea->activeSubWindow()->widget();
        ui->statusbar->showMessage(formDoc->getCurFileName());
    }
}
