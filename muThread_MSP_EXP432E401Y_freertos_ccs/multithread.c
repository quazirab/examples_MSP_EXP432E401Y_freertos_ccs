/*
 * Copyright (c) 2015-2019, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ======== empty.c ========
 */

/* For usleep() */
#include <unistd.h>
#include <stdint.h>
#include <stddef.h>

/* Driver Header files */
#include <ti/drivers/GPIO.h>
#include <ti/display/Display.h>

/* Driver configuration */
#include "ti_drivers_config.h"

extern Display_Handle display;

/*
 *  ======== firstThread ========
 */
void *firstThread(void *arg0)
{
    Display_printf(display, 0, 0, "\rThread 1 Started\n\r");

    /* 100 millisecond delay */
    useconds_t time = 100000;
//    uint32_t time_int = 5;

    /* Configure the LED pin */
    GPIO_setConfig(CONFIG_GPIO_LED_0, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);

    /* Turn on user LED */
    GPIO_write(CONFIG_GPIO_LED_0, CONFIG_GPIO_LED_ON);

    while (1) {
        int usleepRtn;
        usleepRtn = usleep(time);
        if (usleepRtn != 0){
            Display_printf(display, 0, 0, "\rProblem Loading usleep\n\r");
            return(0);
        }
//        sleep(time_int);
        Display_printf(display, 0, 0, "\rThread 1 Toggle \n\r");
        GPIO_toggle(CONFIG_GPIO_LED_0);
    }
}

/*
 *  ======== secondThread ========
 */
void *secondThread(void *arg0)
{
    Display_printf(display, 0, 0, "\rThread 2 Started\n\r");

    /* 50 millisecond delay */
    useconds_t time = 50000;

    /* Configure the LED pin */
    GPIO_setConfig(CONFIG_GPIO_LED_1, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);

    /* Turn on user LED */
    GPIO_write(CONFIG_GPIO_LED_1, CONFIG_GPIO_LED_ON);

    while (1) {
        usleep(time);
        Display_printf(display, 0, 0, "\rThread 2 Toggle\n\r");
        GPIO_toggle(CONFIG_GPIO_LED_1);
    }
}
