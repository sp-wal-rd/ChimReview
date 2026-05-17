//************************************************************
//  Copyright (c) 深圳市赛元微电子股份有限公司
//	文件名称	: IAP_Option_EW.h
//	作者		  :
//	模块功能	: IAP固件库函数头文件
//	局部函数列表:
//  最后更正日期: 2025/5/7
// 	版本		  : V1.1.2
//  说明      :该文件适用于SC92F6x1x、SC92R43X、SC92Fx41xB、SC92R445、SC92L840x、SC92R422A、SC92R429B、
//             SC92R448M、SC92R449、SC92R450、YX2501、SC92F652x、SC92R343、SC92R519系列芯片
//*************************************************************
#ifndef _IAP_OPTION_EW_H_
#define	_IAP_OPTION_EW_H_

typedef enum{
	IAP_ENABLE =0x69,
	IAP_DISABLE=0x00,
}IAPOPTION_FLAG;

extern unsigned char IapWriteFlag;

/** @brief CPU Hold Time Duration Configuration
 * @{
 */
#if defined(SC92Fx41xB)||defined(SC92R343)
typedef enum
{
  CPU_Hold_4ms = (unsigned char)(0x00U << 2), /*!< CPU Hold 4ms */
  CPU_Hold_2ms = (unsigned char)(0x01U << 2), /*!< CPU Hold 2ms */
  CPU_Hold_1ms  = (unsigned char)(0x02U << 2), /*!< CPU Hold 1ms */
} CPU_HoldTime_TypeDef;
#endif
/**************************************************
*函数名称：void IAP_CodeProgramByteOption(unsigned long Add,unsigned char Data)
*函数功能：单Byte写入
*入口参数：Add ：需要写入的地址
*         Data：要写入的Byte        
*出口参数：void
**************************************************/
void IAP_CodeProgramByteOption(unsigned long Add,unsigned char Data);

/**************************************************
*函数名称：void IAP_CodeSectorEraseOption(unsigned long Add)
*函数功能：扇区擦除
*入口参数：Add ：需要擦除的地址        
*出口参数：void
**************************************************/
#if defined(SC92F6x1x)||defined(SC92R436)||defined(SC92R438)||defined(SC92R439)||defined(SC92R422A)||defined(YX2501)||defined(SC92F652x)||defined(SC92R519)
void IAP_CodeSectorEraseOption(unsigned long Add);
#endif

/**************************************************
*函数名称：void IAP_EEPROMProgramByteOption(unsigned int Add, unsigned char Data)
*函数功能：单Byte写入
*入口参数：Add ：需要擦除的地址
*          Data：要写入的Byte         
*出口参数：void
**************************************************/
#if defined(SC92Fx41xB)||defined(SC92R445)||defined(SC92L840x)||defined(SC92R429B)||defined(SC92R448M)\
    ||defined(SC92R449)||defined(SC92R450)||defined(YX2501)||defined(SC92F652x)||defined(SC92R343)||defined(SC92R519)
void IAP_EEPROMProgramByteOption(unsigned int Add, unsigned char Data);
#endif

/**************************************************
*函数名称：void IAP_EEPROMSectorEraseOption(unsigned int Add)
*函数功能：扇区擦除
*入口参数：Add ：需要擦除的地址        
*出口参数：void
**************************************************/
#if defined(YX2501)||defined(SC92F652x)||defined(SC92R519)
void IAP_EEPROMSectorEraseOption(unsigned int Add);
#endif

/**************************************************
*函数名称：void CPU_HoldTime_Config(CPU_HoldTime_TypeDef CPU_HoldTime)
*函数功能：CPU HoldTime设置
*入口参数：CPU_HoldTime_TypeDef ：CPU_HoldTime
*          CPU_Hold_4ms：CPU Hold 4ms
*          CPU_Hold_2ms：CPU Hold 2ms
*          CPU_Hold_1ms：CPU Hold 1ms
*出口参数：void
**************************************************/
#if defined(SC92Fx41xB)||defined(SC92R343)
void CPU_HoldTime_Config(CPU_HoldTime_TypeDef CPU_HoldTime);
#endif

#endif
