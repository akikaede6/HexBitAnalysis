#include "util.h"

#include <iostream>

FontSize::FontSize() = default;

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
