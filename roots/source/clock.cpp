#include "clock.h"

CClock::CClock(OBJ_ATTR *_att1, OBJ_ATTR *_att2, OBJ_ATTR *_att3, int _num1, int _num2, int _num3)
    :m_sec1(_att1, _num1, 48, 16, 0), 
    m_sec2(_att2, _num2, 40, 16, 0), 
    m_sec3(_att3, _num3, 32, 16, 0)
{
    m_isec1 = 0;
    m_isec2 = 0;
    m_isec3 = 0;
    m_counter = 0;
}

CClock::~CClock()
{
}

void CClock::Update()
{
    m_counter++;
    if(m_counter >= 60 && m_isec3 < 9)//60fps
    {
        m_counter = 0;
        m_isec1++;
        if(m_isec1 == 10)
        {
            m_isec1 = 0;
            m_isec2++;
            if(m_isec2 == 10)
            {
                m_isec2 = 0;
                m_isec3++;
                m_sec3.SetDigit(m_isec3);
            }
            m_sec2.SetDigit(m_isec2);
        }
        m_sec1.SetDigit(m_isec1);
    }
}

void CClock::ResetTime()
{
    m_counter = 0;
    m_isec1 = 0;
    m_isec2 = 0;
    m_isec3 = 0;
    m_sec1.SetDigit(0);
    m_sec2.SetDigit(0);
    m_sec3.SetDigit(0);
}
