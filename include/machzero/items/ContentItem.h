#pragma once
#include <QAbstractItemModel>
#include <QList>
#include <QString>
#include <QVariant>
#include <QModelIndex>
#include <QObject>
#include <QModelIndex>

class ContentsModel;

class ContentItem {
    public:
        ContentItem(QString label, QAbstractItemModel* model = nullptr);

        QVariant data() const;
        int GetChildCount() { return _children.size(); }
        ContentItem* GetChild(int row) { return _children[row]; }
        void AddChild(ContentItem* child);

        ContentItem* Parent = nullptr;
        // The actual data
        QString Label;
        int Row;
        QAbstractItemModel* Model = nullptr;
    private:
        QList<ContentItem*> _children;
};