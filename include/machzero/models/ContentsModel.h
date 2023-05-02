#pragma once

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>
#include <QList>

class ContentItem;

class ContentsModel : public QAbstractItemModel {
    Q_OBJECT

    public:
        ContentsModel(QObject* parent = nullptr);
        QVariant data(const QModelIndex &index, int role) const override;
        Qt::ItemFlags flags(const QModelIndex &index) const override;
        QModelIndex index(int row, int column,
                        const QModelIndex &parent = QModelIndex()) const override;
        QModelIndex parent(const QModelIndex &index) const override;
        int rowCount(const QModelIndex &parent = QModelIndex()) const override;
        int columnCount(const QModelIndex &parent = QModelIndex()) const override;
        
        QAbstractItemModel* GetModelAtIndex(QModelIndex& selected);
        void AddItem(ContentItem* item);
        ContentItem* GetItemByLabel(QString label);

        void UpdateItemAtIndex(QModelIndex topLeft, QModelIndex bottomRight);
    private:
        QList<ContentItem*> _children;
};