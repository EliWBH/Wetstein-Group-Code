#!/bin/bash

# Define file pattern (change as needed)
FILE_PATTERN="MRD_2025_3*"

# First SCP: Copy from remote server to local machine
ssh -K annie@annie-gw01.fnal.gov <<EOF
scp annie@192.168.163.23:/monitoringfiles/$FILE_PATTERN ./MRDmonitoring/
EOF

# Transfer files to the second remote server
ssh -K aupmeyer@anniegpvm02.fnal.gov <<EOF
scp -r annie@annie-gw01.fnal.gov:MRDmonitoring/ /exp/annie/data/users/aupmeyer
EOF

# Final SCP: Copy from the second remote server to local directory
scp -r -o GSSAPIAuthentication=yes aupmeyer@anniegpvm02.fnal.gov:/exp/annie/data/users/aupmeyer/MRDmonitoring/$FILE_PATTERN ./MRDFiles

echo "File transfer complete."
