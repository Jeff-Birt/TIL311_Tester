/*
 Simple test program for TI TIL311 Hex LED displays
 Jeffrey T. Birt (Hey Birt!) 
 website: http://www.soigeneris.com
 YouTube: http://www.youtube.com/c/HeyBirt
*/

// NOTES: Used a Arduino Mega 2560 as that is what I had at hand
// You could use any Arudio for this by adjusting the DDRx and PORTx lines

// Mega	2560	Arduino	TIL311	TIL311
// Port			Pin		Pin		Name
// PA0			22		3		Data A
// PA1			23		2		Data B
// PA2			24		13		Data C
// PA3			25		12		Data D
// PA4			26		4		Left Decimal
// PA5			27		10		Right Decimal
// PA6			28		8		Blank
// PA7			29		5		Strobe

#define DATA_ATOD	0x0F // active high
#define L_DEC		0x10 // active low
#define R_DEC		0x20 // active low
#define BLANK		0x40 // active high
#define STROBE		0x80 // active low

void setup() 
{
  PORTA = PORTA & ~DATA_ATOD;		// digit pins low
  PORTA = PORTA & ~BLANK;			// blanking low (not blanked)
  PORTA = PORTA | L_DEC | R_DEC | STROBE; // all else high to turn off

  DDRA = 0xFF;						// all outputs
}

void loop() 
{
	// cycle through displaying 0-F digits
	for (int i = 0; i < 0x10; i++)
	{
		PORTA = PORTA & ~DATA_ATOD; // clear digit output bits
		PORTA = PORTA | i;			// set new digit value
		PORTA = PORTA & ~STROBE;	// STROBE low to latch digit
		PORTA = PORTA | STROBE;		// STROBE back high
		delay(2000);				// pause for 2 seconds
	}

	// at this point we should be displaying an 'F'
	// use BLANK line to flash whole display ON/OFF
	for (int i = 0; i < 0x04; i++)
	{
		PORTA = PORTA | BLANK;		// BLANK HIGH to blank display
		delay(1000);				// pause for 1 seconds
		PORTA = PORTA & ~BLANK;		// BLANK back LOW
		delay(1000);				// pause for 1 seconds
	}

	// now display decimal points
	for (int i = 0; i < 0x04; i++)
	{
		PORTA = PORTA & ~L_DEC;		// turn ON left decimal
		delay(2000);				// pause for 2 seconds
		PORTA = PORTA | L_DEC;		// turn OFF left decimal

		PORTA = PORTA & ~R_DEC;		// turn ON right decimal
		delay(2000);				// pause for 2 seconds
		PORTA = PORTA | R_DEC;		// turn OFF right decimal
	}

	delay(2000);					// pause for 2 seconds
}
