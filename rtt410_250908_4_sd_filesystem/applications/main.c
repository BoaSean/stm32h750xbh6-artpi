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
        rt_pin_write(PIN_LED_B, PIN_HIGH);
        rt_thread_mdelay(500);
        rt_pin_write(PIN_LED_B, PIN_LOW);
        rt_thread_mdelay(500);
    }

    return RT_EOK;
}


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

