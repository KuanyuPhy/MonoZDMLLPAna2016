#include <iostream>
#include <sstream>
#include <TTree.h>
#include <TMath.h>
#include <TFile.h>
#include <TH1D.h>
#include <TROOT.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TLatex.h>
#include <TAxis.h>
#include <TLine.h>
#include "./../../../lib/kuan_ana_utils.h"
#include "./../../../lib/tdrstyle.C"
#include "./../../../lib/CMS_lumi.h"
using namespace std;

void ana_sig()
{

    TFile *Mx2_1 = new TFile("/home/kuanyu/Documents/root_file/Ztoee/ee_Mx2_1_old_remove_0alpha.root");
    TFile *Mx2_50 = new TFile("/home/kuanyu/Documents/root_file/Ztoee/ee_Mx2_50_old_remove_0alpha.root");
    TFile *Mx2_150 = new TFile("/home/kuanyu/Documents/root_file/Ztoee/ee_Mx2_150_old_remove_0alpha.root");

    TFile *Bgfile = new TFile("/home/kuanyu/Documents/CMS/Background_Estimate/cut_opt/punzi/MET/ee_bgall_punzi_MET.root");

    TH1D *h_bgall_nMET_cut = ((TH1D *)Bgfile->Get("h_pass_Bg_nMetcut"));

    TH1D *h_pass_Mx2_1 = new TH1D("h_pass_Mx2_1", "", 160, 0, 160);
    h_pass_Mx2_1->Sumw2();

    TH1D *h_pass_Mx2_1_nMetcut = new TH1D("h_pass_Mx2_1_nMetcut", "", 160, 0, 160);
    h_pass_Mx2_1_nMetcut->Sumw2();

    TH1D *h_pass_Mx2_50 = new TH1D("h_pass_Mx2_50", "", 160, 0, 160);
    h_pass_Mx2_50->Sumw2();

    TH1D *h_pass_Mx2_50_nMetcut = new TH1D("h_pass_Mx2_50_nMetcut", "", 160, 0, 160);
    h_pass_Mx2_50_nMetcut->Sumw2();

    TH1D *h_pass_Mx2_150 = new TH1D("h_pass_Mx2_150", "", 160, 0, 160);
    h_pass_Mx2_150->Sumw2();

    TH1D *h_pass_Mx2_150_nMetcut = new TH1D("h_pass_Mx2_150_nMetcut", "", 160, 0, 160);
    h_pass_Mx2_150_nMetcut->Sumw2();

    Int_t I_Mx1_weight, I_Mx50_weight, I_Mx150_weight;

    float_t f_Mx1_Met, f_Mx50_Met, f_Mx150_Met;

    Int_t I_Mx1_nThinJets, I_Mx50_nThinJets, I_Mx150_nThinJets;

    vector<float> *v_Mx1_alpha = new vector<float>();
    vector<float> *v_Mx50_alpha = new vector<float>();
    vector<float> *v_Mx150_alpha = new vector<float>();

    v_Mx1_alpha->clear();
    v_Mx50_alpha->clear();
    v_Mx150_alpha->clear();

    for (int i = 1; i <= 150; i++)
    {
        float metcut = i * 10;

        TTree *T_Mx2_1;
        Mx2_1->GetObject("T_tree", T_Mx2_1);
        T_Mx2_1->SetBranchAddress("I_weight", &I_Mx1_weight);
        T_Mx2_1->SetBranchAddress("f_Met", &f_Mx1_Met);
        T_Mx2_1->SetBranchAddress("v_fakealpha", &v_Mx1_alpha);
        for (int evt = 0; evt < T_Mx2_1->GetEntries(); evt++)
        {
            T_Mx2_1->GetEntry(evt);
            //-------------------
            // Scan Met
            //-------------------
            h_pass_Mx2_1->Fill(i, I_Mx1_weight);
            // cout << "Met cut"<<i*10<<endl;
            if (f_Mx1_Met > metcut)
            {
                h_pass_Mx2_1_nMetcut->Fill(i, I_Mx1_weight);
            }
        } // End of Mx2_1 Entries loop
        TTree *T_Mx2_50;
        Mx2_50->GetObject("T_tree", T_Mx2_50);
        T_Mx2_50->SetBranchAddress("I_weight", &I_Mx50_weight);
        T_Mx2_50->SetBranchAddress("f_Met", &f_Mx50_Met);
        T_Mx2_50->SetBranchAddress("v_fakealpha", &v_Mx50_alpha);
        for (int evt = 0; evt < T_Mx2_50->GetEntries(); evt++)
        {
            T_Mx2_50->GetEntry(evt);
            //-------------------
            // Scan Met
            //-------------------
            h_pass_Mx2_50->Fill(i, I_Mx50_weight);
            if (f_Mx50_Met > metcut)
            {
                h_pass_Mx2_50_nMetcut->Fill(i, I_Mx50_weight);
            }
        } // End of Mx2_50 Entries loop
        TTree *T_Mx2_150;
        Mx2_150->GetObject("T_tree", T_Mx2_150);
        T_Mx2_150->SetBranchAddress("I_weight", &I_Mx150_weight);
        T_Mx2_150->SetBranchAddress("f_Met", &f_Mx150_Met);
        T_Mx2_150->SetBranchAddress("v_fakealpha", &v_Mx150_alpha);
        for (int evt = 0; evt < T_Mx2_150->GetEntries(); evt++)
        {
            T_Mx2_150->GetEntry(evt);
            //-------------------
            // Scan Met
            //-------------------
            h_pass_Mx2_150->Fill(i, I_Mx150_weight);
            if (f_Mx150_Met > metcut)
            {
                h_pass_Mx2_150_nMetcut->Fill(i, I_Mx150_weight);
            }
        } // End of Mx2_150 Entries loop
    }     // End of 150 loops

    TH1D *h_Mx2_1_eff = (TH1D *)h_pass_Mx2_1_nMetcut->Clone("h_Mx2_1_eff");
    h_Mx2_1_eff->Divide(h_pass_Mx2_1_nMetcut, h_pass_Mx2_1, 1, 1, "b");

    TH1D *h_Mx2_50_eff = (TH1D *)h_pass_Mx2_50_nMetcut->Clone("h_Mx2_50_eff");
    h_Mx2_50_eff->Divide(h_pass_Mx2_50_nMetcut, h_pass_Mx2_50, 1, 1, "b");

    TH1D *h_Mx2_150_eff = (TH1D *)h_pass_Mx2_150_nMetcut->Clone("h_Mx2_150_eff");
    h_Mx2_150_eff->Divide(h_pass_Mx2_150_nMetcut, h_pass_Mx2_150, 1, 1, "b");

    double Sig1_punzi[150];
    double Sig50_punzi[150];
    double Sig150_punzi[150];

    for (int i = 1; i <= 150; i++)
    {
        Sig1_punzi[i] = punzi(h_Mx2_1_eff->GetBinContent(i), h_bgall_nMET_cut->GetBinContent(i));
        Sig50_punzi[i] = punzi(h_Mx2_50_eff->GetBinContent(i), h_bgall_nMET_cut->GetBinContent(i));
        Sig150_punzi[i] = punzi(h_Mx2_150_eff->GetBinContent(i), h_bgall_nMET_cut->GetBinContent(i));

        cout << "i =" << i << endl;
        cout << "eff =" << h_Mx2_150_eff->GetBinContent(i) << endl;
        cout << "punzi =" << Sig150_punzi[i] << endl;
    }

    TH1D *h_punzisig1 = new TH1D("h_punzisig1", "", 160, 0, 160);
    TH1D *h_punzisig50 = new TH1D("h_punzisig50", "", 160, 0, 160);
    TH1D *h_punzisig150 = new TH1D("h_punzisig150", "", 160, 0, 160);
    for (int i = 1; i <= 150; i++)
    {
        h_punzisig1->SetBinContent(i, Sig1_punzi[i]);
        h_punzisig50->SetBinContent(i, Sig50_punzi[i]);
        h_punzisig150->SetBinContent(i, Sig150_punzi[i]);
    }

    h_punzisig1->SetLineWidth(2);
    h_punzisig50->SetLineWidth(2);
    h_punzisig150->SetLineWidth(2);

    h_punzisig1->SetLineColor(kRed);
    h_punzisig50->SetLineColor(kBlack);
    h_punzisig150->SetLineColor(kBlue);

    setTDRStyle();
    auto canv = new TCanvas("c", "c", 800, 700);
    canv->cd();
    canv->SetRightMargin(0.08);
    canv->SetBottomMargin(0.12);
    canv->SetTopMargin(0.07);
    canv->SetLeftMargin(0.12);

    TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
    pad1->SetBottomMargin(0); // Upper and lower plot are joined
    pad1->SetGridx();         // Vertical grid
    pad1->Draw();             // Draw the upper pad: pad1

    h_punzisig150->GetXaxis()->SetTitleSize(0.045);
    h_punzisig150->GetXaxis()->SetLabelSize(0.045);
    h_punzisig150->GetXaxis()->SetLabelOffset(0.02);
    h_punzisig150->GetXaxis()->SetTitleOffset(1.3);
    h_punzisig150->GetYaxis()->SetTitleSize(0.045);
    h_punzisig150->GetYaxis()->SetLabelSize(0.045);
    h_punzisig150->GetYaxis()->SetTitleOffset(1.4);
    h_punzisig150->GetYaxis()->SetTitle("Punzi Significance");
    h_punzisig150->GetXaxis()->SetTitle("MET [GeV]");

    h_punzisig150->GetXaxis()->SetRangeUser(0, 50);
    h_punzisig150->GetXaxis()->SetBinLabel(1, "MET > 10");
    h_punzisig150->GetXaxis()->SetBinLabel(5, "MET > 50");
    h_punzisig150->GetXaxis()->SetBinLabel(10, "MET > 100");
    h_punzisig150->GetXaxis()->SetBinLabel(14, "MET > 140");
    h_punzisig150->GetXaxis()->SetBinLabel(20, "MET > 200");
    h_punzisig150->GetXaxis()->SetBinLabel(30, "MET > 300");
    //h_punzisig150->GetXaxis()->SetBinLabel(40, "MET > 400");

    h_punzisig150->Draw();
    h_punzisig50->Draw("same");
    h_punzisig1->Draw("same");

    TLegend *l1 = new TLegend(0.55, 0.7, 0.80, 0.90);
    l1->SetBorderSize(0);
    l1->SetFillStyle(0);
    l1->SetTextSize(0.03);
    l1->AddEntry(h_punzisig1, "m_{#chi_{2}} = 1 GeV, c#tau = 1 mm", "lE");
    l1->AddEntry(h_punzisig50, "m_{#chi_{2}} = 50 GeV, c#tau = 10 mm", "lE");
    l1->AddEntry(h_punzisig150, "m_{#chi_{2}} = 150 GeV, c#tau = 1 mm", "lE");
    l1->Draw();

    gStyle->SetOptStat(0);

    CMS_lumi((TPad *)canv, 5, 0, "35.9 fb^{-1}", 2016, true, "Simulation", "", "");

    // CMS_lumi(canv, iPeriod, iPos);
    // canv->Update();
    // canv->RedrawAxis();

    // canv->SaveAs("ee_MET_punzi.png");

    // gPad->SetLogy();

    // auto c1 = new TCanvas("c", "BPRE");
    /*
    c1->Divide(3, 1);
    c1->cd(1);
    h_Mx2_1_eff->Draw("text 45");
    c1->cd(2);
    h_Mx2_50_eff->Draw("");
    c1->cd(3);
    h_Mx2_150_eff->Draw("");
    */

    // TString outputfile1 = "./ee_Sig_punzi.root";
    // TFile *outfile_HT0 = TFile::Open(outputfile1, "RECREATE");
    // h_pass_Mx2_1->Write();
    // h_pass_Mx2_50->Write();
    // h_pass_Mx2_150->Write();
    // h_Mx2_1_eff->Write();
    // h_Mx2_50_eff->Write();
    // h_Mx2_150_eff->Write();
    // outfile_HT0->Close();
}