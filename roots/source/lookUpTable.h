#ifndef _LOOKUPTABLE_H_
#define _LOOKUPTABLE_H_

extern int angleTable[360];

extern const float sineTable[91];

float GetSin(int x);
float GetCos(int x);
float GetTan(int x);

#endif