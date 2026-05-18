/**
  ******************************************************************************
  * @file    wm_led_ctrl.c
  * @brief   Global Variables.
  * @author  Walnut Medical
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 Walnut Medical
  * All rights reserved.
  *
  ******************************************************************************
  */
  
#include "wm_global.h"


bit wm_HalfFanSpeedLED= FALSE;
bit wm_IncFanSpeedLED= FALSE;
bit wm_DecFanSpeedLED= FALSE;

void wm_OnStartUp()
{

/*  Enable LED`s On startup  */
	wm_TurnOnAllTKLed(0);
	wm_UiBoardState = TRUE;
	wm_ReservedBitState = TRUE;
	wm_InitialBootUp = TRUE;
	wm_GeneralCnt =0;
	wm_DisplayDigit(8);
}

void wm_TurnOnAllTKLed(uint16_t ms)
{
	TURN_ON_LED(LED_1);
	wm_DelayMS(ms); WDT_SetReload();
	TURN_ON_LED(LED_2);
	wm_DelayMS(ms); WDT_SetReload();
	TURN_ON_LED(LED_3);
	wm_DelayMS(ms); WDT_SetReload();
	TURN_ON_LED(LED_4);
	wm_DelayMS(ms); WDT_SetReload();
	TURN_ON_LED(LED_5);
	wm_DelayMS(ms); WDT_SetReload();
	TURN_ON_LED(LED_6);
}


void wm_TurnOffAllTKLed(void)
{
    if(!wm_IncFanSpeedLED)    TURN_OFF_LED(LED_1);
    if(!wm_DecFanSpeedLED)    TURN_OFF_LED(LED_2);
    if(!wm_HalfFanSpeedLED)   TURN_OFF_LED(LED_3);
    if(!wm_KitchenLightState) TURN_OFF_LED(LED_4);
    TURN_OFF_LED(LED_5);
    if(!wm_UiBoardState)      TURN_OFF_LED(LED_6);
}

