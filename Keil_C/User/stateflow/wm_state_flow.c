/**
 ******************************************************************************
 * @file    wm_state_flow.c
 * @author  Walnut Medical
 * @brief   Source file of state flow.
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 Walnut Medical
 * All rights reserved.
 *
 ******************************************************************************
 */

#include "wm_global.h"
#include "wm_state_flow.h"

//// LED mode macros
//#define SET_LED_INC_MODE()  do { wm_IncFanSpeedLED=1; wm_HalfFanSpeedLED=0; wm_DecFanSpeedLED=0; } while(0)
//#define SET_LED_DEC_MODE()  do { wm_DecFanSpeedLED=1; wm_IncFanSpeedLED=0; wm_HalfFanSpeedLED=0; } while(0)
//#define SET_LED_HALF_MODE() do { wm_HalfFanSpeedLED=1; wm_IncFanSpeedLED=0; wm_DecFanSpeedLED=0; } while(0)
//#define CLEAR_LED_MODES()   do { wm_IncFanSpeedLED=0; wm_HalfFanSpeedLED=0; wm_DecFanSpeedLED=0; } while(0)

#define WM_TK_DEBOUNCE_MS 300

// Static helper functions
//static void wm_TurnOffFan(void);
//static void wm_ShutdownUI(void);

void wm_TurnOffFan(void)
{
	//wm_FanSpeed = 0;
    wm_FanState = FALSE;
    CLEAR_LED_MODES();
    wm_TurnOnAllTKLed(0);
    wm_DisplayDigit(wm_FanSpeed);
}

void wm_ShutdownUI(void)
{
	wm_EnGestureProcessing = TRUE;
    wm_UiBoardState = FALSE;
    wm_IsUiDisableRequested = FALSE;
    wm_HeaterState = FALSE;
    wm_KitchenLightState = FALSE;
    wm_FanSpeed = 0;
    wm_FanState = FALSE;
    wm_IsHtDisFanEnReq = FALSE;
    CLEAR_LED_MODES();
    wm_TurnOffAllTKLed();
    wm_DisplayOff();
}

void wm_StateFlow(void)
{
    if(wm_IsTkScanRoundFinished && (wm_TkDelayCnt >= WM_TK_DEBOUNCE_MS))
    {
        wm_IsTkScanRoundFinished = FALSE;
        
        // Early exit if UI disabled and not power key
        if(!wm_UiBoardState && !(wm_TkStatus & TK6)) {
        	if((wm_TkStatus & TK4) && wm_IsTk4Released) {
            	LED_4 = !LED_4;
            	wm_KitchenLightState = !wm_KitchenLightState;
            	wm_IsTk4Released = FALSE;
            	wm_TkDelayCnt = 0;
            }
            else if(!(wm_TkStatus & TK4)){
            	wm_IsTk4Released = TRUE;
            }
           goto wm_HandleSleepState;
        }
        
        // Disable first four features when Heater Enabled
        if(wm_HeaterState)
        {
        	goto wm_Heater;
        }
        
        // Process touch keys
        if((wm_TkStatus & TK1))  // Fan Speed Increment
        {
        if(wm_IsTk1Released)
        {
            wm_TkDelayCnt = 0;
            wm_IsTk1Released = FALSE;
            
            if(wm_IsUiDisableRequested)
            	wm_IsUiDisableRequested = FALSE;
            
            if(++wm_FanSpeed > 9) wm_FanSpeed = 0;
            
            if(!wm_FanSpeed) {
                wm_TurnOffFan();
            } else {
                wm_FanState = TRUE;
                SET_LED_INC_MODE();
                wm_TurnOffAllTKLed();
                TURN_ON_LED(LED_1);
                wm_DisplayDigit(wm_FanSpeed);
            }
            }
        }
        else
        {
        	 wm_IsTk1Released = TRUE;

        }
        
        
        if((wm_TkStatus & TK2))  // Fan Speed Decrement
        {
                if(wm_IsTk2Released)
        {
            wm_TkDelayCnt = 0;
			wm_IsTk2Released = FALSE;			
			
            if(wm_IsUiDisableRequested)
            	wm_IsUiDisableRequested = FALSE;            
            
            if(wm_FanSpeed == 0) {
                wm_FanSpeed = 9;
            } else {
                wm_FanSpeed--;
            }
            
            if(!wm_FanSpeed) {
                wm_TurnOffFan();
            } else {
                wm_FanState = TRUE;
                SET_LED_DEC_MODE();
                wm_TurnOffAllTKLed();
                TURN_ON_LED(LED_2);
                wm_DisplayDigit(wm_FanSpeed);
            }
            }
        }
        else
        {
        	 wm_IsTk2Released = TRUE;

        }
        if((wm_TkStatus & TK3))  // Half Speed Toggle
        {
                if(wm_IsTk3Released)
        {
            wm_TkDelayCnt = 0;
            wm_IsTk3Released = FALSE;
            
            if(wm_IsUiDisableRequested)
            	wm_IsUiDisableRequested = FALSE;
            wm_FanSpeed = (wm_FanSpeed == 5) ? 0 : 5;
            
            if(!wm_FanSpeed) {
                wm_TurnOffFan();
            } else {
                wm_FanState = TRUE;
                SET_LED_HALF_MODE();
                wm_TurnOffAllTKLed();
                TURN_ON_LED(LED_3);
            }
            wm_DisplayDigit(wm_FanSpeed);
            }
        }
        else
        {
        	 wm_IsTk3Released = TRUE;

        }
wm_Heater: 
        if((wm_TkStatus & TK4))  // Kitchen Light Toggle
        {       
                if(wm_IsTk4Released)
        {
            wm_TkDelayCnt = 0;
            wm_IsTk4Released = FALSE;
            
            wm_KitchenLightState = !wm_KitchenLightState;
            
            if(wm_KitchenLightState) {
                wm_TurnOffAllTKLed();
                TURN_ON_LED(LED_4);
            } else {
                TURN_OFF_LED(LED_4);
                if((!wm_FanState) && (!wm_HeaterState)) {
                   	wm_TurnOnAllTKLed(0);
                    wm_DisplayDigit(0);
                }
            }              
            } 
        }
        else
        {
        	  wm_IsTk4Released = TRUE;

        }
       
//wm_Heater:              
        if(wm_TkStatus & TK5)  // Heater Long Press
        {
            wm_TkDelayCnt = 0;
            
            if(!wm_IsHeaterEnRequested) {
                wm_IsHeaterEnRequested = TRUE;
                wm_HeaterLongPressCnt = 0;
                //wm_IsHkReleased = FALSE;
            }
            
             if((wm_HeaterLongPressCnt >= WM_HTK_LONGPRESS_TIMEOUT) && (wm_IsHeaterEnRequested) && (wm_IsHkReleased)) {
                // Toggle heater
                wm_HeaterState = !wm_HeaterState;
                
                if(wm_HeaterState) {
                    wm_HeaterDelayCnt = WM_HEATER_TIMEOUT;
                    wm_LedDelayCnt = 0;
                    wm_FanState = FALSE;
                    wm_FanSpeed = 0;
                    //wm_KitchenLightState = FALSE;
                    //wm_EnGestureProcessing = FALSE;
                   
    				CLEAR_LED_MODES();
                    wm_TurnOffAllTKLed();
                   // TURN_ON_LED(LED_4);
                    //wm_KitchenLightState = TRUE;
                    wm_IsHtDisFanEnReq = FALSE;
                } else {
                	wm_EnGestureProcessing = TRUE;
                   	wm_TurnOnAllTKLed(0);
                    wm_DisplayDigit(0);
                }
                wm_HeaterLongPressCnt = 0;
                wm_IsHkReleased = FALSE;
            }
        }
        if((wm_TkStatus & TK6))  // Power On/Off
        { 
          if(wm_IsTk6Released)
          {
            wm_TkDelayCnt = 0;
            wm_IsTk6Released = FALSE;
            
            if(!wm_UiBoardState) {
                // Power ON
                wm_TurnOnAllTKLed(0);
                wm_DisplayDigit(0);
                wm_UiBoardState = TRUE;
                wm_ReservedBitState = FALSE;
                wm_InitialBootUp = FALSE;
                wm_EnGestureProcessing = TRUE;
            }
            else {
                // Power OFF logic
               // bit systemActive = wm_FanState || wm_HeaterState;
                
                if((!wm_FanState) ||(wm_HeaterState) ) {
                    wm_ShutdownUI();
                }
                else if(wm_IsUiDisableRequested) {
                    wm_ShutdownUI();
                }
                else {
                    wm_IsUiDisableRequested = TRUE;
                    wm_UiDisTimeOutCnt = WM_UI_DIS_TIMEOUT;
                    wm_HeaterState = FALSE;
                    wm_TurnOffAllTKLed();
                }
             }
           }
        }

        
        // Handle TK5 release (heater toggle)
        if(!(wm_TkStatus & TK5) && wm_IsHeaterEnRequested) {

            wm_IsHeaterEnRequested = FALSE;
            wm_IsHkReleased = TRUE;
        }
    }
   
wm_HandleSleepState:

	/* Handle on/Off Key state*/
	if(!(wm_TkStatus & TK6))
    {
    	 wm_IsTk6Released = TRUE;
    }
	
    /* Process IR Gesture */
    wm_ProcessIrGesture();
    
    /* Handle 7-Segment Display Time Activity */
    wm_HandleTimeActivity();
    
    /* Send Serial cmd to Peripheral controller*/	
	wm_TransmitSerialCMD();
    
    #ifdef DEBUG_UART
    if(!sendflag) {
        print_u32(wm_UiDisTimeOutCnt);
    }
    #endif
}
