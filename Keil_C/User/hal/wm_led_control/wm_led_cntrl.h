/**
  ******************************************************************************
  * @file    wm_led_cntrl.h
  * @author  Walnut Medical
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 Walnut Medical
  * All rights reserved.
  *
  ******************************************************************************
  */

#ifndef __WM_LED_CNTRL_H__
#define __WM_LED_CNTRL_H__


#define TOGGLE_LED(X) (X = !X)
#define TURN_ON_LED(X) (X = 0)
#define TURN_OFF_LED(X) (X = 1)

// LED mode macros
#define SET_LED_INC_MODE()  do { wm_IncFanSpeedLED=1; wm_HalfFanSpeedLED=0; wm_DecFanSpeedLED=0; } while(0)
#define SET_LED_DEC_MODE()  do { wm_DecFanSpeedLED=1; wm_IncFanSpeedLED=0; wm_HalfFanSpeedLED=0; } while(0)
#define SET_LED_HALF_MODE() do { wm_HalfFanSpeedLED=1; wm_IncFanSpeedLED=0; wm_DecFanSpeedLED=0; } while(0)
#define CLEAR_LED_MODES()   do { wm_IncFanSpeedLED=0; wm_HalfFanSpeedLED=0; wm_DecFanSpeedLED=0; } while(0)

extern bit wm_HalfFanSpeedLED;
extern bit wm_IncFanSpeedLED;
extern bit wm_DecFanSpeedLED;

/*Extern Functions*/

extern void wm_OnStartUp();
extern void wm_TurnOnAllTKLed(uint16_t ms);
extern void wm_TurnOffAllTKLed();



#endif
