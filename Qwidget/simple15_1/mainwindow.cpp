#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDir>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    player = new QMediaPlayer(this);
    playlist=new QMediaPlaylist(this);
    playlist->setPlaybackMode(QMediaPlaylist::Loop);
    player->setPlaylist(playlist);
    connect(player,SIGNAL(stateChanged(QMediaPlayer::State)),this,SLOT(on_StateChanged(QMediaPlayer::State)));
    connect(player,SIGNAL(positionChanged(qint64)),this,SLOT(on_PositionChanged(qint64)));
    connect(player,SIGNAL(durationChanged(qint64)),this,SLOT(on_DurationChanged(qint64)));
    connect(playlist,SIGNAL(currentIndexChanged(int)),this,SLOT(on_PlaylistCurrentIndexChanged(int)));



}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_StateChanged(QMediaPlayer::State State)
{
    ui->btnPlay->setEnabled(!(State ==QMediaPlayer::PlayingState));
    ui->btnPause->setEnabled(State ==QMediaPlayer::PlayingState);
    ui->btnStop->setEnabled(State ==QMediaPlayer::PlayingState);
}

void MainWindow::on_PositionChanged(qint64 position)
{
    if(ui->sliderPosition->isSliderDown()) return;
    ui->sliderPosition->setSliderPosition(position);
    int secs = position/1000;
    int mins = secs/60;
    secs = secs%60;
    positionTime = QString::asprintf("%d:%d",mins,secs);
    ui->LabRatio->setText(positionTime+"/"+durationTime);
}

void MainWindow::on_DurationChanged(qint64 duration)
{
    ui->sliderPosition->setMaximum(duration);
    int secs = duration/1000;
    int mins = secs/60;
    secs = secs%60;
    durationTime = QString::asprintf("%d:%d",mins,secs);
    ui->LabRatio->setText(positionTime+"/"+durationTime);

}

void MainWindow::on_PlaylistCurrentIndexChanged(int index)
{
    ui->listWidget->setCurrentRow(index);
    QListWidgetItem *item= ui->listWidget->currentItem();
    if(item){
        ui->LabCurMedia->setText(item->text());
    }
}


void MainWindow::on_btnAdd_clicked()
{
    QString curPath = QDir::currentPath();
    QString digTitle = "选择音频文件";
    QString filter = "音频文件(*.mp3 *.wav *.wma *.flac);;mp3文件(*.mp3)"
            ";;wav文件(*.wav);;wma文件(*.wma));;flac文件(*.flac)";
    QStringList fileList = QFileDialog::getOpenFileNames(this,digTitle,curPath,filter);
    if(fileList.count()<1)
        return;
    foreach(auto aFile,fileList){
        playlist->addMedia(QUrl::fromLocalFile(aFile));
        QFileInfo fileInfo(aFile);
        ui->listWidget->addItem(fileInfo.fileName());
    }
    if(player->state()!=QMediaPlayer::PlayingState){
        playlist->setCurrentIndex(0);
    }
    player->play();
}

void MainWindow::on_btnRemove_clicked()
{
    int pos =ui->listWidget->currentRow();
    QListWidgetItem *item=ui->listWidget->takeItem(pos);
    delete  item;
    playlist->removeMedia(pos);

    QString str="无曲目";
    if(ui->listWidget->currentItem())
        str = ui->listWidget->currentItem()->text();
    ui->LabCurMedia->setText(str);

}

void MainWindow::on_btnClear_clicked()
{
    playlist->clear();
    ui->listWidget->clear();
    QString str="无曲目";
    ui->LabCurMedia->setText(str);
}

void MainWindow::on_listWidget_doubleClicked(const QModelIndex &index)
{
    int rowNo = index.row();
    playlist->setCurrentIndex(rowNo);
    player->play();
}

void MainWindow::on_btnPlay_clicked()
{
    if(playlist->currentIndex()<0)
        playlist->setCurrentIndex(0);
    player->play();
}

void MainWindow::on_btnPause_clicked()
{
    player->pause();
}

void MainWindow::on_btnStop_clicked()
{
    player->stop();
}

void MainWindow::on_btnPrevious_clicked()
{
    playlist->previous();
}

void MainWindow::on_btnNext_clicked()
{
    playlist->next();
}

void MainWindow::on_sliderVolumn_valueChanged(int value)
{
    player->setVolume(value);
}

void MainWindow::on_sliderPosition_valueChanged(int value)
{
    player->setPosition(value);
}

void MainWindow::on_btnSound_clicked()
{
    bool mute= player->isMuted();
    player->setMuted(!mute);

    mute=player->isMuted();
    if(mute)
        ui->btnSound->setIcon(QIcon(":/images/images/mute.bmp"));
    else
        ui->btnSound->setIcon(QIcon(":/images/images/volumn.bmp"));
}
