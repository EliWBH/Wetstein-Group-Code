#define Calibration_cxx
#include "Calibration.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void Calibration::Loop(metaD meta)
{
   //Branch Initialization
   if (fChain == 0) return;
   fChain->SetBranchStatus("*",0);
   fChain->SetBranchStatus("digitPeak",1);
   fChain->SetBranchStatus("digitPMTID",1);
   fChain->SetBranchStatus("digitTime",1);

   //Metadata Initialization
   vector<double> xPositions = *meta.pmtX;
   vector<double> yPositions = *meta.pmtY;
   vector<double> zPositions = *meta.pmtZ;
   double xPos;
   double yPos;
   double zPos;

   int channelSelect;

   // printf("Which pmt do you want to look at? ");
   // scanf("%d", &channelSelect);

   Long64_t nentries = fChain->GetEntriesFast();
   
   TCanvas *c1 = new TCanvas("c1", "Axial Sensitivity 20mm", 200,10,800,600);
   // TCanvas *c2 = new TCanvas("c2", "Axial Sensitivity 20mm", 200,10,800,600);
   // TCanvas *c3 = new TCanvas("c3", "Axial Sensitivity 20mm", 200,10,800,600);


   // TH1F *pulseFrequency = new TH1F("pulseFreq", "Frequency of a given PMT Seeing Light",241,0, 242);
   // TH1F *pulseHeight = new TH1F("myHisto", "Pulse Height Distribution of PMT",50, -50,0);
   // TH2F *pulseHeat = new TH2F("twoD", "Position Heatmap", 24,0, 360, 10, -1050, 1050);
   
   // TH2F *timeDist = new TH2F("timingDist", "Time Distribution",24,0,360, 100, 325, 350);
   // TH1F *timeHist = new TH1F("timeHist", "Timing Histogram",1000, 0,800);
   // TH1F *timeHistTotal = new TH1F("totalTimeHist", "Total Timing Histogram", 1000,0,800);

   TH1F *frontHalfTime = new TH1F("frontTime", "Time Distribution for Full Range", 1000, 250, 500);
   TH1F *backHalfTime = new TH1F("backTime", "Time Distribution for Full Range", 1000,250,500);

   TH1F *frontHalfRestrict = new TH1F("frontTime", "Time Distribution for  120-Degree Spread", 1000, 250, 500);
   TH1F *backHalfRestrict = new TH1F("frontTime", "Time Distribution for  120-Degree Spread", 1000, 250, 500);

   TH1F *frontRestrict = new TH1F("frontTime", "Time Distribution for  60-Degree Spread", 1000, 250, 500);
   TH1F *backRestrict = new TH1F("frontTime", "Time Distribution for  60-Degree Spread", 1000, 250, 500);

   TH1F *phiDist = new TH1F("angle", "Phi Hits", 36, 0,360);

   TH2F *timePhi = new TH2F("timePhi", "Phi vs. Time", 100,300,400,18,150,330);

   TH2F *idTime = new TH2F("idTime", "Id vs. Time", 100,320,340,50, 0,50);
   TH1F *hitID = new TH1F("hitID", "Searching for Broken PMT", 281,0,281);


   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      GetEntry(jentry);
      
      vector<double> peakData = *digitPeak;
      vector<int> idData = *digitPMTID;
      vector<double> times = *digitTime;
      
      double max = peakData[0]; 
      int index = 0;

      // for(int startTime = 0; startTime < times.size(); startTime++){
      //    timeDist->Fill(times[startTime]);
      // }

      for(int entry=0; entry < peakData.size(); entry++){
        //pulseFrequency->Fill(idData[entry]); 
	      if(idData[entry] == channelSelect){
            //pulseHeight->Fill(peakData[entry]);     
         }
      }

      for(int pmt = 0; pmt < idData.size(); pmt++){
         double length = TMath::Sqrt(TMath::Power(yPositions[idData[pmt]], 2 ) + TMath::Power(xPositions[idData[pmt]], 2 ));
         double phi = TMath::ATan2(yPositions[idData[pmt]], xPositions[idData[pmt]]) * -180 / TMath::Pi() + 180;
   
         //pulseHeat->Fill(phi,zPositions[idData[pmt]]);   
         //timeDist->Fill(phi, times[pmt]);
         //timeHistTotal->Fill(times[pmt]);

         if(phi > 260 && phi < 280){
            printf("%d\n", pmt);
            idTime->Fill(times[pmt], pmt);
            hitID->Fill(pmt);
         }

         
         // if(phi > 330 || phi < 150){
         //    //timeHist->Fill(times[pmt]);
         //    frontHalfTime->Fill(times[pmt]);
         //    phiDist->Fill(phi);
         // } else if(phi > 150 && phi < 330){
         //    backHalfTime->Fill(times[pmt]);
         //    phiDist->Fill(phi);
         //    timePhi->Fill(times[pmt], phi);

         // }
         
         // if(phi < 120 && phi > 0){
         //    //timeHist->Fill(times[pmt]);
         //    frontHalfRestrict->Fill(times[pmt]);
         //    phiDist->Fill(phi);
         // } else if(phi > 180 && phi < 300){
         //    backHalfRestrict->Fill(times[pmt]);
         //    phiDist->Fill(phi);
         //    timePhi->Fill(times[pmt], phi);

         // }

         // if(phi > 30 && phi < 90){
         //    //timeHist->Fill(times[pmt]);
         //    frontRestrict->Fill(times[pmt]);
         //    phiDist->Fill(phi);
         // } else if(phi > 210 && phi < 270){
         //    backRestrict->Fill(times[pmt]);
         //    phiDist->Fill(phi);
         //    timePhi->Fill(times[pmt], phi);
         // }
      }
      // double selectBinMax = timeHist->GetXaxis()->GetBinCenter(timeHist->GetMaximumBin());
      // double totalBinMax = timeHistTotal->GetXaxis()->GetBinCenter(timeHistTotal->GetMaximumBin());
      // //printf("%lf\n", selectBinMax);
      // printf("%lf\n" ,selectBinMax - totalBinMax);
   
      //printf("%d\n", index); //, xPos, yPos, zPos);
      

      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
   }
   //c1->Update();
   //pulseFrequency->Draw();
   // c1->Write();
   // c2->Update();
   //pulseHeight->Draw();
   // c2->Write();
   //pulseHeat->Draw("colz");
   // c3->Write();
   
   // backHalfTime->SetLineColor(kRed);
   // frontHalfTime->Draw();
   // backHalfTime->Draw("same");

   // backHalfRestrict->SetLineColor(kRed);
   // frontHalfRestrict->Draw();
   // backHalfRestrict->Draw("same");

   // backRestrict->SetLineColor(kRed);
   // frontRestrict->Draw();
   // backRestrict->Draw("same");

   //phiDist->Draw();

   // timePhi->GetXaxis()->SetTitle("Time (ns)");
   // timePhi->GetYaxis()->SetTitle("Phi (degrees)");
   // timePhi->Draw();

   //idTime->Draw();
   hitID->Draw();
}

TH1F* phiSelect(TH1F* phiDist, vector<int> idData, vector<double> yPositions, vector<double> xPositions){
   for(int pmt = 0; pmt < idData.size(); pmt++){
         double length = TMath::Sqrt(TMath::Power(yPositions[idData[pmt]], 2 ) + TMath::Power(xPositions[idData[pmt]], 2 ));
         double phi = TMath::ATan2(yPositions[idData[pmt]], xPositions[idData[pmt]]) * -180 / TMath::Pi() + 180;
   
         //pulseHeat->Fill(phi,zPositions[idData[pmt]]);   
         //timeDist->Fill(phi, times[pmt]);
         //timeHistTotal->Fill(times[pmt]);

         if(phi > 260 && phi < 280){
            printf("%d\n", pmt);
            //idTime->Fill(times[pmt], pmt);
            //hitID->Fill(pmt);
            phiDist->Fill(phi);
         }
   }
   return phiDist;
}