#include <hidef.h>      /* common defines and macros */
#include <mc9s12dp256.h>     /* registers & ports definitions */
#pragma LINK_INFO DERIVATIVE "mc9s12dp256b"
#include "funkyfunctions.h"
#include <stdio.h> 



/***********************
*  Global Variables    *
************************/
long int absoluteTime=0; // I'M A WORLDIE BUT I GET NO RESPECT
int bogusISRFlag= 0;
/***********************
*  Interrupting cows   *
************************/

interrupt void RTI_ISR(void) {
      absoluteTime++;  // INCREMENT DAMNIT!
      if(!(PTH & 0x40)){
         if(absoluteTime % (1000 / (PTH & 0x07)) == 0) PTT ^= 0x20;
      }
      CRGFLG = 0x80;
  }

interrupt void UnimplementedISR(void) 
  {  // handle bogus interrupts
      bogusISRFlag=1; 
  }

typedef void (*near tIsrFunc)(void); // tIsrFunc is a pointer to a function
const tIsrFunc _vect[] @0x3E70 = 
{   // table in RAM at 0x3E70 
    /*  Top 8 vectors of Interrupt table @0xFFF0 in Flash, but DBug12  redirects them to shadow in RAM @ 0x3E70 thru 0x3E7F */
        RTI_ISR,             /* vector 07: RTI */
        UnimplementedISR,    /* vector 06: IRQ */
        UnimplementedISR,    /* vector 05: XIRQ */
        UnimplementedISR,    /* vector 04: SWI */
        UnimplementedISR,    /* vector 03: unimplemented opcode trap*/
        UnimplementedISR,    /* vector 02: COP */
        UnimplementedISR,    /* vector 01: Clock monitor fail */
        UnimplementedISR		 /* Reset vector */
 };

/***********************
*  Function Prototypes *
************************/
void initAll(void); 

/***********************
*  We arrive in Maine  *
************************/

void main(){
    unsigned char seg7[] ={0x3f, 0x06,0x5b,0x4f,0x66, 
  0x6d,0x7d,0x07,0x7f,0x6f, 0x77,0x7c,0x39,0x5e,0x79,0x71}; //Array of Hex table

    initAll(); // DO EVERYTHING NOW
    while(1){ // this could go on f0r3v3r
       lights(PTH & 0x07 );
       LED7();
    }

}

/***********************
*  Function definitions*
************************/

void initAll(void){
    RTIInit(0x14);  // INTIALIZE RTI
    DDRH=0;
    DDRT=0x20;  // SET RELAVENT DDRs
    DDRB=0xff;
    DDRP = 0xFF;        //PORTP output
    DDRJ = 0xFF;    //PTJ  out
    PTJ=0x0;      
    EnableInterrupts;      // <=== WHAT  HE SAID
}




