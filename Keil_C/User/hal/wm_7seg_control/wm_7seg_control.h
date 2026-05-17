/**
  ******************************************************************************
  * @file    wm_7seg_control.h
  * @author  Walnut Medical
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 Walnut Medical
  * All rights reserved.
  *
  ******************************************************************************
  */
  
#ifndef __WM_7SEG_CNTRL_H__
#define __WM_7SEG_CNTRL_H__

#define SEG_A_A P22
#define SEG_A_B P23
#define SEG_A_C P51
#define SEG_A_D P50
#define SEG_A_E P11
#define SEG_A_F P26
#define SEG_A_G P27

extern void wm_DisplayDigit(uint8_t num);
extern void wm_DisplayOff();
#endif


