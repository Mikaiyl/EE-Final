#include <hidef.h>      /* common defines and macros */
#include <mc9s12dp256.h>     /* registers & ports definitions */
#pragma LINK_INFO DERIVATIVE "mc9s12dp256b"
#include "funkyfunctions.h"
#include <stdio.h> 



/***********************
 *  Global Variables    *
 ************************/
long int absoluteTime=0;
int bogusISRFlag= 0;

/***********************
 *  Interrupting cows   *
 ************************/

interrupt void RTI_ISR(void) {
    absoluteTime++;  
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
uint scaleV(uint input);
int freak(char i);

/***********************
 *  We arrive in Maine  *
 ************************/

void main(){
    int checkHigh, checkLow; // checking for highs
    char chump[33];          // buffer char
    initAll();
        while(1){
            if(ATD0STAT0);      // wait for conversion
            (void)sprintf(chump,"%4d  mV \n P%d    F%d", scaleV((uint)ATD0DR2),checkLow,freak(ATD0DR2));
                LCDshark(chump);
                
                if(checkHigh < ATD0DR2) checkHigh = ATD0DR2 ;
                    if(checkLow > ATD0DR2) checkLow = ATD0DR2;
        }
    
}

/***********************
 *  Function definitions*
 ************************/
int freak(char i){ // this is a freaky frequency
    int r;
        r = 255000 / i;
        return r;
}
void initAll(void){
    ATDinit();
        LCDinit();
        RTIInit(0x13);
        
}

uint scaleV(uint input){
    ulong limitH = 4300 ,limitL = 0;
        ulong max = 25300 ,min = 0;
        return (((input - min) * limitH) / (max - min)) + limitL;
} 




