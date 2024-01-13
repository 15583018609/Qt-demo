#ifndef QINTDALEGATE_H
#define QINTDALEGATE_H
#include <QStyledItemDelegate>

class QIntDalegate : public QStyledItemDelegate
{
public:
    QIntDalegate();
    // editing
    QWidget *createEditor(QWidget *parent,
                          const QStyleOptionViewItem &option,
                          const QModelIndex &index) const override;

    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor,
                      QAbstractItemModel *model,
                      const QModelIndex &index) const override;

    void updateEditorGeometry(QWidget *editor,
                              const QStyleOptionViewItem &option,
                              const QModelIndex &index) const override;
};

#endif // QINTDALEGATE_H
