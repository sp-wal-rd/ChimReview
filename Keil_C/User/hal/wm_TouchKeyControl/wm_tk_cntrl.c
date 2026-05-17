/**
  ******************************************************************************
  * @file    wm_tk_ctrl.c
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

#include "..\Drivers\SCDriver_list.h"
#include "wm_global.h"

bit wm_IsTkScanRoundFinished = FALSE;

bit wm_IsTk1Released = TRUE;
bit wm_IsTk2Released = TRUE;
bit wm_IsTk3Released = TRUE;
bit wm_IsTk4Released = TRUE;
bit wm_IsTk6Released = TRUE;

unsigned long wm_TkStatus = 0;

void wm_sys_tk_scan(void)
{
        if(SOCAPI_TouchKeyStatus & 0x80)
        {
			wm_IsTkScanRoundFinished = TRUE;
            SOCAPI_TouchKeyStatus &= 0x7f;

            wm_TkStatus = TouchKeyScan();


            TouchKeyRestart();
            
        }
}
