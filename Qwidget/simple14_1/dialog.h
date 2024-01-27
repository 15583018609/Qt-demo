#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QHostInfo>
#include <QNetworkInterface>
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
    void lookUpHostInfo(const QHostInfo& host);

    void on_btnGetHostInfo_clicked();

    void on_btnClear_clicked();

    void on_btnLookup_clicked();

    void on_btnDetail_clicked();

    void on_btnALLInterface_clicked();

private:
    QString protecolName(QAbstractSocket::NetworkLayerProtocol protocol);
    Ui::Dialog *ui;
};
#endif // DIALOG_H
