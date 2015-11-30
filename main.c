//******************************************************************************
// MSP430FR4133 launchpad test project
//
// author: Ondrej Hejda
// date:   26.11.2015
//
// resources:
//
//   https://github.com/sgergo/project4133 .. nice project, thanks
//   TI example sources .. MSP-EXP430FR4133_Software_Examples_windows.zip
//
// hardware: MSP430FR4133 (launchpad)
//
//                MSP430FR4133
//             -----------------
//         /|\|              XIN|----  -----------
//          | |                 |     | 32.768kHz |---
//          --|RST          XOUT|----  -----------    |
//            |                 |                    ---
//            |                 |
//            |           P1.1,2|---> UART (debug output 9.6kBaud)
//            |                 |
//            |             P1.0|---> RED LED (active high)
//            |             P4.0|---> GREEN LED (active high)
//            |                 |
//            |             P1.2|<--- BTN1 --
//            |             P2.6|<--- BTN2 --|--
//            |                 |               |
//            |                 |              ---
//            |                 |
//            |                 |         -------------------
//            | L0..31, L36..39 |--/36/--| LCD  108seg. 4com |
//            |                 |        |                   |
//            |                 |        |    8.8:8.8:8.8    |
//             -----------------          -------------------
//
//
//******************************************************************************

// include section
#include <msp430fr4133.h>

#include "board.h"
#include "lcd.h"

// main program body
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// Stop WDT

	board_init(); // init dco and leds
	lcd_init();

	LED_RED_ON();

	int symbol = 0;

	while(1)
	{
	    showChar('H',pos1);
	    showChar('E',pos2);
	    showChar('L',pos3);
	    showChar('L',pos4);
	    showChar('O',pos5);
	    showChar(' ',pos6);
        dispWord(0,symbols);
		__delay_cycles(10000000);

	    showChar(' ',pos1);
	    showChar('W',pos2);
	    showChar('O',pos3);
	    showChar('R',pos4);
	    showChar('L',pos5);
	    showChar('D',pos6);

		switch (symbol) {
        case 0:
            dispWordOR(LCD_P6_RX|LCD_P6_TX,pos6);
            dispWordOR(LCD_P3_TRANSMITTER,pos3);
            break;
        case 1:
            dispWord(LCD_HEART,symbols);
            break;
        case 2:
            dispWord(LCD_BANG,symbols);
            break;
        case 3:
            dispWord(LCD_CLOCK,symbols);
            break;
        case 4:
            dispWord(LCD_RSYMBOL,symbols);
            break;
        case 5:
            dispWord(LCD_BATTERY,symbols);
            break;
		}
		symbol++;
		symbol%=6;

        __delay_cycles(10000000);

        LED_GREEN_SWAP();
        LED_RED_SWAP();
	}

	return -1;
}
