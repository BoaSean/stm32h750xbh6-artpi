/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-03-05     whj4674672   first version
 */


#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

#define DBG_TAG "main"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>

#include "BoardBsp.h"

int main(void)
{

    while (1){
        // printf("%d\n",1);
        // LOG_D("Hello RT-Thread250811!");
        rt_pin_write(PIN_LED_R, PIN_HIGH);
        rt_thread_mdelay(500);
        rt_pin_write(PIN_LED_R, PIN_LOW);
        rt_thread_mdelay(500);
    }

    return RT_EOK;
}
