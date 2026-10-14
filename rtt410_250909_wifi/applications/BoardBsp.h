#ifndef BOARDBSP_H
#define BOARDBSP_H

#include <rtthread.h>
#include <stm32h7xx.h>
#include "drv_common.h"
#include "drv_gpio.h"

#include <stdbool.h>
#include <rtdevice.h>


/*-------------------------Pin begin----------------------------------*/
#define PIN_LED_R           GET_PIN(C, 15)
#define PIN_LED_B           GET_PIN(I, 8)

#define PIN_USER_KEY1       GET_PIN(H, 4)


/*-------------------------Pin end----------------------------------*/





#endif 