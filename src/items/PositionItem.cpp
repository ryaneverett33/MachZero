#include "machzero/items/PositionItem.h"

#include <sstream>
#include <string>
#include <iomanip>

PositionItem::PositionItem(uint64_t position)
    : QStandardItem(),
    Position(position) {
    // Create the offset string
    std::stringstream buffer;
    buffer << std::hex << std::setw(8) << std::setfill('0') << std::left << position;
    _offsetString = QString::fromStdString(buffer.str());

    // Create the RVA string
    ApplyRVAOffset(0x100000000);
}

void PositionItem::ApplyRVAOffset(uint64_t offset) {
    std::stringstream buffer;
    buffer << std::hex << (offset | Position);
    _rvaString = QString::fromStdString(buffer.str());
}

QVariant PositionItem::data(int role) const {
    if (role == Qt::DisplayRole) {
        return _rvaString;
    }
    return QVariant();
}