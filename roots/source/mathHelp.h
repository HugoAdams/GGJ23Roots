#ifndef _MATHHELP_H_
#define _MATHHELP_H_

#include <tonc_types.h>

struct Vec2
{
    FIXED x;
    FIXED y;

    Vec2(){x = 0; y = 0;}
    
};

struct Vec2Int
{
    Vec2Int(){}
    Vec2Int(int _x, int _y)
    : x(_x), y(_y)
    {}
    
    int x;
    int y;

    Vec2Int Lerp(Vec2Int _a, Vec2Int _b, int _f)
    {
        return Vec2Int
        (
            (_a.x * (1024-_f) + _b.x * _f) >> 10,
            (_a.y * (1024-_f) + _b.y * _f) >> 10 
        );
    }
};

struct RectInt
{
    RectInt(){}
    RectInt(int _x, int _y, int _w, int _h)
    :x(_x), y(_y), w(_w), h(_h)
    {}

    int x;
    int y;
    int w;
    int h;
};


#endif