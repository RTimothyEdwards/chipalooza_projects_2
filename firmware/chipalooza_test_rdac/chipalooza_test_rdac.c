#include <defs.h>
#include <chipalooza_stubs.h>

/*
 *-----------------------------------------------------------
 * chipalooza_test_rdac.c:
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
 * 5) connect GPIO 8 to ground (reference low)
 * 6) connect GPIO 10 to power (reference high)
 *
 * Firmware preparation:
 * 1) set all GPIOs to analog mode (config_io).
 * 2) disable all power supplies
 *
 *-----------------------------------------------------------
 * 1st test:  Clock at the blink interval.  Check
 * response.  Output should be a sawtooth wave on 
 * GPIO 7 with approximately rail-to-rail operation.
 *-----------------------------------------------------------
 *
 * 1) enable power supply for RDAC
 * 2) power supply is monitored on GPIO 14.
 * 3) present sawtooth wave on the digital input, incrementing
 *    with the blink cycles.
 * 4) view analog output on GPIO 7
 *
 * Measurements:  Measure linearity, monotonicity, rail-to-rail
 * operation, INL, and DNL.
 *
 * To be done:  Test high and low references by changing
 * GPIO 5 and 6 to digital inputs and setting GPIO 5 high
 * (3.3V) and GPIO 6 low (0V).  Redo all measurements.
 * Do not apply reference voltages to GPIO 8 and GPIO 10
 * in this mode.
 *
 * Set GPIO 5 to an input pull-up and GPIO 6 to an input
 * pull-down.  Do not drive either pad.  Redo all
 * measurements.
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
    unit8_t value;

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

    // Enable the power switch to the RDAC
    rdac_enable();
    value = 0;

    // If the LED on the board is blinking,
    // GPIO 7 should be the output and should be an
    // almost rail-to-rail sawtooth wave.

    // Proceed with the blink test.  For most measurements,
    // this should not be enabled to keep the digital
    // environment quieter for analog measurements.

    reg_gpio_out = 1; // OFF

    while(1) {

	reg_mprj_datal = 0x00000000;
	reg_mprj_datah = 0x00000000;

	reg_gpio_out = 0x0;
	value++;
	rdac_set_value(value);

	delay(1000000);

	reg_mprj_datal = 0xffffffff;
	reg_mprj_datah = 0xffffffff;

	reg_gpio_out = 0x1;
	value++;
	rdac_set_value(value);

	delay(1000000);
    }
}
