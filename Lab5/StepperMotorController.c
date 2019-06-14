// StepperMotorController.c starter file EE319K Lab 5
// Runs on TM4C123
// Finite state machine to operate a stepper motor.  
// Jonathan Valvano
// January 18, 2019

// Hardware connections (External: two input buttons and four outputs to stepper motor)
//  PA5 is Wash input  (1 means pressed, 0 means not pressed)
//  PA4 is Wiper input  (1 means pressed, 0 means not pressed)
//  PE5 is Water pump output (toggle means washing)
//  PE4-0 are stepper motor outputs 
//  PF1 PF2 or PF3 control the LED on Launchpad used as a heartbeat
//  PB6 is LED output (1 activates external LED on protoboard)

#include "SysTick.h"
#include "TExaS.h"
#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"

void EnableInterrupts(void);
// edit the following only if you need to move pins from PA4, PE3-0      
// logic analyzer on the real board
#define PA4       (*((volatile unsigned long *)0x40004040))
#define PE25      (*((volatile unsigned long *)0x400240FC))
#define W1	0
#define W2	1
#define W4	2
#define W8	3
#define W16	4
#define W12	5
#define W22	6
#define W42	7
#define W82	8	
#define W162	9
#define W83	10
#define W43	11
#define W23 12
#define W13 13
#define W163	14
#define W84	15
#define W44	16
#define W24	17

#define C1	18
#define C2	19
#define C4	20
#define C8	21
#define C16	22
#define C12	23
#define C22	24
#define C42	25
#define C82	26
#define C162	27
#define C83	28
#define C43	29
#define C23	30	
#define C13	31
#define C163	32
#define C84	33
#define C44	34	
#define C24	35

struct Wiper{uint8_t output; uint16_t delay; uint8_t next[4];};
struct Wiper FSM[36] = {
		{0x01,	100,	{W1,	W2,	C2,  C2}},					//FSM
		{0x02,	50,		{W4,	W4,	C4,  C4}},
		{0x04,	50,		{W8,	W8,	C8,  C8}},
		{0x08,	50,		{W16,	W16, C16, C16}},
		{0x10,	50,		{W12,	W12, C12,	C12}},
		{0x01,	50,		{W22,	W22, C22,	C22}},
		{0x02,	50,		{W42,	W42, C42,	C42}},
		{0x04,	50,		{W82,	W82, C82,	C82}},
		{0x08,	50,		{W162,	W162, C162, C162}},
		{0x10,	100,	{W83,	W83, C83, C83}},
		{0x08,	50,		{W43,	W43, C43,	C43}},
		{0x04,	50,		{W23,	W23, C23, C23}},
		{0x02,	50,		{W13,	W13, C13,	C13}},
		{0x01,	50,		{W163,	W163, C163, C163}},
		{0x10,  50,		{W84,	W84, C84,	C84}},
		{0x08,	50,		{W44,	W44, C44,	C44}},
		{0x04,  50,		{W24,	W24, C24, C24}},
		{0x02,	50,		{W1,	W1, C1,	C1}},
		{0x21,	100,	{W2,	W2, W2,	W2}},
		{0x22,	50,		{W4,	W4,	W4,	W4}},
		{0x24,	50, 	{W8,	W8, W8,	W8}},
		{0x28,	50,		{W16,	W16, W16,	W16}},
		{0x30,	50,		{W12,	W12, W12,	W12}},
		{0x21,	50,		{W22,	W22, W22,	W22}},
		{0x22,	50,		{W42,	W42, W42,	W42}},
		{0x24,	50,		{W82,	W82, W82,	W82}},
		{0x28,	50,		{W162,	W162,	W162, W162}},
		{0x30,	100,	{W83,	W83, W83,	W83}},
		{0x28,	50,		{W43,	W43, W43,	W43}},
		{0x24,	50,		{W23,	W23, W23,	W23}},
		{0x22,	50,		{W13,	W13, W13,	W23}},
		{0x21,	50,		{W163,	W163, W163,	W163}},
		{0x30,	50,		{W84,	W84, W84,	W84}},
		{0x28,	50,		{W44,	W44, W44,	W44}},
		{0x24,	50,		{W24,	W24, W24,	W24}},
		{0x22,	50,		{W1,	W1, W1, W1}},

	};
	uint8_t cs;															//current state
	uint8_t input;
	uint32_t bit4,bit5;
	volatile int delay;	

void SendDataToLogicAnalyzer(void){
  UART0_DR_R = 0x80|(PA4<<2)|PE25;
}

void toggle(void)
{
		GPIO_PORTE_DATA_R ^= 0X20;
}
int main(void){ 
  TExaS_Init(&SendDataToLogicAnalyzer);   // activate logic analyzer and set system clock to 80 MHz
  SysTick_Init();   
	// you initialize your system here
	
	SYSCTL_RCGCGPIO_R |=  0x33;
	delay+=123456;
																					//intializing port E
	GPIO_PORTE_DIR_R |=0X3F;
	GPIO_PORTE_DEN_R |=0X3F;
																					//intializaing port A
	GPIO_PORTA_DIR_R |=0X0F;
	GPIO_PORTA_DEN_R |=0X30;
																					//intializing port B
	GPIO_PORTB_DIR_R |=0X40;
	GPIO_PORTB_DEN_R |=0X40;
																					//intializing port F
	GPIO_PORTF_DIR_R |=0X04;
	GPIO_PORTF_DEN_R |=0X04;
	
	
	
	cs=W1;
					
	
  EnableInterrupts();   
  while(1){
		
		GPIO_PORTF_DATA_R ^= 0X04;						//heartbeat
// output
		GPIO_PORTE_DATA_R=FSM[cs].output;			//give the stepper motor and the LED the output
// wait	
		SysTick_Wait1ms(FSM[cs].delay);				//dwell time for motor to step
// input				
		bit4=GPIO_PORTA_DATA_R & 0X10;				//isolate bit 4
		bit5=GPIO_PORTA_DATA_R & 0X20;				//isolate bit 5
		bit4=bit4>>4;													//Right shift into LSB
		bit5=bit5>>4;													//Right shift into one before LSB
		input = (bit4|bit5);									//OR the bits together to get the input of 2 bits

// next		
		cs=FSM[cs].next[input];								//current state gets the next state
  }
}


