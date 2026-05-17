/**
 ******************************************************************************
 * @file    sc92f_timer3.h
 * @author  SOC AE Team
 * @version V1.2.1
 * @date    2025-07-24
 * @brief   Header file of TIMER3 module.
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
#ifndef _sc92f_TIMER3_H_
#define _sc92f_TIMER3_H_

/* Includes ------------------------------------------------------------------*/
#include "sc92f.H"

/** @addtogroup sc92f_StdPeriph_Driver
 * @{
 */

/** @addtogroup TIMER3
 * @{
 */
 
/** @defgroup TIMER3_Enumerations
 * @{
 */
#if defined(SC92F84Hx) || defined(SC92F83Hx)
/** @brief TIM3_PinSelection_TypeDef TIM3 PinSelection
 * @{
 */
typedef enum
{
  TIM3_PinRemap_Default = (uint8_t)0x00, /*!< TIM3引脚为默认引脚 */
  TIM3_PinRemap_A = (uint8_t)0x10,       /*!< TIM3引脚为A组引脚 */
} TIM3_PinSelection_TypeDef;
/**
 * @}
 */
void TIM3_PinSelection(TIM3_PinSelection_TypeDef PinSeletion);
#endif
/** @brief TIM3_PresSel_TypeDef TIM3 Prescaler
 * @{
 */
typedef enum
{
  TIM3_PRESSEL_FSYS_D12 = ((uint8_t)0x00), /*!< TIMER3计数源来自系统时钟12分频 */
  TIM3_PRESSEL_FSYS_D1 = ((uint8_t)0x01)   /*!< TIMER3计数源来自系统时钟1分频 */
} TIM3_PresSel_TypeDef;
/**
 * @}
 */

/** @brief TIM3_CountMode_TypeDef TIM3 Count Mode
 * @{
 */
typedef enum
{
  TIM3_MODE_TIMER = ((uint8_t)0x01),  /*!< TIMER3做定时器 */
  TIM3_MODE_COUNTER = ((uint8_t)0x02) /*!< TIMER3做计数器 */
} TIM3_CountMode_TypeDef;
/**
 * @}
 */

/** @brief TIM3_CountDirection_TypeDef TIM3 CountDirection
 * @{
 */
typedef enum
{
  TIM3_COUNTDIRECTION_UP = ((uint8_t)0x00),     /*!< 向上计数模式 */
  TIM3_COUNTDIRECTION_DOWN_UP = ((uint8_t)0x10) /*!< 向上/向下计数模式 */
} TIM3_CountDirection_TypeDef;
/**
 * @}
 */

/** @brief TIM3_Flag_TypeDef TIM3 Flag
 * @{
 */
typedef enum
{
  TIM3_FLAG_TF3 = (uint8_t)0x80, /*!< 中断标志位TF3 */
  TIM3_FLAG_EXF3 = (uint8_t)0x40 /*!< 中断标志位EXF3 */
} TIM3_Flag_TypeDef;
/**
 * @}
 */

/** @brief TIM3_WorkMode_TypeDef TIM3 WorkMode
 * @{
 */
typedef enum
{
  TIM3_WORK_MODE0 = ((uint8_t)0x00), /*!< TIMER3选择工作模式0 */
  TIM3_WORK_MODE1 = ((uint8_t)0x01), /*!< TIMER3选择工作模式1 */
  TIM3_WORK_MODE3 = ((uint8_t)0x03), /*!< TIMER3选择工作模式3 */
} TIM3_WorkMode_TypeDef;
/**
 * @}
 */
/**
 * @}
 */
/* End of enumerations -----------------------------------------------------*/

/** @addtogroup TIM3_Functions TIM3 Functions
 * @{
 */
/* Initialization and Configuration functions ***********************************************/
void TIM3_DeInit();
void TIM3_PrescalerSelection(TIM3_PresSel_TypeDef TIM3_PrescalerSelection);
void TIM3_WorkMode1Config(uint16_t TIM3_SetCounter);
void TIM3_Cmd(FunctionalState NewState);
void TIM3_ITConfig(FunctionalState NewState, PriorityStatus Priority);
FlagStatus TIM3_GetFlagStatus(TIM3_Flag_TypeDef TIM3_Flag);
void TIM3_ClearFlag(TIM3_Flag_TypeDef TIM3_Flag);

void TIM3_TimeBaseInit(TIM3_PresSel_TypeDef TIM3_PrescalerSelection,TIM3_CountMode_TypeDef TIM3_CountMode,
                       TIM3_CountDirection_TypeDef TIM3_CountDirection);
void TIM3_WorkMode0Config(uint16_t TIM3_SetCounter);
void TIM3_WorkMode3Config(uint16_t TIM3_SetCounter);
void TIM3_WorkModeConfig(TIM3_WorkMode_TypeDef TIM3_WorkMode, uint16_t TIM3_SetCounter);
void TIM3_SetEXEN3(FunctionalState NewState);
/**
 * @}
 */
/* End of exported functions --------------------------------------------------*/
/**
 * @}
 */

/**
 * @}
 */

#endif
/******************* (C) COPYRIGHT 2025 SinOne Microelectronics *****END OF FILE****/