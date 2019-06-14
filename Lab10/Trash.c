#include <stdint.h>
#include "Sprites.h"
#include "ST7735.h"
#include "../inc/tm4c123gh6pm.h"
#include "Random.h"
#include "Images.h"


const int y1 = 37;
const int y2= 74;
const int y3= 111;
int xtrash;
int ytrash;
void TrashInit()
{

}

void refreshTrash()
{
	
	xtrash= Random32()%98;
 ytrash= Random32()%3;
	
	//for y
	if (ytrash==0)
	{
		ST7735_DrawBitmap(xtrash, y1, trash, 30,36);
		ytrash=y1;
		//make sure sprites gets the coordinates;
	}
	if (ytrash==1)
	{
		ST7735_DrawBitmap(xtrash, y2, trash, 30,36);
		ytrash=y2;
		//make sure sprites gets the coordinates;
	}
	if (ytrash==2)
	{
		ST7735_DrawBitmap(xtrash, y3,trash, 30,36);
		ytrash=y3;
		//make sure sprites gets the coordinates;
	}
	
	
}

