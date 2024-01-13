#ifndef QPERSON_H
#define QPERSON_H

#include <QObject>
#include <QDebug>

class QPerson : public QObject
{
    Q_OBJECT
    Q_CLASSINFO("author","Arxibye")
    Q_CLASSINFO("company","NCHL")
    Q_CLASSINFO("version","1.0.0")
    Q_PROPERTY(int age READ age WRITE setAge NOTIFY ageChanged)
    Q_PROPERTY(QString name MEMBER m_name )
    Q_PROPERTY(int score MEMBER m_score)

private:
private:
    unsigned m_age =10;
    QString  m_name;
    int m_score = 79;
public:
    explicit QPerson(QString name ,QObject *parent = nullptr);
    int age();
    void  setAge(int value);
    void incAge();
signals:
    void ageChanged(int value);


};

#endif // QPERSON_H
