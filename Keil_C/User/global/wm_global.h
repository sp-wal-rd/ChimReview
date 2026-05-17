/**
  ******************************************************************************
  * @file    wm_global.h
  * @author  Walnut Medical
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 Walnut Medical
  * All rights reserved.
  *
  ******************************************************************************
  */

#ifndef __WM_GLOBAL_H__
#define __WM_GLOBAL_H__

#include "sc92f_gpio.h"
#include "SC_Init.h"
#include "global\wm_extern_fnc.h"
#include "global\wm_enum.h"
#include "hal\wm_TouchKeyControl\wm_tk_cntrl.h"
#include "stateflow\wm_state_flow.h"
#include "hal\wm_gpio_map\wm_gpio_map.h"
#include "hal\wm_led_control\wm_led_cntrl.h"
#include "hal\wm_7seg_control\wm_7seg_control.h"
#include "hal\wm_uart\wm_uart.h"

/* Uart cmd Byte Index*/
#define WM_HEATER_INDX 4       // Heater on/off bit
#define WM_KL_INDX 5           // Kitchen Light
#define WM_UI_EN_DIS_INDX 6    // Board En/Dis
#define WM_RESERVE_BIT_INDX 7  

#define WM_MINUTE_IN_MS ((uint32_t)(60000))
#define WM_UI_DIS_TIMEOUT  ((uint32_t)(180000))  //ms
#define WM_HEATER_TIMEOUT  ((uint32_t)(600000)) //ms
#define WM_HTK_LONGPRESS_TIMEOUT (2000) //ms
#define WM_SERIAL_CMD_TIMEOUT (500)
#define WM_IR_DEBOUNCE_TIMEOUT (10)
#define WM_ON_STARTUP_CNT (1000)


extern bit wm_IsHkReleased;
extern bit wm_IsHeaterEnRequested;
extern bit wm_HeaterKeyPressed;
extern bit wm_HeaterKeyLongPressed;
extern bit wm_HeaterKeyDelayChk;
extern bit wm_HeaterEnabled;
extern bit wm_IsReconfigTime;

extern bit wm_InitialBootUp;


extern bit wm_IsHtDisFanEnReq;
extern uint8_t wm_cmdByte;
extern bit wm_HeaterState ;
extern bit wm_KitchenLightState;
extern bit wm_UiBoardState;
extern bit wm_FanState;
extern bit wm_ReservedBitState;

extern volatile bit wm_EnGestureProcessing;
extern bit wm_rightSwipeInit ;
extern bit wm_rightSwipe;
extern bit wm_LeftSwipeInit;
extern bit wm_LeftSwipe;

extern bit wm_IsSleepModeRequested;
extern bit wm_IsUiDisableRequested;
extern volatile uint32_t wm_UiDisTimeOutCnt;
extern volatile uint16_t wm_IrDelayCnt;
extern volatile uint16_t wm_IrGeastureTimeOutCnt;
extern volatile uint32_t wm_DelayCnt;
extern volatile uint32_t wm_HeaterDelayCnt;
extern volatile uint16_t wm_HeaterLongPressCnt;
extern volatile uint16_t wm_SerialCmdTimeOutCnt;
extern volatile uint16_t wm_TkDelayCnt;
extern volatile uint16_t wm_GeneralCnt;
extern volatile uint16_t wm_LedDelayCnt;
extern volatile uint16_t wm_IrEnCnt;
extern volatile uint16_t wm_WdtTimOutCnt;

extern bit wm_En38khzfreq;

extern uint8_t wm_FanSpeed;

/* Externs */


/*  Extern Functions*/

extern void wm_DelayMS(uint16_t Delay);
extern void wm_OnStartUp();
extern void wm_ProcessIrGesture();

extern void wm_HandleTimeActivity();


extern void wm_SleepFromGesture(uint16_t ms);

#endif
