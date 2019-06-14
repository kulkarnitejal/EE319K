#include "Music.h"
#include "Timer0A.h"
#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"
#include "Sound.h"
#include "Piano.h"
#include "dac.h"
#include "TExaS.h"	

int value=0;
	int checker=0;
struct Song{double frequ; uint32_t time;};	

struct Song	songone[72] =  { 									//struct for song
	{4778,40000000},
	{4778,40000000},
	{3189,40000000},
	{3189,40000000},
	{2841,20000000},
	{0,2500000},
	{2841,20000000},
	{0,2500000},
	{2841,20000000},
	{0,2500000},
	{2841,20000000},
	{0,2500000},
	{3189,80000000},
	{3579,40000000},
	{3579,40000000},
	{3792,40000000},
	{3792,40000000},
	{4257,40000000},
	{4257,40000000},
	{4778,80000000},
	{3189,40000000},
	{3189,20000000},
	{0,2500000},
	{3189,20000000},
	{0,2500000},
	{3579,40000000},
	{3579,40000000},
	{3792,40000000},
	{3792,20000000},
		{0,2500000},
	{3792,20000000},
		{0,2500000},
	{4257,80000000},
	{3189,40000000},
	{3189,20000000},
		{0,2500000},
	{3189,20000000},
		{0,2500000},
	{3579,20000000},
		{0,2500000},
	{3579,20000000},
		{0,2500000},
	{3579,20000000},
		{0,2500000},
	{3579,20000000},
		{0,2500000},
	{3792,40000000},
	{3792,20000000},
		{0,2500000},
	{3792,20000000},
		{0,2500000},
	{4257,80000000},
	{4778,40000000},
	{4778,40000000},
	{3189,40000000},
	{3189,40000000},
	{2841,20000000},
		{0,2500000},
	{2841,20000000},
		{0,2500000},
	{2841,20000000},
		{0,2500000},
	{2841,20000000},
		{0,2500000},
	{3189,80000000},
	{3579,40000000},
	{3579,40000000},
	{3792,40000000},
	{3792,40000000},
	{4257,40000000},
	{4257,40000000},
	{4778,80000000},

};

void Music_Init(void)
{
	int delay;																						//use port e0 for switch
	SYSCTL_RCGCGPIO_R |=  0x10;
	delay+=123456;
	GPIO_PORTE_DIR_R &=0XFE;															//intialization of port e0
	GPIO_PORTE_DEN_R |=0X01;
	Timer0A_Init();

}

uint32_t isPressed()
{
	int isolated =GPIO_PORTE_DATA_R &  0X01;							//isolate port e0
	if( isolated == 1)			
		return 0;																						//is pressed
	else 
		return 1;																						//song button not pressed
}

void SongPlay(uint32_t input)													
{
			if(input==1)																			//select song
			{
			Sound_Play(songone[value].frequ);									//use struct
			if(checker==0){																		//check next note
		 TIMER0_TAILR_R= songone[value].time;								//timer0A for duration of note
				checker++;}																			//next note
			TIMER0_CTL_R = 0x00000001;
			
			}
		
}


