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

void process(std::string filename){
    const char* file = filename.c_str();

    //Create in-data, out-data, and the root tree
    auto fIn = TFile::Open(file);
    TTree* inData;

    TFile *fOut = TFile::Open("Eos_data.root", "RECREATE");
    TTree* outTree;
    
    //Output Stuffs
    fIn->GetObject("output", inData);    
    inData->SetBranchStatus("*", 0);
    inData->SetBranchStatus("digitPMTID", 1);
    inData->SetBranchStatus("digitTime", 1);
    inData->SetBranchStatus("digitCharge",1);

    outTree = inData->CloneTree(0);
    outTree->CopyEntries(inData);
    outTree->Write();

    //Metadata Stuffs
    fIn->GetObject("meta", inData);
    inData->SetBranchStatus("*", 0);
    inData->SetBranchStatus("pmtX",1);
    inData->SetBranchStatus("pmtY",1);
    inData->SetBranchStatus("pmtZ", 1);
    inData->SetBranchStatus("runId",1);
    inData->SetBranchStatus("pmtType",1);

    outTree = inData->CloneTree(0);
    outTree->CopyEntries(inData);

    // std::cout << sizeof(*inTree) << endl;
    // int nevents = inTree->GetEntries();
    // std::cout << nevents << endl;

    //tree->Branch("pmtID", &pmtID, "pmtID/I");
    
    

    

    outTree->Write();
    fOut->Close();
    fIn->Close();
}



int main(int argc, char *argv[]){
    if(argc == 2){
        std::string input_filename(argv[1]);
        process(input_filename);
    }
    else{
        std::cout << "Wrong number of arguments." << std::endl;
    }

    return 0;
  
}


//Slide deck describing data format
//How was the data obtained?
//What are the "bare essentials"
/*pmtID
digitTime
digitCharge

Meta
    x,y,z
    runType
    runID
    pmtType*/