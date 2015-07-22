#ifndef _FUNCTIONS_HCS12
	#define _FUNCTIONS_HCS12 
	
	
		extern void delayms(unsigned int n);
		extern void delayus(unsigned int n);
		
		extern void LCDcmd(char c);
		extern void LCDinit(void);
		extern void LCDchar(char c);
		extern void LCDshark(char i[]);
  
  	extern void RTIInit (unsigned char rtictlvalue); 
		
		extern void ATDinit(void);

    extern int scaleL(unsigned char );
    
#endif