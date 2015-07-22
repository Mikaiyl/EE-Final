// File = 222defs.h
//   Handy macros for ECT 222 HCS12 labs
//   M.D. Atkins
//   7/23/07
#define B0 0b00000001
#define B1 0b00000010
#define B2 0b00000100
#define B3 0b00001000
#define B4 0b00010000
#define B5 0b00100000
#define B6 0b01000000
#define B7 0b10000000

#define DIPSWITCHES PTH
#define LEDS  PORTB
#define LCD PORTK
#define LEDS7_ENABLE PTP

/* PORTB definitions -- include these only if not including mc9s12dp256.h*/
//#define PORTB    (*((volatile unsigned char*)(0x0001)))     
//#define DDRB     (*((volatile unsigned char*)(0x0003))) 

/* RTI definitions */
//#define CRGINT   (*((volatile unsigned char*)(0x0038))) 
//#define CRGFLG   (*((volatile unsigned char*)(0x0037))) 
//#define RTICTL   (*((volatile unsigned char*)(0x003B))) 
 
/*****************************************************************************/
/*Macro Definitions				from Freescale's projectglobals.h  	 */

#define int_enable()  {asm andcc   #0xEF;}	  //interrupts enabled
#define int_disable() {asm orcc    #0x10;}	  //interrupts disabled
#define wait()        {asm wait;}			  //enter wait mode
#define stop_enable() {asm andcc   #0x7F;}	  //stop mode enabled
#define stop()        {asm stop;}			  //enter stop mode
#define nop()         {asm nop;}			  //enter NOP asm instruction
#define bgnd()        {asm bgnd; asm nop;}	  //enter BGND asm instruction

#define ON 1								  //ON 
#define OFF 0								  //OFF
#define TRUE 1								  //TRUE
#define FALSE 0								  //FALSE	
