#include "stm32f4xx.h"
#include "led.h"
#include "key.h"  
#include "delay.h"
#include "usart.h"
#include "los_base.h"
#include "los_sys.h"
#include "los_typedef.h"
#include "los_task.ph"

UINT32 creat_task1(void);
UINT32 creat_task2(void);


int main(void)
{
	UINT32 uwRet;
	uwRet = LOS_KernelInit();
	Delay_Init();
   Usart_Config();
	LED_Init();

	
	if (uwRet != LOS_OK)
	{
     return LOS_NOK;
	}
	uwRet = creat_task1();
	if (uwRet != LOS_OK)
	{
     return LOS_NOK;
	}
	uwRet = creat_task2();
	if (uwRet != LOS_OK)
	{
     return LOS_NOK;
	}
LOS_Start();

}


void task1(void)
{
int count = 1;
while (1)
  {
		printf("This is task1,count is %d\r\n",count++);
		LOS_TaskDelay(1000);
  }
}

UINT32 creat_task1(void)
{
    UINT32 uwRet = LOS_OK,g_TskHandle1;
    TSK_INIT_PARAM_S task_init_param;
 
    task_init_param.usTaskPrio = 0;
    task_init_param.pcName = "task1";
    task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)task1;
    task_init_param.uwStackSize = 0x200;
 
    uwRet = LOS_TaskCreate(&g_TskHandle1, &task_init_param);
    if(LOS_OK != uwRet)
    {
        return uwRet;
    }
    return uwRet;
}
 
void task2(void)
{
int count = 1;
while (1)
  {
        printf("This is task2,count is %d\r\n",count++);
        LOS_TaskDelay(2000);
  }
}

UINT32 creat_task2(void)
{
    UINT32 uwRet = LOS_OK,g_TskHandle;
    TSK_INIT_PARAM_S task_init_param;
 
    task_init_param.usTaskPrio = 1;
    task_init_param.pcName = "task2";
    task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)task2;
    task_init_param.uwStackSize = 0x200;
 
    uwRet = LOS_TaskCreate(&g_TskHandle, &task_init_param);
    if(LOS_OK != uwRet)
		{
        return uwRet;
		}
    return uwRet;
}

