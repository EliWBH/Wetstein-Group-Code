# Oscilloscope Pulse Analysis



# IMPORTANT: For the next user:
# Typically, the second cell (labelled as "Functioning Code Backup (Testing?)" is where I 
# would input waveform txt files for analysis. All of the other cells hve different purposes, 
# and most of not all of them should be functionl. Backup code is further down. 

# To insert a file, place it between the parenthesis for: file_name = "[YOUR FILE].txt" 

# To analyze a waveform, please ensure that you have converted it into a .txt file before 
# inserting it here. Examples of the filenames I input are listed near line 180, for reference

# Please contact me at 630-888-0610 if problems arise!




# Name Swapping

# %%

import random
import math
import numpy as np
import matplotlib as plt 
import matplotlib_inline as plt
import matplotlib.pyplot as plt

# Load data from file
all_data = []
with open('pmt1-160v-b1_CH3.txt', 'r') as file:
    for line in file:  
        data = [float(val) for val in line.split()]
        all_data.append(data)

# Print the total number of values in a single row (assuming all rows have the same length)
total_values = len(all_data[0])
print(f"Total number of values in each waveform: {total_values}")

# Find the top value from each waveform
all_top = [max(row) for row in all_data]

print(f"Number of top values: {len(all_top)}")
print(f"top values: {all_top}")  # Print top values as a sample

# Histogram of top values
plt.figure(figsize=(12, 6))
plt.hist(all_top, bins=100, range=(-5, 50))
plt.xlabel("Amplitude (mV)")
plt.ylabel("Frequency")
plt.title("Histogram of Top Amplitudes from All Waveforms")
plt.show()

# Histogram of top values
plt.figure(figsize=(12, 6))
plt.hist(all_top, bins=100, range=(-5, 50))
plt.xlabel("Amplitude (mV)")
plt.ylabel("Frequency")
plt.title("Histogram of Top Amplitudes from All Waveforms, zoomed")

# Set y-axis range
plt.ylim(0, 30)  # Desired range

plt.show()

all_data = []



# %%


# Easier computing, so this was removed:

with open('pmt1_165v_all.txt', 'r') as file:
    for line in file:  
        data = [float(val) for val in line.split()]
        all_data.append(data)


for row in all_data:
    x = range(1, len(row) + 1) 
    plt.plot(x, row)

print("All fastframe waveforms, layered")
plt.show()






# Functioning code backup (testing?)

# %%

import random
import math
import numpy as np
import matplotlib as plt 
import matplotlib_inline as plt
import matplotlib.pyplot as plt

file_name = "BaseTests_Pmt3_b4_allCH.txt"

# Load data from file
all_top = []
data = []
with open(file_name, 'r') as file:
    for line in file:  
        data = [float(val) for val in line.split()]

        top = max(data)
      #  top = top*(-1)
# numpy.array(top)*-1
        all_top.append(top)

# Print the total number of values in a single row (assuming all rows have the same length)
# total_values = len(all_data[0])
# print(f"Total number of values in each waveform: {total_values}")

# Find the top value from each waveform
# all_top = [max(row) for row in all_data]

print(f"Number of top values: {len(all_top)}")
print(f"top values: {all_top}")  # Print top values as a sample
print()
print(f"For file {file_name}")

# Histogram of top values
plt.figure(figsize=(12, 6))
plt.hist(all_top, bins=2000, range=(-5, 50))
plt.xlabel("Amplitude (mV)")
plt.ylabel("Frequency")
plt.title("Histogram of Top Amplitudes from All Waveforms")
plt.show()

# Histogram of top values
plt.figure(figsize=(12, 6))
plt.hist(all_top, bins=2000, range=(-5, 50)) # For non-PMT1 (high gain), lower range to (-5,10), otherwiseramain at (-5,50)
plt.xlabel("Amplitude (mV)")
plt.ylabel("Frequency")
plt.title("Histogram of Top Amplitudes from All Waveforms, zoomed")

# Set y-axis range (either logarithmic or noram upper/lower limits, depending on thich of the following lines are in/out)
# plt.yscale("log")
plt.ylim(0, 200)  
# Desired range

plt.show()

# %%

'''all_data = []

with open('pmt1-140v-b1_CH3.txt', 'r') as file:
    for line in file:  
        data = [float(val) for val in line.split()]
        all_data.append(data)


for row in all_data:
    x = range(1, len(row) + 1) 
    plt.plot(x, row)

print("Total fastframe waveforms, layered")
plt.show()

'''

# %%




# File names, for copy/pasting

# cpmt1b2155Ch3.txt
# pmt1-140v-b1_CH3.txt
# pmt1-150v-b1_CH3.txt
# pmt1-160v-b1_CH3.txt
# Pmt3_160v_Led_allCH.txt
# Pmt3_160v_Dark_allCH.txt
# pmt3-175v-b1_CH3.txt
# pmt3-180v-b1_CH3.txt
# pmt3-185v-b1_CH3.txt
# pmt1_165v_r_allCH.txt     -r 165v
# testittt_allCH.txt"       -r Wrong channel (trigger channel)
# pmt1_155v_r_allCH.txt     -r                                     ["-r" tests are retests, with similar conditions]
# pmt1_175v_r_allCH.txt     -r
# pmt1_145v_r_allCH.txt     -r
# pmt4_155v_ts_allCH.txt
# BaseTests_Pmt3_b1_allCH.txt
# BaseTests_Pmt3_b3_allCH.txt
# BaseTests_Pmt3_b4_allCH.txt

# %%


with open('pmt1_165v_all.txt', 'r') as file:
    for line in file:  
        data = [float(val) for val in line.split()]
        all_data.append(data)


for row in all_data:
    x = range(1, len(row) + 1) 
    
    random_number = random.randint(1, x)
    plt.plot(random_number, row)

print("All fastframe waveforms, layered")
plt.show()


import matplotlib.pyplot as plt
import random

# %%

file_name = "pmt1-160v-b1_CH3.txt"

all_data = []
with open(file_name, 'r') as file:
    for line in file:
        data = [float(val) for val in line.split()]
        all_data.append(data)
for row in all_data:
    x = range(1, len(row) + 1)
    row = all_data[1]
    plt.plot(x, row)
plt.show()

# %%

# Single wave with + offset

import random
import matplotlib.pyplot as plt

with open('pmt3-180v-b1_CH3.txt', 'r') as file:
    lines = sum(1 for _ in file)
line_to_plot = random.randint(0, lines-1)
current_line = 0
with open('pmt3-180v-b1_CH3.txt', 'r') as file:
    plt.figure()
    for line in file:
        if current_line == line_to_plot:
            data = [float(val)+2 for val in line.split()]
            x = range(1, len(data) + 1)
            plt.plot(x, data)
            break
        current_line+=1
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
plt.hist(all_top1, bins=280, range=(-5, 10))
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
plt.hist(all_top2, bins=280, range=(-5, 10))
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
plt.hist(hist_diff, bins=280, range=(-5, 10))
plt.xlabel("Amplitude (mV)")
plt.ylabel("Frequency")
plt.title("Difference Histogram (LED - Dark)")
plt.ylim(0, 200)
plt.show()

plt.figure(figsize=(12, 6))
plt.hist(hist_diff, bins=280, range=(-5, 50))
plt.xlabel("Amplitude (mV)")
plt.ylabel("Frequency")
plt.title("Difference Histogram (LED - Dark)")
plt.show()
# %%
