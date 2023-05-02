#include "machzero/items/DataItem.h"

#include <sstream>
#include <string>
#include <iomanip>

QString buildString(std::vector<std::byte>& data) {
    std::stringstream buffer;
    for (std::byte element : data) {
        buffer << std::hex << std::setw(2) << std::setfill('0') << std::left << static_cast<uint32_t>(element);
    }
    return QString::fromStdString(buffer.str());
}

DataItem::DataItem(std::vector<std::byte>& data)
    : QStandardItem() {
    _dataString = buildString(data);
}
DataItem::DataItem(uint32_t data)
    : QStandardItem() {
    std::byte* array = reinterpret_cast<std::byte*>(&data);
    std::vector<std::byte> byteArray = {array[3], array[2], array[1], array[0]};
    _dataString = buildString(byteArray);
}

QVariant DataItem::data(int role) const {
    if (role == Qt::DisplayRole) {
        return _dataString;
    }
    return QVariant();
}

DecimalItem::DecimalItem(uint32_t data)
    : DataItem() {
    _dataString = QString::number(data);
}