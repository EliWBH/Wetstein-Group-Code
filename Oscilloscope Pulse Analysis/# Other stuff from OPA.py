

# %%    Hist Subtractor

import random
import math
import numpy as np
import matplotlib as plt 
import matplotlib_inline as plt
import matplotlib.pyplot as plt

file_name1 = "Pmt3_160v_Led_allCH.txt"

# Load data from file
all_top1 = []
data1 = []
with open(file_name1, 'r') as file:
    for line in file:  
        data1 = [float(val) for val in line.split()]

        top1 = max(data1)
      #  top = top*(-1)
# numpy.array(top)*-1
        all_top1.append(top1)

# Print the total number of values in a single row (assuming all rows have the same length)
# total_values = len(all_data[0])
# print(f"Total number of values in each waveform: {total_values}")

# Find the top value from each waveform
# all_top = [max(row) for row in all_data]

print(f"Number of top values: {len(all_top1)}")
print(f"top values: {all_top1}")  # Print top values as a sample
print()
print(f"For file {file_name1}")

# Histogram of top values
plt.figure(figsize=(12, 6))
plt.hist(all_top1, bins=2500, range=(-5, 10)) # For non-PMT1 (high gain), lower range to (-5,10), otherwiseramain at (-5,50)
plt.xlabel("Amplitude (mV)")
plt.ylabel("Frequency")
plt.title("Histogram of Top Amplitudes from All Waveforms, zoomed")

# Set y-axis range (either logarithmic or noram upper/lower limits, depending on thich of the following lines are in/out)
# plt.yscale("log")
plt.ylim(0, 200)  
# Desired range

plt.show()


file_name2 = "Pmt3_160v_Dark_allCH.txt"

# Load data from file
all_top2 = []
data2 = []
with open(file_name2, 'r') as file:
    for line in file:  
        data2 = [float(val) for val in line.split()]

        top2 = max(data2)
      #  top = top*(-1)
# numpy.array(top)*-1
        all_top2.append(top2)

# Print the total number of values in a single row (assuming all rows have the same length)
# total_values = len(all_data[0])
# print(f"Total number of values in each waveform: {total_values}")

# Find the top value from each waveform
# all_top = [max(row) for row in all_data]

print(f"Number of top values: {len(all_top2)}")
print(f"top values: {all_top2}")  # Print top values as a sample
print()
print(f"For file {file_name2}")

# Histogram of top values
plt.figure(figsize=(12, 6))
plt.hist(all_top2, bins=2500, range=(-5, 10)) # For non-PMT1 (high gain), lower range to (-5,10), otherwiseramain at (-5,50)
plt.xlabel("Amplitude (mV)")
plt.ylabel("Frequency")
plt.title("Histogram of Top Amplitudes from All Waveforms, zoomed")

# Set y-axis range (either logarithmic or noram upper/lower limits, depending on thich of the following lines are in/out)
# plt.yscale("log")
plt.ylim(0, 200)  
# Desired range

plt.show()

hist_diff = all_top1 - all_top2

# Hist Diff print
plt.figure(figsize=(12, 6))
plt.hist(hist_diff, bins=2500, range=(-5, 10)) # For non-PMT1 (high gain), lower range to (-5,10), otherwiseramain at (-5,50)
plt.xlabel("Amplitude (mV)")
plt.ylabel("Frequency")
plt.title("Histogram of Top Amplitudes from All Waveforms, zoomed")

# Set y-axis range (either logarithmic or noram upper/lower limits, depending on thich of the following lines are in/out)
# plt.yscale("log")
plt.ylim(0, 200)  
# Desired range

plt.show()


# %%

import random
import math
import numpy as np
import matplotlib as plt 
import matplotlib_inline as plt
import matplotlib.pyplot as plt

file_name1 = "Pmt3_160v_Led_allCH.txt"

# Load data from file
all_top1 = []
data1 = []
with open(file_name1, 'r') as file:
    for line in file:  
        data1 = [float(val) for val in line.split()]
        top1 = max(data1)
        all_top1.append(top1)

print(f"Number of top values: {len(all_top1)}")
print(f"top values: {all_top1}")
print(f"For file {file_name1}")

# Histogram of top values
plt.figure(figsize=(12, 6))
plt.hist(all_top1, bins=2500, range=(-5, 10))
plt.xlabel("Amplitude (mV)")
plt.ylabel("Frequency")
plt.title("Histogram of Top Amplitudes - LED On")
plt.ylim(0, 200)
plt.show()

file_name2 = "Pmt3_160v_Dark_allCH.txt"

# Load data from file
all_top2 = []
data2 = []
with open(file_name2, 'r') as file:
    for line in file:  
        data2 = [float(val) for val in line.split()]
        top2 = max(data2)
        all_top2.append(top2)

print(f"Number of top values: {len(all_top2)}")
print(f"top values: {all_top2}")
print(f"For file {file_name2}")

plt.figure(figsize=(12, 6))
plt.hist(all_top2, bins=2500, range=(-5, 10))
plt.xlabel("Amplitude (mV)")
plt.ylabel("Frequency")
plt.title("Histogram of Top Amplitudes - Dark")
plt.ylim(0, 200)
plt.show()

# Convert lists to numpy arrays and subtract
all_top1_array = np.array(all_top1)
all_top2_array = np.array(all_top2)
hist_diff = all_top1_array - all_top2_array

plt.figure(figsize=(12, 6))
plt.hist(hist_diff, bins=2500, range=(-5, 10))
plt.xlabel("Amplitude (mV)")
plt.ylabel("Frequency")
plt.title("Difference Histogram (LED - Dark)")
plt.ylim(0, 200)
plt.show()
# %%
