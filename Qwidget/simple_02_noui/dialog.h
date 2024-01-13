#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QCheckBox>
#include <QRadioButton>
#include <QPushButton>
#include <QPlainTextEdit>

class Dialog : public QDialog
{
    Q_OBJECT
private:
    QCheckBox *checkBoxUnderline;
    QCheckBox *checkBoxItalic;
    QCheckBox *checkBoxBlod;

    QRadioButton *rBtnRed;
    QRadioButton *rBtnBlue;
    QRadioButton *rBtnBlack;

    QPlainTextEdit *plainTextEdit;

    QPushButton *btnOK;
    QPushButton *btnCancel;
    QPushButton *btnClose;

    void initUI();
    void iniSignalSlots();
private slots:
    void on_checkUnderline(bool checked);
    void on_checkItalic(bool checked);
    void on_checkBlod(bool checked);
    void setTextFontColor();

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();
};
#endif // DIALOG_H
