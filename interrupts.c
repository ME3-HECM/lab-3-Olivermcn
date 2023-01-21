#include <xc.h>
#include "interrupts.h"

/************************************
 * Function to turn on interrupts and set if priority is used
 * Note you also need to enable peripheral interrupts in the INTCON register to use CM1IE.
************************************/
void Interrupts_init(void)
{
	PIE0bits.INT0IE=1; 	//enable interrupt source INT0
    INTCONbits.GIE=1; 	//turn on interrupts globally (when this is off, all interrupts are deactivated) 
	// It's a good idea to turn on global interrupts last, once all other interrupt configuration is done.
}

/************************************
 * High priority interrupt service routine
 * Make sure all enabled interrupts are checked and flags cleared
************************************/
void __interrupt(high_priority) HighISR()
{
    if(PIR0bits.INT0IF){ 		//check the interrupt source
	// setup pin for output (connected to LED)
    LATHbits.LATH3=0;   //set initial output state
    TRISHbits.TRISH3=0; //set TRIS value for pin (output);
    LATHbits.LATH3 = !LATHbits.LATH3; //toggle LED
	PIR0bits.INT0IF=0; 						//clear the interrupt flag!
	}
	//add your ISR code here i.e. check the flag, do something (i.e. toggle an LED), clear the flag...
}

