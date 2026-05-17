/**
 ******************************************************************************
 * @file    sc92f_uart2.c
 * @author  SOC AE Team
 * @version V1.2.1
 * @date    2025-07-24
 * @brief   UART2 function module
 *******************************************************************************
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
 
/* Includes ------------------------------------------------------------------*/
#include "sc92f_uart2.h"

#if defined (SC92F652x)
/** @addtogroup sc92f_StdPeriph_Driver
 * @{
 */

/** @defgroup UART2
 * @brief UART2 driver modules
 * @{
 */

/** @defgroup UART2_Functions
 * @{
 */
 
/** @defgroup UART2_Group1 Configuration of the UART2 computation unit functions
 *  @brief   Configuration of the UART2 computation unit functions
 *
 
@verbatim
 ===============================================================================
                     ##### UART2 configuration functions #####
 ===============================================================================
@endverbatim
  * @{
  */
 
 /**
 * @brief  UART2相关寄存器复位至缺省值
 * @param  None
 * @retval None
 */ 
void UART2_DeInit(void)
{
  U2SCON = 0X00;
  IE &= 0XDF;
  IP &= 0XDF;
}

/**
 * @brief  UART2初始化配置函数
 * @param  Uart2Fsys[in]:系统时钟频率
 * @param  BaudRate[in]:波特率
 * @param  Mode[in]:工作模式
 *          - UART2_Mode_10B:UART2工作模式:10位全双工
 *          - UART2_Mode_11B:UART2工作模式:11位全双工
 * @param  RxMode[in]:接收允许选择
 *          - UART2_RX_ENABLE:允许接收数据
 *          - UART2_RX_DISABLE:不允许接收数据
 * @retval None
 */
void UART2_Init(uint32_t Uart2Fsys, 
								uint32_t BaudRate,
                UART2_Mode_Typedef Mode,
                UART2_RX_Typedef RxMode)
{
	U2SCON  = (U2SCON & 0X2F) | Mode | RxMode;	//设置UART工作模式,设置接收允许位

	/* 配置UART2波特率 */
	U2BAUDH = (Uart2Fsys / BaudRate) / 256;
	U2BAUDL = (Uart2Fsys / BaudRate) % 256;
}

/**
 * @}
 */
/* End of UART2_Group1.	*/

/** @defgroup UART2_Group2 Base functions
 *  @brief   UART2 functions
 *
@verbatim
 ===============================================================================
                     ##### Base functions #####
 ===============================================================================
@endverbatim
  * @{
  */


/**
 * @brief  UART2发送8位数据
 * @param  Data[in]:UART2发送8位数据
 * @retval None
 */
void UART2_SendData8(uint8_t Data)
{
  U2SBUF = Data;
}

/**
 * @brief  获得SBUF中的值
 * @param  None
 * @retval UART接收到的8位数据
 */
uint8_t UART2_ReceiveData8(void)
{
  return U2SBUF;
}

/**
 * @brief  UART2发送9位数据
 * @param  Data[in]:发送的数据
 * @retval None
 */
void UART2_SendData9(uint16_t Data)
{
  uint8_t Data_9Bit;
  Data_9Bit = (Data >> 8);

  if(Data_9Bit)
  {
    U2SCON |= 0X08;
  }
  else
  {
    U2SCON &= 0XF7;
  }

  U2SBUF = (uint8_t)Data;
}

/**
 * @brief  获得SBUF中的值及第九位的值
 * @param  None
 * @retval UART接收到的数据
 */
uint16_t UART2_ReceiveData9(void)
{
  uint16_t Data9;
  Data9 =  U2SBUF + ((uint16_t)(U2SCON & 0X04) << 6);
  U2SCON &= 0XFB;
  return Data9;
}

/**
 * @brief  UART在轮询模式下发送大量数据
 * @param  UART_HANDLE[out]:指向包含指定UART模块的配置信息结构体的指针
 * @param  pData[out]:接收数据的存放区
 * @param  Size[in]:待接收的数据量
 * @param  timeout[in]:超时时间设置
 * @retval SSI 状态
 *          - Status_ERROR:错误
 *          - Status_OK:正常
 *          - Status_BUSY:正忙
 *          - Status_TIMEOUT:超时
 */
StatusTypeDef UART2_Transmit(UART2_HandleInfoDef* UART_HANDLE, uint8_t* pData, uint8_t Size, uint32_t Timeout)
{
    uint32_t TimeoutCnt;
    /* 检查一个发送进程是否正在进行 */
    if (UART_HANDLE->TxState == UART2_STATE_READY)
    {
        /* 待发送数据长度必须大于0，否则返回错误状态 */
        if (Size == 0U)
        {
            return  Status_ERROR;
        }

        UART_HANDLE->TxState = UART2_STATE_BUSY;			//发送进程忙碌中
				UART2_ClearFlag(UART2_FLAG_TI); //发送前清除发送标志,写1清0
        UART_HANDLE->pTxBuffPtr.Size_u8 = pData;			//指向待发送数据的地址
        UART_HANDLE->TxXferSize = Size;			//更新待发送的数据量
        UART_HANDLE->TxXferCount = 0;			//发送计数器清零

        while (UART_HANDLE->TxXferCount < UART_HANDLE->TxXferSize)//判断是否接收所有数据
        {
            if (U2SCON & 0x80 == UART2_Mode_11B)
            {
                U2SCON &= ~0x08;
                U2SCON |= (*(UART_HANDLE->pTxBuffPtr.Size_u16 + UART_HANDLE->TxXferCount) >> 5);//设置第9位校验位
                U2SBUF = *(UART_HANDLE->pTxBuffPtr.Size_u16 + UART_HANDLE->TxXferCount);
            }
            else
            {
                U2SBUF = *(UART_HANDLE->pTxBuffPtr.Size_u8 + UART_HANDLE->TxXferCount);
            }

            while (!(UART2_GetFlagStatus(UART2_FLAG_TI))) //等待发送完成
            {
                if (TimeoutCnt++ > Timeout)
                {
                    UART_HANDLE->TxState = UART2_STATE_TIMEOUT;//发送超时
                    return Status_TIMEOUT;
                }
                WDTCON |= 0x10;;          //喂狗函数，防止看门狗复位
            }

            UART2_ClearFlag(UART2_FLAG_TI); //发送中断标志清除，写1清零
            TimeoutCnt = 0;
            UART_HANDLE->TxXferCount++;	//发送数据量计数
        }

        if (UART_HANDLE->TxXferCount == UART_HANDLE->TxXferSize)
        {
            UART_HANDLE->TxState = UART2_STATE_READY;	//发送完成
            return Status_OK;
        }
        else
        {
            UART_HANDLE->TxState = UART2_STATE_ERROR;//发生发送错误
            return Status_ERROR;
        }
    }
    else
    {
        return Status_BUSY;//返回忙碌状态
    }
}

/**
 * @brief  UART在中断模式下发送大量数据时，先在main函数中调用此函数
 * @param  UART_HANDLE[out]:指针指向UART数据信息存放区
 * @param  pData[out]:接收数据的存放区
 * @param  Size[in]:待接收的数据量
 * @param  timeout[in]:超时时间设置
 * @retval 函数执行状态
 *          - Status_ERROR:错误
 *          - Status_OK:正常
 *          - Status_BUSY:正忙
 *          - Status_TIMEOUT:超时
 */
StatusTypeDef UART2_Transmit_IT(UART2_HandleInfoDef* UART_HANDLE, uint8_t* pData, uint8_t Size)
{
    /* 检查一个发送进程是否正在进行 */
    if (UART_HANDLE->TxState == UART2_STATE_READY)
    {
        /* 没有开启UART2中断或发送数据量大小为0，返回错误 */
        if ((IE1&0x20 == 0) || (UART_HANDLE->TxXferSize == 0U))
        {
            return Status_ERROR;
        }

        UART_HANDLE->TxState = UART2_STATE_BUSY;			//发送进程忙碌中
        UART2_ClearFlag(UART2_FLAG_TI);  //发送前清除发送标志,写1清0
        UART_HANDLE->pTxBuffPtr.Size_u8 = pData;			//指向待发送数据的地址
        UART_HANDLE->TxXferSize = Size;			//更新待发送的数据量
        UART_HANDLE->TxXferCount = 0;			//发送计数器清零


        /* 发送第1帧数据 */
        if (U2SCON & 0x80 == UART2_Mode_11B)
        {
            U2SCON |= (*(UART_HANDLE->pTxBuffPtr.Size_u16 + UART_HANDLE->TxXferCount) >> 5) & 0x08;//设置第9位校验位
            U2SBUF = *(UART_HANDLE->pTxBuffPtr.Size_u16 + UART_HANDLE->TxXferCount);
        }
        else
        {
            U2SBUF = *(UART_HANDLE->pTxBuffPtr.Size_u8 + UART_HANDLE->TxXferCount);
        }
        return Status_OK;
    }
    else
    {
        return Status_BUSY;//返回标志位
    }
}

/**
 * @brief  UART在中断模式下发送大量数据时，在中断服务函数中调用
 * @param  UART_HANDLE[out]:指向包含指定UART模块的配置信息结构体的指针
 * @retval 函数执行状态
 *          - Status_ERROR:错误
 *          - Status_OK:正常
 *          - Status_BUSY:正忙
 *          - Status_TIMEOUT:超时
 */
StatusTypeDef UART2_Transmit_IRQHandler(UART2_HandleInfoDef* UART_HANDLE)
{
    /* 处于发送线程 */
    if (UART_HANDLE->TxState == UART2_STATE_BUSY)
    {
        UART_HANDLE->TxXferCount++;
        /* 判断上一次发送是否是最后一次 */
        if (UART_HANDLE->TxXferCount < UART_HANDLE->TxXferSize)
        {
            /* 待发送数据量未为0，继续发送 */
            if (U2SCON & 0x80 == UART2_Mode_11B)
            {
                U2SCON |= (*(UART_HANDLE->pTxBuffPtr.Size_u16 + UART_HANDLE->TxXferCount) >> 5) & 0x08;//设置第9位校验位
                U2SBUF = *(UART_HANDLE->pTxBuffPtr.Size_u16 + UART_HANDLE->TxXferCount);
            }
            else
            {
                U2SBUF = *(UART_HANDLE->pTxBuffPtr.Size_u8 + UART_HANDLE->TxXferCount);
            }
            return Status_BUSY;
        }
        else if (UART_HANDLE->TxXferCount == UART_HANDLE->TxXferSize)
        {
            /* 发送完成 */
            UART_HANDLE->TxState = UART2_STATE_READY;
            return Status_OK;
        }
        else
        {
            /* 发送数据量为0时还发送数据，返回错误 */
            UART_HANDLE->TxState = UART2_STATE_ERROR;
            return Status_ERROR;
        }
    }
    else
    {
        return Status_ERROR;
    }
}

/**
 * @brief  UART在轮询模式下接收大量数据
 * @param  UART_HANDLE[out]:指针指向UART数据信息存放区
 * @param  pData[out]:接收数据的存放区
 * @param  Size[in]:待接收的数据量
 * @param  timeout[in]:超时时间设置
 * @retval 函数执行状态
 *          - Status_ERROR:错误
 *          - Status_OK:正常
 *          - Status_BUSY:正忙
 *          - Status_TIMEOUT:超时
 */
StatusTypeDef UART2_Receive(UART2_HandleInfoDef* UART_HANDLE, uint8_t* pData, uint8_t Size, uint32_t Timeout)
{
    uint32_t TimeoutCnt = 0;
    /* 检查接收进程正在运行 */
    if (UART_HANDLE->RxState == UART2_STATE_READY)
    {
        /* 检查接收数据量大小和是否开启接收使能 */
        if ((UART_HANDLE->RxXferSize == 0U) || ((U2SCON & 0x10) == UART2_RX_ENABLE))
        {
            return  Status_ERROR;
        }

        UART_HANDLE->RxState = UART2_STATE_BUSY;			//状态更新为接收忙碌中
        UART2_ClearFlag(UART2_FLAG_RI);			 //接收前清除接收中断标志
        UART_HANDLE->pRxBuffPtr.Size_u8 = pData;			//指向待发送数据的地址
        UART_HANDLE->RxXferSize = Size;			//更新待发送的数据量
        UART_HANDLE->RxXferCount = 0;			//发送计数器清零

        while (UART_HANDLE->RxXferCount < UART_HANDLE->RxXferSize) //判断是否接收所有数据
        {
            if (UART2_GetFlagStatus(UART2_FLAG_RI)) //判断接收标志位
            {
                if (U2SCON & 0x80 == UART2_Mode_11B)
                {
                    *(UART_HANDLE->pRxBuffPtr.Size_u16 + UART_HANDLE->RxXferCount) = U2SBUF + ((uint16_t)(U2SCON & 0X04) << 6); //接收数据
                }
                else
                {
                    *(UART_HANDLE->pRxBuffPtr.Size_u8 + UART_HANDLE->RxXferCount) = U2SBUF;			//接收数据
                }
                UART2_ClearFlag(UART2_FLAG_RI);			//接收标志位清零
                UART_HANDLE->RxXferCount++;	//接收数据量计数加1
                TimeoutCnt = 0;//收到数据，超时计数清零
            }
            else
            {
                if (TimeoutCnt++ > Timeout)//计时溢出
                {
                    UART_HANDLE->RxState = UART2_STATE_TIMEOUT;//发送超时
                    return Status_TIMEOUT;
                }
                WDTCON |= 0x10;;			//喂狗，防止等待时间过长，导致WDT复位
            }
        }

        if (UART_HANDLE->RxXferCount == UART_HANDLE->RxXferSize)
        {
            UART_HANDLE->RxState = UART2_STATE_READY;	//接收完成
            return Status_OK;
        }
        else
        {
            UART_HANDLE->RxState = UART2_STATE_ERROR;//接收错误
            return Status_ERROR;
        }
    }
    else
    {
        return Status_BUSY;//返回标志位
    }
}

/**
 * @brief  UART在中断模式下接收大量数据时，先在main函数中调用此函数
 * @param  UART_HANDLE[out]:指针指向UART数据信息存放区
 * @param  pData[out]:接收数据的存放区
 * @param  Size[in]:待接收的数据量
 * @retval 函数执行状态
 *          - Status_ERROR:错误
 *          - Status_OK:正常
 *          - Status_BUSY:正忙
 *          - Status_TIMEOUT:超时
 */
StatusTypeDef UART2_Receive_IT(UART2_HandleInfoDef* UART_HANDLE, uint8_t* pData, uint8_t Size)
{
    /* 检查一个接收进程是否正在进行 */
    if (UART_HANDLE->RxState == UART2_STATE_READY)
    {
        /* 检查是否开启UART2中断或发送数据量大小为0或是否开启接收使能，返回错误 */
        if ((IE1&0x20 == 0) || (Size == 0U) || ((U2SCON & 0x10) == UART2_RX_ENABLE))
        {
            return UART2_STATE_ERROR;
        }

        UART_HANDLE->RxState = UART2_STATE_BUSY;
        UART_HANDLE->pRxBuffPtr.Size_u8 = pData;			//指向接收数据的存放地址
        UART_HANDLE->RxXferSize = Size;			//更新待接收的数据量
        UART_HANDLE->RxXferCount = 0;			//发送计数器清零

        return Status_OK;
    }
    else
    {
        return Status_BUSY;//返回标志位
    }
}

/**
 * @brief  UART在中断模式下接收大量数据时，在中断服务函数中调用 注：该函数调用需要判断中断标志位是否置起
 * @param  UART_HANDLE[out]:指针指向SSI数据信息存放区
 * @retval 函数执行状态
 *          - Status_ERROR:错误
 *          - Status_OK:正常
 *          - Status_BUSY:正忙
 *          - Status_TIMEOUT:超时
 */
StatusTypeDef UART2_Receive_IRQHandler(UART2_HandleInfoDef* UART_HANDLE)
{
    /* 检查一个接收进程是否正在进行 */
    if (UART_HANDLE->RxState == UART2_STATE_BUSY)
    {
        /* 处于接收线程，检查待接收数据量是否为0 */
        if (UART_HANDLE->RxXferCount < UART_HANDLE->RxXferSize)
        {
            if (U2SCON & 0x80 == UART2_Mode_11B)
            {
                *(UART_HANDLE->pRxBuffPtr.Size_u16 + UART_HANDLE->RxXferCount) = U2SBUF + ((uint16_t)(U2SCON & 0X04) << 6); //接收数据
            }
            else
            {
                *(UART_HANDLE->pRxBuffPtr.Size_u8 + UART_HANDLE->RxXferCount) = U2SBUF;			//接收数据
            }
            UART_HANDLE->RxXferCount++;
            /* 判断上一次发送是否是最后一次 */
            if (UART_HANDLE->RxXferCount == UART_HANDLE->RxXferSize)
            {
                /* 接收完成 */
                UART_HANDLE->RxState = UART2_STATE_READY;
                return Status_OK;
						}
            return Status_BUSY;
        }
        else
        {
            /* 接收数据量为0时还接收数据，返回错误 */
            UART_HANDLE->RxState = UART2_STATE_ERROR;
            return Status_ERROR;
        }
    }
    else
    {
        return Status_BUSY;
    }
}
/**
 * @}
 */
/* End of UART2_Group2.	*/

/** @defgroup UART2_Group3 Interrupts and flags management functions
 *  @brief   Interrupts and flags management functions
 *
@verbatim
 ===============================================================================
                     ##### Interrupts and flags management functions #####
 ===============================================================================
@endverbatim
  * @{
  */

/**
 * @brief  UART2中断初始化
 * @param  NewState[in]: 断使能/关闭选择
 *              - DISABLE:关闭
 *              - ENABLE:使能
 * @param  Priority[in]: 中断优先级选择
 *              - LOW:低
 *              - HIGH:高
 * @retval None
 */ 
void UART2_ITConfig(FunctionalState NewState,
                    PriorityStatus Priority)
{
  if(NewState == DISABLE)
  {
    IE1 &= 0XDF;
  }
  else
  {
    IE1 |= 0X20;
  }

  //设置中断优先级
  if(Priority == LOW)
  {
    IP1 &= 0XDF;
  }
  else
  {
    IP1 |= 0X20;
  }
}
/**
 * @}
 */
/* End of UART2_Group3.	*/

#endif
/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */
/******************* (C) COPYRIGHT 2025 SinOne Microelectronics *****END OF FILE****/