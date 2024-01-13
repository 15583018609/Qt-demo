#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::initUI()
{
    fLabCurFile = new QLabel;
    fLabCurFile ->setMidLineWidth(150);
    fLabCurFile ->setText("当前文件: ");
    ui->statusbar->addWidget(fLabCurFile);

    progressBar = new QProgressBar;
    progressBar ->setMinimum(5);
    progressBar ->setMaximum(50);
    progressBar ->setValue(ui->textEdit->font().pointSize());
    ui->statusbar ->addWidget(progressBar);

    spinFontSize = new QSpinBox;
    spinFontSize ->setMinimum(5);
    spinFontSize ->setMaximum(50);
    ui->toolBar ->addWidget(new QLabel("字体大小"));
    ui->toolBar ->addWidget(spinFontSize);

    comboFont = new QFontComboBox;
    ui->toolBar ->addWidget(new QLabel("字体"));
    ui->toolBar ->addWidget(comboFont);

    setCentralWidget(ui->textEdit);
}

void MainWindow::initSignalSlot()
{
    connect(spinFontSize,SIGNAL(valueChanged(int)),
            this,SLOT(on_spinBoxFontSize_valueChanged(int)));
    connect(comboFont,SIGNAL(currentIndexChanged(const Qstring&)),
            this,SLOT(on_comboFont_currentIndexChanged(const Qstring&)));

}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initUI();
    initSignalSlot();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actFontBlod_triggered(bool checked)
{
    QTextCharFormat fmt;
//    fmt = ui->textEdit->currentCharFormat();
    if(checked)
        fmt.setFontWeight(QFont::Bold);
    else
        fmt.setFontWeight(QFont::Normal);
    ui->textEdit->mergeCurrentCharFormat(fmt);

}

void MainWindow::on_textEdit_copyAvailable(bool b)
{
    ui->actCut->setEnabled(b);
    ui->actCopy->setEnabled(b);
    ui->actPaste->setEnabled(ui->textEdit->canPaste());
}

void MainWindow::on_textEdit_selectionChanged()
{
    QTextCharFormat fmt;
    fmt = ui->textEdit->currentCharFormat();
    ui->actFontItalic->setEnabled(fmt.fontItalic());
    ui->actFontBlod->setEnabled(fmt.font().bold());
    ui->actFontUnder->setEnabled(fmt.fontUnderline());
}

void MainWindow::on_spinBoxFontSize_valueChanged(int aFontSize)
{
    QTextCharFormat fmt;
    fmt.setFontPointSize(aFontSize);
    ui->textEdit->mergeCurrentCharFormat(fmt);
    progressBar->setValue(aFontSize);
}

void MainWindow::on_comboFont_currentIndexChanged(const QString &arg1)
{
     QTextCharFormat fmt;
     fmt.setFontFamily(arg1);
     ui->textEdit->mergeCurrentCharFormat(fmt);
}
