#include "cursor.h"
#include "include/tonc.h"
#include "gInfo.h"

Cursor::Cursor(OBJ_ATTR *_attr, int _num, CGrid* _grid)
: SpriteObject(_attr, _num), m_grid(_grid)
{
    obj_set_attr(m_attribute,
    ATTR0_8BPP | ATTR0_REG | ATTR0_SQUARE,
    ATTR1_SIZE_8,
    ATTR2_ID(10));

    SetPosition(_gridX, _gridY);
    Vec2Int gr = m_grid->GetSize();
    m_index = Vec2Int(0,0);
    m_bounds = RectInt(_gridX, _gridY, gr.x * 8 - 7, gr.y * 8-7);
    m_done = false;
}

Cursor::~Cursor()
{
}

void Cursor::Update()
{
    key_poll();
    if(m_done)
    {
        if(m_grid->IsBusy() == false)
        {
            m_done = false;
            SetPosition(_gridX, _gridY);
            m_index = Vec2Int(0,0);
        }
        return;
    }
    int x = key_tri_horz();
    int y = key_tri_vert();
    
    
    if(m_lastMove > 0)
    {
        m_lastMove--;
    }
    else if (x == 0 && y == 0)
    {
        m_lastMove = 0;
    }
    else
    {
        //moving here
        m_pos.x += x * 8;
        m_pos.y += y * 8;
        m_index.x += x;
        m_index.y += y;
        
        m_pos.x = clamp(m_pos.x, m_bounds.x, m_bounds.x + m_bounds.w);
        m_pos.y = clamp(m_pos.y, m_bounds.y, m_bounds.y + m_bounds.h);
        m_index.x = clamp(m_index.x, 0, 8);
        m_index.y = clamp(m_index.y, 0, 8);
        SetPosition(m_pos.x, m_pos.y);
        m_lastMove = 10;
    }
    
    bool L = key_held(KEY_L);
    if(key_hit(KEY_A))
    {
        if(m_grid->SetBlock(m_index.x, m_index.y, L ? bt_DOT : bt_BLOCK))
        {
            SetPosition(0,0);//end game
            m_done = true;
            return;
        }
    }
    else if(key_hit(KEY_B))
    {
        m_grid->SetBlock(m_index.x, m_index.y, L ? bt_EMPTY : bt_CROSS);
    }

    m_frame++;
    if(m_frame > 16)
    {
        m_frame = 0;
    }
    ChangeSprite(m_frame > 8 ? 12 : 10);
}

void Cursor::SetPosition(int _x, int _y)
{
    SpriteObject::SetPosition(_x, _y);
    m_pos.x = _x;
    m_pos.y = _y;
}

void Cursor::ChangeSprite(int _frame)
{
    obj_set_attr(m_attribute,
    ATTR0_8BPP | ATTR0_REG | ATTR0_SQUARE,
    ATTR1_SIZE_8,
    ATTR2_ID(_frame));

    obj_set_pos(m_attribute, m_pos.x, m_pos.y);
}
