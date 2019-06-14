// Lab6.c
// Runs on LM4F120 or TM4C123
// Use SysTick interrupts to implement a 3-key digital piano
// MOOC lab 13 or EE319K lab6 starter
// Program written by: Meha Halabe & Tejal Kulkarni
// Date Created: 3/6/17 
// Last Modified: 3/5/18 
// Lab number: 6
// Hardware connections
// PortB0-3 for DAC PortA2-4 for keys

#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"
#include "Sound.h"
#include "Piano.h"
#include "dac.h"
#include "Music.h"
#include "TExaS.h"
const double freq[3]={6378,5682,5062};

// basic functions defined at end of startup.s
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
int val=0;
extern int value;

int main(void){      
  TExaS_Init(SW_PIN_PE3210,DAC_PIN_PB3210,ScopeOn);    // bus clock at 80 MHz
	int delay;
	int count=0;
	SYSCTL_RCGCGPIO_R |=  0x20;
	delay+=123456;
	GPIO_PORTF_DIR_R |=0X04;											//intialize portf for heartbeat
	GPIO_PORTF_DEN_R |=0X04;
  Piano_Init();
  Sound_Init();
	Music_Init();
  // other initialization
  EnableInterrupts();


  while(1)
	{ 
		
		if(count==500000){
			GPIO_PORTF_DATA_R ^= 0X04;								//heartbeat toggle
			count=0;
		}
		count++;
		val=Piano_In();															//val has key pressed (0-7)
		if(val==0x01||val==0x02||val==0x04)	
		{
			Sound_Play(freq[val/2]);									//freqency in freq array of key pressed
		}
		else 
		{
			Sound_Play(0);														//not pressed, no sougn outputted
		}
		if(isPressed()== 0)
		{
		SongPlay(1);																//song button pressed, play song
		}
		else 
		{
			value=0;																	//song button not pressed
		}
		
  }    
}


