#ifndef _NUMBER_H_
#define _NUMBER_H_

#include "spriteObject.h"
#include "mathHelp.h"

class CNumber : public SpriteObject
{
public:
    CNumber(OBJ_ATTR* _attr, int _num, int _x, int _y, int _digit);
    ~CNumber();

    void SetDigit(int _i);
    int GetDigit();
private:
    int m_digit;
    Vec2Int m_pos;
};




#endif