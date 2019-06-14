#include <stdint.h>
#include "Sprites.h"
#include "ST7735.h"
#include "Images.h"
#include "Trash.h"
#include "../inc/tm4c123gh6pm.h"

const int top = 1626;
const int high = 1258;
const int med = 870;
const int low = 491;
const int bot = 113;

const int sec1 = 416;
const int sec2 = 718;
const int sec3 = 1021;
const int sec4 = 1323; 

int x,y,score,lives, highscore;
 
 
 void Sprites()
 {
	 x=64;
	 y=159;
	 score=0;
	 highscore=0;
	 lives=3;
	
 }

void updateScore()
{
	updateHighscore();
ST7735_SetCursor(0, 0);
	ST7735_OutString("Score: ");
	ST7735_SetCursor(6,0);
	ST7735_OutUDec(score);
}

void updateHighscore()
{
	if(score>highscore)
		highscore = score;
}

void checkIfIn(uint32_t dat1, uint32_t dat2)
{
	if(lives==1)
	{

		ST7735_FillScreen(0x0000);            								// set screen to black
		ST7735_SetCursor(1, 1);
		ST7735_OutString("GAME OVER");
		ST7735_SetCursor(1, 2);
		ST7735_OutString("Highscore: ");											//print high score once game is over
		ST7735_OutUDec(highscore);
		reset();
		while((GPIO_PORTF_DATA_R & 0X01)==1){};
	}

	checkBall(dat1,dat2);
	//int height = 149-y;
// ST7735_DrawFastVLine(x, 149, height, 0x0000);
//	for(int i=0;i<5000000;i++){};
	if(x<xtrash+30&& x>xtrash-20)
	{
		if(y<ytrash+36 &&y>ytrash-20)														//check if range is enough for trashcan
		{
			score+=10;
			updateScore();
			
		}
		else 
		{
		lives--;
		updateLives();
		}
	}
	else 
	{
		lives--;
		updateLives();

		
	}
	

}

void updateLives()
{
		
		//ST7735_SetCursor(6,1);
		//ST7735_OutUDec(lives);	
	int val=95;
		for(int i=1;i<lives+1;i++){
	 ST7735_DrawCircle(val,0,0xFFFF);												//draws circles for lives
		val+=10;}
}


void reset() 
{
	x=64;
	y=159;
	score=0;
	lives=4;
}

void checkBall(uint32_t dat1, uint32_t dat2)
{
	//check x first
	if(dat2<sec1)																					//sections are for x's
	{
		if(dat1>high)																				//high etc is for ys
		{
			x=13;
			y=18;
			ST7735_DrawBitmap(x, y, ball,20,20);
		}
		else if(dat1>med && dat1<high)
		{
			x=13;
			y=55;
			ST7735_DrawBitmap(x, y, ball, 20,20);
		}
		else if(dat1>low && dat1<med)
		{
			x=13;
			y=92;
			ST7735_DrawBitmap(x, y, ball, 20,20);
		}
		else if(dat1<low)
		{
			x=13;
			y=129;
			ST7735_DrawBitmap(x, y, ball, 20,20);
		}
		
	}
	
	else if(dat2<sec2 && dat2>sec1)
	{
		if(dat1>high)
		{
			x=38;
			y=18;
			ST7735_DrawBitmap(x, y, ball, 20,20);
		}
		else if(dat1>med && dat1<high)
		{
			x=38;
			y=55;
			ST7735_DrawBitmap(x, y, ball, 20,20);
		}
		else if(dat1>low && dat1<med)
		{
			x=38;
			y=92;
			ST7735_DrawBitmap(x, y, ball, 20,20);
		}
		else if(dat1<low)
		{
			x=38;
			y=129;
			ST7735_DrawBitmap(x, y, ball, 20,20);
		}
	}
		
	else if(dat2<sec3 && dat2>sec2)
	{
		if(dat1>high)
		{
			x=63;
			y=18;
			ST7735_DrawBitmap(x, y, ball, 20,20);
		}
		else if(dat1>med && dat1<high)
		{
			x=63;
			y=55;
			ST7735_DrawBitmap(x, y, ball, 20,20);
		}
		else if(dat1>low && dat1<med)
		{
			x=63;
			y=92;
			ST7735_DrawBitmap(x, y, ball, 20,20);
		}
		else if(dat1<low)
		{
			x=63;
			y=129;
			ST7735_DrawBitmap(x, y, ball, 20,20);
		}
		
	}
	
	else if(dat2<sec4 && dat2>sec3)
	{
		if(dat1>high)
		{
			x=88;
			y=18;
			ST7735_DrawBitmap(x, y, ball, 20,20);
		}
		else if(dat1>med && dat1<high)
		{
			x=88;
			y=55;
			ST7735_DrawBitmap(x, y, ball, 20,20);
		}
		else if(dat1>low && dat1<med)
		{
			x=88;
			y=92;
			ST7735_DrawBitmap(x, y, ball, 20,20);
		}
		else if(dat1<low)
		{
			x=88;
			y=129;
			ST7735_DrawBitmap(x, y, ball, 20,20);
		}
		
	}
	
	else if(dat2>sec4)
	{
		if(dat1>high)
		{
			x=113;
			y=18;
			ST7735_DrawBitmap(x, y, ball, 20,20);
		}
		else if(dat1>med && dat1<high)
		{
			x=113;
			y=55;
			ST7735_DrawBitmap(x, y, ball, 20,20);
		}
		else if(dat1>low && dat1<med)
		{
			x=113;
			y=92;
			ST7735_DrawBitmap(x, y, ball, 20,20);
		}
		else if(dat1<low)
		{
			x=113;
			y=129;
			ST7735_DrawBitmap(x, y, ball, 20,20);
		}
		
	}
}


