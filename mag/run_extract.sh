#! /bin/bash

project=user_analog_project_wrapper

echo ${PDK_ROOT:=/usr/share/pdk} > /dev/null
echo ${PDK:=sky130A} > /dev/null

magic -dnull -noconsole -rcfile \$PDK_ROOT/\$PDK/libs.tech/magic/sky130A.magicrc << EOF
#
load $project
select top cell
expand
extract path extfiles
# Reinstate "extract unique" for signoff.
extract unique notopports
# Do not do parasitic extraction here. . .
extract no all
extract all
ext2spice lvs
ext2spice -p extfiles -o ../netlist/layout/$project.spice
quit -noprompt
EOF
rm -r extfiles
exit 0

