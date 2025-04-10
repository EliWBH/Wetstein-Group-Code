from functions import *
import uproot 

filename = "calibration_runs/run623/eos_data-fiber_calibration-5-3-run-623.0.ntuple.root"

with uproot.open(filename) as file:
    print(file.keys())

    data = file['output']
    print(data.keys())
    digitIDs = data['digitPMTID'].array()
    digitPeaks = data['digitPeak'].array()
    max_array = []

    for peaks,IDs in zip(digitPeaks, digitIDs):
        peaks = np.array(peaks)
        max_array.append(IDs[np.argmax(peaks)])
    print(len(max_array))
    print("The average is " + str(np.average(max_array)))
    print("The standard deviation is " + str(np.std(max_array)))
    bins = np.linspace(0,241,241)
    plt.hist(max_array, bins=bins)
    plt.show()
    
    # for event in hitPMTS:
    #     while len(event) < 241:
    #         event = np.append(event, 0)
    #     event = np.asarray(event)
        
    
    # hitsOne = hitPMTS[:49]
    # hitsTwo = hitPMTS[50:99]
    # hitsThree = hitPMTS[100:149]
    # hitsFour = hitPMTS[150:199]
    # hitsFive = hitPMTS[200:]

    # print(hitsOne)

#     hitsOne = np.asarray(hitsOne)
#     hitPMTS = ak.Array(hitPMTS)
#     hitPMTS = ak.flatten(hitPMTS)
#     hitPMTS = ak.to_numpy(hitPMTS)
    
#     bins = np.linspace(0, 241, 242)
#     counts, bins = np.histogram(hitPMTS, bins=bins)
#     print(counts, bins)

#     heatmap_data = []

#     row_counter = 0
#     total_counter = 0

#     while(total_counter < len(counts)-1):
#         inst_row = []
#         row_counter = 0
#         while(row_counter < 20):
#             inst_row.append(counts[total_counter])
#             row_counter +=1
#             total_counter += 1
#         heatmap_data.append(inst_row)
#     print(heatmap_data)

# ######
#     x_list = []
#     y_list = []

#     for pmt in hitPMTS[:100]:
#         x_list.append(x[pmt])
#         y_list.append(y[pmt])

#     print(max(y_list))
#     #data = (x_list, y_list)
# # #######
    
# r = np.random.random((4,4))
# #     print(hitPMTS)  
# print(r)
        
# plt.imshow(heatmap_data)
# plt.show()
