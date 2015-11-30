#ifndef __LCD_H__
#define __LCD_H__

#include <msp430fr4133.h>
#include <inttypes.h>

#define pos1 4   /* Digit A1 - L4  */
#define pos2 6   /* Digit A2 - L6  */
#define pos3 8   /* Digit A3 - L8  */
#define pos4 10  /* Digit A4 - L10 */
#define pos5 2   /* Digit A5 - L2  */
#define pos6 18  /* Digit A6 - L18 */
#define symbols 12

#define LCDMEMW ((int*)LCDMEM)

// decimal point (works for P1 .. P5, P6 its RX)
#define LCD_DECIMAL 0x0100
#define LCD_P6_RX LCD_DECIMAL

// colon
#define LCD_COLON 0x0400 /*pos2,pos4*/
#define LCD_P1_MINUS       LCD_COLON /*pos1*/
#define LCD_P3_TRANSMITTER LCD_COLON /*pos3*/
#define LCD_P5_DEGREE      LCD_COLON /*pos5*/
#define LCD_P6_TX          LCD_COLON /*pos6*/

// symbols
#define LCD_BANG 0x0001 /* ! */
#define LCD_RSYMBOL 0x0002 /* (R) */
#define LCD_HEART 0x0004 /* <3 */
#define LCD_CLOCK 0x0008 /* clock */
#define LCD_BATTERY 0x0FF0 /* [xxxxxx]o */
#define LCD_BATT0 0x0010   /*         o */
#define LCD_BATT1 0x0100   /* [      ]  */
#define LCD_BATT2 0x0080   /*       x   */
#define LCD_BATT3 0x0800   /*      x    */
#define LCD_BATT4 0x0040   /*     x     */
#define LCD_BATT5 0x0400   /*    x      */
#define LCD_BATT6 0x0020   /*   x       */
#define LCD_BATT7 0x0200   /*  x        */

extern const uint16_t digW[10];
extern const uint16_t alphaW[26];

void lcd_init(void);
//void displayScrollText(char *msg);
void showChar(char c, int position);
void dispWord(uint16_t w, int position);
void dispWordOR(uint16_t w, int position);

#endif // __LCD_H__
