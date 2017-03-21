#ifndef TREEMODEL_H
#define TREEMODEL_H

#include <QAbstractItemModel>
#include <QVariant>

class Item {
public:
    Item() {
        index = counter++;
        text += QString::number(index);
    }
    Item * addChild() {
        Item * item = new Item;
        item->setParent(this);
        children.append(item);
        return item;
    }
    Item * childAt(int t_row) const {
        return children.at(t_row);
    }
    int row() const {
        const Item * parent = getParent();
        //Q_ASSERT(!parent);
        int row = parent->children.indexOf(const_cast<Item *>(this));
        return row;
    }
    int numberOfChildren() const {
        return children.size();
    }

    Item * getParent() const;
    void setParent(Item *value);

    const QString & getText() const {
        return text;
    }


private:
    QString text {"index is "};
    QList<Item *> children;
    Item * parent;
    int index;
    static int counter;
};

class TreeModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    TreeModel();
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &) const;
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QModelIndex parent(const QModelIndex &index) const;
private:
    Item rootItem;
};

#endif // TREEMODEL_H
