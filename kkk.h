#ifndef KKK_H
#define KKK_H
#include <QAbstractListModel>

class Kkk : public QAbstractListModel{
    Q_OBJECT
public:
    Kkk();
    int rowCount(const QModelIndex& parent = QModelIndex {}) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    Q_INVOKABLE bool move(int index);
};

#endif // KKK_H
