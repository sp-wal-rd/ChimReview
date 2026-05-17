/**
 ******************************************************************************
 * @file    CRC_Option_EW.h
 * @author  SOC AE Team
 * @version V1.2.0
 * @date    2025-05-20
 * @brief   Header file of CRC lib module.
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
 *  COPYRIGHT 2024 SinOne Microelectronics
 */
 /* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _CRC_OPTION_EW_H_
#define	_CRC_OPTION_EW_H_

/** @addtogroup CRC_Option_Functions CRC_Option Functions
 * @{
 */
#if !defined(SC92L840x)
unsigned long CRC_CodeAllOption(void);  /*!< 计算Code区域的CRC检验值 */ 
#endif
void CRC_ResetDROption(void);   /*!< CRCDR寄存器复位 */ 
void CRC_CalcOption(unsigned char Data);
unsigned long CRC_GetOption(void);      /*!< 获取CRC校验值 */ 
/**
 * @}
 */
/* End of functions --------------------------------------------------*/
#endif
/**
 * @}
 */
 
/**
 * @}
 */
/******************* (C) COPYRIGHT 2024 SinOne Microelectronics *****END OF FILE****/