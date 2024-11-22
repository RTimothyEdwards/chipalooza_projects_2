# Caravel Analog User

[![License](https://img.shields.io/badge/License-Apache%202.0-blue.svg)](https://opensource.org/licenses/Apache-2.0) [![CI](https://github.com/efabless/caravel_user_project_analog/actions/workflows/user_project_ci.yml/badge.svg)](https://github.com/efabless/caravel_user_project_analog/actions/workflows/user_project_ci.yml) [![Caravan Build](https://github.com/efabless/caravel_user_project_analog/actions/workflows/caravan_build.yml/badge.svg)](https://github.com/efabless/caravel_user_project_analog/actions/workflows/caravan_build.yml)

---

| :exclamation: Important Note            |
|-----------------------------------------|

This is the second test chip from the Chipalooza challenge 2024.
14 designs made it on the September tapeout, although many of those were Efabless designs filling
in gaps for IP not provided through the Chipalooza challenge.

The projects on this tapeout and their source URLs are as follows:


	1.	Power-on-reset
		sky130_sw_ip__bgrref_por
		https://github.com/efabless/sky130_sw_ip__bgrref_por (forked)
		https://github.com/openicdesign/sky130_sw_ip__bgrref_por
		Stephen Wu

	2.	Ultra-low-power comparator
		sky130_icrg_ip__ulpcomp
		https://github.com/efabless/sky130_icrg_ip__ulpcomp (forked)
		https://github.com/JYSquare2/sky130_ef_ip__ulpcomp
		ICRG (Lee Jun Yan and team)

	3.	MOSFET voltage reference
		sky130_ak_ip__cmos_vref
		https://github.com/efabless/sky130_ak_ip__cmos_vref (forked)
		https://gihub.com/adankvitschal/sky130_ak_ip__cmos_vref
		Adan Kvitschal

	4.	LDO
		sky130_am_ip__ldo_01v8
		https://github.com/efabless/sky130_am_ip__ldo_01v8 (forked)
		https://github.com/AlexMenu/sky130_am_ip__ldo_01v8
		Alexandre Menu

	5.	Programmable PLL
		sky130_aa_ip__programmable_pll
		https://github.com/efabless/sky130_aa_ip__programmable_pll (forked)
		https://github.com/Azeem-Abbas/Sky130_ef_ip__Programmable_PLL
		Hafiz Azeem Abbas and team

	6.	Audio sigma-delta ADC output driver
		sky130_iic_ip__audiodac_v1
		https://github.com/efabless/sky130_iic_ip__audiodac_v1 (forked)
		https://github.com/iic-jku/iic-audiodac-v1
		IIC-JKU (Harald Pretl)

	7.	16MHz R-C oscillator
		sky130_ef_ip__rc_osc_16M
		https://github.com/RTimothyEdwards/sky130_ef_ip__rc_osc_16M
		Tim Edwards/Efabless

	8.	500MHz R-C oscillator
		sky130_ef_ip__rc_osc_500k
		https://github.com/RTimothyEdwards/sky130_ef_ip__rc_osc_500k
		Tim Edwards/Efabless

	9.	8-bit rheostat
		sky130_ef_ip__rheostat_8bit
		https://github.com/RTimothyEdwards/sky130_ef_ip__rheostat_8bit
		Tim Edwards/Efabless

	10.	8-bit IDAC
		sky130_ef_ip__biasgen
		https://github.com/RTimothyEdwards/sky130_ef_ip__biasgen
		Tim Edwards/Efabless

	11.	8-bit RDAC
		sky130_ef_ip__rdac3v_8bit
		https://github.com/RTimothyEdwards/sky130_ef_ip__rdac3v_8bit
		Tim Edwards/Efabless

	12.	Comparator for ADC
		sky130_ef_ip__ccomp3v
		https://github.com/RTimothyEdwards/sky130_ef_ip__ccomp3v
		Tim Edwards/Efabless

	13.	Sample-and-hold
		sky130_ef_ip__samplehold
		https://github.com/RTimothyEdwards/sky130_ef_ip__samplehold
		Tim Edwards/Efabless

	14.	12-bit CDAC
		sky130_ef_ip__cdac3v_12bit
		https://github.com/RTimothyEdwards/sky130_ef_ip__cdac3v_12bit
		Tim Edwards/Efabless

(Documentation, including test instructions, still needs to be completed)

:---: | :---

Building:

Get the dependencies above by doing "make get_ip_blocks" in the top level
directory.  This will clone all of the IP blocks from various github
repository sources into the "dependencies" directory.

The test chip is generated in magic by running magic in the mag/ directory
and issuing the command "source construct_testchip.tcl".

Verifying:

In the top level directory, do "make run-precheck".  This requires at
least setting environment variables PDK_ROOT, PDK, and PRECHECK_ROOT.
If the PDK is installed with open_pdks, then PRECHECK_ROOT can be set
to open_pdks/sources/precheck_sky130.

Testing:

All projects are connected either to the logic analyzer (256 I/O bits) or
the GPIO pins.  Generally speaking, static control bits (enable and trim,
for example) are logic analyzer outputs.  Dynamic digital bits are routed
to GPIO digital outputs, while analog I/O are routed to the analog
connections of the GPIO.  Each GPIO will need to be configured for
digital input, digital output, or analog operation by the program running
the test.  Because the number of digital outputs exceeds the 128-bit
width of the logic analyzer, both "la_data_in" and "la_oenb" lines (which
are effectively just additional output bits) have been used.

Unlike the first test chip, this one has a standardized set of
multiplexers on the GPIO analog pins, allowing each GPIO pin to access
one of two internal analog signals (otherwise, there would not be enough
GPIO pins to accommodate all of the test points needed for every analog
block).  Each multiplexer consists of two isolated switches, each with two
control bits, one of which makes the connection and the other of which
grounds the center.  These bits should never both be enabled (value 1) at
the same time;  otherwise, the analog signal gets shorted to ground.
These are not, strictly speaking, multiplexers;  they are two independent
switches connected to the same pin.  For that reason, both switches
should not be enabled at the same time.  In the list of analog blocks and
their control signals, below, both the controls for the output of the
block in question, and the controls for the other analog block connected
to the same GPIO.

Each power supply is routed through gated power pFETs so each project
can be powered individually.  Each power supply connection internally
is routed to a bare analog pin for monitoring the supply voltage of the
project, for 11 of the 14 projects (because only 11 bare-analog pins are
available).  Be aware that these are ESD-sensitive points!

Project circuit blocks are described below, starting at the top left
corner of the chip and working counterclockwise around the chip
perimeter.

8-bit IDAC
(Tim Edwards)
Enable:	la_oenb[35]
Bias:   Internally self-biased when Reference select = 0
Bias:	gpio_analog[17] (pin GPIO 24) set externally to 1.2V nominal
	when Reference select = 1
Reference select:  la_data_in[35] (0 = internal self-bias, 1 = external bias)
Upstream analog power supply: vdda2/vssa2
Upstream digital power supply: vccd2/vssd2
Power supply monitor:  (none)
Power supply enable: la_data_in[47]
Digital input:
	8-bit value vector is:
		la_data_in[31], la_oenb[31], la_data_in[32], la_oenb[32],
		la_data_in[33], la_oenb[33], la_data_in[34], la_oenb[34],
Analog output:
	source out = gpio_noesd[7] (pin GPIO 14) when
		la_data_in[18] = 0 (no ground shunt)
		la_oeb[18] = 1 (connect channel)
		la_data_in[19] = 1 (ground shunt on other channel)
		la_oeb[19] = 0 (disconnect other channel)
	sink out = gpio_noesd[8] (pin GPIO 15) when
		la_data_in[16] = 0 (no ground shunt)
		la_oeb[16] = 1 (connect channel)
		la_data_in[17] = 1 (ground shunt on other channel)
		la_oeb[17] = 0 (disconnect other channel)
Analog input:
	IDAC reference trim: gpio_noesd[10] (pin GPIO 17) when 
		la_data_in[12] = 0 (no ground shunt)
		la_oeb[12] = 1 (connect channel)
		la_data_in[13] = 1 (ground shunt on other channel)
		la_oeb[13] = 0 (disconnect other channel)

---

LDO
(Alexandre Menu)

Enable:	la_oenb[30]
Bias:   Internally self-biased when Reference select = 0
Bias:	gpio_analog[17] (pin GPIO 24) set externally to 1.2V nominal
	when Reference select = 1
Reference select:  la_data_in[30] (0 = internal self-bias, 1 = external bias)
Upstream analog power supply: vdda2/vssa2
Upstream digital power supply: vccd2/vssd2
Power supply monitor:  io_analog[10] (pin GPIO 24)
Power supply enable: la_data_in[46]
Analog output:
	voltage out = gpio_noesd[9] (pin GPIO 16) when
		la_data_in[14] = 0 (no ground shunt)
		la_oeb[14] = 1 (connect channel)
		la_data_in[15] = 1 (ground shunt on other channel)
		la_oeb[15] = 0 (disconnect other channel)

---

MOSFET voltage reference
(Adan Kvitschal)

Enable:	la_oenb[27]
Upstream analog power supply: vccd2/vssd2 (note this is a 1.8V supply)
Upstream digital power supply: vccd2/vssd2
Power supply monitor:  io_analog[9] (pin GPIO 23)
Power supply enable: la_data_in[45]
Trim: la_data_in[28], la_oenb[28], la_data_in[29], la_oenb[29]
Analog outputs:
	vbg reference out = gpio_noesd[8] (pin GPIO 15) when
		la_data_in[17] = 0 (no ground shunt)
		la_oeb[17] = 1 (connect channel)
		la_data_in[16] = 1 (ground shunt on other channel)
		la_oeb[16] = 0 (disconnect other channel)
	vbgsc reference out = gpio_noesd[9] (pin GPIO 16) when
		la_data_in[15] = 0 (no ground shunt)
		la_oeb[15] = 1 (connect channel)
		la_data_in[14] = 1 (ground shunt on other channel)
		la_oeb[14] = 0 (disconnect other channel)
	vbgtg reference out = gpio_noesd[10] (pin GPIO 17) when
		la_data_in[13] = 0 (no ground shunt)
		la_oeb[13] = 1 (connect channel)
		la_data_in[12] = 1 (ground shunt on other channel)
		la_oeb[12] = 0 (disconnect other channel)
	vptat reference out = gpio_noesd[11] (pin GPIO 18) when
		la_data_in[19] = 0 (no ground shunt)
		la_oeb[19] = 1 (connect channel)
		la_data_in[18] = 1 (ground shunt on other channel)
		la_oeb[18] = 0 (disconnect other channel)

---

Comparator for ADC
(Tim Edwards)

Enable:	la_data_in[27]
Upstream analog power supply: vdda2/vssa2
Upstream digital power supply: vccd2/vssd2
Power supply monitor:  io_analog[8] (pin GPIO 22)
Power supply enable: la_data_in[44]
Analog output:
	io_out[17] (pin GPIO 28)
Analog inputs:
	in positive = gpio_noesd[11] (pin GPIO 18) when
		la_data_in[10] = 0 (no ground shunt)
		la_oeb[10] = 1 (connect channel)
		la_data_in[11] = 1 (ground shunt on other channel)
		la_oeb[11] = 0 (disconnect other channel)
	in negative = gpio_noesd[12] (pin GPIO 19) when
		la_data_in[8] = 0 (no ground shunt)
		la_oeb[8] = 1 (connect channel)
		la_data_in[9] = 1 (ground shunt on other channel)
		la_oeb[9] = 0 (disconnect other channel)

---

12-bit CDAC
(Tim Edwards)

Enable:	N/A
Upstream analog power supply: vdda2/vssa2
Upstream digital power supply: vccd2/vssd2
Power supply monitor:  io_analog[7] (pin GPIO 21)
Power supply enable: la_data_in[43]
Analog inputs:
	reference high = gpio_noesd[11] (pin GPIO 18) when
		la_data_in[11] = 0 (no ground shunt)
		la_oeb[11] = 1 (connect channel)
		la_data_in[10] = 1 (ground shunt on other channel)
		la_oeb[10] = 0 (disconnect other channel)
	reference low = gpio_noesd[12] (pin GPIO 19) when
		la_data_in[9] = 0 (no ground shunt)
		la_oeb[9] = 1 (connect channel)
		la_data_in[8] = 1 (ground shunt on other channel)
		la_oeb[8] = 0 (disconnect other channel)
Analog output:
	CDAC out = gpio_noesd[13] (pin GPIO 20) when
		la_data_in[7] = 0 (no ground shunt)
		la_oeb[7] = 1 (connect channel)
		la_data_in[6] = 1 (ground shunt on other channel)
		la_oeb[6] = 0 (disconnect other channel)
Digital inputs:
	reset = la_oenb[26]
	12-bit value =
		la_oenb[20], la_data_in[21], la_oenb[21], la_data_in[22],
		la_oenb[22], la_data_in[23], la_oenb[23], la_data_in[24],
		la_oenb[24], la_data_in[25], la_oenb[25], la_data_in[26]

---

16MHz R-C oscillator
(Tim Edwards)

Enable:	la_data_in[20]
Upstream analog power supply: vdda2/vssa2
Upstream digital power supply: vccd2/vssd2
Power supply monitor:  io_analog[6] (pin GPIO 20)
Power supply enable: la_data_in[42]
Output: io_out[21] (GPIO 21)

---

Audio sigma-delta ADC output driver
(Harald Pretl)

Enable:	N/A (As a digital driver, it does not consume power unless driven.)
Upstream analog power supply: vccd2/vccd2 (note this is a 1.8V supply)
Upstream digital power supply: vccd2/vssd2
Power supply monitor:  io_analog[5] (pin GPIO 19)
Power supply enable: la_data_in[41]
Digital inputs:
	positive: io_in[26] (GPIO 37)
	negative: io_in[25] (GPIO 36)
Analog outputs:
	positive: gpio_noesd[16] (pin GPIO 23) when
		la_data_in[1] = 0 (no ground shunt)
		la_oeb[1] = 1 (connect channel)
		la_data_in[0] = 1 (ground shunt on other channel)
		la_oeb[0] = 0 (disconnect other channel)
	negative: gpio_noesd[15] (pin GPIO 22) when
		la_data_in[3] = 0 (no ground shunt)
		la_oeb[3] = 1 (connect channel)
		la_data_in[2] = 1 (ground shunt on other channel)
		la_oeb[2] = 0 (disconnect other channel)

---

8-bit RDAC
(Tim Edwards)

Enable:	la_oenb[115]
Upstream analog power supply: vdda1/vdda1
Upstream digital power supply: vccd1/vssd1
Power supply monitor:  io_analog[0] (pin GPIO 14)
Power supply enable: la_data_in[54]

Analog inputs:
	reference high = gpio_noesd[3] (pin GPIO 18) when
		la_oeb[123] = 0 (no ground shunt)
		la_data_in[123] = 1 (connect channel)
		la_oeb[122] = 1 (ground shunt on other channel)
		la_data_in[122] = 0 (disconnect other channel)
	reference low = gpio_noesd[1] (pin GPIO 19) when
		la_oeb[125] = 0 (no ground shunt)
		la_data_in[125] = 1 (connect channel)
		la_oeb[124] = 1 (ground shunt on other channel)
		la_data_in[124] = 0 (disconnect other channel)

Analog output:
	RDAC out = gpio_noesd[0] (pin GPIO 16) when
		la_oeb[126] = 0 (no ground shunt)
		la_data_in[126] = 1 (connect channel)
		la_oeb[127] = 1 (ground shunt on other channel)
		la_data_in[127] = 0 (disconnect other channel)
Digital input:
	la_data_in[115], la_oenb[114], la_data_in[114], la_oenb[113],
	la_data_in[113], la_oenb[112], la_data_in[112], la_oenb[111]

---

8-bit rheostat
(Tim Edwards)

Enable:	N/A
Upstream analog power supply: vdda1/vdda1
Upstream digital power supply: vccd1/vssd1
Power supply monitor:  io_analog[1] (pin GPIO 15)
Power supply enable: la_data_in[53]

Analog inputs:
	reference high = gpio_noesd[3] (pin GPIO 18) when
		la_oeb[122] = 0 (no ground shunt)
		la_data_in[122] = 1 (connect channel)
		la_oeb[123] = 1 (ground shunt on other channel)
		la_data_in[123] = 0 (disconnect other channel)
	reference low = gpio_noesd[1] (pin GPIO 19) when
		la_oeb[124] = 0 (no ground shunt)
		la_data_in[124] = 1 (connect channel)
		la_oeb[125] = 1 (ground shunt on other channel)
		la_data_in[125] = 0 (disconnect other channel)

Analog output:
	RDAC out = gpio_noesd[0] (pin GPIO 16) when
		la_oeb[127] = 0 (no ground shunt)
		la_data_in[127] = 1 (connect channel)
		la_oeb[126] = 1 (ground shunt on other channel)
		la_data_in[126] = 0 (disconnect other channel)
Digital input:
	la_data_in[111], la_oenb[110], la_data_in[110], la_oenb[109],
	la_data_in[109], la_oenb[108], la_data_in[108], la_oenb[107]

---

Power-on-reset
(Stephen Wu)

Enable:	N/A
Bias:	gpio_analog[17] (pin GPIO 24) set externally to 1.2V nominal
Upstream analog power supply: vdda1/vdda1
Upstream digital power supply: vccd1/vssd1
Power supply monitor:  io_analog[2] (pin GPIO 16)
Power supply enable: la_data_in[52]
Digital outputs:
	por:	io_out[7] (GPIO 7)
	porb:	io_out[8] (GPIO 8)
	porb_h:	gpio_noesd[5] (pin GPIO 21) when
		la_oeb[118] = 0 (no ground shunt)
		la_data_in[118] = 1 (connect channel)
		la_oeb[119] = 1 (ground shunt on other channel)
		la_data_in[119] = 0 (disconnect other channel)

---

Programmable PLL
(Azeem Abbas)

Upstream analog power supply: vccd1/vccd1 (note this is a 1.8V supply)
Upstream digital power supply: N/A (single supply)
Power supply monitor:  N/A
Power supply enable: la_data_in[51]
Analog I/O:
	lowpass filter = gpio_noesd[4] (pin GPIO 11) when
		la_oeb[120] = 0 (no ground shunt)
		la_data_in[120] = 1 (connect channel)
		la_oeb[121] = 1 (ground shunt on other channel)
		la_data_in[121] = 0 (disconnect other channel)
	fin = gpio_noesd[13] (pin GPIO 20) when
		la_data_in[6] = 0 (no ground shunt)
		la_oeb[6] = 1 (connect channel)
		la_data_in[7] = 1 (ground shunt on other channel)
		la_oeb[7] = 0 (disconnect other channel)
	ibias = gpio_noesd[14] (pin GPIO 21) when
		la_data_in[5] = 0 (no ground shunt)
		la_oeb[5] = 1 (connect channel)
		la_data_in[4] = 1 (ground shunt on other channel)
		la_oeb[4] = 0 (disconnect other channel)
	vctrl_in = gpio_noesd[15] (pin GPIO 22) when
		la_data_in[2] = 0 (no ground shunt)
		la_oeb[2] = 1 (connect channel)
		la_data_in[3] = 1 (ground shunt on other channel)
		la_oeb[3] = 0 (disconnect other channel)
Digital inputs:
	S7-S1:  la_data_in[100], la_data_in[103], la_oenb[100], la_data_in[101],
		la_oenb[101], la_data_in[102], la_data_in[104]
	D19-D12: la_data_in[92], la_oenb[92], la_data_in[93], la_oenb[93],
		la_data_in[94], la_oenb[94], la_data_in[95], la_oenb[95]
	D10-D0: la_data_in[106], la_oenb[105], la_data_in[105], la_oenb[104],
		la_data_in[99], la_oenb[98], la_data_in[98], la_oenb[97],
		la_data_in[97], la_oenb[96], la_data_in[96]
Digital outputs:
	prescaler: io_out[20] (GPIO 31)
	up_out: io_out[11] (GPIO 11)
	dn_out: io_out[12] (GPIO 12)
	div_out: io_out[15] (GPIO 26)
	out: io_out[16] (GPIO 27)
	outb: io_out[14] (GPIO 25)
	out_usb: io_out[19] (GPIO 30)
	out_core: io_out[18] (GPIO 29)

Warning: system runs at 1.8V supply but analog pins are not limited;
make sure applied voltage does not exceed the 1.8V rail on lowpass
filter, fin, ibias, and vctrl_in.

---

Ultra-low-power comparator
(Yun Jan Lee)

Enable:	la_data_in[107]
Upstream analog power supply: vdda1/vssa1
Upstream digital power supply: vccd1/vssd1
Power supply monitor:  io_analog[3] (pin GPIO 17)
Power supply enable: la_data_in[50]
Analog output:
	io_out[10] (pin GPIO 10)
Analog inputs:
	in positive = gpio_noesd[4] (pin GPIO 11) when
		la_oeb[121] = 0 (no ground shunt)
		la_data_in[121] = 1 (connect channel)
		la_oeb[120] = 1 (ground shunt on other channel)
		la_data_in[120] = 0 (disconnect other channel)
	in negative = gpio_noesd[6] (pin GPIO 13) when
		la_oeb[116] = 0 (no ground shunt)
		la_data_in[116] = 1 (connect channel)
		la_oeb[117] = 1 (ground shunt on other channel)
		la_data_in[117] = 0 (disconnect other channel)
Digital clock: la_oenb[106]

---

Sample-and-hold
(Tim Edwards)

Enable:	la_data_in[91]
Upstream analog power supply: vdda1/vssa1
Upstream digital power supply: vccd1/vssd1
Power supply monitor:  N/A
Power supply enable: la_data_in[50]
Analog input:
	sample in = gpio_noesd[5] (pin GPIO 12) when
		la_oeb[119] = 0 (no ground shunt)
		la_data_in[119] = 1 (connect channel)
		la_oeb[118] = 1 (ground shunt on other channel)
		la_data_in[118] = 0 (disconnect other channel)
Analog output:
	sample out = gpio_noesd[6] (pin GPIO 13) when
		la_oeb[117] = 0 (no ground shunt)
		la_data_in[117] = 1 (connect channel)
		la_oeb[116] = 1 (ground shunt on other channel)
		la_data_in[116] = 0 (disconnect other channel)
Digital hold: la_oenb[91] 

---

500MHz R-C oscillator
(Tim Edwards)

Enable:	la_oenb[90]
Upstream analog power supply: vdda1/vssa1
Upstream digital power supply: vccd1/vssd1
Power supply monitor:  io_analog[4] (pin GPIO 18)
Power supply enable: la_data_in[48]
Output: io_out[13] (GPIO 13)

---

Loopback test

There is a loopback test connecting two switches that allows the
switch resistance (specifically, the resistance of two switches
in series), and to measure coupling across a switch when the
ground isolation is enabled or disabled.

Analog I/O:
	loopback 1 = gpio_noesd[14] (pin GPIO 25) when
		la_data_in[5] = 0 (no ground shunt)
		la_oeb[5] = 1 (connect channel)
		la_data_in[4] = 1 (ground shunt on other channel)
		la_oeb[4] = 0 (disconnect other channel)
	loopback 2 = gpio_noesd[16] (pin GPIO 27) when
		la_data_in[0] = 0 (no ground shunt)
		la_oeb[0] = 1 (connect channel)
		la_data_in[1] = 1 (ground shunt on other channel)
		la_oeb[1] = 0 (disconnect other channel)

---

