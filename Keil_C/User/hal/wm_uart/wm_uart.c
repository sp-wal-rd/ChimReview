/**
  ******************************************************************************
  * @file    wm_uart.c
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

#include "SC_Init.h"
#include "wm_global.h"


void Uart_SendUnsignedInt(u32 num)
{
    u8 buffer[12];  // Max 10 digits for u32 + null
    u8 i = 0;
    
    if(num == 0)
    {
        buffer[i++] = '0';
    }
    else
    {
        u8 temp[10];
        u8 j = 0;
        
        while(num > 0)
        {
            temp[j++] = (num % 10) + '0';
            num = num / 10;
        }
        
        while(j > 0)
        {
            buffer[i++] = temp[--j];
        }
        buffer[i] = 0x0A;
    }
    
    Uart_SendString(buffer, i+1);
}


void print_u32(uint32_t x) {

	Uart_SendUnsignedInt(x); 
}

void wm_TransmitSerialCMD()
{
	uint8_t i = 0;

	if(wm_SerialCmdTimeOutCnt >= 100)
	{
		bit wm_HeaterBit = (wm_HeaterState && (!wm_IsHtDisFanEnReq));

		wm_cmdByte = (wm_FanSpeed | ((uint8_t)wm_HeaterBit << WM_HEATER_INDX) | ((uint8_t)wm_KitchenLightState << WM_KL_INDX) | ((uint8_t)wm_UiBoardState << WM_UI_EN_DIS_INDX) | ((uint8_t)wm_ReservedBitState << WM_RESERVE_BIT_INDX));

		for (i = 3; i != 0; i--)
		{
			/* 10 ms hard timeout — if a previous send never completed, recover */
			{
				uint16_t t0 = wm_SerialCmdTimeOutCnt;
				while(sendflag)
				{
					if((uint16_t)(wm_SerialCmdTimeOutCnt - t0) >= 10)
					{
						TR0 = 0;
						sendflag = 0;
						break;
					}
				}
			}
			Uart_SendString(&wm_cmdByte, 1);
			wm_DelayMS(5);
		}
		wm_SerialCmdTimeOutCnt = 0;
	}
}
	

//------------------------------------------------------------------------------------

u8    Recedata[RecedataLength]={0};
bit      receflag=0,sendflag=0,startbitflag=0;
u8    THL,TLL;
u8    *senddata;
u8    sendlength=0;
u8    bitdata=0; 
u8    sendbuf=0,recebuf=0,bitcount=0,ReceCount=0,timecount=0; 

/**************************************************
*oˉêy??3??oextern void UART_Timer0_Load()
*oˉêy1|?ü?o?¨ê±?÷?D??'|àíoˉêy
*è??ú2?êy?ovoid
*3??ú2?êy?ovoid
*1|?ü?μ?÷?o?D???'DDoˉêy
**************************************************/
extern void UART_Timer0_Load()
{
	  TH0+=THL;
	  TL0+=TLL;
	  timecount++;	  
	  if(timecount%2==1)				             //??êy'???DD'|àí????êy'?'|àí?óê?ê±??'????úêy?Y?D???áè?
	  {
		// if(timecount==1)							 //μúò?'????D??
		//  {
		//	  if(startbitflag==1)					 
		//	  {
		//		  startbitflag=0;					 //?eê????D??±ê????á?
			//	  bitdata=0;
			  //  if(RXD){bitdata++;}	             //???μ??2¨???áèy'??μ
			 //   _nop_();
			   // _nop_();
			  //  _nop_();
			  //  if(RXD){bitdata++;}
			   // _nop_();
			 //   _nop_();
			//    _nop_();
			 //   if(RXD){bitdata++;}				  
		//	    if(bitdata>>1==0)					//?D???eê?????óDD§?ò??DDêy?Y?óê????TD§1?±??¨ê±?÷?ò??PWM	 */					  
			//	  {
			//		  receflag=1;
				//	  bitcount=0;					 
	//				  UART_INT_DeInit();
		//		  }
			//	  else
				//  {				   	 					  
					//  #if	UART_USE==1		   //1??¨ê±?÷oíPWM
					  //PWMCFG &=0x7F;	
		//			  #else 
			//		  TR0=0;
				//	  #endif 		
	//			  }
		//		  return;
			//  }
		//  }
		if(sendflag==1)
		{
			Uart_SendByte();
		}
	//	if(receflag==1)	   
	//	{
			//Uart_ReceByte();		
	 // }
	} 
}
/**************************************************
*oˉêy??3??oextern void UART_Pwm_Load()
*oˉêy1|?ü?o?¨ê±?÷?D??'|àíoˉêy
*è??ú2?êy?ovoid
*3??ú2?êy?ovoid
*1|?ü?μ?÷?o?D???'DDoˉêy
**************************************************/

static void UART_Pwm_Load()
{
	 PWMCFG &= 0XBF;				
	 timecount++;	  
	 if(timecount%2==1)				//??êy'???DD'|àí????êy'?'|àí?óê?ê±??'????úêy?Y?D???áè?
	 {
		  if(timecount==1)
		  {
			  if(startbitflag==1)					 //?eê????D??±ê??
			  {
				  startbitflag=0;					 //?eê????D??±ê????á?				  
				  bitdata=0;
					if(RXD){bitdata++;}	             //???μ??2¨???áèy'??μ
					_nop_();
					_nop_();
					_nop_();
					if(RXD){bitdata++;}
					_nop_();
					_nop_();
					_nop_();
					if(RXD){bitdata++;}				  
			      if(bitdata>>1==0)					//?D???eê?????óDD§?ò??DDêy?Y?óê????TD§1?±??¨ê±?÷?ò??PWM	 */					 
				  {
					  receflag=1;
					  bitcount=0;					 
					  UART_INT_DeInit();
				  }
				  else
				  {				   	 					  
					  #if	UART_USE==1		   //1??¨ê±?÷oíPWM
					  PWMCFG &=0x7F;	
					  #else 
					  TR0=0;
					  #endif 		
				  }
				  return;
			  }
		}
		if(sendflag==1)
		{
			Uart_SendByte();
		}
		if(receflag==1)	   
		{
			Uart_ReceByte();				  		  
		}
	  }			 		 
}
/**************************************************
*oˉêy??3??oextern void UART_INT_Load()
*oˉêy1|?ü?o?¨ê±?÷?D??'|àíoˉêy
*è??ú2?êy?ovoid
*3??ú2?êy?ovoid
*1|?ü?μ?÷?o?D???'DDoˉêy
**************************************************/
static void UART_INT_Load()
{
	if(sendflag==0)				  		//·??íê±2??óê?
	{
		#if  UART_USE==1	  		//'ò?a?¨ê±?÷?ò??PWM
		PWMCFG |= 0X80;
		#else  
		TR0=1;
		#endif
		timecount=0;
		startbitflag=1;			  		//?D???eê???±êê?????
	}    
}
/**************************************************
*oˉêy??3??oextern void Uart_init()
*oˉêy1|?ü?o???aUART3?ê??ˉ
*è??ú2?êy?ovoid
*3??ú2?êy?ovoid
*1|?ü?μ?÷?o???aUART3?ê??ˉ
**************************************************/
extern void Uart_init()
{
	//PWM_DeInit();		
	#if  UART_USE==0 
		//{THL=(65536-LOAD)/256;TLL=(65536-LOAD)%256;}
		{THL=(65536-LOAD)/256;TLL=(65536-LOAD)%256;}
		//THL = (uint8_t)((65536 - 104) >> 8);   // 0xFF
		//TLL = (uint8_t)((65536 - 104) & 0xFF); // 0x98
	#else
		{PWMCFG = (PWMCFG & 0XF0) | (uint8_t)(LOAD / 256);		//?ü?ú??4??
			PWMCON = (uint8_t)(LOAD & 0X00FF);}					//?ü?úμí8??}
	#endif 		      
	SCD_NT_PinMode(TXD_INIT, GPIO_MODE_OUT_PP);
	SCD_NT_PinMode(RXD_INIT, GPIO_MODE_IN_PU);
	#if UART_USE==0
	//TMCON |= 0X01;
	TMCON &= 0XFE;  // TIM0_PRESSEL_FSYS_D12
	TMOD &= 0xFB;
	TMOD &= 0XFC;
	TMOD |= 0X01;
	TH0=THL;
	TL0=TLL;
	IPT0 = 1;				  			//0?aμíó??è????1?a??ó??è??
	TF0 = 0;						    //???D??±ê??
	TR0=0;								//1??¨ê±?÷0
  	ET0=1;								//ê1?ü?¨ê±?÷0?D??
	#else
	IP1 |= 0X02;						//éè???a??ó??è??
	IE1 |= 0X02;
	PWMCFG &= 0XBF;
	#endif
	//UART_INT_Init();							//ía2??D??3?ê??ˉ
	EA=1; 
}
/**************************************************
*oˉêy??3??oextern void Uart_SendString(u8 *str,u8 strlen)
*oˉêy1|?ü?oUART ·??í êy?Y
*è??ú2?êy?ou8 *str ·??í×?·?'??òêy?Y	 u8 strlen μ±·??íμ?ò?êy?Yê±??3¤?è?a1
*3??ú2?êy?ovoid
*1|?ü?μ?÷?oUART ·??í êy?Y
**************************************************/

static void Uart_SendString(u8 *str,u8 strlen)
{
	sendflag=1;
	senddata=str;
	sendlength=strlen;
	bitcount=0;
	timecount=0;
	#if  UART_USE==1	  		//'ò?a?¨ê±?÷?ò??PWM
	PWMCFG |= 0X80;
	#else  
	TR0=1;
	#endif 	  
}
/**************************************************
*oˉêy??3??ovoid SCD_NT_PinMode(unsigned int IO_Pxx, GPIO_Mode_TypeDef IO_Pxx_Mode)
*oˉêy1|?ü?oIO?ú??ê?éè??
*è??ú2?êy?ounsigned int IO_Pxx              IO?ú
		   GPIO_Mode_TypeDef IO_Pxx_Mode	??ê?????
*3??ú2?êy?ovoid
*1|?ü?μ?÷?oIO?úéè?????ú?§oD?y?ˉéè???D?T?a·?'?oˉêy?ó?ú 
**************************************************/

static void SCD_NT_PinMode(unsigned int IO_Pxx, GPIO_Mode_TypeDef IO_Pxx_Mode)
{
	if(IO_Pxx != IO_NULL)
	{
		GPIO_Init(SCD_IO_PORT(IO_Pxx), SCD_IO_PIN(IO_Pxx), IO_Pxx_Mode);	
	}	
}
/**************************************************
*oˉêy??3??ovoid UART_INT_Init(void)  
*oˉêy1|?ü?o3?ê??ˉía2??D??
*è??ú2?êy?ovoid
*3??ú2?êy?ovoid
*?μ?÷?o2??a·?
**************************************************/
static void UART_INT_Init(void) 
{
	#if UART_INTselect==0
	INT0R&=0x0F;  //INT0é?éy??'?·?1?±?
	INT0F|=SCD_IO_PIN(RXD_INIT);  //INT0???μ??'?·?óDD§
	IPINT0=1;
	EINT0=1;
	#endif
	#if UART_INTselect==1
	INT1R&=0x0F;  //INT1é?éy??'?·?1?±?
	INT1F|=SCD_IO_PIN(RXD_INIT);  //INT1???μ??'?·?óDD§
	IPINT1=1;
	EINT1=1;
	#endif
	#if UART_INTselect==2
	INT2R&=0x0F;  //INT1é?éy??'?·?1?±?
	INT2F|=SCD_IO_PIN(RXD_INIT);  //INT1???μ??'?·?óDD§
	IP1=IP1|0X80;
	IE1=IE1|0X80;
	#endif
}
/**************************************************
*oˉêy??3??ovoid UART_INT_DeInit(void) 
*oˉêy1|?ü?o1?±?ía2??D??
*è??ú2?êy?ovoid
*3??ú2?êy?ovoid
*?μ?÷?o2??a·?
**************************************************/
void UART_INT_DeInit(void)
{
	switch(UART_INTselect)
	{
	#if UART_INTselect==0
			INT0R = 0x00;
			INT0F = 0x00;
			IE &= (~0X01);
			IP &= ~0X01;
			TCON &= (~0X02);
	#endif

	#if UART_INTselect==1
			INT1R = 0x00;
			INT1F = 0x00;
			IE &= (~0X04);
			IP &= ~0X04;
			TCON &= (~0X08);
	#endif

	#if UART_INTselect==2
			INT2R = 0x00;
			INT2F = 0x00;
			IE1 &= (~0X08);
			IP1 &= ~0X08;
	#endif
	}		
}

/**************************************************
*oˉêy??3??ovoid Uart_SendByte(uchar byte) 
*oˉêy1|?ü?o???a'??ú·??íò?byte
*è??ú2?êy?ovoid
*3??ú2?êy?ovoid
*?μ?÷?o?D??·?ê?μ÷ó?
**************************************************/
void Uart_SendByte(void)
{
     bit sendbit;
	 if(sendlength)
	 {
	   if(bitcount==0)			   //?eê???
	   {
	     TXD=(bit)0;		 
		 sendbuf=*(senddata++);
		 sendbit=sendbuf&0x01;
	   }
	   else if(bitcount<=8)		  //·??íbyte
	   {
	     TXD=(bit)sendbit;
		 sendbuf=sendbuf>>1;
		 sendbit=sendbuf&0x01;
	   }
	   else						   //?áê???
	   {
	   	 TXD=(bit)1;
	   }

	   if(bitcount<10)
	   {
		 bitcount++;
	   }
	   else
	   {
	     bitcount=0;
		 sendlength--;
	   }
	 }
	 else
	 {
	  	sendflag=0;
		#if  UART_USE==1		  //1?±??¨ê±?÷oíPWM
		PWMCFG &=0x7F;
		#else
		TR0=0;
		#endif
	 }
}

/**************************************************
*oˉêy??3??ovoid Uart_ReceByte(uchar byte) 
*oˉêy1|?ü?o???a'??ú?óê?ò?byte
*è??ú2?êy?ovoid
*3??ú2?êy?ovoid
*?μ?÷?o ?D??·?ê?μ÷ó?
**************************************************/
void Uart_ReceByte(void)
{
	if(bitcount<8)
	{
		recebuf = recebuf>>1;
		bitdata=0;
	    if(RXD){bitdata++;}	             //???μ??2¨???áèy'??μ
	    _nop_();
        _nop_();
	    _nop_();
	    if(RXD){bitdata++;}
	    _nop_();
	    _nop_();
	    _nop_();
	    if(RXD){bitdata++;}				  
	    if(bitdata>>1)							
		//if(RXD)
		{ recebuf |=0x80;}	
		bitcount++;
	}
	else 
	{	 	
		bitdata=0;
	    if(RXD){bitdata++;}	             //???μ??2¨???áèy'??μ
	    _nop_();
        _nop_();
	    _nop_();
	    if(RXD){bitdata++;}
	    _nop_();
	    _nop_();
	    _nop_();
	    if(RXD){bitdata++;}				  
	    if(bitdata>>1)						
		if(RXD==1)
		{ 
			Recedata[ReceCount++]=recebuf;
		}	
		bitcount=0;
		receflag=0;	 		    	
		#if	UART_USE==1		   //1??¨ê±?÷oíPWM
		PWMCFG &=0x7F;	
		#else 
		TR0=0;
		#endif 		
		UART_INT_Init();  //'ò?aía2??D??	 		  	 	 
	}			  
}

// instead of using this, use below helper function snipper

//bitdata=0;
//if(RXD){bitdata++;}
//_nop_(); _nop_(); _nop_();
//if(RXD){bitdata++;}
//_nop_(); _nop_(); _nop_();
//if(RXD){bitdata++;}
//if(bitdata>>1) ...

//Create a tiny helper:

//static bit rxd_majority_high(void)
//{
 //   unsigned char b = 0;
 //   if (RXD) b++;
  //  _nop_(); _nop_(); _nop_();
   // if (RXD) b++;
   // _nop_(); _nop_(); _nop_();
   // if (RXD) b++;
  //  return (b >> 1);
//}
//Then use this in 3 places , where this code block is repeated:

//Start-bit detect: if (rxd_majority_high() == 0) { ... }

//Data-bit sample: if (rxd_majority_high()) recebuf |= 0x80;

//Stop-bit sample: if (rxd_majority_high()) Recedata[ReceCount++] = recebuf;

