#include <vector>
#include <string>
#include <iostream>

void Compare_2(const char* file1, const char* file2) {
    TFile* tf1 = new TFile(file1, "READ");
    TFile* tf2 = new TFile(file2, "READ");

    if (!tf1 || !tf2 || tf1->IsZombie() || tf2->IsZombie()) {
        std::cerr << "Error: One or both files could not be opened!" << std::endl;
        return;
    }

    std::vector<std::tuple<std::string, TH1D*, TH1D*>> histPairs = {
        {"hitHist7", (TH1D*) tf1->Get("hitHist7"), (TH1D*) tf2->Get("hitHist7")},
        {"hitHist8", (TH1D*) tf1->Get("hitHist8"), (TH1D*) tf2->Get("hitHist8")},
        {"Crate7Hist", (TH1D*) tf1->Get("Crate7Hist"), (TH1D*) tf2->Get("Crate7Hist")},
        {"Crate8Hist", (TH1D*) tf1->Get("Crate8Hist"), (TH1D*) tf2->Get("Crate8Hist")}
    };

    auto extractDate = [](const std::string& filename) -> std::string {
        size_t start = filename.find("_MRD");
        if (start == std::string::npos) return "";
        size_t end = filename.find(".root", start);
        return filename.substr(start, end - start);
    };

    std::string date_range = extractDate(file1) + "_&" + extractDate(file2);
    std::string pdf_filename = "HistComp" + date_range + ".pdf";

    TCanvas *c1 = new TCanvas("c1", "Comparison Canvas", 800, 1000);
    c1->Print((pdf_filename + "[").c_str()); // Open PDF

    for (auto& [name, h1, h2] : histPairs) {
        bool isRatioEligible = (name == "hitHist7" || name == "hitHist8");
        
        for (int pass = 0; pass < (isRatioEligible ? 2 : 1); ++pass) {
            bool isLogY = (pass == 1);  // only 2nd pass is log Y
            c1->Clear();
            c1->Divide(2, 2);
            
            // Panel 1
            c1->cd(1);
            gPad->SetLogy(isLogY);
            h1->SetStats(0);
            h1->SetMaximum(h1->GetMaximum() * 1.1);
            h1->Draw("HIST");
            
            // Panel 2
            c1->cd(2);
            gPad->SetLogy(isLogY);
            h2->SetStats(0);
            h2->SetMaximum(h2->GetMaximum() * 1.1);
            h2->Draw("HIST");
            
            // Panel 3
            c1->cd(3);
            gPad->SetLogy(isLogY);
            h1->SetLineColor(kRed);
            h2->SetLineColor(kBlue);
            double ymax = std::max(h1->GetMaximum(), h2->GetMaximum()) * 1.1;
            h1->SetMaximum(ymax);
            h1->Draw("HIST");
            h2->Draw("HIST SAME");
            
            // Panel 4: Ratio
            if (isRatioEligible) {
                c1->cd(4);
                gPad->SetLogy(isLogY);  // now toggles for pass
                int nbins = h2->GetNbinsX();
                double hlow = h2->GetXaxis()->GetXmin();
                double hhi = h2->GetXaxis()->GetXmax();
                
                TH1D* hratio = new TH1D(Form("hratio_%s_%s", name.c_str(), isLogY ? "log" : "lin"), "Ratio", nbins, hlow, hhi);
                hratio->SetStats(0);
                
                for (int i = 1; i <= nbins; ++i) {
                    double bc1 = h1->GetBinContent(i);
                    double bc2 = h2->GetBinContent(i);
                    hratio->SetBinContent(i, (bc1 > 0) ? (bc2 / bc1) : 0);
                }
                
                hratio->SetMaximum(hratio->GetMaximum() * 1.1);
                hratio->Draw();
            }
            
            c1->Update();
            c1->Print(pdf_filename.c_str());
        }
        
    }
    
    TCanvas* canvas1 = (TCanvas*) tf1->Get("Heatmaps");
    TCanvas* canvas2 = (TCanvas*) tf2->Get("Heatmaps");

    if (canvas1) { canvas1->cd(); canvas1->Update(); canvas1->Print(pdf_filename.c_str()); }
    else std::cerr << "Missing Heatmaps canvas in file1\n";

    if (canvas2) {
        canvas2->cd();
        canvas2->Draw();        // explicitly draw it again
        canvas2->Update();      // refresh all pads
        canvas2->Modified();    // mark as modified
        for (int i = 1; i <= canvas2->GetListOfPrimitives()->GetEntries(); ++i) {
            TPad* pad = (TPad*) canvas2->cd(i);
            pad->Modified();
            pad->Update();
        }
        canvas2->Print(pdf_filename.c_str());
    } else {
        std::cerr << "Missing Heatmaps canvas in file2!\n";
    }




    c1->Print((pdf_filename + "]").c_str()); // Close PDF
}
