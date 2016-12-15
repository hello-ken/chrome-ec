/* Copyright (c) 2014 The Chromium OS Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

/* Veyron board configuration */

#ifndef __BOARD_H
#define __BOARD_H

/* Remove unnecessary function for reduce the flash size */
#undef CONFIG_CONSOLE_CMDHELP
#undef CONFIG_TASK_PROFILING
#undef CONFIG_WATCHDOG_HELP
#define CONFIG_DEBUG_ASSERT_BRIEF
#undef CONFIG_CMD_MEM
#undef CONFIG_CMD_I2C_SCAN
#undef CONFIG_CMD_SHMEM
#undef CONFIG_CMD_TIMERINFO

/* Limit console output */
#undef CONFIG_HOSTCMD_DEBUG_MODE
#define CONFIG_HOSTCMD_DEBUG_MODE HCDEBUG_OFF

/* Optional features */
#define CONFIG_ACCEL_KX022
#define CONFIG_AP_HANG_DETECT
#define CONFIG_BATTERY_BQ27541
#define CONFIG_BATTERY_CUT_OFF
#define CONFIG_BATTERY_OVERRIDE_PARAMS
#define CONFIG_BOARD_PRE_INIT
#define CONFIG_BOARD_SPECIFIC_CHARGER_INIT
#define CONFIG_CHARGER
#define CONFIG_CHARGER_BQ24770
#define CONFIG_CHARGER_DISCHARGE_ON_AC
#define CONFIG_CHARGER_V2
#define CONFIG_CHIPSET_ROCKCHIP

/* Depends on how fast the AP boots and typical ODRs */
#define CONFIG_ACCEL_FIFO 512
#define CONFIG_ACCEL_FIFO_THRES (CONFIG_ACCEL_FIFO / 3)

#define CONFIG_EXTPOWER_GPIO
#define CONFIG_FORCE_CONSOLE_RESUME
#define CONFIG_HOST_COMMAND_STATUS
#define CONFIG_I2C
#define CONFIG_KEYBOARD_COL2_INVERTED
#define CONFIG_KEYBOARD_PROTOCOL_MKBP
#define CONFIG_LED_COMMON
#define CONFIG_LED_POLICY_STD
#define CONFIG_LED_POLICY_STD_BATTERY
#define CONFIG_LED_POLICY_STD_POWER
#define CONFIG_LED_BAT_ACTIVE_LOW
#define CONFIG_LED_POWER_ACTIVE_LOW
#define CONFIG_LED_POWER_IS_EXTERNAL
#define CONFIG_LID_ANGLE
#define CONFIG_LID_ANGLE_KEY_SCAN
#define CONFIG_LOW_POWER_IDLE
#define CONFIG_LOW_POWER_S0
#define CONFIG_MKBP_EVENT
#define CONFIG_POWER_BUTTON
#define CONFIG_POWER_BUTTON_ACTIVE_STATE 1
#define CONFIG_POWER_COMMON
#define CONFIG_POWER_TRACK_HOST_SLEEP_STATE
#define CONFIG_PWM
#define CONFIG_SENSOR_LID 1
#define CONFIG_SPI
#define CONFIG_STM_HWTIMER32
#define CONFIG_UART_RX_DMA
#define CONFIG_VBOOT_HASH

#define CONFIG_HIBERNATE_WAKEUP_PINS (STM32_PWR_CSR_EWUP1 | STM32_PWR_CSR_EWUP6)

#define CONFIG_MKBP_EVENT
/* Define the MKBP events which are allowed to wakeup AP in S3. */
#define CONFIG_MKBP_WAKEUP_MASK \
		(EC_HOST_EVENT_MASK(EC_HOST_EVENT_LID_OPEN) |\
		 EC_HOST_EVENT_MASK(EC_HOST_EVENT_POWER_BUTTON) |\
		 EC_HOST_EVENT_MASK(EC_HOST_EVENT_KEY_PRESSED))

#ifndef __ASSEMBLER__

/* 48 MHz SYSCLK clock frequency */
#define CPU_CLOCK 48000000

/* Keyboard output port list */
#define KB_OUT_PORT_LIST GPIO_A, GPIO_B, GPIO_C

/* Sensor index definition */
enum sensor_id {
	BASE_ACCEL = 0,
	LID_ACCEL = 1,
};

/*
 * We have not enabled the sensor FIFO on the accels, so we force the EC
 * to collect at every sample.
 */
#define CONFIG_ACCEL_FORCE_MODE_MASK \
	((1 << BASE_ACCEL) | (1 << LID_ACCEL))

#define CONFIG_LID_ANGLE_SENSOR_BASE BASE_ACCEL
#define CONFIG_LID_ANGLE_SENSOR_LID LID_ACCEL
/* Single I2C port, where the EC is the master. */
#define I2C_PORT_MASTER 0
#define I2C_PORT_ACCEL   I2C_PORT_MASTER
#define I2C_PORT_BATTERY I2C_PORT_MASTER
#define I2C_PORT_CHARGER I2C_PORT_MASTER

#define CONFIG_SENSOR_BASE 0

/* Timer selection */
#define TIM_CLOCK32  2
#define TIM_WATCHDOG 7

#include "gpio_signal.h"

enum power_signal {
	RK_POWER_GOOD = 0,
	RK_SUSPEND_ASSERTED,
	/* Number of power signals */
	POWER_SIGNAL_COUNT
};

enum pwm_channel {
	PWM_CH_POWER_LED = 0,
	/* Number of PWM channels */
	PWM_CH_COUNT
};

/* Charger module */
#define CONFIG_CHARGER_SENSE_RESISTOR 10 /* Charge sense resistor, mOhm */
#define CONFIG_CHARGER_SENSE_RESISTOR_AC 25 /* Input sensor resistor, mOhm */

/* Input current limit for 24W AC adapter, 24W/12V=2A
 * minnie support the INOM prochot function, 110% input current limit
 * 2A/1.1=1.818A
 */
#define CONFIG_CHARGER_INPUT_CURRENT 1818 /* mA */

/* Discharge battery when on AC power for factory test. */
int board_discharge_on_ac(int enable);

int board_init_charger(void);

#endif /* !__ASSEMBLER__ */

#endif /* __BOARD_H */
