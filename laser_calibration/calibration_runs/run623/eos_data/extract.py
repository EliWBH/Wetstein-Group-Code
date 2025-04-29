#!/usr/bin/python3
import sys
import uproot
import csv
import pandas as pd
import json
import awkward as ak

# filename = "eos_data-fiber_calibration-5-3-run-623.0.ntuple.root"

with uproot.open(str(sys.argv[1])) as file:
    #Extract the meta data
    meta = file['meta']
    x_pos = ak.flatten(meta['pmtX'].array())
    y_pos = ak.flatten(meta['pmtY'].array())
    z_pos = ak.flatten(meta['pmtZ'].array())

    #Extract the output data
    data = file['output']

    #Way to extract the event number (ideally want to find a better way)
    event_number = []
    
    #Storing the data to CSV inspired by Eli Brunner-Huber
    branches =  ['digitPMTID', 'digitTime', 'digitCharge']
    df = data.arrays(branches, library="pd")

for col in df:
    df[col] = df[col].apply(json.dumps)
csv_file_path = "outputData.csv"
df.to_csv(csv_file_path, index=True)

    
#Make the meta data CSV    
with open('metaData.csv', 'w', newline='') as meta_csv:
    fieldnames = ['PMT ID', 'X Position', 'Y Position', 'Z Position']
    meta_writer = csv.DictWriter(meta_csv, fieldnames=fieldnames)
    meta_writer.writeheader()

    for i in range(0, len(x_pos)):
        meta_writer.writerow({'PMT ID': i, 'X Position': x_pos[i], 'Y Position': y_pos[i], 'Z Position': z_pos[i]})
    meta_csv.close()

