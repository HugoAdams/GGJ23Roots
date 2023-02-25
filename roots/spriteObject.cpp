#include "spriteObject.h"
#include "tonc.h"

SpriteObject::SpriteObject(OBJ_ATTR* _attribute, int _number)
    :m_attribute(_attribute), m_number(_number)
{
    
}

SpriteObject::~SpriteObject()
{
    m_attribute = nullptr;
}

void SpriteObject::SetPosition(int x, int y)
{
    obj_set_pos(m_attribute, x, y);
}

void SpriteObject::SetVisible(bool _visible)
{
    if (_visible)
    {
        obj_unhide(m_attribute, ATTR0_REG);
    }
    else
    {
        obj_hide(m_attribute);
    }
}