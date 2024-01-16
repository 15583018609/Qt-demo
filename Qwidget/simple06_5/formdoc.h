#ifndef FORMDOC_H
#define FORMDOC_H

#include <QWidget>

namespace Ui {
class FormDoc;
}

class FormDoc : public QWidget
{
    Q_OBJECT

public:
    explicit FormDoc(QWidget *parent = nullptr);
    ~FormDoc();

    bool isFileOpened();
    void loadFromFile(QString fileName);
    QString getCurFileName();
    void setTextFont();

    void textCopy();
    void textPaste();
    void textCut();

private:
    Ui::FormDoc *ui;
    bool mFileOpened = false;
    QString mCurrentFileName;
};

#endif // FORMDOC_H
