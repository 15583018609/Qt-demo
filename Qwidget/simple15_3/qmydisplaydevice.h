#ifndef QMYDISPLAYDEVICE_H
#define QMYDISPLAYDEVICE_H

#include <QObject>

class QmyDisplayDevice : public QObject
{
    Q_OBJECT
public:
    explicit QmyDisplayDevice(QObject *parent = nullptr);

signals:

};

#endif // QMYDISPLAYDEVICE_H
