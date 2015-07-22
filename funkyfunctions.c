#include <hidef.h>      /* common defines and macros */
#include <mc9s12dp256.h>     /* registers & ports definitions */

/*****************************
*
******************************/
void delayms(unsigned int n){ // delay loop 
    unsigned long delay;    // Long is better than int because int fills up faster                
     delay = 0x000000FF * n ;// multiply by input 
     while(delay--);         // count down
  }
void delayus(unsigned int n)
  {  unsigned int delay;                    

     delay = 0x0005 * n ; 
     while(delay--);
  }
/*****************************
*
******************************/
void LCDcmd(char c) { //send cmd byte c to LCD control reg
  char lownib = (0x0f & c) <<2; //shift into bits 2:5)
  char hinib = (0xf0 & c) >>2;  //shift into bits 2:5)
 
  PORTK = hinib; 		//Set up data while EN=0
  PORTK = 0x02 | hinib; 	//turn on EN bit, with RS=0
  PORTK = hinib;      	//turn off EN bit
  
  PORTK = lownib; 		//Set up data while EN=0
  PORTK = 0x02 | lownib; //turn on EN bit
  PORTK = lownib;      	//turn off EN bit
 
  delayus(1800);    //wait for command completion
  }
 
void LCDchar(char c) { //send cmd byte c to LCD control reg
  char lownib = ((0x0f & c) <<2); //shift into bits 2:5) 
  char hinib = ((0xf0 & c) >>2);  //shift into bits 2:5)
 
  PORTK = hinib  ; 		//Set up data while EN=0
  PORTK = 0x02 | hinib | 0x01; 	//turn on EN bit, with RS=01
  PORTK = hinib;      	//turn off EN bit
  
  PORTK = lownib; 		//Set up data while EN=0
  PORTK = 0x02 | lownib | 0x01; //turn on EN bit with RS=1
  PORTK = lownib;      	//turn off EN bit
 
  delayus(51);    //wait for command completion
  }
void LCDinit(void) {   

  const int INITLENGTH = 6;//initialize LCD controller on PORTK
                         // send this sequence of bytes to control reg
  char initseq[] = { 0x33, 0x32,0x28,0x06,0x01}; 	// 0x0F=cursor on,blink;  0x01=Clear
  int i=0; 
  DDRK = 0xFF; // enable Port K to send the stuff
    for (i=0; i<INITLENGTH; i++){  // send each char to LCD 
    
      LCDcmd(initseq[i]);  // iterate and execute each commnd
     delayms(5);
    }
  }		


void LCDshark(char i[]){  // iterate through array of chars and send to LCD

    int count = 0;       // count iterations
    LCDcmd(0x02);
  
    for(;i[count]!='\0';){ // loop through each char
        
        LCDchar(i[count++]);     // from var to LCD print function
        if(i[count]=='\n'){
		    LCDcmd(0xc0);   // skip to second line
	      count++;
	      }
    } 
} 
/**************************************
* ATD Functions
***************************************/ 
 void ATDinit(void) 
{
  ATD0CTL2 |= 0x80;//ADPU=1
  delayms(10); //wait 10 us for power-up
  ATD0CTL3 = 0; 
  ATD0CTL4 = 0x00;//set SRES8=0 10bit conversion
  ATD0CTL5 = 0x30;//pin 0 start,SCAN=1,MULT=1
 }
/*****************************
* RTI functions
******************************/
void RTIInit(unsigned char rtictlvalue) {
  /* setup RTI interrupt frequency & enable RTI interrupts, assuming 4MHz xtal */
  /* clock divider set in RTICTL reg, and is (N+1)*2^(M+9), where N=bits(3:0), M=bits(6:4).
    But M=0 disables divider.
    f= 4MHz / ((n+1)*2^(M+9)).  
    Useful values:  0x10 = 4kHz, 0x11 = 2kHz, 0x12 = 1.33kHz, 0x13 = 1kHz
   */  
   if (!rtictlvalue) //if zero, set to default
		RTICTL =0x10;
	else
		RTICTL = rtictlvalue; /*set RTI prescaler */ 
    CRGINT = 0b10000000; /* enable RTI interrupts */ 
}

/*****************************
*   Scalers
******************************/


 
uchar scaleL(uchar L){
     uchar i;
     i = 255 * (((-55 + ( L < 55 ? 55 : L > 198 ? 198 : L))*100)/143);
     return (unsigned char)i;
}
/*****************************
*   Random Shit
******************************/
void lights(char c){
     PTP = 0x0f;
     PTJ=0;
     PORTB = c;
     delayms(1); 
}
void Welcome (void){
     int i;
     LCDshark(" Light Teramin \n Project 2015 ");
         
     for(i=0;i<10;i++){
      
     PORTB=0x55;
     delayms(50);
     PORTB=0xAA;
     delayms(50);  
     }
     EnableInterrupts;
}

/***************************
*   LEDS  7SEG I HATE MULTIPLEXING
****************************/
void LED7(void){    
unsigned char seg7[] ={0x3f, 0x06,0x5b,0x4f,0x66, 
  0x6d,0x7d,0x07,0x7f,0x6f, 0x77,0x7c,0x39,0x5e,0x79,0x71}; //Array of Hex table
        PTJ = 0x02;
        PORTB = seg7[PTH & 0x07];   // 
        PTP = 0x0D;
        delayms(1);
        PORTB = 0x76;
        PTP = 0x0B;
        delayms(1);
        PORTB = 0x5B;      
        PTP = 0x07; 
        delayms(1);       
}
