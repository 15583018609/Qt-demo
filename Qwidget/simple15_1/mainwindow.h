#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QMediaPlaylist>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void on_StateChanged(QMediaPlayer::State State);
    void on_PositionChanged(qint64 position);
    void on_DurationChanged(qint64 duration);
    void on_PlaylistCurrentIndexChanged(int index);
    void on_btnAdd_clicked();

    void on_btnRemove_clicked();

    void on_btnClear_clicked();

    void on_listWidget_doubleClicked(const QModelIndex &index);

    void on_btnPlay_clicked();

    void on_btnPause_clicked();

    void on_btnStop_clicked();

    void on_btnPrevious_clicked();

    void on_btnNext_clicked();

    void on_sliderVolumn_valueChanged(int value);

    void on_sliderPosition_valueChanged(int value);

    void on_btnSound_clicked();

private:
    QMediaPlayer *player;
    QMediaPlaylist *playlist;

    QString durationTime;
    QString positionTime;

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
