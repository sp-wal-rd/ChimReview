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
  
#ifndef __WM_TK_CTRL_H__
#define __WM_TK_CTRL_H__
  
extern bit wm_IsTkScanRoundFinished;

extern bit wm_IsTk1Released;
extern bit wm_IsTk2Released;
extern bit wm_IsTk3Released;
extern bit wm_IsTk4Released;
extern bit wm_IsTk6Released;

extern unsigned long wm_TkStatus;

/*  Touch Key config */
#define TK1 0x00040000
#define TK2 0x00000010
#define TK3 0x00000100
#define TK4 0x00001000
#define TK5 0x00000002
#define TK6 0x00000008

#endif
