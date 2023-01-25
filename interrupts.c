#include <xc.h>
#include "interrupts.h"

/************************************
 * Function to turn on interrupts and set if priority is used
 * Note you also need to enable peripheral interrupts in the INTCON register to use CM1IE.
************************************/
void Interrupts_init(void)
{
    //comparator 1 interrupt enable bit, enables comparator bit
	PIE2bits.C1IE=1; 	//E at the end means enable
    IPR2bits.C1IP = 1; //set priority for main
    
    //set up LED for output 
    LATHbits.LATH3 = 0;//set initial output space 
    TRISHbits.TRISH3=0; //set TRIS value for pin (output)
    
    INTCONbits.GIE=1; 	//turn on interrupts globally (when this is off, all interrupts are deactivated) 
    INTCONbits.PEIE = 1;//enable peripheral interrupts
	// It's a good idea to turn on global interrupts last, once all other interrupt configuration is done.
}

/************************************
 * High priority interrupt service routine
 * Make sure all enabled interrupts are checked and flags cleared
************************************/
void __interrupt(high_priority) HighISR()
{
    if(PIR2bits.C1IF){ 		//check the interrupt source
    LATHbits.LATH3 = !LATHbits.LATH3; //toggle LED
	PIR2bits.C1IF = 0; 						//clear the interrupt flag!
	}
	//add your ISR code here i.e. check the flag, do something (i.e. toggle an LED), clear the flag...
}

