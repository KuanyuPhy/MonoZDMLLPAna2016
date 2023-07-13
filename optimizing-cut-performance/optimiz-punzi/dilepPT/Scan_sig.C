#include <iostream>
#include <sstream>
#include <TTree.h>
#include <TMath.h>
#include <TFile.h>
#include <TH3D.h>
#include <TROOT.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TLatex.h>
#include <TAxis.h>
#include <TLine.h>

using namespace std;

// define punzi_eq
double punzi(double sigeff, double bg)
{
    return sigeff / (1 + TMath::Power(abs(bg), 0.5));
}

void Scan_sig()
{

    TFile *Bgfile = new TFile("./ee_bgall_punzi.root");

    TH1D *h_pass_Bg_nDilepPTcut = ((TH1D *)Bgfile->Get("h_pass_Bg_nDilepPTcut"));

    TFile *Mx2_1 = new TFile("/home/kuanyu/Documents/root_file/Ztoee/ee_Mx2_1_old_remove_0alpha.root");
    TFile *Mx2_50 = new TFile("/home/kuanyu/Documents/root_file/Ztoee/ee_Mx2_50_old_remove_0alpha.root");
    TFile *Mx2_150 = new TFile("/home/kuanyu/Documents/root_file/Ztoee/ee_Mx2_150_old_remove_0alpha.root");

    TH1D *h_pass_Mx2_1 = new TH1D("h_pass_Mx2_1", "", 110, 1, 110);
    h_pass_Mx2_1->Sumw2();

    TH1D *h_pass_Mx2_1_ndilepPTcut = new TH1D("h_pass_Mx2_1_ndilepPTcut", "", 110, 1, 110);
    h_pass_Mx2_1_ndilepPTcut->Sumw2();

    TH1D *h_pass_Mx2_50 = new TH1D("h_pass_Mx2_50", "", 110, 1, 110);
    h_pass_Mx2_50->Sumw2();

    TH1D *h_pass_Mx2_50_ndilepPTcut = new TH1D("h_pass_Mx2_50_ndilepPTcut", "", 110, 1, 110);
    h_pass_Mx2_50_ndilepPTcut->Sumw2();

    TH1D *h_pass_Mx2_150 = new TH1D("h_pass_Mx2_150", "", 110, 1, 110);
    h_pass_Mx2_150->Sumw2();

    TH1D *h_pass_Mx2_150_ndilepPTcut = new TH1D("h_pass_Mx2_150_ndilepPTcut", "", 110, 1, 110);
    h_pass_Mx2_150_ndilepPTcut->Sumw2();

    Int_t I_Mx1_weight, I_Mx50_weight, I_Mx150_weight;

    float_t f_Mx1_Met, f_Mx50_Met, f_Mx150_Met;

    float_t f_Mx1_dilepPT, f_Mx50_dilepPT, f_Mx150_dilepPT;

    Int_t I_Mx1_nThinJets, I_Mx50_nThinJets, I_Mx150_nThinJets;

    vector<float> *v_Mx1_alpha = new vector<float>();
    vector<float> *v_Mx50_alpha = new vector<float>();
    vector<float> *v_Mx150_alpha = new vector<float>();

    v_Mx1_alpha->clear();
    v_Mx50_alpha->clear();
    v_Mx150_alpha->clear();

    for (int i = 1; i <= 100; i++)
    {
        float Metcut = 0.;
        float dilepton_cut = i * 10;

        TTree *T_Mx2_1;
        Mx2_1->GetObject("T_tree", T_Mx2_1);
        T_Mx2_1->SetBranchAddress("I_weight", &I_Mx1_weight);
        T_Mx2_1->SetBranchAddress("f_Met", &f_Mx1_Met);
        T_Mx2_1->SetBranchAddress("f_dileptonPT", &f_Mx1_dilepPT);
        T_Mx2_1->SetBranchAddress("v_fakealpha", &v_Mx1_alpha);
        for (int evt = 0; evt < T_Mx2_1->GetEntries(); evt++)
        {
            T_Mx2_1->GetEntry(evt);
            if (f_Mx1_Met < Metcut)
            {
                continue;
            }
            //-------------------
            // Scan dilepton PT
            //-------------------
            h_pass_Mx2_1->Fill(i, I_Mx1_weight);
            // cout << "Met cut"<<i*10<<endl;
            if (f_Mx1_dilepPT > dilepton_cut)
            {
                h_pass_Mx2_1_ndilepPTcut->Fill(i, I_Mx1_weight);
            }
            else
            {
                continue;
            }
        } // End of Mx2_1 Entries loop
        TTree *T_Mx2_50;
        Mx2_50->GetObject("T_tree", T_Mx2_50);
        T_Mx2_50->SetBranchAddress("I_weight", &I_Mx50_weight);
        T_Mx2_50->SetBranchAddress("f_Met", &f_Mx50_Met);
        T_Mx2_50->SetBranchAddress("f_dileptonPT", &f_Mx50_dilepPT);
        T_Mx2_50->SetBranchAddress("v_fakealpha", &v_Mx50_alpha);
        for (int evt = 0; evt < T_Mx2_50->GetEntries(); evt++)
        {
            T_Mx2_50->GetEntry(evt);
            if (f_Mx50_Met < Metcut)
            {
                continue;
            }
            //-------------------
            // Scan dilepton PT
            //-------------------
            h_pass_Mx2_50->Fill(i, I_Mx50_weight);
            // cout << "Met cut"<<i*10<<endl;
            if (f_Mx50_dilepPT > dilepton_cut)
            {
                // cout << "metcut = " << metcut << endl;
                // cout << "Met = " << f_Mx1_Met << endl;
                h_pass_Mx2_50_ndilepPTcut->Fill(i, I_Mx50_weight);
            }
        } // End of Mx2_50 Entries loop
        TTree *T_Mx2_150;
        Mx2_150->GetObject("T_tree", T_Mx2_150);
        T_Mx2_150->SetBranchAddress("I_weight", &I_Mx150_weight);
        T_Mx2_150->SetBranchAddress("f_Met", &f_Mx150_Met);
        T_Mx2_150->SetBranchAddress("f_dileptonPT", &f_Mx150_dilepPT);
        T_Mx2_150->SetBranchAddress("v_fakealpha", &v_Mx150_alpha);
        for (int evt = 0; evt < T_Mx2_150->GetEntries(); evt++)
        {
            T_Mx2_150->GetEntry(evt);
            if (f_Mx150_Met < Metcut)
            {
                continue;
            }
            //-------------------
            // Scan dilepton PT
            //-------------------
            h_pass_Mx2_150->Fill(i, I_Mx150_weight);
            // cout << "Met cut"<<i*10<<endl;
            if (f_Mx150_dilepPT > dilepton_cut)
            {
                // cout << "metcut = " << metcut << endl;
                // cout << "Met = " << f_Mx1_Met << endl;
                h_pass_Mx2_150_ndilepPTcut->Fill(i, I_Mx150_weight);
            }
        } // End of Mx2_150 Entries loop
    }     // End of 150 loops

    TH1D *h_Mx2_1_eff = (TH1D *)h_pass_Mx2_1_ndilepPTcut->Clone("h_Mx2_1_eff");
    h_Mx2_1_eff->Divide(h_pass_Mx2_1_ndilepPTcut, h_pass_Mx2_1, 1, 1);

    TH1D *h_Mx2_50_eff = (TH1D *)h_pass_Mx2_50_ndilepPTcut->Clone("h_Mx2_50_eff");
    h_Mx2_50_eff->Divide(h_pass_Mx2_50_ndilepPTcut, h_pass_Mx2_50, 1, 1);

    TH1D *h_Mx2_150_eff = (TH1D *)h_pass_Mx2_150_ndilepPTcut->Clone("h_Mx2_150_eff");
    h_Mx2_150_eff->Divide(h_pass_Mx2_150_ndilepPTcut, h_pass_Mx2_150, 1, 1);

    // auto c1 = new TCanvas("c", "BPRE");
    // c1->Divide(3, 1);
    // c1->cd(1);
    // h_Mx2_1_eff->Draw(" text 45");
    // c1->cd(2);
    // h_Mx2_50_eff->Draw("");
    // c1->cd(3);
    // h_Mx2_150_eff->Draw("");

    //---------------------------------
    // Calculate Punzi significance
    //---------------------------------
    double Sig1_punzi[100];
    double Sig50_punzi[100];
    double Sig150_punzi[100];
    for (int i = 1; i <= 100; i++)
    {
        Sig1_punzi[i] = punzi(h_Mx2_1_eff->GetBinContent(i), h_pass_Bg_nDilepPTcut->GetBinContent(i));
        Sig50_punzi[i] = punzi(h_Mx2_50_eff->GetBinContent(i), h_pass_Bg_nDilepPTcut->GetBinContent(i));
        Sig150_punzi[i] = punzi(h_Mx2_150_eff->GetBinContent(i), h_pass_Bg_nDilepPTcut->GetBinContent(i));

        // cout << "i =" << i << endl;
        // cout << "Sig_eff =" << h_Mx2_1_eff->GetBinContent(i) << endl;
    }
    TH1D *h_punzisig1 = new TH1D("h_punzisig1", "", 110, 1, 110);
    TH1D *h_punzisig50 = new TH1D("h_punzisig50", "", 110, 1, 110);
    TH1D *h_punzisig150 = new TH1D("h_punzisig150", "", 110, 1, 110);
    for (int i = 1; i <= 100; i++)
    {
        h_punzisig1->SetBinContent(i, Sig1_punzi[i]);
        h_punzisig50->SetBinContent(i, Sig50_punzi[i]);
        h_punzisig150->SetBinContent(i, Sig150_punzi[i]);
        cout << "i =" << i << endl;
        cout << "punzi 150 =" << Sig150_punzi[i] << endl;
    }
    h_punzisig1->SetLineWidth(2);
    h_punzisig50->SetLineWidth(2);
    h_punzisig150->SetLineWidth(2);

    h_punzisig1->SetLineColor(kRed);
    h_punzisig50->SetLineColor(kBlack);
    h_punzisig150->SetLineColor(kBlue);

    h_punzisig1->GetYaxis()->SetTitle("punzi significance");
    h_punzisig1->GetXaxis()->SetTitle("dilepton PT cut");

    h_punzisig150->GetYaxis()->SetTitle("punzi significance");
    h_punzisig150->GetXaxis()->SetTitle("dilepton PT cut");

    //h_punzisig150->GetXaxis()->SetRangeUser(10, 30);

    // h_punzisig150->GetXaxis()->SetBinLabel(1, "Met > 10");

    Double_t w = 600;
    Double_t h = 600;

    int H_ref = 600;
    int W_ref = 600;

    float T = 0.08 * H_ref;
    float B = 0.12 * H_ref;
    float L = 0.12 * W_ref;
    float R = 0.04 * W_ref;

    auto canv = new TCanvas("c1", "c1", w, h);
    canv->SetFillColor(0);
    canv->SetBorderMode(0);
    canv->SetFrameFillStyle(0);
    canv->SetFrameBorderMode(0);
    canv->SetLeftMargin(L / w);
    canv->SetRightMargin(R / w);
    canv->SetTopMargin(T / h);
    canv->SetBottomMargin(B / h);
    canv->SetTickx(0);
    canv->SetTicky(0);
    // auto c1 = new TCanvas("c", "BPRE");

    h_punzisig1->Draw("");
    h_punzisig150->Draw("same");
    h_punzisig50->Draw("same");

    TLegend *l1 = new TLegend(0.4, 0.4, 0.90, 0.80);
    l1->SetBorderSize(0);
    l1->SetFillStyle(0);
    l1->SetTextSize(0.03);
    l1->AddEntry(h_punzisig1, "m_{#chi_{2}} = 1 GeV, ctau = 1 mm", "lE");
    l1->AddEntry(h_punzisig50, "m_{#chi_{2}} = 50 GeV, ctau = 10 mm", "lE");
    l1->AddEntry(h_punzisig150, "m_{#chi_{2}} = 150 GeV, ctau = 1 mm", "lE");
    l1->Draw();

    gStyle->SetOptStat(0);

    TString outputfile1 = "./ee_Sig_punzi.root";
    TFile *outfile_HT0 = TFile::Open(outputfile1, "RECREATE");
    h_pass_Mx2_1->Write();
    h_pass_Mx2_50->Write();
    h_pass_Mx2_150->Write();
    h_Mx2_1_eff->Write();
    h_Mx2_50_eff->Write();
    h_Mx2_150_eff->Write();
    h_punzisig1->Write();
    h_punzisig50->Write();
    h_punzisig150->Write();
    outfile_HT0->Close();
}