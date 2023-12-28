#ifndef _TICK_H_
#define _TICK_H_

#include "number.h"

class CTick
{
public:
    CTick(OBJ_ATTR* _att1, OBJ_ATTR* _att2, OBJ_ATTR* _att3, int _num1, int _num2, int _num3);
    ~CTick();

    void AddOne();
    void Reset();

private:
    CNumber m_digit1;
    CNumber m_digit2;
    CNumber m_digit3;
    u8 m_idigit1;
    u8 m_idigit2;
    u8 m_idigit3;
};


#endif