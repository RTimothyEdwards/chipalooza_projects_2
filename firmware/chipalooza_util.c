/*------------------------------------------------*/
/* Utility functions for the chipalooza_testchip2 */
/*------------------------------------------------*/
/* Written by Tim Edwards, Open Circuit Design	  */
/* April 19, 2026				  */
/*------------------------------------------------*/

#include "defs.h"
#include "chipalooza_defs.h"

/* Project enables.  Select a project.  Projects are individually
 * enabled or disabled.
 */

/* Implementation note:  The RISC-V compiler is unable to perform
 * logical/arithmetic operations in place on a memory mapped locations,
 * so "reg_la1_data |= VALUE" is invalid and must be written as
 * "value = reg_la1_data | VALUE; reg_la1_data = value".
 */

/*----------------------------------------------------------------------*/
/* IDAC:  8-bit current DAC						*/ 
/*----------------------------------------------------------------------*/

void idac_enable()
{
    uint32_t value;

    /* Power supply enable */
    value = reg_la1_data;
    value &= ~IDAC_PWR_NENABLE;
    reg_la1_data = value;

    /* Local enable */
    value = reg_la2_oenb;
    value |= IDAC_ENABLE;
    reg_la2_oenb = value;

    /* Clear ref select */
    value = reg_la1_data;
    value &= ~IDAC_REF_SELECT;

    /* Set data value to zero when IDAC is enabled */
    value = reg_la0_data;
    value &= ~IDAC_VALUE_7;
    reg_la0_data = value;

    value = reg_la1_data;
    value &= ~(IDAC_VALUE_5 | IDAC_VALUE_3 | IDAC_VALUE_1);
    reg_la1_data = value;

    value = reg_la2_oenb;
    value &= ~(IDAC_VALUE_6 | IDAC_VALUE_4 | IDAC_VALUE_2 | IDAC_VALUE_0);
    reg_la2_oenb = value;

    /* Break before make */
    value = reg_la0_data;
    value &= ~(IDAC_VCM_GROUND | IDAC_REF_TRIM_GROUND |
		IDAC_SINK_OUT_GROUND | IDAC_SOURCE_OUT_GROUND);
    reg_la0_data = value;

    value = reg_la0_oenb;
    value |= IDAC_VCM_ENABLE;
    reg_la0_oenb = value;

    value = reg_la1_oenb;
    value |= IDAC_REF_TRIM_ENABLE | IDAC_SINK_OUT_ENABLE | IDAC_SOURCE_OUT_ENABLE;
    reg_la1_oenb = value;
}

void idac_disable()
{
    uint32_t value;

    /* Break before make */
    value = reg_la0_oenb;
    value &= ~IDAC_VCM_ENABLE;
    reg_la0_oenb = value;

    value = reg_la1_oenb;
    value &= ~(IDAC_REF_TRIM_ENABLE | IDAC_SINK_OUT_ENABLE | IDAC_SOURCE_OUT_ENABLE);
    reg_la1_oenb = value;

    value = reg_la0_data;
    value |= IDAC_VCM_GROUND | IDAC_REF_TRIM_GROUND |
		IDAC_SINK_OUT_GROUND | IDAC_SOURCE_OUT_GROUND;
    reg_la0_data = value;

    /* Clear ref select */
    value = reg_la1_data;
    value &= ~IDAC_REF_SELECT;

    /* Set data value to zero when IDAC is disabled */
    value = reg_la0_data;
    value &= ~IDAC_VALUE_7;
    reg_la0_data = value;

    value = reg_la1_data;
    value &= ~(IDAC_VALUE_5 | IDAC_VALUE_3 | IDAC_VALUE_1);
    reg_la1_data = value;

    value = reg_la2_oenb;
    value &= ~(IDAC_VALUE_6 | IDAC_VALUE_4 | IDAC_VALUE_2 | IDAC_VALUE_0);
    reg_la2_oenb = value;

    /* Local enable */
    value = reg_la2_oenb;
    value &= ~IDAC_ENABLE;
    reg_la2_oenb = value;

    /* Power supply disable */
    value = reg_la1_data;
    value |= IDAC_PWR_NENABLE;
    reg_la1_data = value;
}

void idac_set_value(uint8_t value)
{
    uint32_t ovalue1, ovalue2, ovalue3;

    /* The IDAC value is scrambled between three different registers.
     * Because of this, the IDAC can only be changed in three
     * instruction cycles, forcing a glitch in between.
     */

    ovalue1 = reg_la0_data;
    ovalue1 &= ~IDAC_VALUE_7;
    if (((uint32_t)value & 0x80) != 0) ovalue1 |= IDAC_VALUE_7;

    ovalue2 = reg_la1_data;
    ovalue2 &= ~(IDAC_VALUE_5 | IDAC_VALUE_3 | IDAC_VALUE_1);
    if (((uint32_t)value & 0x20) != 0) ovalue2 |= IDAC_VALUE_5;
    if (((uint32_t)value & 0x08) != 0) ovalue2 |= IDAC_VALUE_3;
    if (((uint32_t)value & 0x02) != 0) ovalue2 |= IDAC_VALUE_1;

    ovalue3 = reg_la2_oenb;
    ovalue3 &= ~(IDAC_VALUE_6 | IDAC_VALUE_4 | IDAC_VALUE_2 | IDAC_VALUE_0);
    if (((uint32_t)value & 0x40) != 0) ovalue3 |= IDAC_VALUE_6;
    if (((uint32_t)value & 0x10) != 0) ovalue3 |= IDAC_VALUE_4;
    if (((uint32_t)value & 0x04) != 0) ovalue3 |= IDAC_VALUE_2;
    if (((uint32_t)value & 0x01) != 0) ovalue3 |= IDAC_VALUE_0;

    reg_la0_data = ovalue1;
    reg_la1_data = ovalue2;
    reg_la2_oenb = ovalue3;
}

void idac_ref_select(uint8_t value)
{
    uint32_t ovalue;

    ovalue = reg_la1_data;
    ovalue &= ~IDAC_REF_SELECT;
    if (((uint32_t)value & 0x01) != 0) ovalue |= IDAC_REF_SELECT;

    reg_la1_data = ovalue;
}

/*----------------------------------------------------------------------*/
/* AUDDAC:  AudioDAC driver						*/
/*----------------------------------------------------------------------*/

void audiodac_enable()
{
    uint32_t value;

    /* Power enable */
    value = reg_la1_data;
    value &= ~AUDDAC_PWR_NENABLE; 
    reg_la1_data = value;

    /* Break before make */
    value = reg_la0_data;
    value &= ~(AUDDAC_OUTP_GROUND | AUDDAC_OUTN_GROUND);
    reg_la0_data = value;

    value = reg_la0_oenb;
    value |= AUDDAC_OUTP_ENABLE | AUDDAC_OUTN_ENABLE;
    reg_la0_oenb = value;
}

void audiodac_disable()
{
    uint32_t value;

    /* Break before make */
    value = reg_la0_oenb;
    value &= ~(AUDDAC_OUTP_ENABLE | AUDDAC_OUTN_ENABLE);
    reg_la0_oenb = value;

    value = reg_la0_data;
    value |= AUDDAC_OUTP_GROUND | AUDDAC_OUTN_GROUND;
    reg_la0_data = value;

    /* Power disable */
    value = reg_la1_data;
    value |= AUDDAC_PWR_NENABLE; 
    reg_la1_data = value;
}

/*----------------------------------------------------------------------*/
/* CDAC:  12-bit capacitive DAC						*/
/*----------------------------------------------------------------------*/

void cdac_enable()
{
    uint32_t value;

    /* Power enable */
    value = reg_la1_data;
    value &= ~CDAC_PWR_NENABLE; 
    reg_la1_data = value;

    /* Set value to zero */
    value = reg_la0_data;
    value &= ~(CDAC_VALUE_10 | CDAC_VALUE_8 | CDAC_VALUE_6 |
		CDAC_VALUE_4 | CDAC_VALUE_2 | CDAC_VALUE_0);
    reg_la0_data = value;

    value = reg_la1_oenb;
    value &= ~(CDAC_VALUE_11 | CDAC_VALUE_9 | CDAC_VALUE_7 |
		CDAC_VALUE_5 | CDAC_VALUE_3 | CDAC_VALUE_1);
    reg_la1_oenb = value;

    /* Set "hold" to zero */
    value = reg_la2_data;
    value &= ~CDAC_HOLD;
    reg_la2_data = value;

    /* Set "reset" to zero */
    value = reg_la1_oenb;
    value &= ~CDAC_RESET;
    reg_la1_oenb = value;
    
    /* Break before make */
    value = reg_la0_data;
    value &= ~(CDAC_VIN_GROUND | CDAC_OUT_GROUND |
		CDAC_REFH_GROUND | CDAC_REFL_GROUND);
    reg_la0_data = value;

    value = reg_la0_oenb;
    value |= CDAC_VIN_ENABLE | CDAC_OUT_ENABLE;
    reg_la0_oenb = value;

    value = reg_la1_oenb;
    value |= CDAC_REFH_ENABLE | CDAC_REFL_ENABLE;
    reg_la1_oenb = value;
}

void cdac_disable()
{
    uint32_t value;

    /* Break before make */
    value = reg_la0_oenb;
    value &= ~(CDAC_VIN_ENABLE | CDAC_OUT_ENABLE);
    reg_la0_oenb = value;

    value = reg_la1_oenb;
    value &= ~(CDAC_REFH_ENABLE | CDAC_REFL_ENABLE);
    reg_la1_oenb = value;

    value = reg_la0_data;
    value |= CDAC_VIN_GROUND | CDAC_OUT_GROUND |
		CDAC_REFH_GROUND | CDAC_REFL_GROUND;
    reg_la0_data = value;

    /* Set "reset" to zero */
    value = reg_la1_oenb;
    value &= ~CDAC_RESET;
    reg_la1_oenb = value;
    
    /* Set "hold" to zero */
    value = reg_la2_data;
    value &= ~CDAC_HOLD;
    reg_la2_data = value;

    /* Set value to zero */
    value = reg_la0_data;
    value &= ~(CDAC_VALUE_10 | CDAC_VALUE_8 | CDAC_VALUE_6 |
		CDAC_VALUE_4 | CDAC_VALUE_2 | CDAC_VALUE_0);
    reg_la0_data = value;

    value = reg_la1_oenb;
    value &= ~(CDAC_VALUE_11 | CDAC_VALUE_9 | CDAC_VALUE_7 |
		CDAC_VALUE_5 | CDAC_VALUE_3 | CDAC_VALUE_1);
    reg_la1_oenb = value;

    /* Power disable */
    value = reg_la1_data;
    value |= CDAC_PWR_NENABLE; 
    reg_la1_data = value;
}

void cdac_reset(uint8_t value)
{
    uint32_t ovalue;

    ovalue = reg_la1_oenb;
    ovalue &= ~CDAC_RESET;
    if (((uint32_t)value & 0x01) != 0) ovalue |= CDAC_RESET;
    reg_la1_oenb = ovalue;
}

void cdac_hold(uint8_t value)
{
    uint32_t ovalue;

    ovalue = reg_la2_data;
    ovalue &= ~CDAC_HOLD;
    if (((uint32_t)value & 0x01) != 0) ovalue |= CDAC_HOLD;
    reg_la2_data = ovalue;
}

void cdac_set_value(uint16_t value)
{
    uint32_t ovalue1, ovalue2;

    /* The CDAC value is scrambled between reg_la1_oenb
     * and reg_la0_data.  Because of this, the CDAC can only be changed
     * in two instruction cycles, forcing a glitch in between.
     */

    ovalue1 = reg_la1_oenb;
    ovalue1 &= ~(CDAC_VALUE_1 | CDAC_VALUE_3 | CDAC_VALUE_5 | CDAC_VALUE_7 |
		CDAC_VALUE_9 | CDAC_VALUE_11);
    if (((uint32_t)value & 0x0002) != 0) ovalue2 |= CDAC_VALUE_1;
    if (((uint32_t)value & 0x0008) != 0) ovalue2 |= CDAC_VALUE_3;
    if (((uint32_t)value & 0x0020) != 0) ovalue2 |= CDAC_VALUE_5;
    if (((uint32_t)value & 0x0080) != 0) ovalue2 |= CDAC_VALUE_7;
    if (((uint32_t)value & 0x0200) != 0) ovalue2 |= CDAC_VALUE_9;
    if (((uint32_t)value & 0x0800) != 0) ovalue2 |= CDAC_VALUE_11;

    ovalue2 = reg_la0_data;
    ovalue2 &= ~(CDAC_VALUE_0 | CDAC_VALUE_2 | CDAC_VALUE_4 | CDAC_VALUE_6 |
		CDAC_VALUE_8 | CDAC_VALUE_10);
    if (((uint32_t)value & 0x0001) != 0) ovalue1 |= CDAC_VALUE_0;
    if (((uint32_t)value & 0x0004) != 0) ovalue1 |= CDAC_VALUE_2;
    if (((uint32_t)value & 0x0010) != 0) ovalue1 |= CDAC_VALUE_4;
    if (((uint32_t)value & 0x0040) != 0) ovalue1 |= CDAC_VALUE_6;
    if (((uint32_t)value & 0x0100) != 0) ovalue1 |= CDAC_VALUE_8;
    if (((uint32_t)value & 0x0400) != 0) ovalue1 |= CDAC_VALUE_10;

    reg_la1_oenb = ovalue1;
    reg_la0_data = ovalue2;
}

/*----------------------------------------------------------------------*/
/* CCOMP:  Comparator for ADC						*/
/*----------------------------------------------------------------------*/

void ccomp_enable()
{
    uint32_t value;

    /* Power enable */
    value = reg_la1_data;
    value &= ~CCOMP_PWR_NENABLE; 
    reg_la1_data = value;

    /* Local enable */
    value = reg_la0_data;
    value |= CCOMP_ENABLE; 
    reg_la0_data = value;
    
    /* Break before make */
    value = reg_la0_data;
    value &= ~(CCOMP_INN_GROUND | CCOMP_INP_GROUND);
    reg_la0_data = value;

    value = reg_la0_oenb;
    value |= CCOMP_INN_ENABLE | CCOMP_INP_ENABLE;
    reg_la0_oenb = value;
}

void ccomp_disable()
{
    uint32_t value;

    /* Break before make */
    value = reg_la0_oenb;
    value &= ~(CCOMP_INN_ENABLE | CCOMP_INP_ENABLE);
    reg_la0_oenb = value;

    value = reg_la0_data;
    value |= CCOMP_INN_GROUND | CCOMP_INP_GROUND;
    reg_la0_data = value;

    /* Local disable */
    value = reg_la0_data;
    value &= ~CCOMP_ENABLE; 
    reg_la0_data = value;
    
    /* Power disable */
    value = reg_la1_data;
    value |= CCOMP_PWR_NENABLE; 
    reg_la1_data = value;

}

/*----------------------------------------------------------------------*/
/* LDO:	 1.8V regulator for a bandgap					*/
/*----------------------------------------------------------------------*/

void ldo_enable()
{
    uint32_t value;

    /* Power enable */
    value = reg_la1_data;
    value &= ~LDO_PWR_NENABLE; 
    reg_la1_data = value;

    /* Local enable */
    value = reg_la2_oenb;
    value |= LDO_ENABLE; 
    reg_la2_oenb = value;
    
    /* Set ref select to zero */
    value = reg_la1_data;
    value &= ~LDO_REF_SELECT;
    reg_la1_data = value;

    /* Break before make */
    value = reg_la0_data;
    value &= ~LDO_OUTPUT_GROUND;
    reg_la0_data = value;

    value = reg_la1_oenb;
    value |= LDO_OUTPUT_ENABLE;
    reg_la1_oenb = value;
}

void ldo_disable()
{
    uint32_t value;

    /* Break before make */
    value = reg_la1_oenb;
    value &= ~LDO_OUTPUT_ENABLE;
    reg_la1_oenb = value;

    value = reg_la0_data;
    value |= LDO_OUTPUT_GROUND;
    reg_la0_data = value;

    /* Set ref select to zero */
    value = reg_la1_data;
    value &= ~LDO_REF_SELECT;
    reg_la1_data = value;

    /* Local disable */
    value = reg_la2_oenb;
    value &= ~LDO_ENABLE; 
    reg_la2_oenb = value;
    
    /* Power disable */
    value = reg_la1_data;
    value |= LDO_PWR_NENABLE; 
    reg_la1_data = value;
}

void ldo_ref_select(uint8_t value)
{
    uint32_t ovalue;

    ovalue = reg_la0_data;
    ovalue &= ~LDO_REF_SELECT;
    if (((uint32_t)value & 0x01) != 0) ovalue |= LDO_REF_SELECT;

    reg_la0_data = ovalue;
}

/*----------------------------------------------------------------------*/
/* OSC16M:  16MHz R-C oscillator					*/
/*----------------------------------------------------------------------*/

void osc16M_enable()
{
    uint32_t value;

    /* Power enable */
    value = reg_la1_data;
    value &= ~OSC16M_PWR_NENABLE; 
    reg_la1_data = value;

    /* Local enable */
    value = reg_la0_data;
    value |= OSC16M_ENABLE;
    reg_la0_data = value;
}

void osc16M_disable()
{
    uint32_t value;

    /* Local disable */
    value = reg_la0_oenb;
    value &= ~OSC16M_ENABLE;
    reg_la0_oenb = value;

    /* Power disable */
    value = reg_la1_data;
    value |= OSC16M_PWR_NENABLE; 
    reg_la1_data = value;
}

void osc16M_set_enable(uint8_t value)
{
    uint32_t ovalue;

    ovalue = reg_la0_data;
    ovalue &= ~OSC16M_ENABLE;
    if (((uint32_t)value & 0x01) != 0) ovalue |= OSC16M_ENABLE;
    reg_la0_data = ovalue;
}

/*----------------------------------------------------------------------*/
/* VREF:  CMOS 1.2V voltage reference					*/
/*----------------------------------------------------------------------*/

void cmos_vref_enable()
{
    uint32_t value;

    /* Power enable */
    value = reg_la1_data;
    value &= ~VREF_PWR_NENABLE; 
    reg_la1_data = value;

    /* Local enable */
    value = reg_la1_oenb;
    value |= VREF_ENABLE; 
    reg_la1_oenb = value;

    /* Set trim value to zero */
    value = reg_la1_oenb;
    value &= ~(VREF_TRIM_2 | VREF_TRIM_0);
    reg_la1_oenb = value;

    value = reg_la0_data;
    value &= ~(VREF_TRIM_3 | VREF_TRIM_1);
    reg_la0_data = value;

    /* Break before make */
    value = reg_la0_data;
    value &= ~(VREF_VBGTG_GROUND | VREF_VBGSC_GROUND |
		VREF_VBG_GROUND | VREF_VPTAT_GROUND);
    reg_la0_data = value;

    value = reg_la0_oenb;
    value |= VREF_VBGTG_ENABLE;
    reg_la0_oenb = value;

    value = reg_la1_oenb;
    value |= VREF_VBGSC_ENABLE | VREF_VBG_ENABLE | VREF_VPTAT_ENABLE;
    reg_la1_oenb = value;
}

void cmos_vref_disable()
{
    uint32_t value;

    /* Break before make */
    value = reg_la0_oenb;
    value &= ~VREF_VBGTG_ENABLE;
    reg_la0_oenb = value;

    value = reg_la1_oenb;
    value &= ~(VREF_VBGSC_ENABLE | VREF_VBG_ENABLE | VREF_VPTAT_ENABLE);
    reg_la1_oenb = value;

    value = reg_la0_data;
    value |= VREF_VBGTG_GROUND | VREF_VBGSC_GROUND |
		VREF_VBG_GROUND | VREF_VPTAT_GROUND;
    reg_la0_data = value;

    /* Set trim value to zero */
    value = reg_la1_oenb;
    value &= ~(VREF_TRIM_2 | VREF_TRIM_0);
    reg_la1_oenb = value;

    value = reg_la0_data;
    value &= ~(VREF_TRIM_3 | VREF_TRIM_1);
    reg_la0_data = value;

    /* Local disable */
    value = reg_la1_oenb;
    value &= ~VREF_ENABLE; 
    reg_la1_oenb = value;

    /* Power disable */
    value = reg_la1_data;
    value |= VREF_PWR_NENABLE; 
    reg_la1_data = value;
}

void cmos_vref_set_trim(uint8_t value)
{
    uint32_t ovalue1, ovalue2;

    /* The VREF trim value is scrambled between reg_la1_oenb
     * and reg_la0_data.  Because of this, the trim can only be changed
     * in two instruction cycles, forcing a glitch in between.
     */

    ovalue1 = reg_la1_oenb;
    ovalue1 &= ~(VREF_TRIM_0 | VREF_TRIM_2);
    if (((uint32_t)value & 0x01) != 0) ovalue1 |= VREF_TRIM_0;
    if (((uint32_t)value & 0x03) != 0) ovalue1 |= VREF_TRIM_2;

    ovalue2 = reg_la0_data;
    ovalue2 &= ~(VREF_TRIM_1 | VREF_TRIM_3);
    if (((uint32_t)value & 0x02) != 0) ovalue2 |= VREF_TRIM_1;
    if (((uint32_t)value & 0x04) != 0) ovalue2 |= VREF_TRIM_3;

    reg_la1_oenb = ovalue1;
    reg_la0_data = ovalue2;
}

/*----------------------------------------------------------------------*/
/* OSC500K:  500kHz R-C oscillator					*/
/*----------------------------------------------------------------------*/

void osc500k_enable()
{
    uint32_t value;

    /* Power enable */
    value = reg_la1_data;
    value &= ~OSC500K_PWR_NENABLE; 
    reg_la1_data = value;

    /* Local enable */
    value = reg_la2_oenb;
    value |= OSC500K_ENABLE;
    reg_la2_oenb = value;
}

void osc500k_disable()
{
    uint32_t value;

    /* Local disable */
    value = reg_la2_oenb;
    value &= ~OSC500K_ENABLE;
    reg_la2_oenb = value;

    /* Power disable */
    value = reg_la1_data;
    value |= OSC500K_PWR_NENABLE; 
    reg_la1_data = value;
}

void osc500k_set_enable(uint8_t value)
{
    uint32_t ovalue;

    ovalue = reg_la2_oenb;
    ovalue &= ~OSC500K_ENABLE;
    if (((uint32_t)value & 0x01) != 0) ovalue |= OSC500K_ENABLE;
    reg_la2_oenb = ovalue;
}

/*----------------------------------------------------------------------*/
/* POR:	Power-on Reset							*/
/*									*/
/*----------------------------------------------------------------------*/

void por_enable()
{
    uint32_t value;

    /* Power enable */
    value = reg_la1_data;
    value &= ~POR_PWR_NENABLE; 
    reg_la1_data = value;

    /* Break before make */
    value = reg_la3_oenb;
    value &= ~POR_PORB_GROUND;
    reg_la3_oenb = value;

    value = reg_la3_data;
    value |= POR_PORB_ENABLE;
    reg_la3_data = value;
}

void por_disable()
{
    uint32_t value;

    /* Break before make */
    value = reg_la3_data;
    value &= ~POR_PORB_ENABLE;
    reg_la3_data = value;

    value = reg_la3_oenb;
    value |= POR_PORB_GROUND;
    reg_la3_oenb = value;

    /* Power disable */
    value = reg_la1_data;
    value |= POR_PWR_NENABLE; 
    reg_la1_data = value;
}

/*----------------------------------------------------------------------*/
/* SAMPLE:  Sample and Hold						*/
/*----------------------------------------------------------------------*/

void sample_and_hold_enable()
{
    uint32_t value;

    /* Power enable */
    value = reg_la1_data;
    value &= ~SAMPLE_PWR_NENABLE; 
    reg_la1_data = value;

    /* Local enable */
    value = reg_la2_data;
    value |= SAMPLE_ENABLE; 
    reg_la2_data = value;

    /* Set hold value to zero */
    value = reg_la2_oenb;
    value &= ~SAMPLE_HOLD;
    reg_la2_oenb = value;

    /* Break before make */
    value = reg_la3_oenb;
    value &= ~(SAMPLE_OUT_GROUND | SAMPLE_IN_GROUND);
    reg_la3_oenb = value;

    value = reg_la3_data;
    value |= SAMPLE_OUT_ENABLE | SAMPLE_IN_ENABLE;
    reg_la3_data = value;
}

void sample_and_hold_disable()
{
    uint32_t value;

    /* Break before make */
    value = reg_la3_data;
    value &= ~(SAMPLE_IN_ENABLE | SAMPLE_OUT_ENABLE);
    reg_la3_data = value;

    value = reg_la3_oenb;
    value |= SAMPLE_IN_GROUND | SAMPLE_OUT_GROUND;
    reg_la3_oenb = value;

    /* Set hold value to zero */
    value = reg_la2_oenb;
    value &= ~SAMPLE_HOLD;
    reg_la2_oenb = value;

    /* Local disable */
    value = reg_la2_data;
    value &= ~SAMPLE_ENABLE; 
    reg_la2_data = value;

    /* Power disable */
    value = reg_la1_data;
    value |= SAMPLE_PWR_NENABLE; 
    reg_la1_data = value;
}
	
void sample_and_hold_cycle(uint16_t delay)
{
    uint32_t value;
    uint16_t d;

    /* Toggle the hold (clear, then hold) */

    value = reg_la2_oenb;
    value &= ~SAMPLE_HOLD;
    reg_la2_oenb = value;
    for (d = 0; d < delay; d++);
    value |= SAMPLE_HOLD;
    reg_la2_oenb = value;
}

void sample_and_hold_set(uint8_t value)
{
    uint32_t ovalue;

    /* Set the sample and hold "hold" value manually */

    ovalue = reg_la2_oenb;
    ovalue &= ~SAMPLE_HOLD;
    if (((uint32_t)value & 0x01) != 0) ovalue |= SAMPLE_HOLD;
    reg_la2_oenb = ovalue;
}


/*----------------------------------------------------------------------*/
/* ULPCOMP:  Ultra-low-power comparator					*/
/*----------------------------------------------------------------------*/

void ulpcomp_enable()
{
    uint32_t value;

    /* Power enable */
    value = reg_la1_data;
    value &= ~ULPCOMP_PWR_NENABLE; 
    reg_la1_data = value;

    /* Local enable */
    value = reg_la3_data;
    value |= ULPCOMP_ENABLE; 
    reg_la3_data = value;

    /* Set clock to zero */
    value = reg_la2_oenb;
    value &= ~ULPCOMP_CLOCK;
    reg_la2_oenb = value;

    /* Break before make */
    value = reg_la3_oenb;
    value &= ~(ULPCOMP_INN_GROUND | ULPCOMP_INP_GROUND);
    reg_la3_oenb = value;

    value = reg_la3_data;
    value |= ULPCOMP_INN_ENABLE | ULPCOMP_INP_ENABLE;
    reg_la3_data = value;
}

void ulpcomp_disable()
{
    uint32_t value;

    /* Break before make */
    value = reg_la3_data;
    value &= ~(ULPCOMP_INN_ENABLE | ULPCOMP_INP_ENABLE);
    reg_la3_data = value;

    value = reg_la3_oenb;
    value |= ULPCOMP_INN_GROUND | ULPCOMP_INP_GROUND;
    reg_la3_oenb = value;

    /* Set clock to zero */
    value = reg_la2_oenb;
    value &= ~ULPCOMP_CLOCK;
    reg_la2_oenb = value;

    /* Local disable */
    value = reg_la3_data;
    value &= ~ULPCOMP_ENABLE; 
    reg_la3_data = value;

    /* Power disable */
    value = reg_la1_data;
    value |= ULPCOMP_PWR_NENABLE; 
    reg_la1_data = value;
}
	
void ulpcomp_clock_toggle(uint16_t delay)
{
    uint32_t value;
    uint16_t d;

    /* Toggle the comparator clock */

    value = reg_la2_oenb;
    value |= ULPCOMP_CLOCK;
    reg_la2_oenb = value;
    for (d = 0; d < delay; d++);	/* delay */
    value &= ~ULPCOMP_CLOCK;
    reg_la2_oenb = value;
}

void ulpcomp_clock_set(uint8_t value)
{
    uint32_t ovalue;

    /* Set the comparator clock */

    ovalue = reg_la2_oenb;
    ovalue &= ~ULPCOMP_CLOCK;
    if (((uint32_t)value & 0x01) != 0) ovalue |= ULPCOMP_CLOCK;
    reg_la2_oenb = ovalue;
}

/*----------------------------------------------------------------------*/
/* INSTRAMP:  Programmable-gain instrumentation amplifier		*/
/*									*/
/* Note:  The instrumentation amplifier does not have a digital	enable.	*/
/* It is disabled by zeroing the power enable and bias voltage/current.	*/
/*----------------------------------------------------------------------*/

void instramp_enable()
{
    uint32_t value;

    value = reg_la1_data;
    value &= ~INSTRAMP_PWR_NENABLE; 
    reg_la1_data = value;

    /* Set data value to zero when INSTRAMP is enabled */
    value = reg_la2_data;
    value &= ~(INSTRAMP_VALUE_0 | INSTRAMP_VALUE_1);
    reg_la2_data = value;

    value = reg_la3_data;
    value &= ~(INSTRAMP_VALUE_2 | INSTRAMP_VALUE_3 | INSTRAMP_VALUE_4 |
		INSTRAMP_VALUE_5 | INSTRAMP_VALUE_6 | INSTRAMP_VALUE_7 |
		INSTRAMP_VALUE_8 | INSTRAMP_VALUE_9);
    reg_la3_data = value;

    /* Break before make */
    value = reg_la3_oenb;
    value &= ~(INSTRAMP_OUT_GROUND);
    reg_la3_oenb = value;

    value = reg_la0_data;
    value &= ~(INSTRAMP_VINN_GROUND | INSTRAMP_VINP_GROUND | INSTRAMP_IBIAS_GROUND);
    reg_la0_data = value;

    value = reg_la3_data;
    value |= INSTRAMP_OUT_ENABLE;
    reg_la3_data = value;

    value = reg_la0_oenb;
    value |= INSTRAMP_VINN_ENABLE | INSTRAMP_VINP_ENABLE | INSTRAMP_IBIAS_ENABLE;
    reg_la0_oenb = value;
}

void instramp_disable()
{
    uint32_t value;

    /* Break before make */
    value = reg_la0_oenb;
    value &= ~(INSTRAMP_VINN_ENABLE | INSTRAMP_VINP_ENABLE | INSTRAMP_IBIAS_ENABLE);
    reg_la0_oenb = value;

    value = reg_la3_data;
    value &= ~INSTRAMP_OUT_ENABLE;
    reg_la3_data = value;

    value = reg_la0_data;
    value |= INSTRAMP_VINN_GROUND | INSTRAMP_VINP_GROUND | INSTRAMP_IBIAS_GROUND;
    reg_la0_data = value;

    value = reg_la3_oenb;
    value |= INSTRAMP_OUT_GROUND;
    reg_la3_oenb = value;

    value = reg_la1_data;
    value |= INSTRAMP_PWR_NENABLE; 
    reg_la1_data = value;
}

void instramp_set_gain_stage1(uint8_t value)
{
    uint32_t ovalue1, ovalue2;

    /* The INSTRAMP gain stage 1 value is scrambled between reg_la2_data
     * and reg_la3_data.  The low 5 bits of the value are the control of
     * the first gain stage.
     */

    ovalue1 = reg_la2_data;
    ovalue1 &= ~(INSTRAMP_VALUE_0 | INSTRAMP_VALUE_1);
    if (((uint32_t)value & 0x01) != 0) ovalue1 |= INSTRAMP_VALUE_0;
    if (((uint32_t)value & 0x02) != 0) ovalue1 |= INSTRAMP_VALUE_1;

    ovalue2 = reg_la3_data;
    ovalue2 &= ~(INSTRAMP_VALUE_2 | INSTRAMP_VALUE_3 | INSTRAMP_VALUE_4);
    if (((uint32_t)value & 0x04) != 0) ovalue2 |= INSTRAMP_VALUE_2;
    if (((uint32_t)value & 0x08) != 0) ovalue2 |= INSTRAMP_VALUE_3;
    if (((uint32_t)value & 0x10) != 0) ovalue2 |= INSTRAMP_VALUE_4;

    reg_la2_data = ovalue1;
    reg_la3_data = ovalue2;
}

void instramp_set_gain_stage2(uint8_t value)
{
    uint32_t ovalue;

    ovalue = reg_la3_data;
    ovalue &= ~(INSTRAMP_VALUE_5 | INSTRAMP_VALUE_6 | INSTRAMP_VALUE_7 |
		INSTRAMP_VALUE_8 | INSTRAMP_VALUE_9);

    if (((uint32_t)value & 0x01) != 0) ovalue |= INSTRAMP_VALUE_5;
    if (((uint32_t)value & 0x02) != 0) ovalue |= INSTRAMP_VALUE_6;
    if (((uint32_t)value & 0x04) != 0) ovalue |= INSTRAMP_VALUE_7;
    if (((uint32_t)value & 0x08) != 0) ovalue |= INSTRAMP_VALUE_8;
    if (((uint32_t)value & 0x10) != 0) ovalue |= INSTRAMP_VALUE_9;

    reg_la3_data = ovalue;
}

/*----------------------------------------------------------------------*/
/* RHEO:  8-bit Rheostat						*/
/*----------------------------------------------------------------------*/

void rheostat_enable()
{
    uint32_t value;

    /* Power supply enable */
    value = reg_la1_data;
    value &= ~RHEO_PWR_NENABLE;
    reg_la1_data = value;

    /* NOTE:  There is no local "enable" signal for the rheostat */

    /* Set data value to zero when RHEO is enabled */
    value = reg_la3_data;
    value &= ~(RHEO_VALUE_7 | RHEO_VALUE_5 | RHEO_VALUE_3 | RHEO_VALUE_1);
    reg_la3_data = value;

    value = reg_la2_oenb;
    value &= ~(RHEO_VALUE_6 | RHEO_VALUE_4 | RHEO_VALUE_2 | RHEO_VALUE_0);
    reg_la2_oenb = value;

    /* Break before make */
    value = reg_la3_oenb;
    value &= ~(RHEO_REFL_GROUND | RHEO_REFH_GROUND | RHEO_OUT_GROUND);
    reg_la3_oenb = value;

    value = reg_la3_data;
    value |= RHEO_REFH_ENABLE | RHEO_REFL_ENABLE | RHEO_OUT_ENABLE;
    reg_la3_data = value;
}

void rheostat_disable()
{
    uint32_t value;

    /* Break before make */
    value = reg_la3_data;
    value &= ~(RHEO_REFH_ENABLE | RHEO_REFL_ENABLE | RHEO_OUT_ENABLE);
    reg_la3_data = value;

    value = reg_la3_oenb;
    value |= RHEO_REFL_GROUND | RHEO_REFH_GROUND | RHEO_OUT_GROUND;
    reg_la3_oenb = value;

    /* NOTE:  There is no local "enable" signal for the rheostat */

    /* Power supply disable */
    value = reg_la1_data;
    value |= RHEO_PWR_NENABLE;
    reg_la1_data = value;
}

void rheostat_set_value(uint8_t value)
{
    uint32_t ovalue1, ovalue2;

    /* The RHEO value is scrambled between reg_la2_oenb
     * and reg_la3_data.  Because of this, the RHEO can only be changed
     * in two instruction cycles, forcing a glitch in between.
     */

    ovalue1 = reg_la2_oenb;
    ovalue1 &= ~(RHEO_VALUE_0 | RHEO_VALUE_2 | RHEO_VALUE_4 | RHEO_VALUE_6);
    if (((uint32_t)value & 0x01) != 0) ovalue1 |= RHEO_VALUE_0;
    if (((uint32_t)value & 0x04) != 0) ovalue1 |= RHEO_VALUE_2;
    if (((uint32_t)value & 0x10) != 0) ovalue1 |= RHEO_VALUE_4;
    if (((uint32_t)value & 0x40) != 0) ovalue1 |= RHEO_VALUE_6;

    ovalue2 = reg_la3_data;
    ovalue2 &= ~(RHEO_VALUE_1 | RHEO_VALUE_3 | RHEO_VALUE_5 | RHEO_VALUE_7);
    if (((uint32_t)value & 0x02) != 0) ovalue2 |= RHEO_VALUE_1;
    if (((uint32_t)value & 0x08) != 0) ovalue2 |= RHEO_VALUE_3;
    if (((uint32_t)value & 0x20) != 0) ovalue2 |= RHEO_VALUE_5;
    if (((uint32_t)value & 0x80) != 0) ovalue2 |= RHEO_VALUE_7;

    reg_la2_oenb = ovalue1;
    reg_la3_data = ovalue2;
}

/*----------------------------------------------------------------------*/
/* RDAC:  8-bit resistor DAC						*/
/*----------------------------------------------------------------------*/

void rdac_enable()
{
    uint32_t value;

    value = reg_la1_data;
    value &= ~RDAC_PWR_NENABLE;
    reg_la1_data = value;

    /* Set data value to zero when RDAC is enabled */
    value = reg_la3_data;
    value &= ~(RDAC_VALUE_7 | RDAC_VALUE_5 | RDAC_VALUE_3 | RDAC_VALUE_1);
    reg_la3_data = value;

    value = reg_la2_oenb;
    value &= ~(RDAC_VALUE_6 | RDAC_VALUE_4 | RDAC_VALUE_2 | RDAC_VALUE_0);
    reg_la2_oenb = value;

    /* Break before make */
    value = reg_la3_oenb;
    value &= ~(RDAC_REFL_GROUND | RDAC_REFH_GROUND | RDAC_OUT_GROUND);
    reg_la3_oenb = value;

    value = reg_la3_data;
    value |= RDAC_REFH_ENABLE | RDAC_REFL_ENABLE | RDAC_OUT_ENABLE;
    reg_la3_data = value;

    value = reg_la2_oenb;
    value |= RDAC_ENABLE;
    reg_la2_oenb = value;
}

void rdac_disable()
{
    uint32_t value;

    value = reg_la2_oenb;
    value &= ~RDAC_ENABLE;
    reg_la2_oenb = value;

    /* Break before make */
    value = reg_la3_data;
    value &= ~(RDAC_REFH_ENABLE | RDAC_REFL_ENABLE | RDAC_OUT_ENABLE);
    reg_la3_data = value;

    value = reg_la3_oenb;
    value |= RDAC_REFL_GROUND | RDAC_REFH_GROUND | RDAC_OUT_GROUND;
    reg_la3_oenb = value;

    value = reg_la1_data;
    value |= RDAC_PWR_NENABLE;
    reg_la1_data = value;
}

void rdac_set_value(uint8_t value)
{
    uint32_t ovalue1, ovalue2;

    /* The RDAC value is scrambled between reg_la2_oenb
     * and reg_la3_data.  Because of this, the RDAC can only be changed
     * in two instruction cycles, forcing a glitch in between.
     */

    ovalue1 = reg_la2_oenb;
    ovalue1 &= ~(RDAC_VALUE_0 | RDAC_VALUE_2 | RDAC_VALUE_4 | RDAC_VALUE_6);
    if (((uint32_t)value & 0x01) != 0) ovalue1 |= RDAC_VALUE_0;
    if (((uint32_t)value & 0x04) != 0) ovalue1 |= RDAC_VALUE_2;
    if (((uint32_t)value & 0x10) != 0) ovalue1 |= RDAC_VALUE_4;
    if (((uint32_t)value & 0x40) != 0) ovalue1 |= RDAC_VALUE_6;

    ovalue2 = reg_la3_data;
    ovalue2 &= ~(RDAC_VALUE_1 | RDAC_VALUE_3 | RDAC_VALUE_5 | RDAC_VALUE_7);
    if (((uint32_t)value & 0x02) != 0) ovalue2 |= RDAC_VALUE_1;
    if (((uint32_t)value & 0x08) != 0) ovalue2 |= RDAC_VALUE_3;
    if (((uint32_t)value & 0x20) != 0) ovalue2 |= RDAC_VALUE_5;
    if (((uint32_t)value & 0x80) != 0) ovalue2 |= RDAC_VALUE_7;

    reg_la2_oenb = ovalue1;
    reg_la3_data = ovalue2;
}

/*----------------------------------------------------------------------*/
/* LOOPBACK:  Switch resistance loopback test				*/
/*									*/
/* Note:  All switches run on the core 3.3V supply, so there is no	*/
/* power enable for the loopback test.					*/
/*----------------------------------------------------------------------*/

void loopback_enable()
{
    uint32_t value;

    /* Break-before-make */
    value = reg_la0_data;
    value &= ~(LOOPBACK_2_GROUND | LOOPBACK_1_GROUND);
    reg_la0_data = value;
    
    value = reg_la0_oenb;
    value |= LOOPBACK_2_ENABLE | LOOPBACK_1_ENABLE;
    reg_la0_oenb = value;
}

void loopback_disable()
{
    uint32_t value;

    /* Break-before-make */
    value = reg_la0_oenb;
    value &= ~(LOOPBACK_2_ENABLE | LOOPBACK_1_ENABLE);
    reg_la0_oenb = value;

    /* Enable noise isolation ground connections */
    value = reg_la0_data;
    value |= LOOPBACK_2_GROUND | LOOPBACK_1_GROUND;
    reg_la0_data = value;
}

void loopback_disable_noisy()
{
    uint32_t value;

    /* Break connection */
    value = reg_la0_oenb;
    value &= ~(LOOPBACK_2_ENABLE | LOOPBACK_1_ENABLE);
    reg_la0_oenb = value;

    /* Do not enable noise isolation ground connections */
    value = reg_la0_data;
    value &= ~(LOOPBACK_2_GROUND | LOOPBACK_1_GROUND);
    reg_la0_data = value;
}

/*----------------------------------------------------------------------*/
/* ALL POWER SUPPLIES (initialization)					*/
/*----------------------------------------------------------------------*/

void powerdown_all()
{
    uint32_t value;

    value = reg_la1_data;
    value |= (AUDDAC_PWR_NENABLE | OSC16M_PWR_NENABLE |
		CDAC_PWR_NENABLE | CCOMP_PWR_NENABLE | VREF_PWR_NENABLE |
		LDO_PWR_NENABLE | IDAC_PWR_NENABLE | OSC500K_PWR_NENABLE |
		SAMPLE_PWR_NENABLE | ULPCOMP_PWR_NENABLE | INSTRAMP_PWR_NENABLE |
		POR_PWR_NENABLE | RHEO_PWR_NENABLE | RDAC_PWR_NENABLE);
    reg_la1_data = value;
}

/*----------------------------------------------------------------------*/
/* Initialize logic analyzrer						*/
/*----------------------------------------------------------------------*/

void init_logic_analyzer()
{
    // Start with all data bits zero except for the sense-negative
    // power supply enables.
    //
    // This is equivalent to calling powerdown_all() above.

    reg_la0_data = 0x00000000;

    reg_la1_data = AUDDAC_PWR_NENABLE | OSC16M_PWR_NENABLE | CDAC_PWR_NENABLE |
		CCOMP_PWR_NENABLE | VREF_PWR_NENABLE | LDO_PWR_NENABLE |
		IDAC_PWR_NENABLE | OSC500K_PWR_NENABLE | SAMPLE_PWR_NENABLE |
		ULPCOMP_PWR_NENABLE | INSTRAMP_PWR_NENABLE | POR_PWR_NENABLE |
		RHEO_PWR_NENABLE | RDAC_PWR_NENABLE;

    reg_la2_data = 0x00000000;
    reg_la3_data = 0x00000000;
			
    // All logic analyzer outputs being used should be driven.
    // No issue just enabling all of them.

    reg_la0_iena = 0xffffffff;
    reg_la1_iena = 0xffffffff;
    reg_la2_iena = 0xffffffff;
    reg_la3_iena = 0xffffffff;

    // Disable all outputs, as none are used in Chipalooza projects 2.

    reg_la0_oenb = 0x00000000;
    reg_la1_oenb = 0x00000000;
    reg_la2_oenb = 0x00000000;
    reg_la3_oenb = 0x00000000;
}

