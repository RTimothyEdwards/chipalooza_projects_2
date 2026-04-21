#include <defs.h>
#include <chipalooza_stubs.h>

/*
 *-----------------------------------------------------------
 * chipalooza_test_instramp.c:
 *-----------------------------------------------------------
 * Written by Tim Edwards, Open Circuit Design
 * April 20, 2026
 *-----------------------------------------------------------
 *
 * Board-level preparation:
 * 1) connect vccd1 to 1.8V
 * 2) connect vccd2 to 1.8V
 * 3) connect vdda1 to 3.3V
 * 4) connect vdda2 to 3.3V
 *
 * Firmware preparation:
 * 1) set all GPIOs to analog mode (config_io).
 * 2) disable all power supplies
 *
 *-----------------------------------------------------------
 * 1st test:  Check output level
 *-----------------------------------------------------------
 *
 * 1) enable power supply for instrumentation amplifier
 * 2) apply bias to GPIO 32, can be a current source
 *    through a resistor but may be better to be a voltage
 *    set at 0.6 or 0.7V (need to check simulation for
 *    proper value).
 * 3) apply inputs to GPIO 33 (negative) and GPIO 31
 *    (positive) with common mode voltage to GPIO 35.
 * 4) view analog output on GPIO 11.
 *
 * Basic functional test:  Single-ended output should
 * follow (VINP - VINN) with a fixed gain set by the
 * gain values for gain stage 1 and gain stage 2.
 *
 * Measurements:  Measure the power supply rejection and
 * load response.
 */

// --------------------------------------------------------
// Firmware routines
// --------------------------------------------------------

void delay(const int d)
{
    /* Configure timer for a single-shot countdown */
    reg_timer0_config = 0;
    reg_timer0_data = d;
    reg_timer0_config = 1;

    // Loop, waiting for value to reach zero
    reg_timer0_update = 1;  // latch current value
    while (reg_timer0_value > 0) {
	reg_timer0_update = 1;
    }
}

void config_io() {

    reg_mprj_io_0 = GPIO_MODE_MGMT_STD_ANALOG;

    /* Keep the SPI functional */
    reg_mprj_io_1 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_2 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
    reg_mprj_io_3 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
    reg_mprj_io_4 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;

    reg_mprj_io_5 = GPIO_MODE_MGMT_STD_ANALOG;
    reg_mprj_io_6 = GPIO_MODE_MGMT_STD_ANALOG;
    reg_mprj_io_7 = GPIO_MODE_MGMT_STD_ANALOG;
    reg_mprj_io_8 = GPIO_MODE_MGMT_STD_ANALOG;
    reg_mprj_io_9 = GPIO_MODE_MGMT_STD_ANALOG;
    reg_mprj_io_10 = GPIO_MODE_MGMT_STD_ANALOG;
    reg_mprj_io_11 = GPIO_MODE_MGMT_STD_ANALOG;
    reg_mprj_io_12 = GPIO_MODE_MGMT_STD_ANALOG;
    reg_mprj_io_13 = GPIO_MODE_MGMT_STD_ANALOG;
    reg_mprj_io_14 = GPIO_MODE_MGMT_STD_ANALOG;
    reg_mprj_io_15 = GPIO_MODE_MGMT_STD_ANALOG;
    reg_mprj_io_16 = GPIO_MODE_MGMT_STD_ANALOG;
    reg_mprj_io_17 = GPIO_MODE_MGMT_STD_ANALOG;
    reg_mprj_io_18 = GPIO_MODE_MGMT_STD_ANALOG;

    reg_mprj_io_19 = GPIO_MODE_MGMT_STD_ANALOG;
    reg_mprj_io_20 = GPIO_MODE_MGMT_STD_ANALOG;
    reg_mprj_io_21 = GPIO_MODE_MGMT_STD_ANALOG;
    reg_mprj_io_22 = GPIO_MODE_MGMT_STD_ANALOG;
    reg_mprj_io_23 = GPIO_MODE_MGMT_STD_ANALOG;
    reg_mprj_io_24 = GPIO_MODE_MGMT_STD_ANALOG;
    reg_mprj_io_25 = GPIO_MODE_MGMT_STD_ANALOG;
    reg_mprj_io_26 = GPIO_MODE_MGMT_STD_ANALOG;
    reg_mprj_io_27 = GPIO_MODE_MGMT_STD_ANALOG;
    reg_mprj_io_28 = GPIO_MODE_MGMT_STD_ANALOG;
    reg_mprj_io_29 = GPIO_MODE_MGMT_STD_ANALOG;
    reg_mprj_io_30 = GPIO_MODE_MGMT_STD_ANALOG;
    reg_mprj_io_31 = GPIO_MODE_MGMT_STD_ANALOG;
    reg_mprj_io_32 = GPIO_MODE_MGMT_STD_ANALOG;
    reg_mprj_io_33 = GPIO_MODE_MGMT_STD_ANALOG;
    reg_mprj_io_34 = GPIO_MODE_MGMT_STD_ANALOG;
    reg_mprj_io_35 = GPIO_MODE_MGMT_STD_ANALOG;
    reg_mprj_io_36 = GPIO_MODE_MGMT_STD_ANALOG;
    reg_mprj_io_37 = GPIO_MODE_MGMT_STD_ANALOG;
}


void main()
{
    uint16_t value;

    reg_gpio_mode1 = 1;
    reg_gpio_mode0 = 0;
    reg_gpio_ien = 1;
    reg_gpio_oe = 1;

    reg_mprj_datah = 0;
    reg_mprj_datal = 0;

    config_io();

    reg_mprj_xfer = 1;
    while (reg_mprj_xfer == 1);

    // Initialize controls into the user project through the
    // logic analyzer interface.  This routine also powers down
    // all of the power switches.

    init_logic_analyzer();

    // Enable the power switch to the instrumentation amp
    instramp_enable();
    value = 0;

    // That's all!  Now if the LED on the board is blinking,
    // GPIO 11 should follow (GPIO 31 - GPIO 15) with fixed
    // gain.  The gain stage values are set and incremented
    // during the blink test.  Only gain stage 1 is tested
    // here.

    // To be done:  Apply the gain values through sampled
    // digital inputs, and test directly.

    // Proceed with the blink test.  For most measurements,
    // this should not be enabled to keep the digital
    // environment quieter for analog measurements.

    reg_gpio_out = 1; // OFF

    while(1) {

	reg_mprj_datal = 0x00000000;
	reg_mprj_datah = 0x00000000;

	reg_gpio_out = 0x0;

	delay(1000000);
	value++;
	instramp_set_gain_stage1(value);

	reg_mprj_datal = 0xffffffff;
	reg_mprj_datah = 0xffffffff;

	reg_gpio_out = 0x1;

	delay(1000000);
	value++;
	instramp_set_gain_stage1(value);
    }
}
