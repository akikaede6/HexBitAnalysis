#ifndef UTIL_H
#define UTIL_H

#include <QFont>
#include <QString>

const int Bit64 = 64;
const int Bit32 = 32;
const int BitGroupLength = 8;
const int Hex = 16;
const int defaultFont = 18;
const QString default32BitText = "00000000";
const QString default64BitText = "0000000000000000";

class FontSize
{
public:
    static QFont fontSize();
    static int fontPixel();
    static void setFontSize(int size);

private:
    static int m_fontSize;
};
inline int FontSize::m_fontSize = defaultFont;


class BitChange {
public:
    static int bit();
    static int hexMaxLength();
    static void setBit(int newBit);
    static void setHexMaxLength(int newHexMaxLength);

private:
    static int m_bit;
    static int m_hexMaxLength;

};
inline int BitChange::m_bit = 32;
inline int BitChange::m_hexMaxLength = m_bit / 4;
#endif // UTIL_H
