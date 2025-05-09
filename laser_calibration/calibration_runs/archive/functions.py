import numpy as np
import matplotlib.pyplot as plt
import awkward as ak
import h5py
from scipy.optimize import curve_fit
from scipy.stats import norm
from scipy.signal import find_peaks
from meta import *

def read_file(filename):
    waves = []
    times = []
    with h5py.File(filename, "r") as f:
        for board in boards:
            digit = f[board]
            board_id = boards[board]

            dt = digit.attrs['ns_sample']
            bits = digit.attrs['bits']
            nsamples = digit.attrs['samples']

            for ch_num in range(15):
                ch_str = "ch%d" % ch_num
                channel = digit[ch_str]
                dynamic_range = channel.attrs['dynamic_range']
                dv = dynamic_range/np.power(2, bits)

                time = np.arange(0, nsamples*dt, dt)

                data = channel["samples"]
                
                lcn = ch_num + board_id*16
                # pmtx = x[lcn] 
                # pmty = y[lcn] 
                # pmtz = z[lcn] 
                #print("PMT position: (%.2f %.2f %.2f) mm" % (pmtx, pmty, pmtz))
                
                for i in range(len(data)):
                    
                    pedestal = np.mean(data[i][0:ped_window])
                    voltage = ((data[i])-pedestal)*dv
                    peak = np.argmin(voltage)
                    
                    waves.append(voltage)
                    times.append(time)
                    
                    # #Check if voltage is too extreme
                    # minimum = np.min(voltage)
                    # maximum = np.max(voltage)
                    # if ((minimum < THRESHOLD and maximum < 5 and minimum > -40)):# and time[peak] < 125):    
                    #     voltage = np.array(voltage) * -1
                    #     packet_boundaries = find_resolved_packet_boundaries(voltage, threshold) 
                    #     num_packets = len(packet_boundaries)
            
                    #     if (num_packets == 1):    
                    #         waves.append(voltage)
                    #         if(len(packet_boundaries) != 1):
                    #             print(packet_boundaries)
                    #     else:
                    #         continue
                    # else:
                    #     continue
                
    return waves, times
    
#Find the rising and falling edge threshold crossings
def find_resolved_packet_boundaries(combined_pulse, threshold):
    above_threshold = combined_pulse > threshold
    packet_boundaries = []
    start = None
        
    for i, is_above in enumerate(above_threshold):
        if is_above and start is None: 
            start = i
        elif not is_above and start is not None:
            if start != 0:  # Ignore the start at t=0
                packet_boundaries.append((start, i))
            start = None

    if start is not None and start != 0:
        packet_boundaries.append((start, len(combined_pulse) - 1))

    return packet_boundaries
