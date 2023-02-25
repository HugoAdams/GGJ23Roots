#ifndef _CURSOR_H_
#define _CURSOR_H_

#include "spriteObject.h"
#include "mathHelp.h"
#include "grid.h"

class Cursor : public SpriteObject
{
public:
    Cursor(OBJ_ATTR* _attr, int _num, CGrid* _grid);
    ~Cursor();

    void Update();

    void SetPosition(int x, int y);
private:

    Vec2Int m_pos;
    Vec2Int m_index;
    u8 m_frame;
    u8 m_lastMove;
    void ChangeSprite(int _frame);

    CGrid* m_grid;
    RectInt m_bounds;

    bool m_done;
};

#endif