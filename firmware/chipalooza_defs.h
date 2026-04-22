/*----------------------------------------------*/
/* Definitions for the chipalooza_testchip2	*/
/*----------------------------------------------*/
/* Written by Tim Edwards, Open Circuit Design	*/
/* April 19, 2026				*/
/*----------------------------------------------*/

/* Note that multiplexers use switches which can be grounded in the
 * middle for better isolation.  To avoid needed multiple definitions
 * for each bit (one signal's "enable" is another's "disable"), only
 * the "enable" and "ground" bits are defined for signals for which
 * value "1" is active.  All enables except for those of the project
 * being tested should be set to "0", and all grounds should be set
 * to "1"---However, given the risk of shorting lines, it is probably
 * better to leave all grounds at "0" except when doing noise isolation
 * measurements
 *
 * Most vector values have been spread across multiple words, making
 * it rather useless to specify a "mask".  Insead, each bit is given
 * a definition.  Se the chipalooza_utils.c set of utility routines for
 * a more comprehensive description of the value bit fields.
 *
 * Note that due to the large number of controls, the controls make use
 * of both the "data" and "oeb" lines.  These are *not* mutually exclusive,
 * as setting "la_oenb[X]" to zero forces "la_data_in[X]" to zero.  So
 * the signals have been arranged so that for any bit position X, if the
 * oenb line is used as an output, the corresponding data_in line does not
 * control anything in the same project.  This arrangement may limit the
 * ability to run more than one project at the same time, should one wish
 * to do so.
 */

/* Logic analyzer data in bits */

/* Bits on logic analyzer la_data_in word 0 (31-0) */
#define LOOPBACK_2_GROUND	0x00000001
#define AUDDAC_OUTP_GROUND	0x00000002
#define INSTRAMP_VINN_GROUND	0x00000004
#define AUDDAC_OUTN_GROUND	0x00000008
#define INSTRAMP_IBIAS_GROUND	0x00000010
#define LOOPBACK_1_GROUND	0x00000020
#define INSTRAMP_VINP_GROUND	0x00000040
#define CDAC_VIN_GROUND		0x00000080
#define CCOMP_INN_GROUND	0x00000100
#define IDAC_VCM_GROUND		0x00000100
#define VREF_VBGTG_GROUND	0x00000200
#define CCOMP_INP_GROUND	0x00000400
#define CDAC_OUT_GROUND		0x00000400
#define VREF_VBGSC_GROUND	0x00000800
#define IDAC_REF_TRIM_GROUND	0x00001000
#define CDAC_REFH_GROUND	0x00002000
#define LDO_OUTPUT_GROUND	0x00004000
#define CDAC_REFL_GROUND	0x00008000
#define IDAC_SINK_OUT_GROUND	0x00010000
#define VREF_VBG_GROUND		0x00020000
#define IDAC_SOURCE_OUT_GROUND	0x00040000
#define VREF_VPTAT_GROUND	0x00080000
#define OSC16M_ENABLE		0x00100000
#define CDAC_VALUE_10		0x00200000
#define CDAC_VALUE_8		0x00400000
#define CDAC_VALUE_6		0x00800000
#define CDAC_VALUE_4		0x01000000
#define CDAC_VALUE_2		0x02000000
#define CDAC_VALUE_0		0x04000000
#define CCOMP_ENABLE		0x08000000
#define VREF_TRIM_3		0x10000000
#define VREF_TRIM_1		0x20000000
#define LDO_REF_SELECT		0x40000000
#define IDAC_VALUE_7		0x80000000

/* Bits on logic analyzer la_data_in word 1 (63-32) */
#define IDAC_VALUE_5		0x00000001
#define IDAC_VALUE_3		0x00000002
#define IDAC_VALUE_1		0x00000004
#define IDAC_REF_SELECT		0x00000008

/* NOTE: These are all negative-sense enables */

#define AUDDAC_PWR_NENABLE	0x00000200
#define OSC16M_PWR_NENABLE	0x00000400
#define CDAC_PWR_NENABLE	0x00000800
#define CCOMP_PWR_NENABLE	0x00001000
#define VREF_PWR_NENABLE	0x00002000
#define LDO_PWR_NENABLE		0x00004000
#define IDAC_PWR_NENABLE	0x00008000
#define OSC500K_PWR_NENABLE	0x00010000
#define SAMPLE_PWR_NENABLE	0x00020000
#define ULPCOMP_PWR_NENABLE	0x00040000
#define INSTRAMP_PWR_NENABLE	0x00080000
#define POR_PWR_NENABLE		0x00100000
#define RHEO_PWR_NENABLE	0x00200000
#define RDAC_PWR_NENABLE	0x00400000

/* Bits on logic analyzer la_data_in word 2 (95-64) */

#define CDAC_HOLD		0x04000000
#define SAMPLE_ENABLE		0x08000000
#define INSTRAMP_VALUE_0	0x40000000
#define INSTRAMP_VALUE_1	0x80000000

/* Bits on logic analyzer la_data_in word 3 (127-96) */

#define INSTRAMP_VALUE_2	0x00000001
#define INSTRAMP_VALUE_3	0x00000002
#define INSTRAMP_VALUE_4	0x00000004
#define INSTRAMP_VALUE_5	0x00000008
#define INSTRAMP_VALUE_6	0x00000010
#define INSTRAMP_VALUE_7	0x00000020
#define INSTRAMP_VALUE_8	0x00000040
#define INSTRAMP_VALUE_9	0x00000080
#define ULPCOMP_ENABLE		0x00000800
#define RHEO_VALUE_1		0x00001000
#define RHEO_VALUE_3		0x00002000
#define RHEO_VALUE_5		0x00004000
#define RHEO_VALUE_7		0x00008000
#define RDAC_VALUE_1		0x00010000
#define RDAC_VALUE_3		0x00020000
#define RDAC_VALUE_5		0x00040000
#define RDAC_VALUE_7		0x00080000
#define ULPCOMP_INN_ENABLE	0x00100000
#define SAMPLE_OUT_ENABLE	0x00200000
#define POR_PORB_ENABLE		0x00400000
#define SAMPLE_IN_ENABLE	0x00800000
#define INSTRAMP_OUT_ENABLE	0x01000000
#define ULPCOMP_INP_ENABLE	0x02000000
#define RHEO_REFH_ENABLE	0x04000000
#define RDAC_REFH_ENABLE	0x08000000
#define RHEO_REFL_ENABLE	0x10000000
#define RDAC_REFL_ENABLE	0x20000000
#define RDAC_OUT_ENABLE		0x40000000
#define RHEO_OUT_ENABLE		0x80000000

/* Bits on logic analyzer la_oenb word 0 (31-0) */

#define LOOPBACK_2_ENABLE	0x00200000
#define AUDDAC_OUTP_ENABLE	0x00400000
#define INSTRAMP_VINN_ENABLE	0x00800000
#define AUDDAC_OUTN_ENABLE	0x01000000
#define INSTRAMP_IBIAS_ENABLE	0x02000000
#define LOOPBACK_1_ENABLE	0x04000000
#define INSTRAMP_VINP_ENABLE	0x08000000
#define CDAC_VIN_ENABLE		0x10000000
#define CCOMP_INN_ENABLE	0x20000000
#define IDAC_VCM_ENABLE		0x20000000
#define VREF_VBGTG_ENABLE	0x40000000
#define CCOMP_INP_ENABLE	0x80000000
#define CDAC_OUT_ENABLE		0x80000000

/* Bits on logic analyzer la_oenb word 1 (63-32) */

#define VREF_VBGSC_ENABLE	0x00000001
#define IDAC_REF_TRIM_ENABLE  	0x00000002
#define CDAC_REFH_ENABLE   	0x00000004
#define LDO_OUTPUT_ENABLE	0x00000008
#define CDAC_REFL_ENABLE	0x00000010
#define IDAC_SINK_OUT_ENABLE	0x00000020
#define VREF_VBG_ENABLE		0x00000040
#define IDAC_SOURCE_OUT_ENABLE	0x00000080
#define VREF_VPTAT_ENABLE	0x00000100
#define CDAC_VALUE_11		0x00400000
#define CDAC_VALUE_9		0x00800000
#define CDAC_VALUE_7		0x01000000
#define CDAC_VALUE_5		0x02000000
#define CDAC_VALUE_3		0x04000000
#define CDAC_VALUE_1		0x08000000
#define CDAC_RESET		0x10000000
#define VREF_ENABLE		0x20000000
#define VREF_TRIM_2		0x40000000
#define VREF_TRIM_0		0x80000000

/* Bits on logic analyzer la_oenb word 2 (95-64) */

#define LDO_ENABLE		0x00000001
#define IDAC_VALUE_6		0x00000002
#define IDAC_VALUE_4		0x00000004
#define IDAC_VALUE_2		0x00000008
#define IDAC_VALUE_0		0x00000010
#define IDAC_ENABLE	   	0x00000020
#define OSC500K_ENABLE		0x00000040
#define SAMPLE_HOLD		0x00000080
#define ULPCOMP_CLOCK		0x00400000
#define RHEO_VALUE_0		0x00800000
#define RHEO_VALUE_2		0x01000000
#define RHEO_VALUE_4		0x02000000
#define RHEO_VALUE_6		0x04000000
#define RDAC_VALUE_0		0x08000000
#define RDAC_VALUE_2		0x10000000
#define RDAC_VALUE_4		0x20000000
#define RDAC_VALUE_6		0x40000000
#define RDAC_ENABLE		0x80000000

/* Bits on logic analyzer la_oenb word 3 (127-96) */

#define ULPCOMP_INN_GROUND	0x00000001
#define SAMPLE_OUT_GROUND	0x00000002
#define POR_PORB_GROUND		0x00000004
#define SAMPLE_IN_GROUND	0x00000008
#define INSTRAMP_OUT_GROUND	0x00000010
#define ULPCOMP_INP_GROUND	0x00000020
#define RHEO_REFH_GROUND	0x00000040
#define RDAC_REFH_GROUND	0x00000080
#define RHEO_REFL_GROUND	0x00000100
#define RDAC_REFL_GROUND	0x00000200
#define RDAC_OUT_GROUND		0x00000400
#define RHEO_OUT_GROUND		0x00000800

/* (Note that there are no data inputs from Chipalooza_projects_2;  that
 * is, all la_data_out[127:0] are unconnected and should never be enabled.)
 */

