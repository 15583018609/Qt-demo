#ifndef MYGRAPHICSVIEW_H
#define MYGRAPHICSVIEW_H

#include <QObject>

class MyGraphicsView : public QObject
{
    Q_OBJECT
public:
    explicit MyGraphicsView(QObject *parent = nullptr);

signals:

};

#endif // MYGRAPHICSVIEW_H
