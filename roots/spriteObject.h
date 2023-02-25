#ifndef _SPRITEOBJECT_H_
#define _SPRITEOBJECT_H_

#include <tonc_types.h>
#include "gameObject.h"

class SpriteObject : public GameObject
{
public:
    SpriteObject(OBJ_ATTR* _attribute, int _number);
    ~SpriteObject();

    virtual void Update() {};

    virtual void SetVisible(bool _visible);
    virtual void SetPosition(int x, int y);
protected:
    OBJ_ATTR* m_attribute;
    int m_number;

};




#endif //_SPRITEOBJECT_H_