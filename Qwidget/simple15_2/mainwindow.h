#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAudioRecorder>
#include <QAudioProbe>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QAudioRecorder *recorder;
    QAudioProbe *probe;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void onStateChanged(QMediaRecorder::State state);
    void onDurationChanged(qint64 duration);
    void processBuffer(QAudioBuffer buffer);
    void on_btnGetFile_clicked();

    void on_actPause_triggered();

    void on_actStop_triggered();

    void on_actRecord_triggered();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
