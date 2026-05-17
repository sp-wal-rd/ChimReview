/**
 ******************************************************************************
 * @file    wm_7seg_control.c
 * @author  Walnut Medical
 * @brief   Source file of 7-segment display control.
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 Walnut Medical
 * All rights reserved.
 *
 ******************************************************************************
 */

#include "wm_global.h"



code const uint8_t seg_patterns[10] = {
    0x3F,  // 0: ABCDEF
    0x06,  // 1: BC
    0x5B,  // 2: ABDEG
    0x4F,  // 3: ABCDG
    0x66,  // 4: BCFG
    0x6D,  // 5: ACDFG
    0x7D,  // 6: ACDEFG
    0x07,  // 7: ABC
    0x7F,  // 8: ABCDEFG
    0x6F   // 9: ABCDFG
};

void wm_DisplayDigit(uint8_t num)
{   
    uint8_t pattern = seg_patterns[num];
    
    SEG_A_A = pattern & 0x01;
    SEG_A_B = pattern & 0x02;
    SEG_A_C = pattern & 0x04;
    SEG_A_D = pattern & 0x08;
    SEG_A_E = pattern & 0x10;
    SEG_A_F = pattern & 0x20;
    SEG_A_G = pattern & 0x40;
   
   
}
void wm_DisplayOff()
{
    SEG_A_A = 0; 
    SEG_A_B = 0;
    SEG_A_C = 0;
    SEG_A_D = 0;
    SEG_A_E = 0;
    SEG_A_F = 0;
    SEG_A_G = 0;
	
}