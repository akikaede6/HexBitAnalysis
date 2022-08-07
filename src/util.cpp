#include "util.h"

#include <iostream>

QFont FontSize::fontSize()
{
    QFont font;
    font.setPixelSize(m_fontSize);
    return font;
}

int FontSize::fontPixel()
{
    return m_fontSize;
}

void FontSize::setFontSize(int size)
{
    m_fontSize = size;
}

int BitChange::bit()
{
    return m_bit;
}

int BitChange::hexMaxLength()
{
    return m_bit / 4;
}

void BitChange::setBit(int newBit)
{
    m_bit = newBit;
}

void BitChange::setHexMaxLength(int newHexMaxLength)
{
    m_hexMaxLength = newHexMaxLength;
}
