Welcome to the Laser Calibration Event Display README!

If this repo is a mess, blame Eliot Keener. 

In this mess of files and directories, you will have the ability to take data from ANNIE or Eos and be able to make event displays from them.

To get started, look in the 'calibration_runs' directory. You should see a directory for 'eos_data' and 'archive.' 'eos_data' is a batch of data from EOS run623. This would be a good place to take data from if you want to familiarize yourself with the Eos experiment. 'archive' basically contains things that I wrote in the past to get to this point. It should be mostly irrelevant to you, but feel free to take a look around.

The bulk of this repo's utility is from the jupyter notebooks.
Through the pmtMapping.ipynb, you will be able to load data from ANNIE or Eos into your jupyter workspace, and do whatever analysis you want and plot event-by-event displays.

Accessing your data depends on which experiment you are working on.

ANNIE:
The data will be stored in some hierarchal data format such as an ntuple file. To access that data in a way that pmtMapping.ipynb can read it, use Eli's laserRunDataExtraction.ipynb. All you should need to do is change the filename to the one of the data file you want to extract.

EOS:
In 'eos_data' there is a script called extract.py. To run this script, you will want the python script and the Eos ntuple file you want to extract in the same directory. In your terminal, call 
```
python3 extract.py [filename you want to extract]
```
This will produce a metaData.csv and and outputData.csv. Using these names, you should be able to run pmtMapping.ipynb as expected.

Using pmtMapping.ipynb
Outside of this directory, there are a few slides explaining the key features of pmtMapping.ipynb. Here, I will list the essentials to getting started with the code.

1) go to the directory with the jupyter notebook and call 'jupyter-notebook'
2) In the web browser move to pmtMapping and open it
3) Run through each cell until you reach a chunk of code with a comment '#Sample ANNIE loop()' or '#Sample Eos loop(). This will run all of your key functions
4) Make a loop that will extract the data and the geometry using the read_data and read_eos_geometry or read_annie_geometry functions.
5) Using the PDFpages package, make a pdf with a name of your choosing
6) Loop through the length of your extracted data array. This will have arrays of [ID, Time, Charge] for each hit in the event.
7) Loop through each hit in the event and use the plot_hit function to make a figure for that event
8) Go to the directory this is all stored in and view your pdf.
