#ifndef _CCLOCK_H_
#define _CCLOCK_H_

#include "number.h"
#include <tonc_types.h>

class CClock : public GameObject
{
public:
    CClock(OBJ_ATTR* _att1, OBJ_ATTR* _att2, OBJ_ATTR* _att3, int _num1, int _num2, int _num3);
    ~CClock();

    void Update();
    void ResetTime();

private:
    CNumber m_sec1;
    CNumber m_sec2;
    CNumber m_sec3;
    u8 m_isec1;
    u8 m_isec2;
    u8 m_isec3;
    u8 m_counter;
};

#endif //_CCLOCK_H_