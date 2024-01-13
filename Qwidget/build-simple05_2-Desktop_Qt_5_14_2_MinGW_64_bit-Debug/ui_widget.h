/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListView>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QGridLayout *gridLayout_3;
    QSplitter *splitter;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QPushButton *btnIniList;
    QPushButton *btnListAppend;
    QPushButton *btnListInsert;
    QPushButton *btnListDelete;
    QPushButton *btnListClear;
    QListView *listView;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QPushButton *btnTextClear;
    QPushButton *btnTextImport;
    QPlainTextEdit *plainTextEdit;
    QLabel *label;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(840, 387);
        gridLayout_3 = new QGridLayout(Widget);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        splitter = new QSplitter(Widget);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        groupBox = new QGroupBox(splitter);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        btnIniList = new QPushButton(groupBox);
        btnIniList->setObjectName(QString::fromUtf8("btnIniList"));

        gridLayout->addWidget(btnIniList, 0, 0, 1, 1);

        btnListAppend = new QPushButton(groupBox);
        btnListAppend->setObjectName(QString::fromUtf8("btnListAppend"));

        gridLayout->addWidget(btnListAppend, 1, 0, 1, 1);

        btnListInsert = new QPushButton(groupBox);
        btnListInsert->setObjectName(QString::fromUtf8("btnListInsert"));

        gridLayout->addWidget(btnListInsert, 1, 1, 1, 1);

        btnListDelete = new QPushButton(groupBox);
        btnListDelete->setObjectName(QString::fromUtf8("btnListDelete"));

        gridLayout->addWidget(btnListDelete, 2, 0, 1, 1);

        btnListClear = new QPushButton(groupBox);
        btnListClear->setObjectName(QString::fromUtf8("btnListClear"));

        gridLayout->addWidget(btnListClear, 2, 1, 1, 1);

        listView = new QListView(groupBox);
        listView->setObjectName(QString::fromUtf8("listView"));

        gridLayout->addWidget(listView, 3, 0, 1, 2);

        splitter->addWidget(groupBox);
        groupBox_2 = new QGroupBox(splitter);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        btnTextClear = new QPushButton(groupBox_2);
        btnTextClear->setObjectName(QString::fromUtf8("btnTextClear"));

        gridLayout_2->addWidget(btnTextClear, 0, 0, 1, 1);

        btnTextImport = new QPushButton(groupBox_2);
        btnTextImport->setObjectName(QString::fromUtf8("btnTextImport"));

        gridLayout_2->addWidget(btnTextImport, 1, 0, 1, 1);

        plainTextEdit = new QPlainTextEdit(groupBox_2);
        plainTextEdit->setObjectName(QString::fromUtf8("plainTextEdit"));

        gridLayout_2->addWidget(plainTextEdit, 2, 0, 1, 1);

        splitter->addWidget(groupBox_2);

        gridLayout_3->addWidget(splitter, 0, 0, 1, 1);

        label = new QLabel(Widget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_3->addWidget(label, 1, 0, 1, 1);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        groupBox->setTitle(QCoreApplication::translate("Widget", "QListView", nullptr));
        btnIniList->setText(QCoreApplication::translate("Widget", "\346\201\242\345\244\215\345\210\227\350\241\250", nullptr));
        btnListAppend->setText(QCoreApplication::translate("Widget", "\346\267\273\345\212\240\351\241\271", nullptr));
        btnListInsert->setText(QCoreApplication::translate("Widget", "\346\217\222\345\205\245\351\241\271", nullptr));
        btnListDelete->setText(QCoreApplication::translate("Widget", "\345\210\240\351\231\244\345\275\223\345\211\215\351\241\271", nullptr));
        btnListClear->setText(QCoreApplication::translate("Widget", "\346\270\205\351\231\244\345\210\227\350\241\250", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("Widget", "QPlainTextEdit", nullptr));
        btnTextClear->setText(QCoreApplication::translate("Widget", "\346\270\205\347\251\272\346\226\207\346\234\254", nullptr));
        btnTextImport->setText(QCoreApplication::translate("Widget", "\346\230\276\347\244\272\346\225\260\346\215\256\346\250\241\345\236\213\347\232\204StringList", nullptr));
        label->setText(QCoreApplication::translate("Widget", "\350\241\214\357\274\232       \345\210\227\357\274\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
