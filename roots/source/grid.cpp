#include "grid.h"
#include "gInfo.h"
#include "number.h"
#include "debug.h"
#include <stdio.h>
#include "tonc.h"
#include "lookUpTable.h"
#include "clock.h"
#include "tick.h"

CGrid::CGrid(GRIDSIZE _size, OBJ_ATTR* objBuffer, int start, CClock* _clock, CTick* _tick)
:m_objBuffer(objBuffer), m_clock(_clock), m_tick(_tick)
{
    SetSize(_size);
    m_puzzle.SetSize(m_size);
    u16 objcount = 0;
    for(u16 i = 0; i < m_size.y; i++)
    {
        for(u16 j = 0; j < m_size.x; j++)
        {
            OBJ_ATTR* cbOb = &m_objBuffer[start + objcount];
            CBlock cb = CBlock(cbOb, start + i, j*8 + _gridX, i*8 + _gridY);
            m_vecBlocks.push_back(cb);
            objcount++;
        }
    }

    m_numberMemStart = start + objcount;
    
    //assign more objs
    GenPuzzle();

    m_resetAnimate = 0;
    m_resetRad = 0;
    m_resetAngle = 0;
    m_resetDraw = 0;
    m_resetDraw2 = 0;
    m_resetT = 0;
}

CGrid::~CGrid()
{
}

bool CGrid::SetBlock(u16 _x, u16 _y, BLOCKTYPE _setType)
{
    BLOCKTYPE fin = _setType;
    u16 index = _y * 8 + _x;
    BLOCKTYPE curr = m_vecBlocks[index].GetType();
    if(curr == bt_BLOCK && (_setType == bt_BLOCK || _setType == bt_CROSS))
    {
        fin = bt_EMPTY;
    }
    else if (curr == bt_CROSS && (_setType == bt_CROSS || _setType == bt_BLOCK))
    {
        fin = bt_EMPTY;
    }
    else if (curr == bt_DOT && _setType == bt_DOT)
    {
        fin = bt_EMPTY;    
    }

    m_vecBlocks[index].SetType(fin);

    if(fin == bt_BLOCK)
    {
        bool win = CheckWin();
        //maybe do something here
        return win;
    }
    return false;
}

bool CGrid::SetBlockHeld(u16 _x, u16 _y, BLOCKTYPE _heldType)
{
    u16 index = _y * 8 + _x;
    BLOCKTYPE curr = m_vecBlocks[index].GetType();
    
    if ((curr == bt_CROSS && (_heldType == bt_BLOCK || _heldType == bt_DOT)) 
    || (curr == bt_BLOCK && (_heldType == bt_CROSS || _heldType == bt_DOT)))
    {
        return false;
    }
    m_vecBlocks[index].SetType(_heldType);

    if(_heldType == bt_BLOCK)
    {
        return CheckWin();
    }
    return false;
}

BLOCKTYPE CGrid::GetBlockType(u16 _x, u16 _y)
{
    return m_vecBlocks[_y * 8 + _x].GetType();
}

void CGrid::Update()
{
    if(m_resetAnimate > 0)
    {
        if(m_resetAnimate == 1)
        {//go to position
            if(m_resetRad < 72)
            {
                m_resetRad++;
            }

            m_resetDraw++;
            if(m_resetDraw > 1)
            {
                m_resetAngle++;
                ResetCircle(m_resetAngle);
                m_resetDraw = 0;
            }

            if(m_resetT < 1024)
            {
                m_resetT+=8;
            }
            else
            {
                m_resetT = 1024;
                m_resetAnimate = 2;
                m_resetDraw2 = 0;
            }
            for(u8 i = 0; i < m_vecBlocks.size(); i++)
            {
                m_vecBlocks[i].LerpToResetPos(m_resetT);
            }
        }
        else if( m_resetAnimate == 2)//hold position change tile
        {
            m_resetDraw++;
            if(m_resetDraw > 1)
            {
                m_resetAngle++;
                ResetCircle(m_resetAngle);
                m_resetDraw = 0;
                if(m_resetDraw2 < m_vecBlocks.size())
                {
                    m_vecBlocks[m_resetDraw2].SetType(bt_EMPTY);
                    m_resetDraw2++;
                }
                else
                {
                    m_resetAnimate = 3;
                    m_resetDraw2 = 0;
                }
            }
            for(u8 i = 0; i < m_vecBlocks.size(); i++)
            {
                m_vecBlocks[i].LerpToResetPos(m_resetT);
            }
        }
        else if (m_resetAnimate == 3)//return to position
        {
            m_resetDraw++;
            if(m_resetDraw > 1)
            {
                m_resetAngle++;
                ResetCircle(m_resetAngle);
                m_resetDraw = 0;
            }

            if(m_resetT > 0)
            {
                m_resetT -= 8;
            }
            else
            {
                m_resetT = 0;
                m_resetAnimate = 4;
            }
            for(u8 i = 0; i < m_vecBlocks.size(); i++)
            {
                m_vecBlocks[i].LerpToResetPos(m_resetT);
            }
        }
        else if( m_resetAnimate == 4)
        {
            //reset all the numbers
            GenPuzzle();
            EndReset();
        }


    }
}

Vec2Int CGrid::GetSize()
{
    return m_size;
}

bool CGrid::IsBusy()
{
    return m_resetAnimate != 0;
}

bool CGrid::CheckWin()
{
    std::vector<bool> data;
    for(int i = 0; i < m_size.y; i++)
    {
        data.clear();
        for(int j = 0; j < m_size.x; j++)
        {
            bool b = m_vecBlocks[i*m_size.x + j].GetType() == bt_BLOCK;
            data.push_back(b);
        }

        if(!m_puzzle.Compare(i, data))
        {
            
            return false;
        }
    }

    StartReset();
    return true;
}

void CGrid::SetSize(GRIDSIZE _size)
{
    if(_size == GRIDSIZE::SMALL)
    {
        m_size.x = 8;
        m_size.y = 8;
    }
    else if (_size == GRIDSIZE::MEDIUM)
    {
        m_size.x = 10;
        m_size.y = 10;
    }
    else if (_size == GRIDSIZE::LARGE)
    {
        m_size.x = 18;
        m_size.y = 12;
    }
}

void CGrid::StartReset()
{
    m_resetAnimate = 1;
    m_resetDraw = 0;
    m_resetDraw2 = 0;
    m_resetRad = 32;
    m_resetT = 0;

    ResetCircle(0);
    m_tick->AddOne();
}

void CGrid::EndReset()
{
    m_resetAnimate = 0;
    m_clock->ResetTime();
}

void CGrid::GenPuzzle()
{
    if(!m_vecNumCols.empty() || !m_vecNumRows.empty())
    {
        for(u8 i =0; i < m_vecNumCols.size(); i++)
        {
            m_vecNumCols[i].m_cNums.clear();
        }
        for(u8 i = 0; i < m_vecNumRows.size(); i++)
        {
            m_vecNumRows[i].m_cNums.clear();
        }
        m_vecNumCols.clear();
        m_vecNumRows.clear();
        for(u8 i = m_numberMemStart; i < 128; i++)
        {
            OBJ_ATTR* ob = &m_objBuffer[i];
            obj_set_attr(ob, 0,0,0);
        }
    }

    m_puzzle.Generate();

    int objCount = m_numberMemStart;
    //column numbers //nums are upside down.
    int numY = _gridY - 16;
    for(u16 i =0; i < m_size.y; i++)
    {
        std::vector<short> nums = m_puzzle.GetNumsCol(i);
        NumGroup numCol;
        numCol.m_index = i;
        for(u16 j = 0; j < nums.size(); j++)
        {
            OBJ_ATTR* numOb = &m_objBuffer[objCount];
            CNumber cnum = CNumber(numOb, objCount,
            _gridX + i*8, numY - (nums.size()-1 -j) * 8, nums[j]
            );
            numCol.m_cNums.push_back(cnum);
            objCount++;
        }

        m_vecNumCols.push_back(numCol);
    }

    //row numbers
    int numX = _gridX - 16;
    for( u16 i = 0; i < m_size.x; i++)
    {
        NumGroup numRow;
        numRow.m_index = i;
        std::vector<short> nums = m_puzzle.GetNumsRow(i);
        for(u16 j = 0; j < nums.size(); j++)
        {
            OBJ_ATTR* numOb = &m_objBuffer[objCount];
            CNumber cnum = CNumber(numOb, objCount,
            numX - (nums.size()-1 - j) * 8, _gridY + i *8, nums[j]
            );
            objCount++;
        }
        m_vecNumRows.push_back(numRow);
    }
}

void CGrid::ResetCircle(u16 _angleOff)
{
    for(u16 i = 0; i< m_vecBlocks.size(); i++)
    {
        int x = 120 + (m_resetRad * GetCos(i * 6 + _angleOff));
        int y = 80 + (m_resetRad * GetSin(i* 6 +_angleOff));
        m_vecBlocks[i].SetResetPos(x, y);
        //m_vecBlocks[i].SetPosition(x,y);
    }
}
