#include "util.h"

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
