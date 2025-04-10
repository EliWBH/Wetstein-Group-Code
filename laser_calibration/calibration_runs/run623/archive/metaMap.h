//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Feb 20 11:53:55 2025 by ROOT version 6.34.02
// from TTree meta/meta
// found on file: eos_data-fiber_calibration-5-3-run-623.0.ntuple.root
//////////////////////////////////////////////////////////

#ifndef metaMap_h
#define metaMap_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include "c++/13/string"
#include "c++/13/vector"
#include "c++/13/vector"
#include "c++/13/vector"

class metaMap {
public :
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

   metaMap(TTree *tree=0);
   virtual ~metaMap();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual bool     Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef metaMap_cxx
metaMap::metaMap(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("eos_data-fiber_calibration-5-3-run-623.0.ntuple.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("eos_data-fiber_calibration-5-3-run-623.0.ntuple.root");
      }
      f->GetObject("meta",tree);

   }
   Init(tree);
}

metaMap::~metaMap()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t metaMap::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t metaMap::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void metaMap::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   macro = 0;
   pmtType = 0;
   pmtId = 0;
   pmtChannel = 0;
   pmtIsOnline = 0;
   pmtCableOffset = 0;
   pmtX = 0;
   pmtY = 0;
   pmtZ = 0;
   pmtU = 0;
   pmtV = 0;
   pmtW = 0;
   geo_file = 0;
   experiment = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("runId", &runId, &b_runId);
   fChain->SetBranchAddress("runType", &runType, &b_runType);
   fChain->SetBranchAddress("runTime", &runTime, &b_runTime);
   fChain->SetBranchAddress("dsentries", &dsentries, &b_dsentries);
   fChain->SetBranchAddress("macro", &macro, &b_macro);
   fChain->SetBranchAddress("pmtType", &pmtType, &b_pmtType);
   fChain->SetBranchAddress("pmtId", &pmtId, &b_pmtId);
   fChain->SetBranchAddress("pmtChannel", &pmtChannel, &b_pmtChannel);
   fChain->SetBranchAddress("pmtIsOnline", &pmtIsOnline, &b_pmtIsOnline);
   fChain->SetBranchAddress("pmtCableOffset", &pmtCableOffset, &b_pmtCableOffset);
   fChain->SetBranchAddress("pmtX", &pmtX, &b_pmtX);
   fChain->SetBranchAddress("pmtY", &pmtY, &b_pmtY);
   fChain->SetBranchAddress("pmtZ", &pmtZ, &b_pmtZ);
   fChain->SetBranchAddress("pmtU", &pmtU, &b_pmtU);
   fChain->SetBranchAddress("pmtV", &pmtV, &b_pmtV);
   fChain->SetBranchAddress("pmtW", &pmtW, &b_pmtW);
   fChain->SetBranchAddress("geo_index", &geo_index, &b_geo_index);
   fChain->SetBranchAddress("geo_file", &geo_file, &b_geo_file);
   fChain->SetBranchAddress("experiment", &experiment, &b_experiment);
   fChain->SetBranchAddress("source_pos_x", &source_pos_x, &b_source_pos_x);
   fChain->SetBranchAddress("source_pos_y", &source_pos_y, &b_source_pos_y);
   fChain->SetBranchAddress("source_pos_z", &source_pos_z, &b_source_pos_z);
   fChain->SetBranchAddress("source_rot_x", &source_rot_x, &b_source_rot_x);
   fChain->SetBranchAddress("source_rot_y", &source_rot_y, &b_source_rot_y);
   fChain->SetBranchAddress("source_rot_z", &source_rot_z, &b_source_rot_z);
   Notify();
}

bool metaMap::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return true;
}

void metaMap::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t metaMap::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef metaMap_cxx
