#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QToolBar>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->splitter);
}

MainWindow::~MainWindow()
{
    delete ui;
}

