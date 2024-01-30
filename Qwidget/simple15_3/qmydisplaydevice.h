#ifndef QMYDISPLAYDEVICE_H
#define QMYDISPLAYDEVICE_H

#include <QObject>
#include<QtCharts>
#include<QIODevice>
class QmyDisplayDevice : public QIODevice
{
    Q_OBJECT
public:
    explicit QmyDisplayDevice(QXYSeries * series, qint64 pointsCount,QObject *parent = nullptr);

protected:
    qint64 readData(char *data, qint64 maxSize) ;
    qint64 writeData(const char *data, qint64 maxSize);

private:
    QXYSeries *m_series;
    qint64  range=4000;
signals:
    void  updateBlockSize(qint64 blockSize);
};

#endif // QMYDISPLAYDEVICE_H
