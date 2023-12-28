#ifndef _GRID_H_
#define _GRID_H_

#include "gameObject.h"
#include "mathHelp.h"
#include "block.h"
#include "puzzle.h"
#include <vector>

enum GRIDSIZE
{
    SMALL =0,
    MEDIUM,
    LARGE,
};

class CNumber;//pre declare
class CClock;
class CTick;

struct NumGroup
{
    std::vector<CNumber> m_cNums;
    u16 m_index;
};

class CGrid : public GameObject
{
public:
    CGrid(GRIDSIZE _size, OBJ_ATTR* objBuffer, int start, CClock* _clock, CTick* _tick);
    ~CGrid();

    bool SetBlock(u16 _x, u16 _y, BLOCKTYPE _bt);
    bool SetBlockHeld(u16 _x, u16 _y, BLOCKTYPE _heldType);
    BLOCKTYPE GetBlockType(u16 _x, u16 _y);
    void Update();

    Vec2Int GetSize();
    bool IsBusy();

private:
    OBJ_ATTR* m_objBuffer;
    Vec2Int m_size;
    std::vector<CBlock> m_vecBlocks;
    std::vector<NumGroup> m_vecNumCols;
    std::vector<NumGroup> m_vecNumRows;
    CPuzzle m_puzzle;
    CClock* m_clock;
    CTick* m_tick;

    bool CheckWin();
    void SetSize(GRIDSIZE _size);//for puzzle init
    void StartReset();
    void EndReset();

    void GenPuzzle();
    u8 m_resetAnimate;
    u16 m_resetRad;
    u16 m_resetAngle;
    u8 m_resetDraw;
    u8 m_resetDraw2;
    u16 m_resetT;

    u8 m_numberMemStart;
    
    void ResetCircle(u16 _angleOff);
};




#endif //_GRID_H_