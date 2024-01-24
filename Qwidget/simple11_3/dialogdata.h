#ifndef DIALOGDATA_H
#define DIALOGDATA_H

#include <QDialog>
#include <QDialog>
#include    <QSqlRecord>
namespace Ui {
class DialogData;
}

class DialogData : public QDialog
{
    Q_OBJECT
    QSqlRecord  mRecord; //保存一条记录的数据
public:
    explicit DialogData(QWidget *parent = nullptr);
    ~DialogData();

     void setUpdateRecord(QSqlRecord & recData);
     void setInserRecord(QSqlRecord & recData);

     QSqlRecord getRecordData();


private slots:
     void on_btnSetPhoto_clicked();

     void on_btnClearPhoto_clicked();

private:
    Ui::DialogData *ui;
};

#endif // DIALOGDATA_H
