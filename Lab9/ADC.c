// ADC.c
// Runs on LM4F120/TM4C123
// Provide functions that initialize ADC0
// Last Modified: 11/14/2018
// Student names: change this to your names or look very silly
// Last modification date: change this to the last modification date or look very silly

#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"

// ADC initialization function 
// Input: none
// Output: none
void ADC_Init(void){
 // --UUU-- Complete this(copy from Lab8)
		volatile int delay;
	SYSCTL_RCGCGPIO_R |= 0X08;												//activate clock for port d
	
	while((SYSCTL_PRGPIO_R&0X08)==0){};
	GPIO_PORTD_DIR_R &= ~0X04;												//make pd2 an input
	GPIO_PORTD_AFSEL_R |= 0X04;												//enable alt func on pd2
	GPIO_PORTD_DEN_R &= ~0X04;												//disable digital i/o
	GPIO_PORTD_AMSEL_R |= 0X04;												//enable analog func
	SYSCTL_RCGCADC_R |=0X01;													//activate ADC0
	delay=SYSCTL_RCGCADC_R;														//stablizie
	delay=SYSCTL_RCGCADC_R;
	delay=SYSCTL_RCGCADC_R;
	delay=SYSCTL_RCGCADC_R;
	ADC0_PC_R=0X01;																		//configure for 125k sampling rate
	ADC0_SSPRI_R=0X123;																// seq3 is highest priority 
	ADC0_ACTSS_R &= ~0X0008;													//disable sample sequencer 3
	ADC0_EMUX_R &= ~0XF000;														// sq3 is softare trigger
	ADC0_SSMUX3_R = (ADC0_SSMUX3_R&0XFFFFFFF0)+5;			//AIN5
	ADC0_SSCTL3_R= 0X0006;														//no TS0 D0, yes IE0 END0
	ADC0_IM_R &= ~0X0008;															//disable SS3 interrupts
	ADC0_ACTSS_R |= 0X0008;														//enable sample sequencer 3
}

//------------ADC_In------------
// Busy-wait Analog to digital conversion
// Input: none
// Output: 12-bit result of ADC conversion
uint32_t ADC_In(void){  
	uint32_t data;
		GPIO_PORTF_DATA_R ^= 0X08;
	ADC0_PSSI_R = 0X0008;																//start sample capture

	while((ADC0_RIS_R&0X08)==0){};
	data = ADC0_SSFIFO3_R&0XFFF;												//read sample and set data
	ADC0_SAC_R = 0x06;              										//2^{n-1} hardware averaging
	ADC0_ISC_R = 0X0008;																//clears flag
	return data;
}


