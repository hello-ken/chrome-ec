/* Copyright 2016 The Chromium OS Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include "gpio.h"
#include "timer.h"
#include "watchdog.h"
#include "cts_common.h"
#include "dut_common.h"

/* Returns unknown because TH could potentially still get stuck
 * even if the DUT completes the sync
 */
enum cts_rc sync(void)
{
	int input_level;

	gpio_set_level(GPIO_HANDSHAKE_OUTPUT, 0);
	do {
		watchdog_reload();
		input_level = gpio_get_level(GPIO_HANDSHAKE_INPUT);
	} while (!input_level);
	gpio_set_level(GPIO_HANDSHAKE_OUTPUT, 1);
	do {
		watchdog_reload();
		input_level = gpio_get_level(GPIO_HANDSHAKE_INPUT);
	} while (input_level);
	gpio_set_level(GPIO_HANDSHAKE_OUTPUT, 0);

	return CTS_RC_SUCCESS;
}