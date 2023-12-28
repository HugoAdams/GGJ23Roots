#include "block.h"
#include <tonc.h>


CBlock::CBlock(OBJ_ATTR *_attr, int _num, int _x, int _y)
:SpriteObject(_attr, _num), m_pos(_x, _y), m_holdPos(_x, _y)
{
    m_type = BLOCKTYPE::bt_EMPTY;

    obj_set_attr(m_attribute,
    ATTR0_8BPP | ATTR0_REG | ATTR0_SQUARE,
    ATTR1_SIZE_8,
    ATTR2_ID(14));

    SetPosition(_x, _y);
    
}

CBlock::~CBlock()
{
}

void CBlock::SetType(BLOCKTYPE _type)
{
    m_type = _type;
    int spr = 0;
    switch (m_type)
    {
    case bt_EMPTY:
        spr = 14;
        break;
    case bt_BLOCK:
        spr = 4;
        break;
    case bt_CROSS:
        spr = 6;
        break;
    case bt_DOT:
        spr = 8;
    default:
        break;
    }
    ChangeSprite(spr);
}

void CBlock::Update()
{
}

BLOCKTYPE CBlock::GetType()
{
    return m_type;
}

void CBlock::SetResetPos(int _x, int _y)
{
    m_resetPos.x = _x;
    m_resetPos.y = _y;
    m_resetting = 1;
}

void CBlock::LerpToResetPos(int _t)
{
    m_pos = m_pos.Lerp(m_holdPos, m_resetPos, _t);
    SetPosition(m_pos.x, m_pos.y);
}

void CBlock::LerpToHold(int _t)
{
    m_pos = m_pos.Lerp(m_resetPos, m_holdPos, _t);
    SetPosition(m_pos.x, m_pos.y);
}

void CBlock::ReturnToHold()
{
    m_resetting = 2;
}

bool CBlock::AtHold()
{
    return m_pos.x == m_holdPos.x && m_pos.y == m_holdPos.y;
}

void CBlock::ChangeSprite(int _spr)
{
    obj_set_attr(m_attribute,
    ATTR0_8BPP | ATTR0_REG | ATTR0_SQUARE,
    ATTR1_SIZE_8,
    ATTR2_ID(_spr));

    SetPosition(m_pos.x, m_pos.y);
}
