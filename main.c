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

const uint8_t decimal[16] = {0, 1, 1, 2, 3, 3, 4, 4, 5, 6, 6, 7, 8, 8, 9, 9};

// display temperature
void disp_temp(int temp)
{
    uint8_t ts=0, t100=0, t10=0, t1=0, t0=0;
    int16_t t = temp;

    if (t < 0) {ts = 1; t = -t;}
    t0 = decimal[t & 0x000F];
    t >>= 4;
    t100 = t/100;
    t %= 100;
    t10 = t/10;
    t %= 10;
    t1 = t;

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

// display --- (when error)
void disp_error()
{
    showChar(' ', pos2);
    showChar('-', pos3);
    showChar('-', pos4);
    showChar('-', pos5);
    showChar(' ', pos6);
}

// display sensor number (1st position)
void disp_num(int n)
{
    showChar('0' + (n % 10), pos1);
    dispWordOR(LCD_DECIMAL, pos1);
}

void out_set(int n, bool s)
{
    switch (n) {
    case 0: OUT1(s); break;
    case 1: OUT2(s); break;
    case 2: OUT3(s); break;
    case 3: OUT4(s); break;
    case 4: OUT5(s); break;
    case 5: OUT6(s); break;
    case 6: OUT7(s); break;
    case 7: OUT8(s); break;
    default: break;
    }
}

// main program body
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// Stop WDT

	board_init(); // init dco and leds
	lcd_init();

	// initialize sensors
	ds18b20_sensor_t s[6];
	ds18b20_init(&s[0], &P2OUT, &P2IN, &P2REN, &P2DIR, 7); // sensor 1: P2.7
	ds18b20_init(&s[1], &P8OUT, &P8IN, &P8REN, &P8DIR, 0); // sensor 2: P8.0
	ds18b20_init(&s[2], &P5OUT, &P5IN, &P5REN, &P5DIR, 1); // sensor 3: P5.1
	ds18b20_init(&s[3], &P2OUT, &P2IN, &P2REN, &P2DIR, 5); // sensor 4: P2.5
	ds18b20_init(&s[4], &P8OUT, &P8IN, &P8REN, &P8DIR, 2); // sensor 5: P8.2
	ds18b20_init(&s[5], &P8OUT, &P8IN, &P8REN, &P8DIR, 3); // sensor 6: P8.3

    int sn = 0;
    int out = 0;

	while(1)
	{
	    ds18d20_start_conversion(&s[sn]);
	    LED_GREEN_ON();
		__delay_cycles(10000000);
		LED_GREEN_OFF();
		ds18b20_read_conversion(&s[sn]);
        disp_num(sn+1);
		if (s[sn].valid == true) {
            int t = s[sn].data.temp;
            disp_temp(t);
            LED_RED_OFF();
		}
		else {
            disp_error();
            LED_RED_ON();
		}
		__delay_cycles(10000000);
		sn ++;
		sn %= 6;

		int i;
		for (i=0;i<8;i++)
		    out_set(i, (i==out));
        out ++;
        out %= 8;
	}

	return -1;
}
