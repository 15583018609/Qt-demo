#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDir>
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    recorder = new QAudioRecorder(this);
    connect(recorder,SIGNAL(stateChanged(QMediaRecorder::State)),
            this,SLOT(onStateChanged(QMediaRecorder::State)));

    connect(recorder, SIGNAL(durationChanged(qint64)), this,
            SLOT(onDurationChanged(qint64)));

    probe = new QAudioProbe(this);
    connect(probe, SIGNAL(audioBufferProbed(QAudioBuffer)),
            this, SLOT(processBuffer(QAudioBuffer)));

    probe->setSource(recorder);

    if(recorder->defaultAudioInput().isEmpty()) return;
    foreach(auto device,recorder->audioInputs()){
        ui->comboDevices->addItem(device);
    }
    foreach(auto codec,recorder->supportedAudioCodecs()){
        ui->comboCodec->addItem(codec);
    }
    foreach(auto sampRate,recorder->supportedAudioSampleRates()){
        ui->comboSampleRate->addItem(QString::number(sampRate));
    }
    ui->comboChannels->addItem("1");
    ui->comboChannels->addItem("2");
    ui->comboChannels->addItem("4");

    ui->sliderQuality->setRange(0,int(QMultimedia::VeryHighQuality));
    ui->sliderQuality->setValue(int(QMultimedia::NormalQuality));

    ui->comboBitrate->addItem("32000");
    ui->comboBitrate->addItem("64000");
    ui->comboBitrate->addItem("96000");
    ui->comboBitrate->addItem("128000");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onStateChanged(QMediaRecorder::State state)
{
    ui->actRecord->setEnabled(state!=QMediaRecorder::RecordingState);
    ui->actPause->setEnabled(state==QMediaRecorder::RecordingState);
    ui->actStop->setEnabled(state!=QMediaRecorder::StoppedState);

    ui->btnGetFile->setEnabled(state==QMediaRecorder::StoppedState);
    ui->editOutputFile->setEnabled(state==QMediaRecorder::StoppedState);
}

void MainWindow::onDurationChanged(qint64 duration)
{
     ui->LabPassTime->setText(QString("已录制 %1 秒").arg(duration/1000));
  //  ui->LabPassTime->setText(QString("录制了 %1 秒").arg(duration/1000));
}

void MainWindow::processBuffer(QAudioBuffer buffer)
{
    //处理探测到的缓冲区
    ui->spin_byteCount->setValue(buffer.byteCount());//缓冲区字节数
    ui->spin_duration->setValue(buffer.duration()/1000);//缓冲区时长
    ui->spin_frameCount->setValue(buffer.frameCount());//缓冲区帧数
    ui->spin_sampleCount->setValue(buffer.sampleCount());//缓冲区采样数

    QAudioFormat audioFormat=buffer.format();//缓冲区格式
    ui->spin_channelCount->setValue(audioFormat.channelCount()); //通道数
    ui->spin_sampleSize->setValue(audioFormat.sampleSize());//采样大小
    ui->spin_sampleRate->setValue(audioFormat.sampleRate());//采样率
    ui->spin_bytesPerFrame->setValue(audioFormat.bytesPerFrame());//每帧字节数

    if (audioFormat.byteOrder()==QAudioFormat::LittleEndian)
        ui->edit_byteOrder->setText("LittleEndian");//字节序
    else
        ui->edit_byteOrder->setText("BigEndian");

    ui->edit_codec->setText(audioFormat.codec());//编码格式

    if (audioFormat.sampleType()==QAudioFormat::SignedInt)//采样点类型
        ui->edit_sampleType->setText("SignedInt");
    else if(audioFormat.sampleType()==QAudioFormat::UnSignedInt)
        ui->edit_sampleType->setText("UnSignedInt");
    else if(audioFormat.sampleType()==QAudioFormat::Float)
        ui->edit_sampleType->setText("Float");
    else
        ui->edit_sampleType->setText("Unknown");
}


void MainWindow::on_btnGetFile_clicked()
{
    //设置保存文件
    QString curPath=QDir::currentPath();
    QString fileName = QFileDialog::getSaveFileName(this,"选择存放的文件","","wav文件(*.wav)");
    if(fileName.isEmpty()) return;
    ui->editOutputFile->setText(fileName);
}

void MainWindow::on_actPause_triggered()
{
    recorder->pause();
}

void MainWindow::on_actStop_triggered()
{
    recorder->stop();
}

void MainWindow::on_actRecord_triggered()
{
    if(recorder->state()==QMediaRecorder::StoppedState){
        QString selectedFile = ui->editOutputFile->text().trimmed();
        if(selectedFile.isEmpty()){
            QMessageBox::critical(this,"error","请设置正确的输出文件");
            return;
        }
        if(QFile::exists(selectedFile))
            if(!QFile::remove(selectedFile)){
                QMessageBox::critical(this,"error","文件已存在且无法删除");
                return;
            }
        recorder->setOutputLocation(QUrl::fromLocalFile(selectedFile));
        recorder->setAudioInput(ui->comboDevices->currentText());

        QAudioEncoderSettings settings; //音频编码设置
        settings.setCodec(ui->comboCodec->currentText());//编码
        settings.setSampleRate(ui->comboSampleRate->currentText().toInt());//采样率
        settings.setBitRate(ui->comboBitrate->currentText().toInt());//比特率
        settings.setChannelCount(ui->comboChannels->currentText().toInt()); //通道数
        settings.setQuality(QMultimedia::EncodingQuality(ui->sliderQuality->value())); //品质
        if (ui->radioQuality->isChecked())//编码模式为固定品质,自动决定采样率，采样点大小
            settings.setEncodingMode(QMultimedia::ConstantQualityEncoding);
        else
            settings.setEncodingMode(QMultimedia::ConstantBitRateEncoding);//固定比特率

        recorder->setAudioSettings(settings); //音频设置
    }
     recorder->record();
}
