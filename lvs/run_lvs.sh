#!/bin/bash

export NETGEN_COLUMNS=50

project=user_analog_project_wrapper

echo ${PDK_ROOT:=/usr/share/pdk} > /dev/null
echo ${PDK:=sky130A} > /dev/null

netgen -batch source run_lvs.tcl | tee netgen_$project.log
