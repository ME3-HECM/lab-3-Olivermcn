#include <xc.h>
#include "LEDarray.h"

/************************************
/ LEDarray_init
/ Function used to initialise pins to drive the LEDarray
************************************/
void LEDarray_init(void)
{
    //set up TRIS registers for pins connected to LED array
    TRISGbits.TRISG0 = 0;
    TRISGbits.TRISG1 = 0;
    TRISAbits.TRISA2 = 0;
    TRISFbits.TRISF6 = 0;
    TRISAbits.TRISA4 = 0;
    TRISAbits.TRISA5 = 0;
    TRISFbits.TRISF0 = 0;
    TRISBbits.TRISB0 = 0;
    TRISBbits.TRISB1 = 0;
    TRISCbits.TRISC6 = 0;
    //set initial output LAT values (they may have random values when powered on)
    LATGbits.LATG0 = 0;
    LATGbits.LATG1 = 0;
    LATAbits.LATA2 = 0;
    LATFbits.LATF6 = 0;
    LATAbits.LATA4 = 0;
    LATAbits.LATA5 = 0;
    LATFbits.LATF0 = 0;
    LATBbits.LATB0 = 0;
    LATBbits.LATB1 = 0;
    LATCbits.LATC6 = 0;
    
    // setup pin for input (connected to button)
    TRISFbits.TRISF2=1; //set TRIS value for pin (input)
    ANSELFbits.ANSELF2=0; //turn off analogue input on pin 
    
}

/************************************
/ LEDarray_disp_bin
/ Function used to display a number on the LED array in binary
************************************/
void LEDarray_disp_bin(unsigned int number)
{
	//some code to turn on/off the pins connected to the LED array
  if (number & 0b000000001) //1
  {LATGbits.LATG0 = 1;}
  else 
  {LATGbits.LATG0 = 0;}
  
  if (number & 0b000000010) //2
  {LATGbits.LATG1 = 1;}
  else 
  {LATGbits.LATG1 = 0;}
  
  if (number & 0b000000100) //3
  {LATAbits.LATA2 = 1;}
  else 
  {LATAbits.LATA2 = 0;}
  if (number & 0b000001000) //4
  {LATFbits.LATF6 = 1;}
  else 
  {LATFbits.LATF6 = 0;}

  if (number & 0b000010000) //5
  {LATAbits.LATA4 = 1;}
  else 
  {LATAbits.LATA4 = 0;}
  
  if (number & 0b000100000) //6
  {LATAbits.LATA5 = 1;}
  else 
  {LATAbits.LATA5 = 0;}
  
  if (number & 0b001000000) //7
  {LATFbits.LATF0 = 1;}
  else 
  {LATFbits.LATF0 = 0;}
  if (number & 0b010000000) //8
  {LATBbits.LATB0 = 1;}
  else 
  {LATBbits.LATB0 = 0;}
  
  if (number & 0b100000000) //9
  {LATBbits.LATB1 = 1;}
  else 
  {LATBbits.LATB1 = 0;}
  
  
    //if statements and bit masks can be used to determine if a particular pin should be on/off
	
	//see Readme.md for examples
  
}

/************************************
/ Function LEDarray_disp_dec
/ Used to display a number on the LEDs
/ where each LED is a value of 10
************************************/
void LEDarray_disp_dec(unsigned int number)
{
  unsigned int disp_val;
  if (number >= 19) //19 slightly higher value so a return of lowest LDR value should be expected
  {disp_val = 0b000000001;}
  if (number >= 29) //20
  {disp_val = 0b000000010;}
  if (number >=30) //30
  {disp_val = 0b000000100;}
  if (number >=40) //40
  {disp_val = 0b000001000;}
  if (number >=50) //50
  {disp_val = 0b000010000;}
  if (number >=60) //60
  {disp_val = 0b000100000;}
  if (number >=70) //70
  {disp_val = 0b001000000;}
  if (number >=80) //80
  {disp_val = 0b010000000;}
  if (number >=90) //90
  {disp_val = 0b100000000;}
 
 
  
	
	//some code to manipulate the variable number into the correct
	//format and store in disp_val for display on the LED array

	 	//display value on LED array
      LEDarray_disp_bin(disp_val);
}
void LEDarray_disp_upto(unsigned int number)//function to display all LED's up to that number
{
  unsigned int disp_val;
  if (number >= 19) //19 slightly higher value so a return of lowest LDR value should be expected
  {disp_val = 0b000000001;}
  if (number >= 29) //20
  {disp_val = 0b000000011;}
  if (number >=30) //30
  {disp_val = 0b000000111;}
  if (number >=40) //40
  {disp_val = 0b000001111;}
  if (number >=50) //50
  {disp_val = 0b000011111;}
  if (number >=60) //60
  {disp_val = 0b000111111;}
  if (number >=70) //70
  {disp_val = 0b001111111;}
  if (number >=80) //80
  {disp_val = 0b011111111;}
  if (number >=90) //90
  {disp_val = 0b111111111;}
  LEDarray_disp_bin(disp_val);//display value on LED array
 
}

/************************************
/ LEDarray_disp_PPM
/ Function used to display a level on the LED array with peak hold
/ cur_val is the current level from the most recent sample, and max is the peak value for the last second
/ these input values need to calculated else where in your code
************************************/

void LEDarray_disp_PPM(unsigned int cur_val, unsigned int max)
{
	unsigned int disp_val;
    unsigned int max_bin;
    unsigned int cur_bin;
//figuring out the led output for the peak value 
  if (cur_val >= 13) //16 slightly higher value so a return of lowest LDR value should be expected
  {cur_bin = 0b000000001;}
  if (cur_val >= 20) //20
  {cur_bin = 0b000000010;}
  if (cur_val >=31) //30
  {cur_bin = 0b000000100;}
  if (cur_val >=40) //40
  {cur_bin = 0b000001000;}
  if (cur_val >=50) //50
  {cur_bin = 0b000010000;}
  if (cur_val >=60) //60
  {cur_bin = 0b000100000;}
  if (cur_val >=70) //70
  {cur_bin = 0b001000000;}
  if (cur_val >=80) //80
  {cur_bin = 0b010000000;}
  if (cur_val >=90) //90
  {cur_bin = 0b100000000;}

//figuring out the led output for the max    
  if (max >= 13) //19 slightly higher value so a return of lowest LDR value should be expected
  {max_bin = 0b000000001;}
  if (max >= 20) //20
  {max_bin = 0b000000011;}
  if (max >=31) //30
  {max_bin = 0b000000111;}
  if (max >=40) //40
  {max_bin = 0b000001111;}
  if (max >=50) //50
  {max_bin = 0b000011111;}
  if (max >=60) //60
  {max_bin = 0b000111111;}
  if (max >=70) //70
  {max_bin = 0b001111111;}
  if (max >=80) //80
  {max_bin = 0b011111111;}
  if (max >=90) //90
  {max_bin = 0b111111111;}
	// some code to format the variable cur_val and max, store in disp_val for display on the LED array
	// hint: one method is to manipulate the variables separately and then combine them using the bitwise OR operator
    disp_val = cur_bin | max_bin; //put both values together
	LEDarray_disp_bin(disp_val);	//display value on LED array 
}

