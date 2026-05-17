/**
  ******************************************************************************
  * @file    wm_extern_fnc.h
  * @brief   External function calls.
  * @author  Walnut Medical
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024  Walnut Medical
  * All rights reserved.
  *
  ******************************************************************************
  */
#ifndef __WM_EXTERN_FNC_H__
#define __WM_EXTERN_FNC_H__

#include <sc92f_int.h>
/*StateFlow Task*/



/* Sys Init */
extern void IcResourceInit();

/* Timer control */
extern void TIM1_Interrupt(void);

/* Uart control */
extern char* u32_to_str(char *buf, uint32_t v);
extern void print_u32(uint32_t x);

/*Touch Key */
extern void wm_sys_tk_scan(void);

#endif
