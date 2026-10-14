#include "BoardBsp.h"


#define DBG_TAG "Mboard"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>


#include "stm32h7xx.h"
static int vtor_config(void)
{
    /* Vector Table Relocation in Internal QSPI_FLASH */
    SCB->VTOR = QSPI_BASE;
    return 0;
}
INIT_BOARD_EXPORT(vtor_config);



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


void userkey_irq(void *args){           /* 中断回调函数 */
    rt_kprintf("user key!\n");
}

static void pin_key_sample(void){
    rt_pin_mode(PIN_USER_KEY1, PIN_MODE_INPUT_PULLUP);                   /* 按键0引脚为输入模式 */
    rt_pin_attach_irq(PIN_USER_KEY1, PIN_IRQ_MODE_FALLING, userkey_irq, RT_NULL);/* 绑定中断，下降沿模式，回调函数名为beep_on */
    rt_pin_irq_enable(PIN_USER_KEY1, PIN_IRQ_ENABLE);                    /* 使能中断 */
}


int gpio_pin_init(){
    rt_pin_mode(PIN_LED_R, PIN_MODE_OUTPUT);
    rt_pin_mode(PIN_LED_B, PIN_MODE_OUTPUT);

    
    rt_pin_write(PIN_LED_R, PIN_HIGH);
    rt_pin_write(PIN_LED_B, PIN_HIGH);

    // rt_pin_write(PIN_LED_R, PIN_LOW);
    // rt_pin_write(PIN_LED_B, PIN_LOW);


    // rt_pin_mode(PIN_USER_KEY1, PIN_MODE_INPUT);
    pin_key_sample();

    LOG_D("gpio pin init done.");

    return 0;
}

INIT_DEVICE_EXPORT(gpio_pin_init);