#include "number.h"
#include "tonc.h"

CNumber::CNumber(OBJ_ATTR* _attr, int _num, int _x, int _y, int _digit)
: SpriteObject(_attr, _num), m_digit(_digit), m_pos(_x, _y)
{
    obj_set_attr(m_attribute,
    ATTR0_8BPP | ATTR0_REG | ATTR0_SQUARE,
    ATTR1_SIZE_8,
    ATTR2_ID(16 + _digit * 2));//should work

    SetPosition(_x, _y);

    
}

CNumber::~CNumber()
{
}

int CNumber::GetDigit()
{
    return m_digit;
}

void CNumber::SetDigit(int _i)
{
    m_digit = _i;
    obj_set_attr(m_attribute,
    ATTR0_8BPP | ATTR0_REG | ATTR0_SQUARE,
    ATTR1_SIZE_8,
    ATTR2_ID(16 + m_digit * 2));//should work

    SetPosition(m_pos.x, m_pos.y);
}