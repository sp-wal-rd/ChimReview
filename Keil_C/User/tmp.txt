/***************************************************************************************
  * @copyright	(c)  Shenzhen Saiyuan Microelectronics Co., Ltd.
  * @file	SC_it.c
  * @author
  * @version 	V1.2.0
  * @date	2025/05/20
  * @brief	Interrupt Service Routine
  * @details
  **************************************************************************************/

#include "SC_it.h"
#include "..\Drivers\SCDriver_list.h"
//#include "HeadFiles\SC_itExtern.h"
#include "global\wm_global.h"




void INT0Interrupt()		interrupt 0
{
    TCON &= 0XFD;//Clear interrupt flag bit


}
void Timer0Interrupt()		interrupt 1
{


    /***User program***/
      UART_Timer0_Load();


}
void INT1Interrupt()		interrupt 2
{
    TCON &= 0XF7;//Clear interrupt flag bit


}
void Timer1Interrupt()		interrupt 3
{

 TIM1_Mode1SetReloadCounter(64536);
 TIM1_Interrupt();
      

}
#if defined (SC92F742x) || defined (SC92F7490)
void SSI0Interrupt()		interrupt 4
{


}
#elif  !defined ( SC92F827X)  &&  !defined (SC92F837X)
void UART0Interrupt()		interrupt 4
{

	//UART0_INTERRUPT();
}
#endif
void Timer2Interrupt()		interrupt 5
{

   	 //if(wm_En38khzfreq)
	 //{
//		P13 = !P13;
//  	 	P07 = !P07;		
	 //}
	
//	TIM2_ClearFlag(TIM2_FLAG_TF2);
//	TIM2_ClearFlag(TIM2_FLAG_EXF2);

}
void ADCInterrupt()			interrupt 6
{


}
#if defined (SC92F854x) || defined (SC92F754x) ||defined  (SC92F844xB) || defined (SC92F744xB)||defined  (SC92F84Ax_2) || defined (SC92F74Ax_2)|| defined (SC92F846xB) || defined (SC92F746xB)\
|| defined (SC92F836xB) || defined (SC92F736xB) || defined (SC92F8003) || defined (SC92F8003B) || defined  (SC92F84Ax) || defined (SC92F74Ax) || defined  (SC92F83Ax) || defined (SC92F73Ax) \
|| defined (SC92F7003) || defined (SC92F740x) || defined (SC92FWxx) || defined (SC93F743x) || defined (SC93F833x) || defined (SC93F843x) || defined (SC92F848x) || defined (SC92F748x)|| defined (SC92F859x) \
|| defined (SC92F759x) || defined(SC92F84Hx) || defined(SC92F83Hx)|| defined(SC92F827x)|| defined(SC92F837x) ||defined(SC92F841x) || defined(SC92F741x) || defined(SC92R511x) || defined(SC92R342)\
|| defined(SC92R436) || defined(SC92R438) || defined(SC92R439)||defined(SC92Fx41xB)  ||defined(SC92R445) || defined(SC92R422A)||defined(SC92F652x)
void SSIInterrupt()			interrupt 7
{


}
#elif defined (SC92F742x) || defined (SC92F7490)
void SSI1Interrupt()		interrupt 7
{


}
#elif !defined (SC92F730x) && !defined (SC92F730x_2) && !defined (SC92F720x) && !defined (SC92F725X) && !defined (SC92F735X) && !defined (SC92F732X)\
&&!defined (SC92F7308B)
void USCI0Interrupt()			interrupt 7
{


}
#endif
void PWMInterrupt()			interrupt 8
{


}
#if !defined (TK_USE_BTM)
void BTMInterrupt()			interrupt 9
{



}
#endif
void INT2Interrupt()		interrupt 10
{


}
#if defined (SC92F854x) || defined (SC92F754x) || defined  (SC92F844xB) || defined (SC92F744xB)||defined  (SC92F84Ax_2) || defined (SC92F74Ax_2)|| defined (SC92F859x) || defined (SC92F759x) || defined (SC92R511x)\
|| defined (SC92FWxx) || defined (SC95F8x1x) || defined (SC95F7x1x) || defined (SC95FWxx) || defined (SC95F8x3x) || defined (SC95F7x3x) || defined (SC95F8x6x) || defined (SC95F7x6x) || defined (SC95F8x1xB) ||defined ( SC95F7x1xB)\
|| defined (SC95R751) || defined (SC95F7610B) || defined (SC95F7619B) || defined (SC95R602) || defined (SC95R605) || defined (SC95F8x7x) || defined (SC95F7x7x) || defined	(SC95R506)
void ACMPInterrupt()		interrupt 12
{


}
#endif

#if defined (SC92L853x) || defined (SC92L753x) || defined(SC92F84Hx) || defined(SC92F83Hx) || defined( SC95F8x1x) || defined(SC95F7x1x) || defined(SC95F8x2x) || defined(SC95F7x2x) ||defined(SC95FWxx) \
|| defined(SC95F8x3x) || defined(SC95F7x3x) || defined(SC95F8x6x) || defined(SC95F7x6x) || defined(SC95F8x1xB) || defined(SC95F7x1xB) || defined(SC95R751) || defined(SC95F7610B) || defined(SC95F7619B) \
|| defined(SC95FS52x) || defined(SC95R602) || defined(SC95R605) || defined(SC95F8x7x) || defined(SC95F7x7x) || defined(SC92L840x) || defined	(SC95R506)||defined(SC92F652x)
void Timer3Interrupt()		interrupt 13
{


}
void Timer4Interrupt()		interrupt 14
{


}
#if  !defined (SC92F84Hx) && !defined (SC92F83Hx)

void USCI1Interrupt()		interrupt 15
{


}
void USCI2Interrupt()		interrupt 16
{


}
#endif

#if  defined (SC92L853x) || defined (SC92L753x) || defined(SC92L840x)
void LPDInterrupt()		interrupt 22
{


}
#endif
#endif

#if  defined (SC95F8x3x) || defined (SC95F7x3x) || defined (SC95F7619B) || defined ( SC95F8x6x) || defined (SC95F7x6x) || defined (SC95F8x1xB)|| defined (SC95F7x1xB) || defined (SC95R751)|| defined (SC95R605)
void USCI3Interrupt()		interrupt 17
{


}
#if !defined (SC95R751)
void USCI4Interrupt()		interrupt 18
{


}
#endif
#if defined (SC95F8x6x) || defined (SC95F7x6x) || defined (SC95F8x1xB) || defined (SC95F7x1xB)
void USCI5Interrupt()		interrupt 19
{


}
#endif

#endif
void UART2Interrupt()		interrupt 12
{


}
