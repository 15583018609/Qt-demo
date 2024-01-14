#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void on_btnClearText_2_clicked();

    void on_btnOpen_2_clicked();

    void on_btnOpenMulti_2_clicked();

    void on_btnSelDir_2_clicked();

    void on_btnSave_2_clicked();

    void on_btnColor_2_clicked();

    void on_btnFont_2_clicked();

    void on_btnInputString_2_clicked();

    void on_btnInputInt_2_clicked();

    void on_btnInputFloat_2_clicked();

    void on_btnInputItem_2_clicked();

    void on_btnMsgQuestion_2_clicked();

    void on_btnMsgInformation_2_clicked();

    void on_btnMsgWarning_2_clicked();

    void on_btnMsgCritical_2_clicked();

    void on_btnMsgAbout_2_clicked();

    void on_btnMsgAboutQt_2_clicked();

private:
    Ui::Dialog *ui;
};
#endif // DIALOG_H
