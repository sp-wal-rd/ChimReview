/**
 ******************************************************************************
 * @file    wm_timed_activity.c
 * @author  Walnut Medical
 * @brief   Source file of timed activity.
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 Walnut Medical
 * All rights reserved.
 *
 ******************************************************************************
 */

#include "wm_global.h"

#define WM_BlinkInterval 512

volatile uint32_t wm_DelayCnt = 0; 
volatile uint16_t wm_IrDelayCnt = 0;
volatile uint16_t wm_IrGeastureTimeOutCnt = 0;
volatile uint32_t wm_UiDisTimeOutCnt = WM_UI_DIS_TIMEOUT;
volatile uint16_t wm_HeaterLongPressCnt = 0;
volatile uint32_t wm_HeaterDelayCnt = 0;
volatile uint16_t wm_SerialCmdTimeOutCnt = 0;
volatile uint16_t wm_TkDelayCnt = 0;
volatile uint16_t wm_GeneralCnt = 0;
//volatile uint16_t wm_IrEnCnt = 0;
volatile uint16_t wm_LedDelayCnt = 0;
volatile uint16_t wm_WdtTimOutCnt = 0;

//bit wm_En38khzfreq = TRUE;

void wm_DelayMS(uint16_t Delay)
{
    wm_DelayCnt = 0;
    while(wm_DelayCnt < Delay);  // < is slightly more efficient than <=
}




void TIM1_Interrupt(void)//1ms tick
{
  wm_DelayCnt++;
  wm_IrDelayCnt++;
  wm_UiDisTimeOutCnt--;
  wm_HeaterDelayCnt--;
  wm_HeaterLongPressCnt++;
  wm_SerialCmdTimeOutCnt++;
  wm_TkDelayCnt++;
  wm_GeneralCnt++;
  //wm_IrEnCnt++;
  wm_LedDelayCnt++;
  wm_IrGeastureTimeOutCnt++;
  wm_WdtTimOutCnt++;
}

void wm_HandleTimeActivity(void)
{
	if(wm_IsUiDisableRequested )
	{
		if(wm_UiDisTimeOutCnt <= WM_UI_DIS_TIMEOUT)
		{
	        
			//wm_LedDelayCnt++;
	 		if(wm_LedDelayCnt >= WM_BlinkInterval) 
	 		{ 
        		TOGGLE_LED(LED_6); 
        		wm_LedDelayCnt = 0; 
        		if(!LED_6)
        			wm_DisplayDigit((uint8_t)(wm_UiDisTimeOutCnt/WM_MINUTE_IN_MS+1));
        		else
        			wm_DisplayOff();
   			}	
	        
		}
		else
		{
			wm_ShutdownUI();
		}
	}
	if(wm_HeaterState)
	{
		if(wm_HeaterDelayCnt <= WM_HEATER_TIMEOUT)
		{
            wm_EnGestureProcessing = FALSE;
			//wm_LedDelayCnt++;
	  		if(wm_LedDelayCnt >= WM_BlinkInterval) 
	  		{ 
      	 		TOGGLE_LED(LED_5); 
        		wm_LedDelayCnt = 0; 
        		if(wm_HeaterDelayCnt > WM_MINUTE_IN_MS)
        		{
       				wm_DisplayDigit((uint8_t)(wm_HeaterDelayCnt/WM_MINUTE_IN_MS));
       		    }
    		}
    		
    		if(wm_HeaterDelayCnt < WM_MINUTE_IN_MS)
    		{
        		if(!LED_5)
       				wm_DisplayDigit((uint8_t)(wm_HeaterDelayCnt/WM_MINUTE_IN_MS));
       			else
       				wm_DisplayOff();
    			wm_FanSpeed = 5;
    			wm_FanState = TRUE;
    			//wm_HeaterState = FALSE;
    			wm_IsHtDisFanEnReq = TRUE;
    		}
    		
		}
		else{
				// Heater timeout - turn off
           	//	wm_HeaterState = FALSE;
            //	wm_TurnOnAllTKLed(0);
            //	wm_DisplayOff();
            	wm_ShutdownUI();
		}
	}
	if(wm_InitialBootUp)
	{
		if(wm_GeneralCnt >= WM_ON_STARTUP_CNT)
		{
			wm_UiBoardState = FALSE;
			wm_ReservedBitState = TRUE;
			wm_InitialBootUp = FALSE;
			wm_TurnOffAllTKLed();
			wm_DisplayOff();

		}
	}
	if(wm_WdtTimOutCnt > 50)
	{
		WDT_SetReload();
		wm_WdtTimOutCnt = 0;
	}
}
