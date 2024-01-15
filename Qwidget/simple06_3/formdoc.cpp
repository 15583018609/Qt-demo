#include "formdoc.h"
#include "ui_formdoc.h"
#include <QVBoxLayout>
#include <QToolBar>


FormDoc::FormDoc(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormDoc)
{
    ui->setupUi(this);
    QToolBar *localToolBar = new QToolBar("文档",this);
    localToolBar->addAction(ui->actOpen);

    //
    localToolBar->addAction(ui->actFont);
    localToolBar->addSeparator();
    localToolBar->addAction(ui->actCut);
    localToolBar->addAction(ui->actCopy);
    localToolBar->addAction(ui->actPaste);
    localToolBar->addAction(ui->actUndo);
    localToolBar->addAction(ui->actRedo);
    localToolBar->addSeparator();
    localToolBar->addAction(ui->actClose);

    localToolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    QVBoxLayout *laout = new QVBoxLayout();
    laout->addWidget(localToolBar);
    laout->addWidget(ui->plainTextEdit);
    laout->setContentsMargins(2,2,2,2);
    laout->setSpacing(2);

    setLayout(laout);

}

FormDoc::~FormDoc()
{
    delete ui;
}
