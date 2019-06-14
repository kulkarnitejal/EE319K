//#ifndef __sprites_h
#define __sprites_h
#include <stdint.h>

//extern int x,y;
//extern const int top = 1626;
//extern const int high = 1258;
//extern const int med = 870;
//const int low = 491;
//const int bot = 113;
void updateLives(void);
 void Sprites(void);
 void printBall(void);
void updateScore(void);
void updateHighscore(void);
void checkIfIn(uint32_t dat1, uint32_t dat2);
void reset(void);

void checkBall(uint32_t dat1, uint32_t dat2);



























//#endif /* __images_h */
