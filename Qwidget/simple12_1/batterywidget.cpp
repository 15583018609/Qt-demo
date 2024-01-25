#include "batterywidget.h"
#include <QPainter>
BatteryWidget::BatteryWidget(QWidget *parent) : QWidget(parent)
{

}

int BatteryWidget::PowerLeve() const
{
    return m_PowerLeve;
}

void BatteryWidget::setPowerLeve(int PowerLeve)
{
    m_PowerLeve = PowerLeve;
    repaint();
}

void BatteryWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    QRect rect(0,0,width(),height());
    painter.setViewport(rect);
    painter.setWindow(0,0,120,50);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::TextAntialiasing);

    //绘制电池边框
    QPen pen;
    pen.setWidth(2);
    pen.setColor(m_ColorBorder);
    pen.setStyle(Qt::SolidLine);
    pen.setCapStyle(Qt::FlatCap);
    pen.setJoinStyle(Qt::BevelJoin);
    painter.setPen(pen);

    QBrush brush;
    brush.setColor(m_ColorBack);
    brush.setStyle(Qt::SolidPattern);
    painter.setBrush(brush);
    rect.setRect(1,1,109,48);

    painter.drawRect(rect);
    brush.setColor(m_ColorBack);
    painter.setBrush(brush);
    rect.setRect(110,15,10,20);
    painter.drawRect(rect);

    //绘制电量
    if(m_PowerLeve>m_Warning){
        brush.setColor(m_ColorPower);
        pen.setColor(m_ColorPower);
    }else{
        brush.setColor(m_ColorWarning);
        pen.setColor(m_ColorWarning);
    }
    painter.setBrush(brush);
    painter.setPen(pen);
    if(m_PowerLeve>0){
        rect.setRect(5,5,m_PowerLeve,40);
        painter.drawRect(rect);
    }

    //绘制百分比
    QFontMetrics textSize(this->font());
    QString powStr = QString::asprintf("%d%%",m_PowerLeve);
    QRect textRect = textSize.boundingRect(powStr);
    pen.setColor(m_ColorBorder);
    painter.setPen(pen);
    painter.drawText(55-textRect.width()/2,23+textRect.height()/2,powStr);

}
