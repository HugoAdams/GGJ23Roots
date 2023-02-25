#include "include/tonc.h"
#include <string.h>
#include "rootTiles.h"
#include "backMaps.h"
#include "rootSprites.h"
#include "cursor.h"
#include "grid.h"
#include "debug.h"
#include "clock.h"
#include "tick.h"

typedef unsigned char uint8;
typedef unsigned int uint32;
typedef unsigned short uint16;
typedef uint32 Tile[16];
typedef Tile TileBlock[256];
typedef uint16 ScreenBlock[1024];

#define SCREENBUFFER ((volatile uint16*)(0x06000000))
#define SCREEN_W    240
#define SCREEN_H    160
#define MEM_PALETTE ((uint16*)(0x05000200))
#define MEM_BG_PALETTE ((uint16*)(0x05000000))
//#define MEM_VRAM ((volatile uint32*)0x06000000)
#define MEM_TILE ((TileBlock*)MEM_VRAM)
//#define MEM_OAM ((volatile ObjectAttributes *)0x07000000)
#define MEM_SCREENBLOCKS ((ScreenBlock*)0x6000000)

OBJ_ATTR obj_buffer[128];


inline void vsync()
{
    while (REG_VCOUNT >=160);
    while (REG_VCOUNT < 160);   
}


void UploadBackMem()
{
    memcpy(MEM_BG_PALETTE, rootTilesPal, rootTilesPalLen);
    memcpy(&MEM_TILE[0][0], rootTilesTiles, rootTilesTilesLen);
}

void UploadPlayMaps()
{
    memcpy(&MEM_SCREENBLOCKS[30][0], rootTilesMapSmall, rootTilesMapLen);
    memcpy(&MEM_SCREENBLOCKS[31][0], rootTilesMapBack, rootTilesMapLen);
}

void UploadSprites()
{
    /*    
    memcpy(&MEM_TILE[4], doublePyramidBulletTiles, doublePyramidBulletTilesLen);//divide by 4 for 4bpp
    memcpy(MEM_PALETTE, doublePyramidBulletPal, doublePyramidBulletPalLen);*/
    memcpy(&MEM_TILE[4][1], rootSpritesTiles, rootSpritesTilesLen);
    memcpy(MEM_PALETTE, rootSpritesPal, rootSpritesPalLen);
}

int main()
{
    REG_BG0CNT = BG_4BPP | BG_REG_32x32 | BG_CBB(0) | BG_SBB(31) | BG_PRIO(0) |BG_PRIO_MASK;
    REG_BG1CNT = ((0)<<2) | ((30)<<8) | 0x0000 | 0x0000 ;
    
    
    UploadBackMem();
    memcpy(&MEM_SCREENBLOCKS[30][0], rootTilesMapIntro, rootTilesMapLen);
    memcpy(&MEM_SCREENBLOCKS[31][0], rootTilesMapBack, rootTilesMapLen);

    REG_DISPCNT = DCNT_MODE0 | DCNT_BG0  | DCNT_BG1| DCNT_OBJ | DCNT_OBJ_1D;

    UploadSprites();
    oam_init(obj_buffer, 128); 

    OBJ_ATTR* nutobA = &obj_buffer[0];
    OBJ_ATTR* nutobB = &obj_buffer[1];
    OBJ_ATTR* arrow = &obj_buffer[2];
    
    obj_set_attr(nutobA, 
    ATTR0_8BPP |ATTR0_SQUARE | ATTR0_REG,
    ATTR1_SIZE_16,
    ATTR2_ID(42));
    obj_set_pos(nutobA, 88, 64);

    obj_set_attr(nutobB, 
    ATTR0_8BPP |ATTR0_SQUARE | ATTR0_REG,
    ATTR1_SIZE_16,
    ATTR2_ID(42));
    obj_set_pos(nutobB, 136, 64);

    obj_set_attr(arrow,
    ATTR0_8BPP | ATTR0_8BPP | ATTR0_REG,
    ATTR1_SIZE_8,
    ATTR2_ID(40));
    obj_set_pos(arrow, 92, 84);

    Debug debugScreen;
    bool debugMode = false;
    
    Debug::Log((char*)"Made by Hugo Adams - 2023", 26);

    bool right = false;
    u32 ranCount = 0;
    u16 xscroll = 0;
    u16 yscroll = 0;
    bool scroll = false;
    while (1)
    {
        vsync();

        if(debugMode)
        {
            debugScreen.Render();
            key_poll();
        }
        else
        {
            key_poll();

            if(key_hit(KEY_LEFT))
            {
                obj_set_pos(arrow, 92, 84);
                right = false;
            }
            else if (key_hit(KEY_RIGHT))
            {
                obj_set_pos(arrow, 140, 84);
                right = true;
            }
            ranCount++;
            if(key_hit(KEY_A))
            {
                __qran_seed = right ? ranCount * 2 : ranCount * 4;
                break;
            }
            if(scroll)
            {
                xscroll--;
                yscroll--;
                REG_BG0HOFS = xscroll;
                REG_BG0VOFS = yscroll;
            }
            scroll = !scroll;//once every 2 frames
            oam_copy(oam_mem, obj_buffer, 128);
        }
        if(key_hit(KEY_START))
        {
            debugMode = !debugMode;
            debugScreen.EnableDebug(debugMode);
        }
    }
    UploadPlayMaps();

    OBJ_ATTR* cursorOb = &obj_buffer[0];

    CClock clock = CClock
    (
        &obj_buffer[1],
        &obj_buffer[2], 
        &obj_buffer[3], 
        1,2,3
    );

    CTick tick = CTick
    (
        &obj_buffer[4],
        &obj_buffer[5],
        &obj_buffer[6],
        4,5,6
    );

    CGrid grid = CGrid(GRIDSIZE::SMALL, obj_buffer, 7, &clock, &tick);
    Cursor curse = Cursor(cursorOb, 0, &grid);




    
    while(true)
    {
        vsync();

        if(debugMode)
        {
            debugScreen.Render();
            key_poll();
        }
        else
        {
            clock.Update();
            curse.Update();
            grid.Update();
            oam_copy(oam_mem, obj_buffer, 128);

            if(scroll)
            {
                xscroll++;
                yscroll--;
                REG_BG0HOFS = xscroll;
                REG_BG0VOFS = yscroll;
            }
            scroll = !scroll;//once every 2 frames

        }
        if(key_hit(KEY_START))
        {
            debugMode = !debugMode;
            debugScreen.EnableDebug(debugMode);
        }
    }

    return 0;
}

