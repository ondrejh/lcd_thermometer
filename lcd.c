//#include <string.h>

#include "lcd_e.h"
#include "lcd.h"

// LCD memory map for numeric digits
const uint16_t digW[10] = {0x28FC,  // 0
                           0x2060,  // 1
                           0x00DB,  // 2
                           0x00F3,  // 3
                           0x0067,  // 4
                           0x00B7,  // 5
                           0x00BF,  // 6
                           0x00E0,  // 7
                           0x00FF,  // 8
                           0x00F7}; // 9

// LCD memory map for big letters
const uint16_t alphaW[26] = {0x00EF,  // A
                             0x50F1,  // B
                             0x009C,  // C
                             0x50F0,  // D
                             0x009F,  // E
                             0x008F,  // F
                             0x00BD,  // G
                             0x006F,  // H
                             0x5090,  // I
                             0x0078,  // J
                             0x220E,  // K
                             0x001C,  // L
                             0xA06C,  // M
                             0x826C,  // N
                             0x00FC,  // O
                             0x00CF,  // P
                             0x02FC,  // Q
                             0x02CF,  // R
                             0x00B7,  // S
                             0x5080,  // T
                             0x007C,  // U
                             0x280C,  // V
                             0x0A6C,  // W
                             0xAA00,  // X
                             0xB000,  // Y
                             0x2890}; // Z

void lcd_init(void)
{
    // L0~L26 & L36~L39 pins selected
    LCD_E_setPinAsLCDFunctionEx(LCD_E_BASE, LCD_E_SEGMENT_LINE_0, LCD_E_SEGMENT_LINE_26);
    LCD_E_setPinAsLCDFunctionEx(LCD_E_BASE, LCD_E_SEGMENT_LINE_36, LCD_E_SEGMENT_LINE_39);

    LCD_E_initParam initParams = LCD_E_INIT_PARAM;
    initParams.clockDivider = LCD_E_CLOCKDIVIDER_3;
    initParams.muxRate = LCD_E_4_MUX;
    initParams.segments = LCD_E_SEGMENTS_ENABLED;

    // Init LCD as 4-mux mode
    LCD_E_init(LCD_E_BASE, &initParams);

    // LCD Operation - Mode 3, internal 3.02v, charge pump 256Hz
    LCD_E_setVLCDSource(LCD_E_BASE, LCD_E_INTERNAL_REFERENCE_VOLTAGE, LCD_E_EXTERNAL_SUPPLY_VOLTAGE);
    LCD_E_setVLCDVoltage(LCD_E_BASE, LCD_E_REFERENCE_VOLTAGE_2_96V);

    LCD_E_enableChargePump(LCD_E_BASE);
    LCD_E_setChargePumpFreq(LCD_E_BASE, LCD_E_CHARGEPUMP_FREQ_16);

    // Clear LCD memory
    LCD_E_clearAllMemory(LCD_E_BASE);

    // Configure COMs and SEGs
    // L0 = COM0, L1 = COM1, L2 = COM2, L3 = COM3
    LCD_E_setPinAsCOM(LCD_E_BASE, LCD_E_SEGMENT_LINE_0, LCD_E_MEMORY_COM0);
    LCD_E_setPinAsCOM(LCD_E_BASE, LCD_E_SEGMENT_LINE_1, LCD_E_MEMORY_COM1);
    LCD_E_setPinAsCOM(LCD_E_BASE, LCD_E_SEGMENT_LINE_2, LCD_E_MEMORY_COM2);
    LCD_E_setPinAsCOM(LCD_E_BASE, LCD_E_SEGMENT_LINE_3, LCD_E_MEMORY_COM3);

    // Select to display main LCD memory
    LCD_E_selectDisplayMemory(LCD_E_BASE, LCD_E_DISPLAYSOURCE_MEMORY);

    // Turn on LCD
    LCD_E_on(LCD_E_BASE);
}

/*
 * Scrolls input string across LCD screen from left to right
 */
/*void displayScrollText(char *msg)
{
    int length = strlen(msg);
    //int oldmode = *mode;
    int i;
    int s = 5;
    char buffer[6] = "      ";
    for (i=0; i<length+7; i++)
    {
        //if (*mode != oldmode)
        //    break;
        int t;
        for (t=0; t<6; t++)
            buffer[t] = ' ';
        int j;
        for (j=0; j<length; j++)
        {
            if (((s+j) >= 0) && ((s+j) < 6))
                buffer[s+j] = msg[j];
        }
        s--;

        showChar(buffer[0], pos1);
        showChar(buffer[1], pos2);
        showChar(buffer[2], pos3);
        showChar(buffer[3], pos4);
        showChar(buffer[4], pos5);
        showChar(buffer[5], pos6);

        __delay_cycles(8000000);
    }
}*/

void dispWord(uint16_t w, int position)
{
    LCDMEMW[position/2] = w;
}

void dispWordOR(uint16_t w, int position)
{
    LCDMEMW[position/2] |= w;
}

/*
 * Displays input character at given LCD digit/position
 * Only spaces, numeric digits, and uppercase letters are accepted characters
 */
void showChar(char c, int position)
{
    if (c == ' ')
    {
        // Display space
        LCDMEMW[position/2] = 0;
    }
    else if (c >= '0' && c <= '9')
    {
        // Display digit
        LCDMEMW[position/2] = digW[c-'0'];
    }
    else if (c >= 'A' && c <= 'Z')
    {
        // Display alphabet
        LCDMEMW[position/2] = alphaW[c-'A'];
    }
    else
    {
        // Turn all segments on if character is not a space, digit, or uppercase letter
        LCDMEMW[position/2] = 0xFFFF;
    }
}
