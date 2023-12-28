#ifndef _DEBUG_H_
#define _DEBUG_H_

#include <stdio.h>

const extern bool VisualNums[200];
const extern bool VisualLttr[520];
const extern bool VisualSymbl[100];

class Debug
{
public:
    Debug();
    ~Debug();
    static void Log(char* _word, int _len);

    void Render();
    void EnableDebug(bool _enable);

private:
    static char m_word[48];
    
    bool m_drawRequired;
};

#endif