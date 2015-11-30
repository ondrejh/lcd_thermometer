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

void board_init(void);

#endif // __BOARD_H__
