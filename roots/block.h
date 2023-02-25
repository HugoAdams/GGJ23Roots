#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "spriteObject.h"
#include "mathHelp.h"

enum BLOCKTYPE
{
    bt_EMPTY = 0,
    bt_BLOCK,
    bt_CROSS,
    bt_DOT,
};

class CBlock : public SpriteObject
{
public:
    CBlock(OBJ_ATTR* _attr, int num, int _x, int _y);
    ~CBlock();

    void SetType(BLOCKTYPE _bt);
    void Update();
    BLOCKTYPE GetType();

    void SetResetPos(int _x, int _y);
    void LerpToResetPos( int _t);
    void LerpToHold(int _t);
    void ReturnToHold();
    bool AtHold();
private:
    BLOCKTYPE m_type;
    Vec2Int m_pos;
    Vec2Int m_holdPos;

    void ChangeSprite(int _spr);
    u8 m_resetting = 0;
    Vec2Int m_resetPos;
};

#endif