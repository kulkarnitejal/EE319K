// Uart.c
// Runs on LM4F120/TM4C123
// Use UART1 to implement bidirectional data transfer to and from 
// another microcontroller in Lab 9.  This time, interrupts and FIFOs
// are used.
// Daniel Valvano
// November 14, 2018
// Modified by EE345L students Charlie Gough && Matt Hawk
// Modified by EE345M students Agustinus Darmawan && Mingjie Qiu

/* Lab solution, Do not post
 http://users.ece.utexas.edu/~valvano/
*/

// This U0Rx PC4 (in) is connected to other LaunchPad PC5 (out)
// This U0Tx PC5 (out) is connected to other LaunchPad PC4 (in)
// This ground is connected to other LaunchPad ground

#include <stdint.h>
#include "Fifo.h"
#include "Uart.h"
#include "../inc/tm4c123gh6pm.h"
#define PF3       (*((volatile uint32_t *)0x40025020))
uint32_t DataLost; 
// Initialize UART1
// Baud rate is 115200 bits/sec
// Make sure to turn ON UART1 Receiver Interrupt (Interrupt 6 in NVIC)
// Write UART1_Handler
void Uart_Init(void){
   // --UUU-- complete with your code
		Fifo_Init();
		SYSCTL_RCGCUART_R |= 0X002;																							//activate UART 1
		SYSCTL_RCGCGPIO_R |= 0X004;																							//activate Port C
	
		UART1_CTL_R &= ~0X0001;																									//disable UART
		UART1_IBRD_R = 43;																											//80MHZ
		UART1_FBRD_R = 26;
		UART1_LCRH_R = 0X0070;																									//enable FIFO
		UART1_CTL_R = 0X0301;																										//enable RXE, TXE, UART
		GPIO_PORTC_AFSEL_R |= 0X30;																							//alt functions
		GPIO_PORTC_PCTL_R = (GPIO_PORTC_PCTL_R & 0XFF00FFFF) + 0X001100000;			//chooses one specific alt func
		GPIO_PORTC_DEN_R |= 0X30;																								//PortC 4/5 output
		GPIO_PORTC_AMSEL_R &= ~0X30;																						//No analog
}

// input ASCII character from UART
// spin if RxFifo is empty
// Receiver is interrupt driven
char Uart_InChar(void){
  while((UART0_FR_R&0x0010) != 0); // wait until RXFE is 0
	return((char)(UART0_DR_R&0xFF));
}

//------------UART1_InMessage------------
// Accepts ASCII characters from the serial port
//    and adds them to a string until ETX is typed
//    or until max length of the string is reached.
// Input: pointer to empty buffer of 8 characters
// Output: Null terminated string
// THIS FUNCTION IS OPTIONAL
void UART1_InMessage(char *bufPt){
	int i=0;
	while(Uart_InChar()!=0x03||i<8)
	{
		*bufPt=Uart_InChar();
		bufPt++;
		i++;
	}

}

//------------UART1_OutChar------------
// Output 8-bit to serial port
// Input: letter is an 8-bit ASCII character to be transferred
// Output: none
// Transmitter is busywait
void Uart_OutChar(char data){
  // --UUU-- complete with your code
	
	while((UART1_FR_R&0x0020) !=0) {};
	UART1_DR_R = data;
		
}

// hardware RX FIFO goes from 7 to 8 or more items
// UART receiver Interrupt is triggered; This is the ISR
void UART1_Handler(void){
  // --UUU-- complete with your code
	char *data;
	int RxCounter=0;
	PF3 ^= 0x08;
	
	while((UART1_FR_R&UART_FR_RXFE) == 0)
	{
		*data = UART1_DR_R;
		Fifo_Put(*data);
	}
	RxCounter++;
	UART1_ICR_R = 0x10;   // this clears bit 4 (RXRIS) in the RIS register
	PF3 ^=0x08;
	
	
}
