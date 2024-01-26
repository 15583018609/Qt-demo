#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "dicethread.h"
QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();
protected:
    void closeEvent(QCloseEvent *event) Q_DECL_OVERRIDE;

private:
    DiceThread threadA;
    Ui::Dialog *ui;

private slots:
    void on_threadAnewValue(int seq,int diceValue);
    void on_threadAStarted();
    void on_threadAFinished();
    void on_btnStartThread_clicked();
    void on_btnStopThread_clicked();
    void on_btnDiceBegin_clicked();
    void on_btnDiceEnd_clicked();
    void on_btnClear_clicked();
};
#endif // DIALOG_H
