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
#include "ds18b20.h"

void disp_temp(int temp) {
    uint8_t ts=0, t100=0, t10=0, t1=0, t0=0;
    int t = temp;

    if (t < 0) {t = -t; ts = 1;}
    t100 = t/2000;
    t %= 2000;
    t10 = t/200;
    t %= 200;
    t1 = t/20;
    t %= 20;
    t0 = t/2;
    if (t&1) t0 ++;

    if (ts & t10) showChar('-', pos2);
    else if (t100) showChar('0' + t100, pos2);
    else showChar(' ', pos2);
    if (t100 || t10) showChar('0' + t10, pos3);
    else if (ts & (t10==0)) showChar('-', pos3);
    else showChar(' ', pos3);
    showChar('0' + t1, pos4);
    dispWordOR(LCD_DECIMAL, pos4);
    showChar('0' + t0, pos5);
    dispWordOR(LCD_P5_DEGREE, pos5);
    showChar('C', pos6);
}

void disp_error() {
    showChar(' ', pos2);
    showChar('-', pos3);
    showChar('-', pos4);
    showChar('-', pos5);
    showChar(' ', pos6);
}

// main program body
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// Stop WDT

	board_init(); // init dco and leds
	lcd_init();

	ds18b20_sensor_t s[1];
	ds18b20_init(&s[0], &P8OUT, &P8IN, &P8REN, &P8DIR, 3);

	while(1)
	{
	    ds18d20_start_conversion(&s[0]);
		__delay_cycles(10000000);
		ds18b20_read_conversion(&s[0]);
        showChar('1', pos1);
        dispWordOR(LCD_DECIMAL, pos1);
		if (s[0].valid == true) {
            int t = s[0].data.temp;
            disp_temp(t);
		}
		else
            disp_error();
		__delay_cycles(10000000);
		LED_GREEN_SWAP();
	}
/*
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
	}*/

	return -1;
}
