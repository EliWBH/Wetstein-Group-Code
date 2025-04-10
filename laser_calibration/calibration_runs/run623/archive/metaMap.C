#define metaMap_cxx
#include "metaMap.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void metaMap::Loop()
{
//   In a ROOT session, you can do:
//      root> .L metaMap.C
//      root> metaMap t
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
   if (fChain == 0) return;
   fChain->SetBranchStatus("*",0);
   fChain->SetBranchStatus("pmtId", 1);
   fChain->SetBranchStatus("pmtX", 1);
   fChain->SetBranchStatus("pmtY", 1);
   fChain->SetBranchStatus("pmtZ", 1);

   FILE *file_ptr;
   file_ptr = fopen("eosMetaMap.csv", "wr");
   fprintf(file_ptr, "PMT ID, X Position, Y Position, Z Position\n");


   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      GetEntry(jentry);

      vector<int> id_vector = *pmtId;
      vector<double> X_pos = *pmtX;
      vector<double> Y_pos = *pmtY;
      vector<double> Z_pos = *pmtZ;
   
      for(int i=0; i< id_vector.size(); i++){
         fprintf(file_ptr, "%d, %lf, %lf, %lf\n", id_vector[i], X_pos[i], Y_pos[i], Z_pos[i]); 
      
      }
      
      // if (Cut(ientry) < 0) continue;
   }
   fclose(file_ptr);
}
