#ifndef _PUZZLE_H_
#define _PUZZLE_H_

#include <vector>
#include "mathHelp.h"

class CPuzzle
{
public:
    CPuzzle();
    ~CPuzzle();

    bool Compare(int _row, std::vector<bool> _data);
    std::vector<short> GetNumsCol(int _col);
    std::vector<short> GetNumsRow(int _row);

    void Generate();

    void SetSize(Vec2Int _v2);

private:
    std::vector<bool> m_vecAnswer;
    Vec2Int m_size;
};

#endif