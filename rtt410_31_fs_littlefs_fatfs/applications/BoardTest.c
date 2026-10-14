#include "BoardTest.h"

#define DBG_TAG "board_test"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>


#include <stm32h7xx.h>
uint8_t GetMcuRevIDChar(void)
{
  // Reference Manual, June 2018, page 3131 of 3247
  // Bits 31:16 REV_ID[15:0]: Revision
  // 0x1001 = Revision Z
  // 0x1003 = Revision Y
  // 0x2001 = Revision X
  // 0x2003 = Revision V - (See STM32H750/753 Errata sheet, device limitations)
  
  uint32_t ID_Code = DBGMCU->IDCODE;
  uint16_t Dev_ID = ID_Code & 0x0fff;
  uint16_t Rev_ID = (ID_Code >> 16);
  if (Rev_ID == 0x1001)
    return 'Z';
  if (Rev_ID == 0x1003)
    return 'Y';
  if (Rev_ID == 0x2001)
    return 'X';
  if (Rev_ID == 0x2003)
    return 'V';
  return '-';
}
int muc_info(void){

    LOG_D("MCU info:%c",GetMcuRevIDChar());
    return 0;
}
INIT_DEVICE_EXPORT(muc_info);


#ifdef RT_USING_PIN

void userkey_irq(void *args){           /* 中断回调函数 */
    rt_kprintf("user key!\n");
}

static void led_thread_entry(void *parameter){

    rt_pin_mode(PIN_LED_R, PIN_MODE_OUTPUT);
    rt_pin_mode(PIN_LED_B, PIN_MODE_OUTPUT);

    
    rt_pin_write(PIN_LED_R, PIN_HIGH);
    rt_pin_write(PIN_LED_B, PIN_HIGH);


    rt_pin_mode(PIN_USER_KEY1, PIN_MODE_INPUT_PULLUP);                   /* 按键0引脚为输入模式 */
    rt_pin_attach_irq(PIN_USER_KEY1, PIN_IRQ_MODE_FALLING, userkey_irq, RT_NULL);/* 绑定中断，下降沿模式，回调函数名为beep_on */
    rt_pin_irq_enable(PIN_USER_KEY1, PIN_IRQ_ENABLE);                    /* 使能中断 */

    LOG_D("gpio pin init done.");

    while (1){
        rt_pin_write(PIN_LED_R, PIN_HIGH);
        rt_thread_mdelay(500);
        rt_pin_write(PIN_LED_R, PIN_LOW);
        rt_thread_mdelay(500);
    }
}

int gpio_pin_init(void){
    rt_thread_t tid;

    tid = rt_thread_create("led",
                           led_thread_entry,
                           RT_NULL,
                           512,                 // 线程栈大小
                           25,                  // 线程优先级，越小优先级越高
                           10);                 // 时间片

    if (tid != RT_NULL)
        rt_thread_startup(tid);

    return 0;
}

INIT_APP_EXPORT(gpio_pin_init);

#endif


#if defined(RT_USING_FAL) && defined(PKG_USING_EASYFLASH)

#include <fal.h>
#include "easyflash.h"
int easyflash_test(void){
    int boot_count = 0;

    //	ef_env_set_default();
	
	ef_get_env_blob("boot_count", &boot_count, sizeof(boot_count), NULL);
	boot_count++;
	ef_set_env_blob("boot_count",&boot_count,sizeof(boot_count));
    
    LOG_D("boot_count is %d",boot_count);

    return RT_EOK;
}

INIT_APP_EXPORT(easyflash_test);

#endif
