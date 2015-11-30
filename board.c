#include "board.h"

// init clock and onboard ios (leds and buttons)
void board_init(void)
{
	// set clock 8MHz
	P4SEL0 |= BIT1 | BIT2;                  // set XT1 pin as second function

    do {
        CSCTL7 &= ~(XT1OFFG | DCOFFG);      // Clear XT1 and DCO fault flag
        SFRIFG1 &= ~OFIFG;
    }while (SFRIFG1 & OFIFG);               // Test oscillator fault flag

	__bis_SR_register(SCG0);                // disable FLLUNLOCK
    // CSCTL3 |= SELREF__REFOCLK;              // No XTAL, so we set REFO (~32768kHz)
    										// as FLL reference source
    CSCTL3 |= SELREF__REFOCLK;               // 32786khz XTAL is present, so we use it
    										// as FLL reference source
    CSCTL0 = 0;                             // clear DCO and MOD registers
    CSCTL1 &= ~(DCORSEL_7);                 // Clear DCO frequency select bits first
    CSCTL1 |= DCORSEL_3;                    // Set DCO = 8MHz
    CSCTL2 = FLLD_0 + 243;                  // DCODIV = 8MHz
    __delay_cycles(3);
    __bic_SR_register(SCG0);                // enable FLL

    while(CSCTL7 & (FLLUNLOCK0 | FLLUNLOCK1)) // Poll until FLL is locked
    	;

    CSCTL4 = SELMS__DCOCLKDIV | SELA__XT1CLK; // set default REFO(~32768Hz) as ACLK source, ACLK = 32768Hz
                                            // default DCODIV as MCLK and SMCLK source
    __delay_cycles(8000);

	// magic function
	PM5CTL0 &= ~LOCKLPM5; // Important!

	LED_INIT(); // leds
	BTN_INIT(); // buttons
}

