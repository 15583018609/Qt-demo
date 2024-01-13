#include "qintdalegate.h"
#include <QSpinBox>
QIntDalegate::QIntDalegate()
{

}

QWidget *QIntDalegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QSpinBox *editor = new QSpinBox(parent);
    editor->setMinimum(0);
    editor->setMaximum(11100);
    editor->setFrame(false);
    return editor;
}

void QIntDalegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    int value = index.model()->data(index,Qt::EditRole).toInt();
    QSpinBox *spinBox =static_cast<QSpinBox *>(editor);
    spinBox->setValue(value);
}

void QIntDalegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QSpinBox *spinBox =static_cast<QSpinBox *>(editor);
    spinBox->interpretText();
    int value = spinBox->value();
    model->setData(index,value,Qt::EditRole);
}

void QIntDalegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index)
    editor->setGeometry(option.rect);
}
