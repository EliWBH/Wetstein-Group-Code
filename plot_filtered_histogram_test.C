//MRD Analysis
//Alex Upmeyer 3/2/25


#include <TFile.h>
#include <TTree.h>
#include <TH1F.h>
#include <TCanvas.h>
#include <TString.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <map>
#include <tuple>
#include <algorithm>
#include <string>
#include <fstream>

void plot_filtered_histogram_test(const char* filename, int crateFilter = 0, int slotFilter = 0, int channelFilter = 0, int userBinSize = 4) {
    TFile *file = TFile::Open(filename);
    if (!file || file->IsZombie()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }
    
    TTree *tree;
    file->GetObject("mrdmonitor_tree", tree);
    if (!tree) {
        std::cerr << "Error: Tree 'mrdmonitor_tree' not found in file!" << std::endl;
        file->Close();
        return;
    }
    
    // Creation of variables
    std::vector<unsigned int> *crate = nullptr;
    std::vector<unsigned int> *slot = nullptr;
    std::vector<unsigned int> *channel = nullptr;
    std::vector<std::vector<double>> *tdc = nullptr;
    tree->SetBranchAddress("crate", &crate);
    tree->SetBranchAddress("slot", &slot);
    tree->SetBranchAddress("tdc", &tdc);
    tree->SetBranchAddress("channel", &channel);
    
    // Getting lower and upper bounds of data
    std::map<std::tuple<int, int, int>, int> countMap;
    Long64_t nEntries = tree->GetEntries();
    double minValue = std::numeric_limits<double>::max();
    double maxValue = std::numeric_limits<double>::lowest();
    
    // Creating indexes based on filtering criteria
    for (Long64_t i = 0; i < nEntries; ++i) {
        tree->GetEntry(i);
        if (crate && tdc && slot && channel) {
            for (size_t j = 0; j < crate->size(); ++j) {
                bool crateMatch = (crateFilter == 0 || (crateFilter == (*crate)[j]));
                bool slotMatch = (slotFilter == 0 || (*slot)[j] == slotFilter);
                bool channelMatch = (channelFilter == 0 || (*channel)[j] == channelFilter);
                bool exclude = ((*crate)[j] == 7 && ((*slot)[j] == 11 || (*slot)[j] == 19) && (*channel)[j] == 15);
                if (crateMatch && slotMatch && channelMatch && !exclude) {
                    for (double value : (*tdc)[j]) {
                        ++countMap[std::make_tuple((*crate)[j], (*slot)[j], (*channel)[j])];
                        minValue = std::min(minValue, value);
                        maxValue = std::max(maxValue, value);
                    }
                }
            }
        }
    }
    
    std::vector<int> counts;
    for (const auto& [key, count] : countMap) {
        counts.push_back(count);
    }
    
    if (counts.empty()) {
        std::cerr << "Error: No data to process!" << std::endl;
        file->Close();
        return;
    }
    
    std::sort(counts.begin(), counts.end());
    int median = (counts.size() % 2 == 0)
    ? (counts[counts.size() / 2 - 1] + counts[counts.size() / 2]) / 2
    : counts[counts.size() / 2];
    
    std::string resultsFilename = "results.csv";
    std::ifstream infile(resultsFilename);
    std::string existingLine;
    bool alreadyRecorded = false;
    while (std::getline(infile, existingLine)) {
        if (existingLine.find(filename) != std::string::npos) {
            alreadyRecorded = true;
            break;
        }
    }
    infile.close();
    
    // Open results file and append the median result
    std::ofstream outfile(resultsFilename, std::ios::app);
    if (!alreadyRecorded) {
        outfile << "File: " << filename << " - Median: " << median << std::endl;
    }
    
    // Output crate/slot/channel pairs that are 5x or 1/5x the median
    outfile << "Crate/Slot/Channel pairs (5x and 1/5x the median):" << std::endl;
    for (const auto& [key, count] : countMap) {
        int crate, slot, channel;
        std::tie(crate, slot, channel) = key;

        if (count >= 5 * median || count <= median / 5) {
            outfile << "Crate: " << crate << ", Slot: " << slot << ", Channel: " << channel
                    << ", Count: " << count << std::endl;
        }
    }

    outfile.close();
    
    // Creating Histograms for Crate 7 and Crate 8
    TH1D *hitHist7 = new TH1D("hitHist7", "Crate 7: Hit Counts per (Slot, Channel); Index; Hit Count per 1000 Hits", 168, 0, 168);
    TH1D *hitHist8 = new TH1D("hitHist8", "Crate 8: Hit Counts per (Slot, Channel); Index; Hit Count per 1000 Hits", countMap.size() - 167, 168, countMap.size());

    int binIndex = 1;
    for (const auto& [key, count] : countMap) {
        if (binIndex <= 167) {
            hitHist7->SetBinContent(binIndex, count);
        } else {
            hitHist8->SetBinContent(binIndex - 167, count);
        }
        binIndex++;
    }

    // Creating 1ns histogram for dynamic binning
    TH1D *hist1ns = new TH1D("hist1ns", "Filtered Values (1 ns bins);tdc (ns);Count", std::ceil(maxValue - minValue), minValue, maxValue);
    for (size_t j = 0; j < crate->size(); ++j) {
        bool crateMatch = (crateFilter == 0 || (crateFilter == (*crate)[j]));
        bool slotMatch = (slotFilter == 0 || (*slot)[j] == slotFilter);
        bool channelMatch = (channelFilter == 0 || (*channel)[j] == channelFilter);
        bool exclude = ((*crate)[j] == 7 && ((*slot)[j] == 11 || (*slot)[j] == 19) && (*channel)[j] == 15);
        
        if (crateMatch && slotMatch && channelMatch && !exclude) { // Apply filtering here
            for (double value : (*tdc)[j]) {
                hist1ns->Fill(value);
            }
        }
    }

    
    int newBins = std::ceil((maxValue - minValue) / userBinSize);
    TH1D *customHist = new TH1D("customHist", TString::Format("MRD Histogram (%d ns bins); Time from Common Start (1000 tdc = 4 us);Count per 1000 Events", userBinSize), newBins, minValue, minValue + newBins * userBinSize);
    for (int i = 1; i <= hist1ns->GetNbinsX(); ++i) {
        double binContent = hist1ns->GetBinContent(i);
        int newBinIndex = (hist1ns->GetBinCenter(i) - minValue) / userBinSize + 1;
        if (newBinIndex >= 1 && newBinIndex <= customHist->GetNbinsX()) {
            customHist->AddBinContent(newBinIndex, binContent);
        }
    }
    
    // Maps to store total hits per (slot, channel) for crates 7 and 8
    std::map<std::pair<int, int>, int> crate7Counts;
    std::map<std::pair<int, int>, int> crate8Counts;

    // Populate hit counts per (slot, channel)
    for (Long64_t i = 0; i < nEntries; ++i) {
        tree->GetEntry(i);
        if (crate && slot && channel) {
            for (size_t j = 0; j < crate->size(); ++j) {
                int crateNum = (*crate)[j];
                int slotNum = (*slot)[j];
                int chanNum = (*channel)[j];

                if (crateNum == 7) {
                    crate7Counts[{slotNum, chanNum}]++;
                } else if (crateNum == 8) {
                    crate8Counts[{slotNum, chanNum}]++;
                }
            }
        }
    }

    // Maps to store frequency of hit counts for crate 7 and 8
    std::map<int, int> crate7HistData;
    std::map<int, int> crate8HistData;

    // Extract from countMap (already calculated earlier)
    for (const auto& [key, count] : countMap) {
        int crate, slot, channel;
        std::tie(crate, slot, channel) = key;

        if (crate == 7) {
            crate7HistData[count]++; // Increment the count of (slot, channel) pairs with this hit count
        } else if (crate == 8) {
            crate8HistData[count]++;
        }
    }

    // Determine the maximum hit count for binning
    int maxHits7 = crate7HistData.empty() ? 10 : crate7HistData.rbegin()->first;
    int maxHits8 = crate8HistData.empty() ? 10 : crate8HistData.rbegin()->first;

    // Create histograms with bins based on actual hit count values
    TH1D *crate7Hist = new TH1D("crate7Hist", "Crate 7: Frequency of Hit Counts; Hit Count per 1000 Hits; Number of (Slot, Channel) Pairs", maxHits7 / 10, 0, maxHits7 * 1.1);
    TH1D *crate8Hist = new TH1D("crate8Hist", "Crate 8: Frequency of Hit Counts; Hit Count per 1000 Hits; Number of (Slot, Channel) Pairs", maxHits8 / 10, 0, maxHits8 * 1.1);

    // Fill histograms properly
    for (const auto& [hitCount, frequency] : crate7HistData) {
        crate7Hist->Fill(hitCount, frequency);
    }

    for (const auto& [hitCount, frequency] : crate8HistData) {
        crate8Hist->Fill(hitCount, frequency);
    }

    int totalHits = 0;
    for (const auto& [_, count] : countMap) {
        totalHits += count;
    }

    if (totalHits > 0) {
        double scale_factor = 1000.0 / totalHits;
        hitHist7->Scale(scale_factor);
        hitHist8->Scale(scale_factor);
        hist1ns->Scale(scale_factor);
        customHist->Scale(scale_factor);
        crate7Hist->Scale(scale_factor);
        crate8Hist->Scale(scale_factor);
    }

    
    // Save Histograms
    // Open a ROOT file for writing
    TString outputROOTFilename = TString::Format("MRD_Hists_%s", filename);
    TFile *outputFile = new TFile(outputROOTFilename, "RECREATE");

    // Create first canvas and save customHist
    TCanvas *c1 = new TCanvas("Raw MRD TDC Data", "Custom Histogram", 900, 600);
    customHist->Draw("HIST");
    gPad->Update();
    c1->Write();
    customHist->Write("Raw MRD TDC Data");

    // Create second canvas and save hitHist7
    TCanvas *c2 = new TCanvas("hitHist7", "Hit Counts Histogram Crate 7", 900, 600);
    gPad->SetLogy();
    hitHist7->Draw("HIST");
    gPad->Update();
    c2->Write();
    hitHist7->Write("hitHist7");

    // Create third canvas and save hitHist8
    TCanvas *c3 = new TCanvas("hitHist8", "Hit Counts Histogram Crate 8", 900, 600);
    gPad->SetLogy();
    hitHist8->Draw("HIST");
    gPad->Update();
    c3->Write();
    hitHist8->Write("hitHist8");

    // Crate 7 and 8 Count Histograms
    TCanvas *c4 = new TCanvas("Crate7Hist", "Crate 7 Histogram", 900, 600);
    gPad->SetLogx();
    crate7Hist->Draw("HIST");
    gPad->Update();
    c4->Write();
    crate7Hist->Write("Crate7Hist");

    TCanvas *c5 = new TCanvas("Crate8Hist", "Crate 8 Histogram", 900, 600);
    gPad->SetLogx();
    crate8Hist->Draw("HIST");
    gPad->Update();
    c5->Write();
    crate8Hist->Write("Crate8Hist");

    
    
    
    // Creat heatmaps
    TCanvas *c6 = new TCanvas("Heatmaps", "Heatmap - Rack 7 and 8", 1200, 600);
    c6->Divide(2,1);

    gStyle->SetOptStat(0);

    // Define proper 22x32 grid: slots [0–21], channels [0–31]
    const int nSlots = 22, nChans = 32;
    TH2D *effMap7 = new TH2D("effMap7", "Heatmap - Rack 7;Slot;Channel", nSlots, 0, nSlots, nChans, 0, nChans);
    TH2D *effMap8 = new TH2D("effMap8", "Heatmap - Rack 8;Slot;Channel", nSlots, 0, nSlots, nChans, 0, nChans);

    std::vector<TBox*> boxes7, boxes8;

    double med_div_5 = median / 5.0;
    double med_x_5 = median * 5.0;

    for (const auto& [key, count] : countMap) {
        int crate, slot, channel;
        std::tie(crate, slot, channel) = key;
        if (crate != 7 && crate != 8 || slot >= nSlots || channel >= nChans) continue;

        TBox *box = new TBox(slot, channel, slot + 1, channel + 1);
        if (count <= med_div_5) box->SetFillColor(kBlue);
        else if (count >= med_x_5) box->SetFillColor(kRed);
        else continue;

        box->SetLineColor(kBlack);
        box->SetLineWidth(1);

        if (crate == 7) {
            boxes7.push_back(box);
            effMap7->Fill(slot + 0.5, channel + 0.5); // center-fill
        } else {
            boxes8.push_back(box);
            effMap8->Fill(slot + 0.5, channel + 0.5);
        }
    }

    // Draw crate 7
    c6->cd(1);
    effMap7->SetMinimum(0); effMap7->SetMaximum(1);
    effMap7->GetXaxis()->SetNdivisions(nSlots, kTRUE);
    effMap7->GetYaxis()->SetNdivisions(nChans, kTRUE);
    effMap7->GetXaxis()->LabelsOption("v");
    effMap7->GetXaxis()->SetLabelSize(0.02);
    effMap7->GetYaxis()->SetLabelSize(0.02);
    effMap7->GetXaxis()->CenterLabels(kTRUE);
    effMap7->GetYaxis()->CenterLabels(kTRUE);
    effMap7->Draw("BOX");
    for (auto* box : boxes7) box->Draw("lfsame");

    // Draw grid lines
    for (int s = 0; s <= nSlots; ++s) {
        TLine *v = new TLine(s, 0, s, nChans);
        v->SetLineColor(kGray+2); v->SetLineStyle(3); v->Draw("same");
    }
    for (int c = 0; c <= nChans; ++c) {
        TLine *h = new TLine(0, c, nSlots, c);
        h->SetLineColor(kGray+2); h->SetLineStyle(3); h->Draw("same");
    }

    TText *t7 = new TText(1, nChans + 0.5, Form("Median: %d | 1/5: %.1f | 5x: %.1f", median, med_div_5, med_x_5));
    t7->SetTextSize(0.03); t7->Draw();

    // Draw crate 8
    c6->cd(2);
    effMap8->SetMinimum(0); effMap8->SetMaximum(1);
    effMap8->GetXaxis()->SetNdivisions(nSlots, kTRUE);
    effMap8->GetYaxis()->SetNdivisions(nChans, kTRUE);
    effMap8->GetXaxis()->LabelsOption("v");
    effMap8->GetXaxis()->SetLabelSize(0.02);
    effMap8->GetYaxis()->SetLabelSize(0.02);
    effMap8->GetXaxis()->CenterLabels(kTRUE);
    effMap8->GetYaxis()->CenterLabels(kTRUE);
    effMap8->Draw("BOX");
    for (auto* box : boxes8) box->Draw("lfsame");

    for (int s = 0; s <= nSlots; ++s) {
        TLine *v = new TLine(s, 0, s, nChans);
        v->SetLineColor(kGray+2); v->SetLineStyle(3); v->Draw("same");
    }
    for (int c = 0; c <= nChans; ++c) {
        TLine *h = new TLine(0, c, nSlots, c);
        h->SetLineColor(kGray+2); h->SetLineStyle(3); h->Draw("same");
    }

    TText *t8 = new TText(1, nChans + 0.5, Form("Median: %d | 1/5: %.1f | 5x: %.1f", median, med_div_5, med_x_5));
    t8->SetTextSize(0.03); t8->Draw();

    c6->Write();
    effMap7->Write("EfficiencyRack7");
    effMap8->Write("EfficiencyRack8");

    
    
    // Close the file
    outputFile->Close();

 

    
    // Cleanup
    delete c1;
    delete c2;
    delete c3;
    delete c4;
    delete c5;
    delete crate7Hist;
    delete crate8Hist;
    delete hist1ns;
    delete customHist;
    delete hitHist7;
    delete hitHist8;
    file->Close();
}
