#include "machzero/models/HexDumpModel.h"
#include "machzero/items/PositionItem.h"
#include <iostream>
#include <stack>
#include <cstring>
#include <llvm/ADT/StringRef.h>

QList<char> hexLookupTable = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

HexDumpModel::HexDumpModel(std::shared_ptr<llvm::WritableMemoryBuffer> data, uint64_t start, uint64_t end, QObject* parent)
    : QAbstractTableModel(parent),
    _dataStart(start),
    _data(data),
    _dataEnd(end)
    { }

QString fastIntToHex(uint8_t value) {
    QString result = "  ";
    result[0] = hexLookupTable[value / 16];
    result[1] = hexLookupTable[value % 16];
    return result;
}

QVariant HexDumpModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid()) {
        return QVariant();
    }
    if (role != Qt::DisplayRole) {
        return QVariant();
    }
    uint64_t offset = _dataStart + (index.row() * 16);
    if (index.column() == 0) {
        // TODO, make pretty
        //return new PositionItem(offset);
        return QString::number(offset);
    }
    else {
        uint64_t size = 16;
        if (_dataEnd - offset < 16) {
            size = _dataEnd - offset;
        }

        llvm::StringRef rowData(_data->getBufferStart() + offset, size);
        if (index.column() == 1) {
            // Data low
            uint16_t dataCount = rowData.size() < 8 ? rowData.size() : 8;
            QString result(dataCount * 3, ' ');

            for (int i = 0; i < dataCount; i++) {
                QString hexString = fastIntToHex(static_cast<uint8_t>(rowData[i]));
                uint16_t stringOffset = i * 3;

                result[stringOffset] = hexString[0];
                result[stringOffset+1] = hexString[1];
            }
            return result;
        }
        else if (index.column() == 2) {
            // Data high
            if (size > 8) {
                // we have at least some data
                uint16_t dataCount = rowData.size() < 16 ? rowData.size() - 8 : 8;
                QString result(dataCount * 3, ' ');

                for (int i = 0; i < dataCount; i++) {
                    QString hexString = fastIntToHex(rowData[i + 8]);
                    uint16_t stringOffset = i * 3;

                    result[stringOffset] = hexString[0];
                    result[stringOffset+1] = hexString[1];
                }
                return result;
            }
            else {
                return QString();
            }
        }
        else if (index.column() == 3) {
            // Hexdump
            QString hexDump(size, '.');
            for (int i = 0; i < rowData.size(); i++) {
                char byte = rowData[i];
                if (byte > '!' && byte <= '~') {
                    hexDump[i] = byte;
                }
            }
            return hexDump;
        }
        // unreachable
        return QVariant();
    }
}
QVariant HexDumpModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole) {
        return QVariant();
    }
    if (orientation != Qt::Horizontal) {
        return QVariant();
    }
    static QList<QString> titles = {"pFile", "Data LO", "Data HI", "Value"};
    return titles[section];
}
Qt::ItemFlags HexDumpModel::flags(const QModelIndex &index) const {
    if (!index.isValid()) {
        return Qt::NoItemFlags;
    }
    Qt::ItemFlags baseFlags = QAbstractItemModel::flags(index);
    
    if (index.column() == 1 || index.column() == 2) {
        return baseFlags | Qt::ItemIsEditable;
    }
    return baseFlags;
}

std::vector<uint8_t> stringToData(QString input) {
    std::vector<uint8_t> data;
    std::stack<QChar> lastData;
    // format should be 'XX XX XX XX XX'
    auto charToByte = [](QChar c) -> uint8_t {
        c = c.toUpper();
        if (c >= '0' && c <= '9') {
            return c.toLatin1() - (int)'0';
        }
        else if (c >= 'A' && c <= 'F') {
            return (c.toLatin1() - (int)'A') + 10;
        }
        return 0;
    };

    //for (QChar& c : input) {
    for (QString::iterator i = input.begin(); i != input.end(); i++) {
        QChar character = *i;
        if (character != ' ') {
            lastData.push(character);
        }

        if (character == ' ' || (i + 1) == input.end()) {
            if (lastData.size() > 2 || lastData.size() == 0) {
                std::cerr << "Invalid hex string\n";
                return {};
            }
            uint8_t byte = charToByte(lastData.top());
            lastData.pop();
            if (lastData.size() > 0) {
                uint8_t upperByte = charToByte(lastData.top());
                lastData.pop();
                byte |= (upperByte << 4);
            }
            data.push_back(byte);
        }
    }

    return data;
}

bool HexDumpModel::setData(const QModelIndex& index, const QVariant& value, int role) {
    if (value.toString().isEmpty()) {
        return false;
    }

    std::vector<uint8_t> data = stringToData(value.toString());
    if (data.size() != 0) {
        uint64_t dataOffset = _dataStart + (16 * index.row());
        if (index.column() == 2) {
            dataOffset += 8;
        }
        uint64_t sizeLeft = _dataEnd - dataOffset;
        uint64_t dataSize = data.size();
        if (data.size() > sizeLeft) {
            dataSize = sizeLeft;
        }
        std::memcpy(_data->getBufferStart() + dataOffset, data.data(), dataSize);

        emit dataChanged(index, index, {Qt::DisplayRole, Qt::EditRole});
        return true;
    }
    return false;
}

int HexDumpModel::rowCount(const QModelIndex& parent) const {
    // each row contains up to 16 bytes
    uint64_t dataSize = _dataEnd - _dataStart;
    // Dive the number of bytes by 16 to get the number of rows
    // and round up. See https://stackoverflow.com/a/2745086
    return (dataSize + 16 - 1) / 16;
}
int HexDumpModel::columnCount(const QModelIndex& parent) const {
    return 4;
}