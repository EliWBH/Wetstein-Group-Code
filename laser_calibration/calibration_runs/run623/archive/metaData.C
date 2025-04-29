#define metaData_cxx
#include "metaData.h" 
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

metaD metaData::Loop()
{
//   In a ROOT session, you can do:
//      root> .L metaData.C
//      root> metaData t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   metaD meta;

   if (fChain == 0) return meta;
   fChain->SetBranchStatus("*",0);
   fChain->SetBranchStatus("pmtX",1);
   fChain->SetBranchStatus("pmtY",1);
   fChain->SetBranchStatus("pmtZ",1);


   Long64_t nentries = fChain->GetEntriesFast();
   printf("%lld\n", nentries);
   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry < nentries; jentry++) {

      Long64_t ientry = LoadTree(jentry);
      GetEntry(jentry);
      
      meta.pmtX = pmtX;
      meta.pmtY = pmtY;
      meta.pmtZ = pmtZ;
      //printf("%zu", xPositions.size());

      // for(int value=0; value < xPositions.size(); value++){
      //    printf("%lf\n", xPositions[value]);
      // }
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
   }
   return meta;
}
