#!/bin/bash
#
# Use klayout to convert GDS to OASIS
# Usage: convert.sh <gds_file_name> <oasis_file_name>
#
# This stupid-simple script does no argument checks;  it needs some work.
#
klayout -b -r ../scripts/convert.py -rd input=$1 -rd output=$2
