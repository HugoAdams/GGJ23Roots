#include "puzzle.h"
#include "tonc.h"
#include "debug.h"

CPuzzle::CPuzzle()
{

}

CPuzzle::~CPuzzle()
{
}

bool CPuzzle::Compare(int _row, std::vector<bool> _data)
{
    if(_row < m_size.y && (int)_data.size() == m_size.x)
    {
        u16 start = _row * m_size.x;
        for(u8 i = 0; i< m_size.x; i++)
        {
            if(_data[i] != m_vecAnswer[start + i])
            {
                char ch[40];
                snprintf(ch,40, "row %i, doesnt match", _row);
                Debug::Log(ch,40);
                return false;
            }
        }
        return true;
    }

    return false;
}

std::vector<short> CPuzzle::GetNumsCol(int _col)
{
    std::vector<short> nums{};
    int count = 0;
    for(u8 i = 0; i < m_size.y; i++)
    {
        bool b = m_vecAnswer[_col + i * m_size.x];
        if(b)
        {
            count++;
        }
        else if(!b && count > 0)
        {
            nums.push_back(count);
            count = 0;
        }
    }

    if(nums.empty() || count > 0)
    {
        nums.push_back(count);
    }
    return nums;
}

std::vector<short> CPuzzle::GetNumsRow(int _row)
{
    std::vector<short> nums{};
    int count = 0;
    for(u8 i = 0; i < m_size.x; i++)
    {
        bool b = m_vecAnswer[_row * m_size.y + i];
        if(b)
        {
            count++;
        }
        else if(!b && count > 0)
        {
            nums.push_back(count);
            count = 0;
        }
    }
    if(nums.empty() || count > 0)
    {
        nums.push_back(count);
    }

    return nums;
}

void CPuzzle::Generate()
{
    m_vecAnswer.clear();
    //__qran_seed = 0;
    for(u16 i = 0; i < m_size.y; i++)
    {
        for(u16 j =0; j < m_size.x; j++)
        {//splatter
            m_vecAnswer.push_back(qran_range(0, 9) > 7);
        }
    }

    for(u16 i = 0; i < m_size.y; i++)
    {
        for(u16 j = 0; j < m_size.x; j++)
        {
            int n = i * m_size.x + j;
            bool sq = m_vecAnswer[n];
            if(sq)
            {
                continue;
            }
            int add = 0;
            if(j != 0)
            {//w
                add += (m_vecAnswer[n - 1]  ? 2 : 0);
            }
            if(j != m_size.x - 1)
            {//e
                add += (m_vecAnswer[n + 1] ? 2 : 0);
            }
            if(i != 0)
            {
                add += (m_vecAnswer[n - m_size.x] ? 1 : 0);
            }
            if(i != m_size.y -1)
            {
                add += (m_vecAnswer[n + m_size.x] ? 1 : 0);
            }
            m_vecAnswer[n] = (qran_range(0,16) + add) > 8;
        }
    }
    //test
    /*m_vecAnswer[8] = true;
    m_vecAnswer[9] = true;
    m_vecAnswer[10] = true;
    m_vecAnswer[11] = true;
    m_vecAnswer[12] = true;
    m_vecAnswer[16] = true;
    m_vecAnswer[20] = true;

    m_vecAnswer[25] = true;
    m_vecAnswer[27] = true;
    m_vecAnswer[29] = true;
    m_vecAnswer[31] = true;

    m_vecAnswer[33] = true;
    m_vecAnswer[35] = true;
    m_vecAnswer[37] = true;
    m_vecAnswer[39] = true;

    m_vecAnswer[42] = true;
    m_vecAnswer[46] = true;
    m_vecAnswer[50] = true;
    m_vecAnswer[51] = true;
    m_vecAnswer[52] = true;
    m_vecAnswer[53] = true;
    m_vecAnswer[54] = true;
    */

    /*m_vecAnswer[8] = true;
    m_vecAnswer[16] = true;

    m_vecAnswer[32] = true;
    m_vecAnswer[48] = true;

    m_vecAnswer[9] =true;
    m_vecAnswer[11] = true;*/
}

void CPuzzle::SetSize(Vec2Int _v2)
{
    m_size = _v2;
}
