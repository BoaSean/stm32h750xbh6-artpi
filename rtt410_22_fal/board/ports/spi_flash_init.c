#include <rtdevice.h>

#if defined(BSP_USING_SPI1) && defined(RT_USING_SFUD)

#include <drv_spi.h>
#include "spi_flash_sfud.h"

#define FLASH_CS        GET_PIN(A, 4)

int rt_hw_spi_flash_init(void)
{   
    rt_pin_mode(FLASH_CS, PIN_MODE_OUTPUT);

    rt_err_t res;
    res = rt_hw_spi_device_attach("spi1", "spi10", GPIOA, GPIO_PIN_4);

    if (res != RT_EOK){
        rt_kprintf("[flash] Failed to attach device %s\n", "norflash0");
        return res;
    }

    if (RT_NULL == rt_sfud_flash_probe("norflash0", "spi10")){
        return -RT_ERROR;
    }
    return RT_EOK;
}

INIT_DEVICE_EXPORT(rt_hw_spi_flash_init);

#endif