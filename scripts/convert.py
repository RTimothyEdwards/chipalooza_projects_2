#!/usr/bin/env python3
#
# Convert GDS to OASIS using klayout
# (Use "convert.sh" to run klayout and call this script)
#
import pya

layout = pya.Layout()
layout.read(input)
layout.write(output)
