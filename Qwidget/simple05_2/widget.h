#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QStringListModel>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT
private:
    QStringListModel *theModel;

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_btnTextClear_clicked();

    void on_btnTextImport_clicked();

    void on_btnIniList_clicked();

    void on_btnListDelete_clicked();

    void on_btnListClear_clicked();

    void on_btnListAppend_clicked();

    void on_btnListInsert_clicked();

    void on_listView_clicked(const QModelIndex &index);

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
