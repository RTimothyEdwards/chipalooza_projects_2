# Caravel Analog User

[![License](https://img.shields.io/badge/License-Apache%202.0-blue.svg)](https://opensource.org/licenses/Apache-2.0) [![CI](https://github.com/efabless/caravel_user_project_analog/actions/workflows/user_project_ci.yml/badge.svg)](https://github.com/efabless/caravel_user_project_analog/actions/workflows/user_project_ci.yml) [![Caravan Build](https://github.com/efabless/caravel_user_project_analog/actions/workflows/caravan_build.yml/badge.svg)](https://github.com/efabless/caravel_user_project_analog/actions/workflows/caravan_build.yml)

---

| :exclamation: Important Note            |
|-----------------------------------------|

This is the second test chip from the Chipalooza challenge 2024.
15 designs made it on the September tapeout, although many of those were Efabless designs filling
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

	10.	Current bias generator
		sky130_ef_ip__biasgen
		https://github.com/RTimothyEdwards/sky130_ef_ip__biasgen
		Tim Edwards/Efabless

	11.	8-bit IDAC
		sky130_ef_ip__biasgen
		https://github.com/RTimothyEdwards/sky130_ef_ip__biasgen
		Tim Edwards/Efabless

	12.	8-bit RDAC
		sky130_ef_ip__rdac3v_8bit
		https://github.com/RTimothyEdwards/sky130_ef_ip__rdac3v_8bit
		Tim Edwards/Efabless

	13.	Comparator for ADC
		sky130_ef_ip__ccomp3v
		https://github.com/RTimothyEdwards/sky130_ef_ip__ccomp3v
		Tim Edwards/Efabless

	14.	Sample-and-hold
		sky130_ef_ip__samplehold
		https://github.com/RTimothyEdwards/sky130_ef_ip__samplehold
		Tim Edwards/Efabless

	15.	12-bit CDAC
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

All projects are connected either to the logic analyzer (128 I/O bits) or
the GPIO pins.  Generally speaking, static control bits (enable and trim,
for example) are logic analyzer outputs.  Dynamic digital bits are routed
to GPIO digital outputs, while analog I/O are routed to the analog
connections of the GPIO.

Unlike the first test chip, this one has a standardized set of
multiplexers on the GPIO analog pins, allowing each GPIO pin to access
one of two internal analog signals.  Each multiplexer consists of two
isolated switches, each with two control bits, one of which makes the
connection and the other of which grounds the center.  These bits
should never both be enabled (value 1) at the same time;  otherwise,
the analog signal gets shorted to ground.

Each power supply is routed through gated power pFETs so each project
can be powered individually.  Each power supply connection internally
is routed to a bare analog pin for monitoring the supply voltage of
the project.  Be aware that these are ESD-sensitive points!

Some projects take current biases which are distributed by a central
bias current generator circuit.  Various test point bias currents are
connected through ground-isolated switches to GPIO analog signals.

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
		la_data_in[18] =
		la_oeb[18] =
		la_data_in[19] =
		la_oeb[19] =
	sink out = gpio_noesd[8] (pin GPIO 15) when
		la_data_in[16] =
		la_oeb[16] =
		la_data_in[17] =
		la_oeb[17] =

---

LDO
(Alexandre Menu)

---

MOSFET voltage reference
(Adan Kvitschal)

---

Comparator for ADC
(Tim Edwards)

---

12-bit CDAC
(Tim Edwards)

---

16MHz R-C oscillator
(Tim Edwards)

---

Audio sigma-delta ADC output driver
(Harald Pretl)

---

8-bit RDAC
(Tim Edwards)

---

8-bit rheostat
(Tim Edwards)

---

Power-on-reset
(Stephen Wu)

---

Programmable PLL
(Abbas Azeem)

---

Ultra-low-power comparator
(Yun Jan Lee)

---

Sample-and-hold
(Tim Edwards)

---

500MHz R-C oscillator
(Tim Edwards)

---

Current bias generator
(Tim Edwards)

---

