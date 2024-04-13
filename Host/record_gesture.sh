#!/bin/bash

gesture=$1
filename=txt/$gesture".txt"

echo "Recording data for gesture '$gesture' in $filename"

sudo hcidump -R > $filename

# TODO : Try to run this in parallel to make visually appleaing.
# while true; do echo -n ". "; sleep 1; done
