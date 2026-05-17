/**
  ******************************************************************************
  * @file    wm_gpio_map.h
  * @author  Walnut Medical
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 Walnut Medical
  * All rights reserved.
  *
  ******************************************************************************
  */
  
#ifndef _WM_UART_H_
#define _WM_UART_H_


#include "wm_global.h" 

//<<<Use SPTML>>>
#define RXD P16 //RXD 
#define RXD_INIT 0x0140 //RXD_INIT 
#define TXD P12 //TXD 
#define TXD_INIT 0x0104 //TXD_INIT 
#define Fhrc 32 //Fhrc 
#define UART_USE 0 //UART_USE 
#define UART_BAUD 9600 //UART_BAUD 
#define UART_INTselect 0 //UART_INTselect 
#define RecedataLength 20 //RecedataLength 
extern u8 ReceCount;
extern bit sendflag;
extern u8 Recedata[RecedataLength];
extern void UART_Timer0_Load();
extern void UART_Pwm_Load();
extern void UART_INT_Load();
extern void Uart_init();
extern void Uart_SendString(u8 *str,u8 strlen);
//<<<end of SPTML>>>


//**************ò???2??éDT??**********************//
#define  IO_NULL 		   0xFF00//??éè??
#define  SCD_IO_PORT(IO)    (uint8_t)(IO>>8)
#define  SCD_IO_PIN(IO)	    (uint8_t)(IO)
#define LOAD (52)

void SCD_NT_PinMode(unsigned int IO_Pxx, GPIO_Mode_TypeDef IO_Pxx_Mode);	    //IO?úéè??o¯êy
void UART_INT_Init(void);														//ía2??D??3?ê??¯
void UART_INT_DeInit(void);														//1?±?ía2??D??
void Uart_ReceByte(void);														//uart?óê?ò?bit
void Uart_SendByte(void);														//uart·??íò?bit


// extern
extern void wm_TransmitSerialCMD();


								
#endif
