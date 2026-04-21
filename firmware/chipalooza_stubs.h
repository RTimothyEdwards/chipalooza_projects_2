/*----------------------------------------------------------------------*/
/* Utility function prototypes for the chipalooza_testchip_2		*/
/*----------------------------------------------------------------------*/
/* Written by Tim Edwards, Open Circuit Design		    		*/
/* April 20, 2026					    		*/
/*----------------------------------------------------------------------*/

/*----------------------------------------------------------------------*/
/* IDAC:  8-bit current DAC						*/
/*----------------------------------------------------------------------*/

void idac_enable();
void idac_disable();
void idac_set_value(uint8_t value);
void idac_ref_select(uint8_t value);

/*----------------------------------------------------------------------*/
/* AUDDAC:  AudioDAC driver						*/
/*----------------------------------------------------------------------*/

void audiodac_enable();
void audiodac_disable();

/*----------------------------------------------------------------------*/
/* CDAC:  12-bit capacitive DAC						*/
/*----------------------------------------------------------------------*/

void cdac_enable();
void cdac_disable();
void cdac_reset(uint8_t value);
void cdac_hold(uint8_t value);
void cdac_set_value(uint16_t value);

/*----------------------------------------------------------------------*/
/* CCOMP:  Comparator for ADC						*/
/*----------------------------------------------------------------------*/

void ccomp_enable();
void ccomp_disable();

/*----------------------------------------------------------------------*/
/* LDO:	 1.8V regulator for a bandgap					*/
/*----------------------------------------------------------------------*/

void ldo_enable();
void ldo_disable();
void ldo_ref_select(uint8_t value);

/*----------------------------------------------------------------------*/
/* OSC16M:  16MHz R-C oscillator					*/
/*----------------------------------------------------------------------*/

void osc16M_enable();
void osc16M_disable();

/*----------------------------------------------------------------------*/
/* VREF:  CMOS 1.2V voltage reference					*/
/*----------------------------------------------------------------------*/

void cmos_vref_enable();
void cmos_vref_disable();
void cmos_vref_set_trim(uint8_t value);

/*----------------------------------------------------------------------*/
/* OSC500K:  500kHz R-C oscillator					*/
/*----------------------------------------------------------------------*/

void osc500k_enable();
void osc500k_disable();

/*----------------------------------------------------------------------*/
/* POR:	Power-on Reset							*/
/*----------------------------------------------------------------------*/

void por_enable();
void por_disable();

/*----------------------------------------------------------------------*/
/* SAMPLE:  Sample and Hold						*/
/*----------------------------------------------------------------------*/

void sample_and_hold_enable();
void sample_and_hold_disable();
void sample_and_hold_cycle(uint16_t delay);
void sample_and_hold_set(uint8_t value);

/*----------------------------------------------------------------------*/
/* ULPCOMP:  Ultra-low-power comparator					*/
/*----------------------------------------------------------------------*/

void ulpcomp_enable();
void ulpcomp_disable();
void ulpcomp_clock_toggle(uint16_t delay);
void ulpcomp_clock_set(uint8_t value);

/*----------------------------------------------------------------------*/
/* INSTRAMP:  Programmable-gain instrumentation amplifier		*/
/*----------------------------------------------------------------------*/

void instramp_enable();
void instramp_disable();
void instramp_set_gain_stage1(uint8_t value);
void instramp_set_gain_stage2(uint8_t value);

/*----------------------------------------------------------------------*/
/* RHEO:  8-bit Rheostat						*/
/*----------------------------------------------------------------------*/

void rheostat_enable();
void rheostat_disable();
void rheostat_set_value(uint8_t value);

/*----------------------------------------------------------------------*/
/* RDAC:  8-bit resistor DAC						*/
/*----------------------------------------------------------------------*/

void rdac_enable();
void rdac_disable();
void rdac_set_value(uint8_t value);

/*----------------------------------------------------------------------*/
/* LOOPBACK:  Switch resistance loopback test				*/
/*----------------------------------------------------------------------*/

void loopback_enable();
void loopback_disable();
void loopback_disable_noisy();

/*----------------------------------------------------------------------*/
/* ALL POWER SUPPLIES (initialization)					*/
/*----------------------------------------------------------------------*/

void powerdown_all();

/*----------------------------------------------------------------------*/
/* Initialize logic analyzrer						*/
/*----------------------------------------------------------------------*/

void init_logic_analyzer();

/*----------------------------------------------------------------------*/
