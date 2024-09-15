#! /bin/bash

project=user_analog_project_wrapper

echo ${PDK_ROOT:=/usr/share/pdk} > /dev/null
echo ${PDK:=sky130A} > /dev/null

magic -dnull -noconsole -rcfile \$PDK_ROOT/\$PDK/libs.tech/magic/sky130A.magicrc << EOF
#
# NOTE: rdac and rheostat do not extract properly unless flattened first.  Once this is fixed in
# magic's extraction engine, this step can be removed.
load ../dependencies/sky130_ef_ip__rdac3v_8bit/mag/sky130_ef_ip__rdac3v_8bit
select top cell
flatten sky130_ef_ip__rdac3v_8bit_flat
load sky130_ef_ip__rdac3v_8bit_flat
cellname delete sky130_ef_ip__rdac3v_8bit
cellname rename sky130_ef_ip__rdac3v_8bit_flat sky130_ef_ip__rdac3v_8bit
#
load ../dependencies/sky130_ef_ip__rheostat_8bit/mag/sky130_ef_ip__rheostat_8bit
select top cell
flatten sky130_ef_ip__rheostat_8bit_flat
load sky130_ef_ip__rheostat_8bit_flat
cellname delete sky130_ef_ip__rheostat_8bit
cellname rename sky130_ef_ip__rheostat_8bit_flat sky130_ef_ip__rheostat_8bit
#

load $project
select top cell
expand
# NOTE:  programmable PLL cell needs work; replace with abstract view for now.
cellname filepath sky130_aa_ip__programmable_pll ../dependencies/sky130_aa_ip__programmable_pll/maglef
flush sky130_aa_ip__programmable_pll
# Now back to the project
select top cell
extract path extfiles
# Reinstate "extract unique" for signoff.
extract unique
# Do not do parasitic extraction here. . .
extract no all
extract all
ext2spice lvs
ext2spice -p extfiles -o ../netlist/layout/$project.spice
quit -noprompt
EOF
rm -r extfiles
exit 0

