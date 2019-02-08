#ifndef __BOARD_H__
#define __BOARD_H__

#include <msp430fr4133.h>

// board (leds, button)
#define LED_INIT() do{P1DIR|=0x01;P1OUT&=~0x01;P4DIR|=0x01;P4OUT&=~0x01;}while(0)
#define LED_RED_ON() do{P1OUT|=0x01;}while(0)
#define LED_RED_OFF() do{P1OUT&=~0x01;}while(0)
#define LED_RED_SWAP() do{P1OUT^=0x01;}while(0)
#define LED_GREEN_ON() do{P4OUT|=0x01;}while(0)
#define LED_GREEN_OFF() do{P4OUT&=~0x01;}while(0)
#define LED_GREEN_SWAP() do{P4OUT^=0x01;}while(0)
#define BTN_INIT() do{P1DIR&=~0x04;P1REN|=0x04;P2DIR&=~0x40;P2REN|=0x40;}while(0)
#define BTN1 ((P1IN&0x04)==0)
#define BTN2 ((P2IN&0x40)==0)

#define OUT_INIT() do{P1DIR|=0xF8;P5DIR|=0x0D;}while(0)
#define OUT1(x) do{if (x) P1OUT|=0x80; else P1OUT&=~0x80;}while(0)
#define OUT2(x) do{if (x) P1OUT|=0x40; else P1OUT&=~0x40;}while(0)
#define OUT3(x) do{if (x) P5OUT|=0x01; else P5OUT&=~0x01;}while(0)
#define OUT4(x) do{if (x) P1OUT|=0x20; else P1OUT&=~0x20;}while(0)
#define OUT5(x) do{if (x) P1OUT|=0x10; else P1OUT&=~0x10;}while(0)
#define OUT6(x) do{if (x) P1OUT|=0x08; else P1OUT&=~0x08;}while(0)
#define OUT7(x) do{if (x) P5OUT|=0x08; else P5OUT&=~0x08;}while(0)
#define OUT8(x) do{if (x) P5OUT|=0x04; else P5OUT&=~0x04;}while(0)

void board_init(void);

#endif // __BOARD_H__
