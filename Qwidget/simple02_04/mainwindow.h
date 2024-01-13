#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProgressBar>
#include <QLabel>
#include <QSpinBox>
#include <QFontComboBox>
#include <QFont>
#include <QTextFormat>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:

    QLabel *fLabCurFile;
    QProgressBar *progressBar;
    QSpinBox *spinFontSize;
    QFontComboBox *comboFont;

    void initUI();
    void initSignalSlot();
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actFontBlod_triggered(bool checked);

    void on_textEdit_copyAvailable(bool b);

    void on_textEdit_selectionChanged();

    //  自定义槽函数
    void on_spinBoxFontSize_valueChanged(int aFontSize);//改变字体大小的SpinBox的响应
    void on_comboFont_currentIndexChanged(const QString &arg1);//FontCombobox的响应，选择字体名称

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
