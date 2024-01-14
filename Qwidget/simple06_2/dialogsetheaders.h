#ifndef DIALOGSETHEADERS_H
#define DIALOGSETHEADERS_H

#include <QDialog>
#include <QStringListModel>
namespace Ui {
class DialogSetHeaders;
}

class DialogSetHeaders : public QDialog
{
    Q_OBJECT

public:
    explicit DialogSetHeaders(QWidget *parent = nullptr);
    ~DialogSetHeaders();

    void setStringList(QStringList strList);
    QStringList stringList();

private:
    QStringListModel *theModel;
    Ui::DialogSetHeaders *ui;
};

#endif // DIALOGSETHEADERS_H
