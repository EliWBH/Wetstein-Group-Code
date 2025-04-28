#!/bin/bash

echo "=== Histogram Comparison Script ==="

# Set default values
default_crate1="0"
default_slot1="0"
default_chan1="0"
default_ns1="4"

default_crate2="0"
default_slot2="0"
default_chan2="0"
default_ns2="4"

# Prompt for first file
echo "Enter first data file identifier (e.g. MRD2025-4-6.root):"
read file1

echo "Enter crate number for $file1 (0 for all) [Default: $default_crate1]:"
read crate1
crate1=${crate1:-$default_crate1}  # Use default if empty

echo "Enter slot number for $file1 (0 for all) [Default: $default_slot1]:"
read slot1
slot1=${slot1:-$default_slot1}  # Use default if empty

echo "Enter channel number for $file1 (0 for all) [Default: $default_chan1]:"
read chan1
chan1=${chan1:-$default_chan1}  # Use default if empty

echo "Enter binning (ns) for $file1 (4ns recommended) [Default: $default_ns1]:"
read ns1
ns1=${ns1:-$default_ns1}  # Use default if empty

# Prompt for second file
echo "Enter second data file identifier (e.g. MRD2025-4-13.root):"
read file2

echo "Enter crate number for $file2 (0 for all) [Default: $default_crate2]:"
read crate2
crate2=${crate2:-$default_crate2}  # Use default if empty

echo "Enter slot number for $file2 (0 for all) [Default: $default_slot2]:"
read slot2
slot2=${slot2:-$default_slot2}  # Use default if empty

echo "Enter channel number for $file2 (0 for all) [Default: $default_chan2]:"
read chan2
chan2=${chan2:-$default_chan2}  # Use default if empty

echo "Enter binning (ns) for $file2 (4ns recommended) [Default: $default_ns2]:"
read ns2
ns2=${ns2:-$default_ns2}  # Use default if empty


out1="MRD_Hists_${file1}"
out2="MRD_Hists_${file2}"

# Run first ROOT macro if output doesn't exist
if [ ! -f "$out1" ]; then
  echo "Generating $out1..."
  root -l -q "plot_filtered_histogram_test.C(\"$file1\", $crate1, $slot1, $chan1, $ns1)"
else
  echo "$out1 already exists. Skipping generation."
fi

# Run second ROOT macro if output doesn't exist
if [ ! -f "$out2" ]; then
  echo "Generating $out2..."
  root -l -q "plot_filtered_histogram_test.C(\"$file2\", $crate2, $slot2, $chan2, $ns2)"
else
  echo "$out2 already exists. Skipping generation."
fi

# Run comparison
echo "Comparing $out1 and $out2..."
root -l -q "Compare_2.C(\"$out1\", \"$out2\")"
