; Print.s
; Student names: change this to your names or look very silly
; Last modification date: change this to the last modification date or look very silly
; Runs on LM4F120 or TM4C123
; EE319K lab 7 device driver for any LCD
;
; As part of Lab 7, students need to implement these LCD_OutDec and LCD_OutFix
; This driver assumes two low-level LCD functions
; ST7735_OutChar   outputs a single 8-bit ASCII character
; ST7735_OutString outputs a null-terminated string 

    IMPORT   ST7735_OutChar
    IMPORT   ST7735_OutString
    EXPORT   LCD_OutDec
    EXPORT   LCD_OutFix

    AREA    |.text|, CODE, READONLY, ALIGN=2
    THUMB

  

;-----------------------LCD_OutDec-----------------------
; Output a 32-bit number in unsigned decimal format
; Input: R0 (call by value) 32-bit unsigned number
; Output: none
; Invariables: This function must not permanently modify registers R4 to R11
num EQU 0
Res EQU 4
LCD_OutDec
    ; copy/paste Lab 7 solution here
		PUSH{R0,LR}
	SUB SP, #8						;Set up stack for num and res
	STR R0,[SP,#num]
	
	CMP R0,#10						;Compare the input with 10
	BHS skipper						;If greater than 10 then don't print
	ADD R0,#0X30
	BL ST7735_OutChar				;Print number that is less than 10
	B leave
skipper	MOV R3,#10
    UDIV R0,R0,R3					;R0 gets the quotient
	;MOV R3,#10
	LDR R2,[SP,#num]				;R2 gets the original number
	STR R0,[SP,#num]				;Store the quotient
	;UDIV R0,R2,R3				
	BL Rem							
	STR R0, [SP,#Res]				;Store the remainder in Res stack
	LDR R0,[SP,#num]				;R0 gets the quotient
	BL LCD_OutDec					;Recursion
	LDR R0,[SP,#Res]
	ADD R0,#0X30
	BL ST7735_OutChar				;Print out all numbers after recursive calls
leave ADD SP,#8
	POP{R0,LR}
      BX  LR
	  
Rem
	MUL R0, R0,R3					;Multiply quotient and divisor
	SUB R0,R2,R0					;Subtract dividend by the product to find remainder
	BX LR

;* * * * * * * * End of LCD_OutDec * * * * * * * *

; -----------------------LCD _OutFix----------------------
; Output characters to LCD display in fixed-point format
; unsigned decimal, resolution 0.001, range 0.000 to 9.999
; Inputs:  R0 is an unsigned 32-bit number
; Outputs: none
; E.g., R0=0,    then output "0.000 "
;       R0=3,    then output "0.003 "
;       R0=89,   then output "0.089 "
;       R0=123,  then output "0.123 "
;       R0=9999, then output "9.999 "
;       R0>9999, then output "*.*** "
; Invariables: This function must not permanently modify registers R4 to R11
LCD_OutFix
    ; copy/paste Lab 7 solution here
	PUSH{R0,LR}
	
	SUB SP, #8						;Set up stack pointer
	STR R0,[SP, #Res]
	
	
	
	LDR R0, [SP,#Res]
	MOV R3, #9999
	CMP R0, R3						;Compare the input to see if its too big
	BHI tooBig
	MOV R3,#1000
	UDIV R0,R0,R3					;R0 gets the quotient
	STR R0, [SP,#num]				;Store the quotient for 1000 into num
	ADD R0,#0X30
	BL ST7735_OutChar				;print out quotient
	MOV R0, #0X2E
	BL ST7735_OutChar				;print out period
	LDR R0,[SP,#num]
	LDR R2, [SP,#Res]
	MOV R3,#1000
	BL Rem							;R0 has remainder
	
	MOV R3,#100
	STR R0, [SP,#Res]				;Remainder is stored in Res
	UDIV R0,R0, R3
	STR R0, [SP,#num]				;quotient for 100 is stored in num
	ADD R0,#0X30
	BL  ST7735_OutChar				;print out quotient
	LDR R0,[SP,#num]	
	LDR R2, [SP,#Res]				;R2 gets the previous quotient
	MOV R3,#100
	BL Rem
	
	MOV R3,#10
	STR R0, [SP,#Res]
	UDIV R0,R0, R3					;R0 gets the quotient when divided by 10
	STR R0, [SP,#num]
	ADD R0,#0X30
	BL  ST7735_OutChar				;print out the quotient
	LDR R0,[SP,#num]
	LDR R2, [SP,#Res]
	MOV R3,#10
	BL Rem							;find the remainder
	ADD R0,#0X30	
	BL  ST7735_OutChar				;print out the remainder
	B escape
tooBig	
	MOV R0, #0X2A					;print out the stars if greater than 9999
	BL  ST7735_OutChar
	MOV R0, #0X2E
	BL  ST7735_OutChar
	MOV R0, #0X2A
	BL  ST7735_OutChar
	MOV R0, #0X2A
	BL  ST7735_OutChar 
	MOV R0, #0X2A
	BL  ST7735_OutChar 
	
escape LDR R0, [SP,#num]
	ADD SP,#8
	POP{R0,LR}
     BX   LR
 
     
;* * * * * * * * End of LCD_OutFix * * * * * * * *

     ALIGN                           ; make sure the end of this section is aligned
     END                             ; end of file
