//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Nov 13 13:47:23 2024 by ROOT version 6.30/08
// from TTree output/output
// found on file: eos_data-fiber_calibration-5-3-run-623.0.ntuple.root
//////////////////////////////////////////////////////////

#ifndef Calibration_h
#define Calibration_h
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

#include "metaDstruct.h"
// Header file for the classes stored in the TTree if any.
// #include "c++/11/vector"
// #include "c++/11/vector"


class Calibration {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           mcpdg;
   Double_t        mcx;
   Double_t        mcy;
   Double_t        mcz;
   Double_t        mcu;
   Double_t        mcv;
   Double_t        mcw;
   Double_t        mcke;
   Double_t        mct;
   Int_t           evid;
   Int_t           subev;
   Int_t           nhits;
   Double_t        triggerTime;
   ULong64_t       timestamp;
   Double_t        timeSinceLastTrigger_us;
   Int_t           mcid;
   Int_t           mcparticlecount;
   Int_t           mcpecount;
   Int_t           mcnhits;
   Double_t        scintEdep;
   Double_t        scintEdepQuenched;
   Double_t        scintPhotons;
   Double_t        remPhotons;
   Double_t        cherPhotons;
   vector<int>     *hitPMTID;
   vector<double>  *hitPMTTime;
   vector<double>  *hitPMTCharge;
   Int_t           digitNhits;
   vector<int>     *digitPMTID;
   vector<double>  *digitTime;
   vector<double>  *digitCharge;
   vector<int>     *digitNCrossings;
   vector<double>  *digitPeak;
   vector<double>  *digitLocalTriggerTime;
   vector<double>  *fitTime;
   vector<double>  *fitBaseline;
   vector<double>  *fitPeak;
   vector<int>     *mcPMTID;
   vector<int>     *mcPMTNPE;
   vector<double>  *mcPMTCharge;
   vector<double>  *mcPEHitTime;
   vector<double>  *mcPEFrontEndTime;
   vector<int>     *mcPEProcess;
   vector<double>  *mcPEWavelength;
   vector<double>  *mcPEx;
   vector<double>  *mcPEy;
   vector<double>  *mcPEz;
   vector<double>  *mcPECharge;

   // List of branches
   TBranch        *b_mcpdg;   //!
   TBranch        *b_mcx;   //!
   TBranch        *b_mcy;   //!
   TBranch        *b_mcz;   //!
   TBranch        *b_mcu;   //!
   TBranch        *b_mcv;   //!
   TBranch        *b_mcw;   //!
   TBranch        *b_mcke;   //!
   TBranch        *b_mct;   //!
   TBranch        *b_evid;   //!
   TBranch        *b_subev;   //!
   TBranch        *b_nhits;   //!
   TBranch        *b_triggerTime;   //!
   TBranch        *b_timestamp;   //!
   TBranch        *b_timeSinceLastTrigger_us;   //!
   TBranch        *b_mcid;   //!
   TBranch        *b_mcparticlecount;   //!
   TBranch        *b_mcpecount;   //!
   TBranch        *b_mcnhits;   //!
   TBranch        *b_scintEdep;   //!
   TBranch        *b_scintEdepQuenched;   //!
   TBranch        *b_scintPhotons;   //!
   TBranch        *b_remPhotons;   //!
   TBranch        *b_cherPhotons;   //!
   TBranch        *b_hitPMTID;   //!
   TBranch        *b_hitPMTTime;   //!
   TBranch        *b_hitPMTCharge;   //!
   TBranch        *b_digitNhits;   //!
   TBranch        *b_digitPMTID;   //!
   TBranch        *b_digitTime;   //!
   TBranch        *b_digitCharge;   //!
   TBranch        *b_digitNCrossings;   //!
   TBranch        *b_digitPeak;   //!
   TBranch        *b_digitLocalTriggerTime;   //!
   TBranch        *b_fitTime;   //!
   TBranch        *b_fitBaseline;   //!
   TBranch        *b_fitPeak;   //!
   TBranch        *b_mcPMTID;   //!
   TBranch        *b_mcPMTNPE;   //!
   TBranch        *b_mcPMTCharge;   //!
   TBranch        *b_mcPEHitTime;   //!
   TBranch        *b_mcPEFrontEndTime;   //!
   TBranch        *b_mcPEProcess;   //!
   TBranch        *b_mcPEWavelength;   //!
   TBranch        *b_mcPEx;   //!
   TBranch        *b_mcPEy;   //!
   TBranch        *b_mcPEz;   //!
   TBranch        *b_mcPECharge;   //!

   Calibration(TTree *tree=0);
   virtual ~Calibration();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void    Loop(metaD meta);
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef Calibration_cxx
Calibration::Calibration(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("eos_data-fiber_calibration-5-3-run-623.0.ntuple.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("eos_data-fiber_calibration-5-3-run-623.0.ntuple.root");
      }
      f->GetObject("output",tree);

   }
   Init(tree);
}

Calibration::~Calibration()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t Calibration::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t Calibration::LoadTree(Long64_t entry)
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

void Calibration::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   hitPMTID = 0;
   hitPMTTime = 0;
   hitPMTCharge = 0;
   digitPMTID = 0;
   digitTime = 0;
   digitCharge = 0;
   digitNCrossings = 0;
   digitPeak = 0;
   digitLocalTriggerTime = 0;
   fitTime = 0;
   fitBaseline = 0;
   fitPeak = 0;
   mcPMTID = 0;
   mcPMTNPE = 0;
   mcPMTCharge = 0;
   mcPEHitTime = 0;
   mcPEFrontEndTime = 0;
   mcPEProcess = 0;
   mcPEWavelength = 0;
   mcPEx = 0;
   mcPEy = 0;
   mcPEz = 0;
   mcPECharge = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("mcpdg", &mcpdg, &b_mcpdg);
   fChain->SetBranchAddress("mcx", &mcx, &b_mcx);
   fChain->SetBranchAddress("mcy", &mcy, &b_mcy);
   fChain->SetBranchAddress("mcz", &mcz, &b_mcz);
   fChain->SetBranchAddress("mcu", &mcu, &b_mcu);
   fChain->SetBranchAddress("mcv", &mcv, &b_mcv);
   fChain->SetBranchAddress("mcw", &mcw, &b_mcw);
   fChain->SetBranchAddress("mcke", &mcke, &b_mcke);
   fChain->SetBranchAddress("mct", &mct, &b_mct);
   fChain->SetBranchAddress("evid", &evid, &b_evid);
   fChain->SetBranchAddress("subev", &subev, &b_subev);
   fChain->SetBranchAddress("nhits", &nhits, &b_nhits);
   fChain->SetBranchAddress("triggerTime", &triggerTime, &b_triggerTime);
   fChain->SetBranchAddress("timestamp", &timestamp, &b_timestamp);
   fChain->SetBranchAddress("timeSinceLastTrigger_us", &timeSinceLastTrigger_us, &b_timeSinceLastTrigger_us);
   fChain->SetBranchAddress("mcid", &mcid, &b_mcid);
   fChain->SetBranchAddress("mcparticlecount", &mcparticlecount, &b_mcparticlecount);
   fChain->SetBranchAddress("mcpecount", &mcpecount, &b_mcpecount);
   fChain->SetBranchAddress("mcnhits", &mcnhits, &b_mcnhits);
   fChain->SetBranchAddress("scintEdep", &scintEdep, &b_scintEdep);
   fChain->SetBranchAddress("scintEdepQuenched", &scintEdepQuenched, &b_scintEdepQuenched);
   fChain->SetBranchAddress("scintPhotons", &scintPhotons, &b_scintPhotons);
   fChain->SetBranchAddress("remPhotons", &remPhotons, &b_remPhotons);
   fChain->SetBranchAddress("cherPhotons", &cherPhotons, &b_cherPhotons);
   fChain->SetBranchAddress("hitPMTID", &hitPMTID, &b_hitPMTID);
   fChain->SetBranchAddress("hitPMTTime", &hitPMTTime, &b_hitPMTTime);
   fChain->SetBranchAddress("hitPMTCharge", &hitPMTCharge, &b_hitPMTCharge);
   fChain->SetBranchAddress("digitNhits", &digitNhits, &b_digitNhits);
   fChain->SetBranchAddress("digitPMTID", &digitPMTID, &b_digitPMTID);
   fChain->SetBranchAddress("digitTime", &digitTime, &b_digitTime);
   fChain->SetBranchAddress("digitCharge", &digitCharge, &b_digitCharge);
   fChain->SetBranchAddress("digitNCrossings", &digitNCrossings, &b_digitNCrossings);
   fChain->SetBranchAddress("digitPeak", &digitPeak, &b_digitPeak);
   fChain->SetBranchAddress("digitLocalTriggerTime", &digitLocalTriggerTime, &b_digitLocalTriggerTime);
   fChain->SetBranchAddress("fitTime", &fitTime, &b_fitTime);
   fChain->SetBranchAddress("fitBaseline", &fitBaseline, &b_fitBaseline);
   fChain->SetBranchAddress("fitPeak", &fitPeak, &b_fitPeak);
   fChain->SetBranchAddress("mcPMTID", &mcPMTID, &b_mcPMTID);
   fChain->SetBranchAddress("mcPMTNPE", &mcPMTNPE, &b_mcPMTNPE);
   fChain->SetBranchAddress("mcPMTCharge", &mcPMTCharge, &b_mcPMTCharge);
   fChain->SetBranchAddress("mcPEHitTime", &mcPEHitTime, &b_mcPEHitTime);
   fChain->SetBranchAddress("mcPEFrontEndTime", &mcPEFrontEndTime, &b_mcPEFrontEndTime);
   fChain->SetBranchAddress("mcPEProcess", &mcPEProcess, &b_mcPEProcess);
   fChain->SetBranchAddress("mcPEWavelength", &mcPEWavelength, &b_mcPEWavelength);
   fChain->SetBranchAddress("mcPEx", &mcPEx, &b_mcPEx);
   fChain->SetBranchAddress("mcPEy", &mcPEy, &b_mcPEy);
   fChain->SetBranchAddress("mcPEz", &mcPEz, &b_mcPEz);
   fChain->SetBranchAddress("mcPECharge", &mcPECharge, &b_mcPECharge);
   Notify();
}

Bool_t Calibration::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void Calibration::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t Calibration::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef Calibration_cxx
