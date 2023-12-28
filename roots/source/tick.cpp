#include "tick.h"

CTick::CTick(OBJ_ATTR *_att1, OBJ_ATTR *_att2, OBJ_ATTR *_att3, int _num1, int _num2, int _num3)
    :m_digit1(_att1, _num1, 48, 24, 0),
    m_digit2(_att2, _num1, 40, 24, 0),
    m_digit3(_att3, _num1, 32, 24, 0)
{
    m_idigit1 = 0;
    m_idigit2 = 0;
    m_idigit3 = 0;
}

CTick::~CTick()
{
}

void CTick::Reset()
{
    m_idigit1 = 0;
    m_idigit2 = 0;
    m_idigit3 = 0;
    m_digit1.SetDigit(0);
    m_digit2.SetDigit(0);
    m_digit3.SetDigit(0);
}

void CTick::AddOne()
{
    if(m_idigit3 == 9)
    {
        Reset();
    }
    m_idigit1++;
    if(m_idigit1 == 10)
    {
        m_idigit1 = 0;
        m_idigit2++;
        if(m_idigit2 == 10)
        {
            m_idigit2 = 0;
            m_idigit3++;
            m_digit3.SetDigit(m_idigit3);
        }
        m_digit2.SetDigit(m_idigit2);
    }
    m_digit1.SetDigit(m_idigit1);
}