// SpaceInvaders.c
// Runs on LM4F120/TM4C123
// Jonathan Valvano and Daniel Valvano
// This is a starter project for the EE319K Lab 10

// Last Modified: 11/20/2018 
// http://www.spaceinvaders.de/
// sounds at http://www.classicgaming.cc/classics/spaceinvaders/sounds.php
// http://www.classicgaming.cc/classics/spaceinvaders/playguide.php
/* This example accompanies the books
   "Embedded Systems: Real Time Interfacing to Arm Cortex M Microcontrollers",
   ISBN: 978-1463590154, Jonathan Valvano, copyright (c) 2018

   "Embedded Systems: Introduction to Arm Cortex M Microcontrollers",
   ISBN: 978-1469998749, Jonathan Valvano, copyright (c) 2018

 Copyright 2018 by Jonathan W. Valvano, valvano@mail.utexas.edu
    You may use, edit, run or distribute this file
    as long as the above copyright notice remains
 THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 VALVANO SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 For more information about my classes, my research, and my books, see
 http://users.ece.utexas.edu/~valvano/
 */
// ******* Possible Hardware I/O connections*******************
// Slide pot pin 1 connected to ground
// Slide pot pin 2 connected to PD2/AIN5
// Slide pot pin 3 connected to +3.3V 
// fire button connected to PE0
// special weapon fire button connected to PE1
// 8*R resistor DAC bit 0 on PB0 (least significant bit)
// 4*R resistor DAC bit 1 on PB1
// 2*R resistor DAC bit 2 on PB2
// 1*R resistor DAC bit 3 on PB3 (most significant bit)
// LED on PB4
// LED on PB5

// Backlight (pin 10) connected to +3.3 V
// MISO (pin 9) unconnected
// SCK (pin 8) connected to PA2 (SSI0Clk)
// MOSI (pin 7) connected to PA5 (SSI0Tx)
// TFT_CS (pin 6) connected to PA3 (SSI0Fss)
// CARD_CS (pin 5) unconnected
// Data/Command (pin 4) connected to PA6 (GPIO), high for data, low for command
// RESET (pin 3) connected to PA7 (GPIO)
// VCC (pin 2) connected to +3.3 V
// Gnd (pin 1) connected to ground

#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"
#include "ST7735.h"
#include "Random.h"
#include "PLL.h"
#include "ADC.h"
#include "Images.h"
#include "Sound.h"
#include "Timer0.h"
#include "Timer1.h"
#include "Trash.h"
#include "Sprites.h"
#include "DAC.h"

uint32_t data1,data2;
uint32_t data[2];
int xval;
uint32_t Convert(uint32_t input){
  uint32_t pos;
	
	
	pos= (372*input)/1000;
	pos = pos +108;
	return pos;
}
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
void updateScreen(void);
void PortFInit(void);
//void Delay100ms(uint32_t count); // time delay in 0.1 seconds
uint32_t ADCMail;
int32_t ADCStatus=0;
int32_t ballStatus=0;

void SysTick_Init(void){
	// write this
	NVIC_ST_CTRL_R &=0;																//Disable SysTick
	
	NVIC_ST_RELOAD_R|=0x145855;											//Set reload value to 60Hz (1/60)/12.5ns
	
	NVIC_ST_CURRENT_R&=0;														
	
	NVIC_ST_CTRL_R|=0X00000007;												//Enable interrupts and clock
}

void SysTick_Handler(){
	
	ADC_In(data);									
	ADCStatus=-1;																			//Notify that status has changed
	data1=Convert(data[0]);
	data2=Convert(data[1]);
	xval= (data2*7)/100;
 
	if((GPIO_PORTF_DATA_R  &0X10)==0){
		ballStatus=-1;}
	
		
}	

int main(void){
  PLL_Init(Bus80MHz);      												 // Bus clock is 80 MHz 
  Random_Init(1);																		//initialize everything
	PortFInit();
  Output_Init();
	Sound_Init();
	updateScreen();
	refreshTrash();
	Sprites();
	SysTick_Init();
	ADC_Init();
	Timer0_Init(7256);
	updateScore();
			updateLives();
  while(1){
	
		while(ADCStatus<0)
		{
			
			//updateScreen();
			ST7735_DrawBitmap(xval, 159, ball, 20,20);
		
			if(ballStatus ==-1){
			NVIC_ST_CTRL_R&=0X00000005;	
			ST7735_SetCursor(0,0);
			ADCStatus=0;																			//change status
				ballStatus= 0;
			checkIfIn(data1,data2);
			for(int i=0;i<5000000;i++){};
				updateScreen();																	//refreshes screen
				refreshTrash();											
				updateScore();
				updateLives();
			NVIC_ST_CTRL_R|=0X00000007;	
			}
			
		}
  }

}

void updateScreen()
{
	// ST7735_FillScreen(0xF81F);           							 // set screen to black
 for(int i=0; i< 127;i+=32)
	{
		for(int j=0; j<191;j+=32)
		{
				ST7735_DrawBitmap(i, j, floorTile, 32,32); 			// set up screen tiles
		}
	}
}

void PortFInit()
{
	volatile int delay;
		SYSCTL_RCGCGPIO_R |= 0x20;
	delay+=123456;
	GPIO_PORTF_LOCK_R = GPIO_LOCK_KEY;	
	GPIO_PORTF_CR_R |= 0XFFFFFFFF;											//intializing port f
	GPIO_PORTF_DIR_R &=0XEE;
	GPIO_PORTF_DEN_R |= 0x11;
						//unlock port f
	GPIO_PORTF_PUR_R |=0X11;														//pull up resistor for negative logic
		
}


// You can't use this timer, it is here for starter code only 
// you must use interrupts to perform delays
/*void Delay100ms(uint32_t count){uint32_t volatile time;
  while(count>0){
    time = 727240;  // 0.1sec at 80 MHz
    while(time){
	  	time--;
    }
    count--;
  }
}*/
