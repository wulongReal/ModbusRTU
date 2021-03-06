/********************************************************************************
  * @File   : ModBusPort.h
  * @Author : HIENCLUBVN
  * @Version: V0.1
  * @Date   : 25/09/2014
  * @Brief  :
  *******************************************************************************
  * @Attention:
  */

#ifndef _PORT_H
#define _PORT_H

#include <stdint.h>
#include <stdbool.h>
#include <ModbusRTU.h>

#include "Bit.h"
#include "misc.h"
#include "stm32f10x.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

//CPU  寄存器类型指针定义
typedef volatile uint32_t * CPURegistertype;

//线圈类型
typedef struct{
  CPURegistertype Port;
  uint8_t Bit;
}MBCoilType;

//离散类型
typedef struct{
  CPURegistertype Port;
  uint8_t Bit;
}MBDiscreteType;

#define UART_USE                                 1       // USART3
                 
#define TIM_USE                                  3       // TIM3
                 
#define CPU_CLK                                  72      //72MHz             
                 
#define REG_INPUT_START                          0x0000  //输入寄存器起始地址
                      
#define REG_INPUT_NREGS                          14       //输入寄存器数量
                       
#define REG_HOLDING_START                        0x0000  //保持寄存器起始地址
                      
#define REG_HOLDING_NREGS                        15       //Fix
                       
#define REG_COILS_START                          0x0000  //线圈起始地址
                       
#define REG_COILS_SIZE                           8       //线圈数量(小于0x07B0)
                       
#define REG_DISCRETE_START                       0x0000  //离散开关起始地址
                       
#define REG_DISCRETE_SIZE                        8       //离散开关数量（小于0x07D0）

#define MB_FUNC_HANDLERS_MAX                    ( 20  )   //使用的功能码数量
   
#define MB_FUNC_OTHER_REP_SLAVEID_BUF           (  4 )   
   
#define MB_FUNC_OTHER_REP_SLAVEID_ENABLED       (  1 )   //报告从设备功能
   
#define MB_FUNC_READ_INPUT_ENABLED              (  1 )   //读输入寄存器功能
   
#define MB_FUNC_READ_HOLDING_ENABLED            (  1 )   //读保持寄存器功能
   
#define MB_FUNC_WRITE_HOLDING_ENABLED           (  1 )   //写操持寄存存功能
   
#define MB_FUNC_WRITE_MULTIPLE_HOLDING_ENABLED  (  1 )   //写多个操持寄存存功能
   
#define MB_FUNC_READ_COILS_ENABLED              (  1 )   //No Coil
   
#define MB_FUNC_WRITE_COIL_ENABLED              (  1 )   //写线圈
   
#define MB_FUNC_WRITE_MULTIPLE_COILS_ENABLED    (  1 )   //写多个线圈
   
#define MB_FUNC_READ_DISCRETE_INPUTS_ENABLED    (  1 )   //读离散输入
   
#define MB_FUNC_READWRITE_HOLDING_ENABLED       (  1 )   //读写多个寄存器


//输入寄存器内容
extern uint16_t usRegInputBuf[REG_INPUT_NREGS];	//6

//保持寄存器内容
extern uint16_t usRegHoldingBuf[REG_HOLDING_NREGS];	//6

//线圈状态
extern MBCoilType MBCoils[REG_COILS_SIZE];	//8

//开关输入状态
extern MBDiscreteType MBDiscretes[REG_DISCRETE_SIZE];	//8


#define ENTER_CRITICAL_SECTION()    __disable_irq()   
#define EXIT_CRITICAL_SECTION()     __enable_irq()   

bool xMBPortSerialInit(uint32_t ulBaudRate);
void vMBPortSerialEnable( bool xRxEnable, bool xTxEnable );

void xMBPortTimersInit( uint16_t usTimeOut50us );
void vMBPortTimersEnable( void );
void vMBPortTimersDisable( void );

#define assert(expr)

#if (UART_USE == 1)
  #define UART                  USART1
	#define UART_GPIO             GPIOA  
	#define UART_CLK              RCC_APB2Periph_USART1 
	#define UART_GPIO_CLK         RCC_APB2Periph_GPIOA  
	#define UART_TX_PIN           GPIO_Pin_9
	#define UART_RX_PIN           GPIO_Pin_10
	#define UART_IQR_HANDLER      USART1_IRQHandler
	#define UART_IRQN_N           USART1_IRQn
#endif
#if (UART_USE == 2)
  #define UART                  USART2
	#define UART_GPIO             GPIOA  
	#define UART_CLK              RCC_APB1Periph_USART2 
	#define UART_GPIO_CLK         RCC_APB2Periph_GPIOA  
	#define UART_TX_PIN           GPIO_Pin_2
	#define UART_RX_PIN           GPIO_Pin_3
	#define UART_IQR_HANDLER      USART2_IRQHandler
	#define UART_IRQN_N           USART2_IRQn
#endif
#if (UART_USE == 3)
  #define UART                  USART3
	#define UART_GPIO             GPIOB  
	#define UART_CLK              RCC_APB1Periph_USART3 
	#define UART_GPIO_CLK         RCC_APB2Periph_GPIOB  
	#define UART_TX_PIN           GPIO_Pin_10
	#define UART_RX_PIN           GPIO_Pin_11
	#define UART_IQR_HANDLER      USART3_IRQHandler
	#define UART_IRQN_N           USART3_IRQn
#endif

#if (TIM_USE == 2)
#define TIEM                    TIM2
#define TIME_IRQN_N             TIM2_IRQn
#define TIME_IQR_HANDLER        TIM2_IRQHandler
#define TIME_CLK                RCC_APB1Periph_TIM2
#endif  
  
#if (TIM_USE == 3)  
#define TIEM                    TIM3
#define TIME_IRQN_N             TIM3_IRQn
#define TIME_IQR_HANDLER        TIM3_IRQHandler
#define TIME_CLK                RCC_APB1Periph_TIM3
#endif  
  
#if (TIM_USE == 4)  
#define TIEM                    TIM4
#define TIME_IRQN_N             TIM4_IRQn
#define TIME_IQR_HANDLER        TIM4_IRQHandler
#define TIME_CLK                RCC_APB1Periph_TIM4
#endif

#define UART_DR                  (UART->DR)           // USART2->DR                    
#define USART_RX_ENABLE()        USART_ITConfig(UART, USART_IT_RXNE, ENABLE)
#define USART_RX_DISABLE()       USART_ITConfig(UART, USART_IT_RXNE, DISABLE)
#define USART_TX_ENABLE()        USART_ITConfig(UART, USART_IT_TC, ENABLE);
#define USART_TX_DISABLE()       USART_ITConfig(UART, USART_IT_TC, DISABLE);
     
#define RS485PIN                 GPIO_Pin_12	// PA8
#define RS485SWITCH_TO_SEND()    GPIO_SetBits(RS485GPIO, RS485PIN)
#define RS485SWITCH_TO_RECEIVE() GPIO_ResetBits(RS485GPIO, RS485PIN)
#define RS485GPIO                GPIOB  // A
#define RS485GPIO_CLK            RCC_APB2Periph_GPIOB	// GPIOA

#define UsartSend(ucByte)        ((UART_DR) = (ucByte))        
#define UsartReceive(ucByte)     (*(ucByte) = (uint8_t)(UART_DR))

#endif
