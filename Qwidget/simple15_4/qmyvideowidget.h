#ifndef QMYVIDEOWIDGET_H
#define QMYVIDEOWIDGET_H
#include<QObject>
#include<QVideoWidget>
#include<QVideoWidget>
#include<QMediaPlayer>
class QmyVideoWidget : public QVideoWidget
{
    Q_OBJECT
private:
     QMediaPlayer    *thePlayer;//
protected:
     void keyPressEvent(QKeyEvent *event);

     void mousePressEvent(QMouseEvent *event);

public:
     QmyVideoWidget(QWidget *parent = Q_NULLPTR);
     void    setMediaPlayer(QMediaPlayer *player);
signals:

};

#endif // QMYVIDEOWIDGET_H
