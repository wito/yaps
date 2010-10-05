#!/bin/sh
# This file can be run as a shell script to build YAPS when first cloned.
# On subsequent builds, running make should be ample.
# The command `mkdir obj' is omitted from the makefile to save on clutter.

mkdir obj 2> /dev/null
make
