#ifndef METADSTRUCT_H
#define METADSTRUCT_H

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
// #include "c++/11/string"
// #include "c++/11/vector"
// #include "c++/11/vector"
// #include "c++/11/vector"


struct metaD{
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           runId;
   ULong64_t       runType;
   ULong64_t       runTime;
   Int_t           dsentries;
   string          *macro;
   vector<int>     *pmtType;
   vector<int>     *pmtId;
   vector<int>     *pmtChannel;
   vector<bool>    *pmtIsOnline;
   vector<double>  *pmtCableOffset;
   vector<double>  *pmtX;
   vector<double>  *pmtY;
   vector<double>  *pmtZ;
   vector<double>  *pmtU;
   vector<double>  *pmtV;
   vector<double>  *pmtW;
   Double_t        geo_index;
   string          *geo_file;
   string          *experiment;
   Double_t        source_pos_x;
   Double_t        source_pos_y;
   Double_t        source_pos_z;
   Double_t        source_rot_x;
   Double_t        source_rot_y;
   Double_t        source_rot_z;

   // List of branches
   TBranch        *b_runId;   //!
   TBranch        *b_runType;   //!
   TBranch        *b_runTime;   //!
   TBranch        *b_dsentries;   //!
   TBranch        *b_macro;   //!
   TBranch        *b_pmtType;   //!
   TBranch        *b_pmtId;   //!
   TBranch        *b_pmtChannel;   //!
   TBranch        *b_pmtIsOnline;   //!
   TBranch        *b_pmtCableOffset;   //!
   TBranch        *b_pmtX;   //!
   TBranch        *b_pmtY;   //!
   TBranch        *b_pmtZ;   //!
   TBranch        *b_pmtU;   //!
   TBranch        *b_pmtV;   //!
   TBranch        *b_pmtW;   //!
   TBranch        *b_geo_index;   //!
   TBranch        *b_geo_file;   //!
   TBranch        *b_experiment;   //!
   TBranch        *b_source_pos_x;   //!
   TBranch        *b_source_pos_y;   //!
   TBranch        *b_source_pos_z;   //!
   TBranch        *b_source_rot_x;   //!
   TBranch        *b_source_rot_y;   //!
   TBranch        *b_source_rot_z;   //!
};

#endif