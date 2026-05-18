/**
 ******************************************************************************
 * @file    wm_global.c
 * @author  Walnut Medical
 * @brief   Source file of state flow.
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 Walnut Medical
 * All rights reserved.
 *
 ******************************************************************************
 *///wm_global.c
 
#include "wm_global.h"
 
//bit wm_IsTkScanRoundFinished = FALSE;

// Active system state flags
bit wm_IsHeaterEnRequested = FALSE;
bit wm_IsSleepModeRequested = FALSE;
bit wm_IsHkReleased = TRUE;
bit wm_HeaterState = FALSE;
bit wm_KitchenLightState = FALSE;
bit wm_UiBoardState = FALSE;
bit wm_ReservedBitState = FALSE;
bit wm_FanState = FALSE;

bit wm_IsHtDisFanEnReq = FALSE;

// Gesture processing flags
volatile bit wm_EnGestureProcessing = TRUE;
bit wm_rightSwipeInit = 0;
bit wm_LeftSwipeInit = 0;
bit wm_IsUiDisableRequested = FALSE;
bit wm_InitialBootUp = FALSE;

uint8_t wm_FanSpeed = 0;
uint8_t wm_cmdByte =0;


bit leftSensor = FALSE;
bit rightSensor = FALSE;


void wm_ProcessIrGesture(void)
{
    if(wm_IrDelayCnt < 200) return;
    if(!wm_EnGestureProcessing) return;
    
    leftSensor = !P07;
    rightSensor = !P17;
    
    if((leftSensor || rightSensor) && (wm_IrGeastureTimeOutCnt > 500)) {
        // False geasture - reset swipe state
        wm_LeftSwipeInit = 0;
        wm_rightSwipeInit = 0;
        wm_IrGeastureTimeOutCnt = 0;
        return;
    }
    
    // Left swipe detection (right--left)
    if(leftSensor && wm_LeftSwipeInit) {
        // Complete left swipe - increment fan speed
        wm_LeftSwipeInit = 0;
        wm_rightSwipeInit = 0;
        wm_IrDelayCnt = 0;

		if(wm_IsUiDisableRequested)
		{
			wm_IsUiDisableRequested = FALSE;		
			wm_IsSleepModeRequested = FALSE;
			TURN_ON_LED(LED_6);
		}
    

        if(++wm_FanSpeed > 9) wm_FanSpeed = 0;
        if((wm_FanSpeed == 1) && (!wm_UiBoardState) )
        {
        	wm_UiBoardState = TRUE;
        	wm_ReservedBitState = FALSE;
        	wm_TurnOnAllTKLed(100);
        	SET_LED_INC_MODE();
        	wm_KitchenLightState = TRUE;
        	wm_TurnOffAllTKLed();
        }
        if(!wm_FanSpeed) 
        {
            wm_TurnOffFan();
        } 
        else 
        {
           wm_FanState = TRUE;
     	   SET_LED_INC_MODE();
           wm_TurnOffAllTKLed();
           TURN_ON_LED(LED_1);

        }
        	
        wm_DisplayDigit(wm_FanSpeed);
    }
    else if(leftSensor) {
        wm_rightSwipeInit = 1;
        wm_IrGeastureTimeOutCnt = 0;
    }
    
    // Right swipe detection (left--right)
    if(rightSensor && wm_rightSwipeInit) {
        // Complete right swipe - sleep request
        wm_LeftSwipeInit = 0;
        wm_rightSwipeInit = 0;
        wm_IrDelayCnt = 0;
        
		if((!wm_IsSleepModeRequested)&& (wm_UiBoardState)) {
            wm_IsSleepModeRequested = TRUE;
            wm_GeneralCnt = 0;
            wm_UiDisTimeOutCnt = WM_UI_DIS_TIMEOUT;
            wm_IsUiDisableRequested = TRUE;
        }
        else if(wm_IsSleepModeRequested) {
            // Double swipe within timeout - immediate sleep
            wm_IsSleepModeRequested = FALSE;
            wm_ShutdownUI();
			wm_SleepFromGesture(100);
        }
    }
    else if(rightSensor) {
        wm_LeftSwipeInit = 1;
        wm_IrGeastureTimeOutCnt = 0;
    }
}



void wm_SleepFromGesture(uint16_t ms)
{
	wm_TurnOnAllTKLed(0);

	TURN_OFF_LED(LED_6);
	wm_DelayMS(ms); WDT_SetReload();
	TURN_OFF_LED(LED_5);
	wm_DelayMS(ms); WDT_SetReload();
	TURN_OFF_LED(LED_4);
	wm_DelayMS(ms); WDT_SetReload();
	TURN_OFF_LED(LED_3);
	wm_DelayMS(ms); WDT_SetReload();
	TURN_OFF_LED(LED_2);
	wm_DelayMS(ms); WDT_SetReload();
	TURN_OFF_LED(LED_1);
	wm_DelayMS(ms);
}

