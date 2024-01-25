#ifndef BATTERYWIDGET_H
#define BATTERYWIDGET_H

#include <QWidget>
#include <QColor>
class BatteryWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BatteryWidget(QWidget *parent = nullptr);

    int PowerLeve() const;
    void setPowerLeve(int PowerLeve);

signals:

private:
    QColor m_ColorBack = Qt::white;
    QColor m_ColorBorder=Qt::black;
    QColor m_ColorPower=Qt::green;
    QColor m_ColorWarning=Qt::red;

    int m_PowerLeve = 50;
    int m_Warning = 20;

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
};

#endif // BATTERYWIDGET_H
