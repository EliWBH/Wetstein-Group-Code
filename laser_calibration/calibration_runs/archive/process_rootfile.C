#include <stdio.h>
#include <iostream>
#include <string>
#include <map>
#include <vector>

#include <TCanvas.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TFile.h>
#include <TTree.h>
#include <TBranch.h>
#include <TSystem.h>

void process(std::string filename){
    gSystem->Load("libTree");
    const char* file = filename.c_str();


    //Create in-data, out-data, and the root tree
    auto fIn = TFile::Open(file);
    TTree* tree= (TTree*)fIn->Get("meta");

    // vector<double> *x;
    
    // tree->SetBranchAddress("pmtX",&x);

    // Open the ROOT file
    std::vector<double>* branchData = nullptr;
    std::vector<double> x_pos = {};
    
    // Set the branch address
    tree->SetBranchAddress("pmtX", &branchData);

    // Loop over entries
    for (Long64_t i = 0; i < tree->GetEntries(); i++) {
        tree->GetEntry(i);
        std::cout << "Entry " << i << ": ";
        for(double val : *branchData){
            std::cout << val << std::endl;
        }
        branchData->clear();
    }

    fIn->Close();  // Close the ROOT file
}



    

    //Output Stuffs
    // fIn->GetObject("output", inData);    
    // inData->SetBranchStatus("*", 0);
    // inData->SetBranchStatus("digitPMTID", 1);
    // inData->SetBranchStatus("digitTime", 1);
    // inData->SetBranchStatus("digitCharge",1);

    // outTree = inData->CloneTree(0);
    // outTree->CopyEntries(inData);
    // outTree->Write();

    
    // //Metadata Stuffs
    // fIn->GetObject("meta", inData);
    // //inData->SetBranchStatus("*", 0);
    // inData->SetBranchAddress("pmtX",&x_pos);
    // inData->SetBranchStatus("pmtY",1);
    // inData->SetBranchStatus("pmtZ", 1);
    // // inData->SetBranchStatus("runId",1);
    // // inData->SetBranchStatus("pmtType",1);

  

    //inData->Branch("pmtX", &x_pos);
    //printf("%zu", x_pos->size());

    // outTree = inData->CloneTree(0);
    // outTree->CopyEntries(inData);

    // std::cout << sizeof(*inTree) << endl;
    // int nevents = inTree->GetEntries();
    // std::cout << nevents << endl;

    //tree->Branch("pmtID", &pmtID, "pmtID/I");
    
    

    

    // outTree->Write();
    // fOut->Close();
    // fIn->Close();
