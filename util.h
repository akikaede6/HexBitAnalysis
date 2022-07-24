#ifndef UTIL_H
#define UTIL_H

const int Bit = 32;
const int HexMaxLength = 8;
const int Hex = 16;
const int defaultFont = 18;

#include <QFont>

class FontSize
{
public:
    FontSize();
    static QFont fontSize();
    static int fontPixel();
    static void setFontSize(int size);

private:
    static int m_fontSize;
};
inline int FontSize::m_fontSize = defaultFont;

const int EditMaxWidth = HexMaxLength * FontSize::fontPixel();


#endif // UTIL_H
