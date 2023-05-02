#include "machzero/items/ContentItem.h"
#include <iostream>
ContentItem::ContentItem(QString label, QAbstractItemModel* model)
            : Label(label),
            Model(model),
            Row(0)
            {}

void ContentItem::AddChild(ContentItem* child) {
    child->Parent = this;
    child->Row = _children.size();
    _children.append(child);
}

QVariant ContentItem::data() const {
    return Label;
}