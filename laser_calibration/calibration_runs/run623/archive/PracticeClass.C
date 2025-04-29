#define PracticeClass_cxx
#include "PracticeClass.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void PracticeClass::Loop()
{
//   In a ROOT session, you can do:
//      root> .L PracticeClass.C
//      root> PracticeClass t
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
   
   //Initialize Data Tree
   if (fChain == 0) return;
   fChain->SetBranchStatus("*",0);
   fChain->SetBranchStatus("digitPeak",1);

   Int_t nentries = fChain->GetEntriesFast();
   TH1F *myHisto = new TH1F("myHisto", "digitPeak Maxima",100, -15,0);

   //Find max peak per event and plot hist
   for(Int_t jentry=0; jentry<nentries;jentry++){
      GetEntry(jentry);
      
      vector<double> peakData = *digitPeak;
      vector<int> pmtID = *digitPMTID;
      
      double max = peakData[0];
      for(int i=0; i<peakData.size(); i++){
         if(peakData[i] > max){
            max = peakData[i];
         } else{
            continue;
         }
      }
      printf("%lf", max);
      myHisto->Fill(max);  
   }

   myHisto->Draw();

}
