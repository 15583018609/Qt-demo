/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolBox>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout_4;
    QSplitter *splitter_2;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QTreeView *treeView;
    QSplitter *splitter;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QListView *listView;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_3;
    QTableView *tableView;
    QToolBox *toolBox;
    QWidget *page;
    QWidget *page_2;
    QHBoxLayout *horizontalLayout;
    QLabel *labName;
    QLabel *labSize;
    QLabel *labType;
    QCheckBox *checkBox;
    QLabel *labPath;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(926, 570);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout_4 = new QGridLayout(centralwidget);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        splitter_2 = new QSplitter(centralwidget);
        splitter_2->setObjectName(QString::fromUtf8("splitter_2"));
        splitter_2->setOrientation(Qt::Horizontal);
        groupBox = new QGroupBox(splitter_2);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        treeView = new QTreeView(groupBox);
        treeView->setObjectName(QString::fromUtf8("treeView"));

        gridLayout->addWidget(treeView, 0, 0, 1, 1);

        splitter_2->addWidget(groupBox);
        splitter = new QSplitter(splitter_2);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Vertical);
        groupBox_2 = new QGroupBox(splitter);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        listView = new QListView(groupBox_2);
        listView->setObjectName(QString::fromUtf8("listView"));

        gridLayout_2->addWidget(listView, 0, 0, 1, 1);

        splitter->addWidget(groupBox_2);
        groupBox_3 = new QGroupBox(splitter);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        gridLayout_3 = new QGridLayout(groupBox_3);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        tableView = new QTableView(groupBox_3);
        tableView->setObjectName(QString::fromUtf8("tableView"));

        gridLayout_3->addWidget(tableView, 0, 0, 1, 1);

        toolBox = new QToolBox(groupBox_3);
        toolBox->setObjectName(QString::fromUtf8("toolBox"));
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        page->setGeometry(QRect(0, 0, 487, 85));
        toolBox->addItem(page, QString::fromUtf8("Page 1"));
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        page_2->setGeometry(QRect(0, 0, 487, 85));
        toolBox->addItem(page_2, QString::fromUtf8("Page 2"));

        gridLayout_3->addWidget(toolBox, 1, 0, 1, 1);

        splitter->addWidget(groupBox_3);
        splitter_2->addWidget(splitter);

        gridLayout_4->addWidget(splitter_2, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        labName = new QLabel(centralwidget);
        labName->setObjectName(QString::fromUtf8("labName"));

        horizontalLayout->addWidget(labName);

        labSize = new QLabel(centralwidget);
        labSize->setObjectName(QString::fromUtf8("labSize"));

        horizontalLayout->addWidget(labSize);

        labType = new QLabel(centralwidget);
        labType->setObjectName(QString::fromUtf8("labType"));

        horizontalLayout->addWidget(labType);

        checkBox = new QCheckBox(centralwidget);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));

        horizontalLayout->addWidget(checkBox);


        gridLayout_4->addLayout(horizontalLayout, 1, 0, 1, 1);

        labPath = new QLabel(centralwidget);
        labPath->setObjectName(QString::fromUtf8("labPath"));

        gridLayout_4->addWidget(labPath, 2, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        toolBox->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "TreeView", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "ListView", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("MainWindow", "TableView", nullptr));
        toolBox->setItemText(toolBox->indexOf(page), QCoreApplication::translate("MainWindow", "Page 1", nullptr));
        toolBox->setItemText(toolBox->indexOf(page_2), QCoreApplication::translate("MainWindow", "Page 2", nullptr));
        labName->setText(QString());
        labSize->setText(QString());
        labType->setText(QString());
        checkBox->setText(QCoreApplication::translate("MainWindow", "\346\230\257\345\220\246\346\230\257\346\226\207\344\273\266\345\244\271", nullptr));
        labPath->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
