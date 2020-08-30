Udemy Course:

1. Robot - ARM cortex M


6/21/2020

->Modular Design:
	
	Complex task --- "break into smaller task"

	Modules coupling
	call graph
	data flow

***********Drawing a call-graph**********************

	Software Module (.c , .h files and.s files)
	
->Central Module
	-> Ultrasonic ------ hw Ultrasound sensor
	-> Timer      ------ hw GPTM
	-> PWM        ------ hw Servo Motor
	-> Motor      ------ hw DC Motor
	-> Light      ------ hw LED
	-> IR         ------ hw IR Pair

***********Data flow graph***************************


Distance - Head -> Untrasonic -> Central
	   Neck <- PWM <- Central
	Limbs <- Motor <- Central
	      <- Light <- Central
	Tail -> IR -> Central

		IR <- Timer 2A 100Hz


**************Flow chart**************************

Foreground thread and background thread

Forground thread:

main
Intialize module
Enable interrupt
Run robit behaviour

Background thread:

_________________________________________________________________

Cortex-M Assembly primer

Assembly Language Syntax

	Label opcode operand; comment
ex  Init  Mov    RO,#150; R=150

    Label  : optional, used to find the position of current instruction
	opcode : specifies processor operation to perform
	operand: source/destination of data to be processed by opcode
	Comment: optional
	
Directives -> they are not instructions
	
	Type Instruction 
	Thumb -
	Thumb2
	
	Thumb 
	DATA
	CODE
	AREA
	SPACE
	ALIGN
	Export
	GLOBAL
	IMPORT
	END
	DCB
	DCW
	DCD
	EQU -> directive used to give symbolic name
	.text 
	
Tiva C Launchpad TMC4c123GXL 
Processor: CortexM4
Flash    : 256k
Speed    : up to 80MHz

Source Code

	opcode:
		1. MOV 
				Move data within processor without accessing memory
				
			ex. MOV R0,#150
				MOV R1,R3
				
		2. LDR Load Register
					Loads a register with either 32 bit constant or another
					register
			ex. LDR R0,=0xFFFF
				LDR R1,[R2]
		
		3. STR Stores a register value into memory
		
			ex. STR R0,[R1]
			
		4. B Branch to a Location
			
			B loop
			
		5. BL Branch to Subroutine
		
			BL turn_On
			
		6. BX LR Return from Subroutine call
			
			MOV R2,#0x01
			BX  LR
		
		7. NOP No operation
		
			STR R0,[R1]
			NOP
			NOP

uVision 

	Create a Project
	choose uC going to use
	
	CMSIS
	startup
	
	setup conditions
		target options
		freq 16MHz
		select Debugger
	
	New file
	.s extentio for assembly code
	
	user guide to refer pin 
	
	LED connected to PF1
	
	initilize i/o
	
	clk setting
	direction
	Enable

SYSCTL_RCGCGPIO_R EQU 0x400FE608
GPIO_PORTF_DIR_R  EQU 0x40025400
GPIO_PORTF_DEN_R  EQU 0x4002531C
GPIOF_DATA_R      EQU 0x400253FC
		
		AREA	|.text|,CODE,READONLY,ALIGN=2
		THUMB
		EXPORT Main
	
	Main
		    BL    GPIOF_Init ;it should run once

	loop	BL    LIGHT_ON
			B     loop   
	
	GPIOF_Init ;init subroutine
		LDR R1, =SYSCTL_RCGCGPIO_R ; SYSCTL_RCGCGPIO_R ->symbolic name
		LDR R0,[R1]
		ORR R0,R0,#0x20
		STR R0,[R1]
		
		LDR R1, =GPIO_PORTF_DIR_R
		MOV R0,#0x02
		STR R0,[R1]
		
		LDR R1, =GPIO_PORTF_DEN_R
		MOV R0, #0x02 
		STR R0,[R1]
		
		BX LR ; return from subroutine
		
	LIGHT_ON ;write data register
		LDR R1, =GPIOF_DATA_R
		MOV R0, #0x02
		STR R0,[R1]
		BX LR
		
		ALIGN
		END
		
Inform reset handler after reset start main
find reset in startup code
change the IMPORT 
LDR R0, MAIN ; by default LDR R0, _main

Embedded C primer

	Create a new project
	
	int main()
	{
		int counter = 0;
		++counter;
		++counter;
	}
	
	First look at debug
	
CMSIS
	CMSIS compliance project
	
	
	add device header file


main.c
	
	#include "TM4c123.h" //device header
	#include "delay.h"
	

	
	int main()
	{
		uint32_t sw_state;
		PortF_INIT();
		
		while(1)
		{
			sw_state = SW_INPUT();
		
			switch(sw_state)
			{
				case sw1:
				LED_ON(GREEN);
				break;
				
				case sw2:
				LED_ON(BLUE);
				break;
				
			}
		
		}
	}
	




delay.h

	#ifndef __DELAY_H__
	#define __DELAY_H__
	
	void delay(int time);
	
	#endif
	
delay.c

	#include "delay.h"
	
	void delay(int time)
	{
		int volatile delay;
		delay = 0;
		while(delay<time)
		{
		++delay;
		}
	}
	
io.c
    #include "TM4C123.H"
	#include "delay.h"
	#include "stdint"
	#include "io.h"
	
	void LED_ON(uint32_t LED)
	{
		GPIOF->DATA = LED;
		delay(2000000);
		GPIOF->DATA &= ~LED;
	}
		
	uint32_t SW_INPUT()
	{
		return (GPIOF->DATA &0x11); //0B 0001 0001
	}
	
	void PortF_INIT()
	{
		//intialize port
		SYSCTL->RCGCGPIO |= (1U<<5);
		
		GPIO->LOCK = KEY;
		GPIOF->CR = 0xFF;
		GPIOF-DIR |= (BLUE | GREEN | RED);		// 1 for output, o for input
		GPIO->PUR |=(SW1 | SW2);
		GPIOF->DEN |= (BLUE | GREEN | RED | SW1 | SW2);	
	}
		
io.h

	#ifndef __IO_H__
	#define __IO_H__
	
	#define BLUE (1U<<2)
	#define GREEN (1U<<3)
    #define RED (1U<<1)

	#define SW1 (1U<<2)
	#define SW2 (1U<<2)
	#define SW1_ 0x10
	#define SW2_ 0x01
	
	#define KEY 0x4C4F434B //lock register write to unlock
	
	uint32_t SW_INPUT();
	void LED_ON(uint32_t LED);
	void PortF_INIT();
	
	#endif		