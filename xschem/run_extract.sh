#!/bin/bash

project=user_analog_project_wrapper

echo ${PDK_ROOT:=/usr/share/pdk} > /dev/null
echo ${PDK:=sky130A} > /dev/null

# Construct XSCHEM_LIBRARY_PATH
tclstr="set lvs_netlist 1"
tclstr="$tclstr ; append XSCHEM_LIBRARY_PATH :$PWD/../dependencies/sky130_aa_ip__programmable_pll/Xschem/PLL_TOP_Schematics"
tclstr="$tclstr ; append XSCHEM_LIBRARY_PATH :$PWD/../dependencies/sky130_ak_ip__cmos_vref/xschem"
tclstr="$tclstr ; append XSCHEM_LIBRARY_PATH :$PWD/../dependencies/sky130_am_ip__ldo_01v8/xschem"
tclstr="$tclstr ; append XSCHEM_LIBRARY_PATH :$PWD/../dependencies/sky130_ef_ip__analog_switches/xschem"
tclstr="$tclstr ; append XSCHEM_LIBRARY_PATH :$PWD/../dependencies/sky130_ef_ip__biasgen/xschem"
tclstr="$tclstr ; append XSCHEM_LIBRARY_PATH :$PWD/../dependencies/sky130_ef_ip__ccomp3v/xschem"
tclstr="$tclstr ; append XSCHEM_LIBRARY_PATH :$PWD/../dependencies/sky130_ef_ip__cdac3v_12bit/xschem"
tclstr="$tclstr ; append XSCHEM_LIBRARY_PATH :$PWD/../dependencies/sky130_ef_ip__rdac3v_8bit/xschem"
tclstr="$tclstr ; append XSCHEM_LIBRARY_PATH :$PWD/../dependencies/sky130_ef_ip__rheostat_8bit/xschem"
tclstr="$tclstr ; append XSCHEM_LIBRARY_PATH :$PWD/../dependencies/sky130_ef_ip__samplehold/xschem"
tclstr="$tclstr ; append XSCHEM_LIBRARY_PATH :$PWD/../dependencies/sky130_icrg_ip__ulpcomp/xschem"
tclstr="$tclstr ; append XSCHEM_LIBRARY_PATH :$PWD/../dependencies/sky130_iic_ip__audiodac_v1/xschem"
tclstr="$tclstr ; append XSCHEM_LIBRARY_PATH :$PWD/../dependencies/sky130_sw_ip__bgrref_por/xschem"
tclstr="$tclstr ; append XSCHEM_LIBRARY_PATH :$PWD/../dependencies/sky130_ef_ip__rc_osc_500k/xschem"
tclstr="$tclstr ; append XSCHEM_LIBRARY_PATH :$PWD/../dependencies/sky130_ef_ip__rc_osc_16M/xschem"

xschem -n -s -r -x -q --tcl "$tclstr" --rcfile $PDK_ROOT/$PDK/libs.tech/xschem/xschemrc -o ../netlist/schematic -N $project.spice $project.sch

