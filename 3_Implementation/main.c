/**@file main.c
   @mainpage Electronic Walking Stick.
   @brief This is the main page of my project.
  Project includes an electronic walking stick for visually impaired people.
  @bug no bug found
  @author Nidhi Chawla
  
 @brief This code is built in reference with the electronic walking stick. This stick serves the functionality of obstacle detection throgh ultrasonic sensors by measuring the distance between the obstacle and the user and displaying it on the lcd. Additional features have been added for the surrounding people to know about the presence of a visually impaired person near them by mimicing the functionality of an LDR sensor through a LED. Also, a buzzer is included for the user itself to get notified of the obstacle near by.*/
/** @file Headers included are listed
#include <avr/io.h>
#include "MrLCDATmega32.h"
#include <interrupt.h>
#include <unit/delay.h>
#include <stdlib.h>
 @param no parameters are given
	@return no return is expected.
*/

#include <avr/io.h>
#include "MrLCDATmega32.h"
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
/** @brief Declaration of the variables
    The variable ring is used to store the count from a TCNT Register.
    The variable v is used as a flag to show thw current status of the echo pin.
	@param no parameter is passed.
	@return no return is expected.
	*/
static volatile int ring = 0;
static volatile int v = 0;
/**@brief void sensor(void)
    PORTC is accessed to show the functionality of blinking tge led at different frequencies and with different delays in order to make the surrounding people aware of the presence of a avisually impaired person .
	here we have tried to mimic the functionality of an LDR sensor.
   @param int i,j,k
   @return void
   */
void sensor(void)
 {
	int i=0,j=0,k=0;
DDRC= 0xFF;
for (i=0;i<10;i++)
{	
	PORTC = 0xFF;
	_delay_ms(2000);
	PORTC =0x00;
	_delay_ms(2000);
	for(j=0;j<2;j++)
	{
		PORTC = 0xFF;
		_delay_ms(500);
		PORTC =0x00;
		_delay_ms(500);	
		for(k=0;k<1;k++)
		{
			PORTC = 0xFF;
			_delay_ms(100);
			PORTC =0x00;
			_delay_ms(100);	
		}
	}
}
}

/**@brief main function:it contains all the control mechanism of the project.
   @param defined a variable count_p is used to store the output.
   output=ring/58(cm)
   show_p converts the int type into char to display it on the LCD.
   @return void
   */

int main(void)
{
  int16_t count_p = 0; 
  char show_p[16];
  Initialise();/** @brief Initialise is the function used to initialise LCD and has been defined in the library of LCD that is made. Next step shows the setting up the pins of the port D of the microcontroller.
  1 implies that an output device is connected at that PIN and microcontroller will write the logic there and 0 implies that input device is connected there and microcontroller will read the logic from there.*/
  DDRD = 0b11111011;/** @brief DDR is known as Data Direction Register. '0b' means binary and Each pin after 0b indicates the status of the each pin of the register in the reverse order.*/
  _delay_ms(200);
  /**@brief Now setting the interrupt.
  GICR implies the general control interrupt register. It is used to configure the PIN D2 as the Interrupt pin and echo pin of the ultrasonic sensor is connected here.
  MCUCR: MCU Control Register: It defines any logical change at the INT0/PIND2 will cause to the microcontroller. MCU will be interrupted if logic changes from 0to1 or vice versa.
   @param no parameters are given.
   @return no return is expected.*/

  Initialise();

  GICR |= 1<<INT0; 
  MCUCR |= 1<<ISC00;

  sei();
  
 
  while(1)
  { 
  sensor();
    PORTD |= 1<<PIND0;/** @brief Now occurs the part involving the triggering the ultrasonic sensor. Pin 0 of the port D is connected to the trigger pin of the ultrasonic sensor.
	To trigger the sensor we have applied a pulse width of 20ms.
	PIN D0 IS SET TO +5V.
	A delay of 20ms is given then 
	PIN D0 IS SET TO 0V.*/
    _delay_us(20);

    PORTD &= ~(1<<PIND0);
    count_p = ring/58;

    Send_A_String("Status");/** @brief Next part contains the instructions to display the output on the LCD.
	Send_A_String("string"), GoToMrLCDLocation(int x, int y), are the functions used which are defined in the library.
	“Send_A_String” uses ‘char’ type parameter but the final value ‘count_p’ is a ‘int’ type variable. 
	Thus to convert ‘int’ type to char type we use the ‘itoa’ instruction which converts integer to string.*/
    GoToMrLCDLocation(1,2);
    Send_A_String("Distance=");
    itoa(count_p,show_p,10);
    Send_A_String(show_p);
    Send_A_String(" ");
    GoToMrLCDLocation(13,2);
    Send_A_String("cm");
    GoToMrLCDLocation(1,1);
  }
  
}
/**@brief ISR known as Interrupt Servic Routine is a function which is executed when the microcontroller is interrupted.
Echo pin is set high when an ultrasound wave is sent and sets low when receives the reflected wave.
Duration for which the echo pin remains high depends on the distance between the obstacle and the user. To calculate this time we have used the inter counter of the microcontroller.*/

ISR(INT0_vect)
{
  if(v == 0)
  {
    TCCR1B |= 1<<CS10;
    v = 1;
  }
  else
  {
    TCCR1B = 0;
    ring = TCNT1;
    TCNT1 = 0;
    v = 0;
  }
}
