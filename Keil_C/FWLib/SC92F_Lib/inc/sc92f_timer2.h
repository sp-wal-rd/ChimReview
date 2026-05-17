/**
 ******************************************************************************
 * @file    sc92f_timer2.h
 * @author  SOC AE Team
 * @version V1.2.1
 * @date    2025-07-24
 * @brief   Header file of TIMER2 module.
 ******************************************************************************
 * @attention
 *
 *1.This software is supplied by SinOne Microelectronics Co.,Ltd. and is only 
 *intended for use with SinOne products. No other uses are authorized. This 
 *software is owned by SinOne Microelectronics Co.,Ltd. and is protected under 
 *all applicable laws, including copyright laws. 
 *2.The software which is for guidance only aims at providing customers with 
 *coding information regarding their products in order for them to save time. 
 *As a result, SinOne shall not be held liable for any direct, indirect or 
 *consequential damages with respect to any claims arising from the content of 
 *such software and/or the use made by customers of the coding information 
 *contained herein in connection with their products.
 *
 *  COPYRIGHT 2025 SinOne Microelectronics
 ******************************************************************************
 */
 
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _sc92f_TIMER2_H_
#define	_sc92f_TIMER2_H_

/* Includes ------------------------------------------------------------------*/
#include "sc92f.h"

/** @addtogroup sc92f_StdPeriph_Driver
 * @{
 */

/** @addtogroup TIMER2
 * @{
 */
 
/** @defgroup TIMER2_Enumerations
 * @{
 */
 
 /** @brief TIM2_PresSel_TypeDef TIM2 Prescaler
 * @{
 */
typedef enum
{
  TIM2_PRESSEL_FSYS_D12  = ((uint8_t)0x00), /*!< TIMER2计数源来自系统时钟12分频 */
  TIM2_PRESSEL_FSYS_D1   = ((uint8_t)0x01)  /*!< TIMER2计数源来自系统时钟 */
} TIM2_PresSel_TypeDef;
/**
 * @}
 */

#if defined (SC92F730x) || defined (SC92F827X) || defined (SC92F837X) || defined (SC92F725X) || defined(SC92F735X) || defined(SC92F730x_2) || defined(SC92F720x) \
|| defined (SC92F7308B)
/** @brief TIM2_CountMode_TypeDef TIM2 Count Mode
 * @{
 */
typedef enum
{
  TIM2_MODE_TIMER   = ((uint8_t)0x01), /*!< TIMER2做定时器 */
} TIM2_CountMode_TypeDef;
/**
 * @}
 */

/** @brief TIM2_CountDirection_TypeDef TIM CountDirection
 * @{
 */
typedef enum
{
  TIM2_COUNTDIRECTION_UP       = ((uint8_t)0x00),  /*!< 向上计数模式 */
} TIM2_CountDirection_TypeDef;
/**
 * @}
 */

/** @brief TIM2_Flag_TypeDef TIM2 Flag
 * @{
 */
typedef enum
{
  TIM2_FLAG_TF2   = (uint8_t)0x80, 	   /*!< 中断标志位TF2，计数溢出 */
} TIM2_Flag_TypeDef;
/**
 * @}
 */

/** @brief TIM2_WorkMode_TypeDef TIM2 WorkMode
 * @{
 */
typedef enum
{
  TIM2_WORK_MODE1   = ((uint8_t)0x00),		/*!< TIMER2选择工作模式1 */
} TIM2_WorkMode_TypeDef;
/**
 * @}
 */
#else
/** @brief TIM2_CountMode_TypeDef TIM2 Count Mode
 * @{
 */
typedef enum
{
  TIM2_MODE_TIMER   = ((uint8_t)0x01), /*!< TIMER2做定时器 */
  TIM2_MODE_COUNTER = ((uint8_t)0x02)  /*!< TIMER2做计数器 */
} TIM2_CountMode_TypeDef;
/**
 * @}
 */

/** @brief TIM_WorkMode TIM WorkMode
 * @{
 */
typedef enum
{
  TIM2_COUNTDIRECTION_UP  		 = ((uint8_t)0x00),  /*!< 向上计数模式 */
  TIM2_COUNTDIRECTION_DOWN_UP  = ((uint8_t)0x10)    /*!< 向上/向下计数模式 */
} TIM2_CountDirection_TypeDef;
/**
 * @}
 */

/** @brief TIM2_Flag_TypeDef TIM2 Flag
 * @{
 */
typedef enum
{
  TIM2_FLAG_TF2   = (uint8_t)0x80, 	   /*!< 中断标志位TF2，计数溢出 */
  TIM2_FLAG_EXF2  = (uint8_t)0x40 	   /*!< 中断标志位EXF2，外部触发 */
} TIM2_Flag_TypeDef;
/**
 * @}
 */

/** @brief TIM2_WorkMode_TypeDef TIM2 WorkMode
 * @{
 */
typedef enum
{
  TIM2_WORK_MODE0   = ((uint8_t)0x00),		/*!< TIMER2选择工作模式0 */
  TIM2_WORK_MODE1   = ((uint8_t)0x01),		/*!< TIMER2选择工作模式1 */
  TIM2_WORK_MODE3   = ((uint8_t)0x03),		/*!< TIMER2选择工作模式3 */
} TIM2_WorkMode_TypeDef;
/**
 * @}
 */
#endif

#if defined(SC92F84Hx) || defined(SC92F83Hx)
/** @brief TIM2_PinSelection_TypeDef TIM2 PinSelection
 * @{
 */
typedef enum
{
  TIM2_PinRemap_Default = (uint8_t)0x00, /*!< TIM2引脚为默认引脚 */
  TIM2_PinRemap_A = (uint8_t)0x04,       /*!< TIM2引脚为A组引脚 */
} TIM2_PinSelection_TypeDef;
/**
 * @}
 */
void TIM2_PinSelection(TIM2_PinSelection_TypeDef PinSeletion);
#endif
/**
 * @}
 */
/* End of enumerations -----------------------------------------------------*/

/** @addtogroup TIM2_Functions TIM2 Functions
 * @{
 */
/* Initialization and Configuration functions ***********************************************/
void TIM2_DeInit();
void TIM2_PrescalerSelection(TIM2_PresSel_TypeDef TIM2_PrescalerSelection);
void TIM2_TimeBaseInit(TIM2_PresSel_TypeDef TIM2_PrescalerSelection,
                       TIM2_CountMode_TypeDef TIM2_CountMode,
                       TIM2_CountDirection_TypeDef TIM2_CountDirection);
void TIM2_WorkMode0Config(uint16_t TIM2_SetCounter);
void TIM2_WorkMode1Config(uint16_t TIM2_SetCounter);
void TIM2_WorkMode3Config(uint16_t TIM2_SetCounter);
void TIM2_WorkModeConfig(TIM2_WorkMode_TypeDef TIM2_WorkMode, uint16_t TIM2_SetCounter);
/* Time Base functions ********************************************************/
void TIM2_SetEXEN2(FunctionalState NewState);
void TIM2_Cmd(FunctionalState NewState);
/* Interrupt Handler functions  ***********************************************/
void TIM2_ITConfig(FunctionalState NewState, PriorityStatus Priority);
FlagStatus TIM2_GetFlagStatus(TIM2_Flag_TypeDef TIM2_Flag);
void TIM2_ClearFlag(TIM2_Flag_TypeDef TIM2_Flag);
/**
 * @}
 */
/* End of exported functions --------------------------------------------------*/
#endif
/**
 * @}
 */

/**
 * @}
 */
/******************* (C) COPYRIGHT 2025 SinOne Microelectronics *****END OF FILE****/