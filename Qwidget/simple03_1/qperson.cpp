#include "qperson.h"

QPerson::QPerson(QString name,QObject *parent) : QObject(parent)
{
    m_name = name;
}

int QPerson::age()
{
    return m_age;
}

void QPerson::setAge(int value)
{
    m_age = value;
    emit (ageChanged(m_age));
}
void QPerson::incAge()
{
    m_age++;
    qDebug()<<"m_age is "<<m_age;
    emit (ageChanged(m_age));
}


