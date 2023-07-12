#include "TFile.h"
#include <iostream>
#include "TTree.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TLegend.h>
#include <TProfile.h>
#include <string>
#include <TCanvas.h>
#include <TAttLine.h>
#include <TStyle.h>
#include "./../lib/Cross_section.h"

using namespace std;

//-------------------
// Create New class
//-------------------
class ThinJet
{
private:
    float jetpt, jeteta, jetntrk;

public:
    ThinJet() {}
    ThinJet(const float &a, const float &b, const float &c) : jetpt(a), jeteta(b), jetntrk(c) {}

    Float_t GetPt() const { return jetpt; }
    Float_t GetEta() const { return jeteta; }
    Float_t GetNtrk() const { return jetntrk; }

    friend ostream &operator<<(ostream &out, const ThinJet &foo)
    {
        return out << foo.jetpt << " " << foo.jeteta << " " << foo.jetntrk << "" << endl;
    }
    // greater() is used for JetPT
    friend bool operator>(const ThinJet &a, const ThinJet &b)
    {
        return a.GetPt() > b.GetPt();
    }
};

TFile *Mx2_1 = new TFile("/home/kuanyu/Documents/root_file/Ztoee/ee_Mx2_1_old_remove_0alpha.root");
TFile *Mx2_50 = new TFile("/home/kuanyu/Documents/root_file/Ztoee/ee_Mx2_50_old_remove_0alpha.root");
TFile *Mx2_150 = new TFile("/home/kuanyu/Documents/root_file/Ztoee/ee_Mx2_150_old_remove_0alpha.root");

void Sig_ee_corr()
{

    TH2D *h_Sig1_MET_dileptonPT = new TH2D("h_Sig1_MET_dileptonPT", "", 150, 0, 1500, 100, 0, 1000);
    h_Sig1_MET_dileptonPT->Sumw2();

    TH2D *h_Sig50_MET_dileptonPT = new TH2D("h_Sig50_MET_dileptonPT", "", 150, 0, 1500, 100, 0, 1000);
    h_Sig50_MET_dileptonPT->Sumw2();

    TH2D *h_Sig150_MET_dileptonPT = new TH2D("h_Sig150_MET_dileptonPT", "", 150, 0, 1500, 100, 0, 1000);
    h_Sig150_MET_dileptonPT->Sumw2();

    TH1D *h_Sig1_dileptonPT = new TH1D("h_Sig1_dileptonPT", "", 100, 0, 1000);
    h_Sig1_dileptonPT->Sumw2();

    TH1D *h_Sig50_dileptonPT = new TH1D("h_Sig50_dileptonPT", "", 100, 0, 1000);
    h_Sig50_dileptonPT->Sumw2();

    TH1D *h_Sig150_dileptonPT = new TH1D("h_Sig150_dileptonPT", "", 100, 0, 1000);
    h_Sig150_dileptonPT->Sumw2();

    TH1D *h_Sig1_dileptonPT_cutedMET = new TH1D("h_Sig1_dileptonPT_cutedMET", "", 100, 0, 1000);
    h_Sig1_dileptonPT_cutedMET->Sumw2();

    TH1D *h_Sig50_dileptonPT_cutedMET = new TH1D("h_Sig50_dileptonPT_cutedMET", "", 100, 0, 1000);
    h_Sig50_dileptonPT_cutedMET->Sumw2();

    TH1D *h_Sig150_dileptonPT_cutedMET = new TH1D("h_Sig150_dileptonPT_cutedMET", "", 100, 0, 1000);
    h_Sig150_dileptonPT_cutedMET->Sumw2();

    TH1D *h_Sig1_deltaPhi = new TH1D("h_Sig1_deltaPhi", "", 40, 0., 4.);
    h_Sig1_deltaPhi->Sumw2();

    TH1D *h_Sig50_deltaPhi = new TH1D("h_Sig50_deltaPhi", "", 40, 0., 4.);
    h_Sig50_deltaPhi->Sumw2();

    TH1D *h_Sig150_deltaPhi = new TH1D("h_Sig150_deltaPhi", "", 40, 0., 4.);
    h_Sig150_deltaPhi->Sumw2();

    TH1D *h_Sig1_deltaPhi_cutedMET = new TH1D("h_Sig1_deltaPhi_cutedMET", "", 40, 0., 4.);
    h_Sig1_deltaPhi_cutedMET->Sumw2();

    TH1D *h_Sig50_deltaPhi_cutedMET = new TH1D("h_Sig50_deltaPhi_cutedMET", "", 40, 0., 4.);
    h_Sig50_deltaPhi_cutedMET->Sumw2();

    TH1D *h_Sig150_deltaPhi_cutedMET = new TH1D("h_Sig150_deltaPhi_cutedMET", "", 40, 0., 4.);
    h_Sig150_deltaPhi_cutedMET->Sumw2();

    TH1D *h_Sig1_alpha = new TH1D("h_Sig1_alpha", "", 24, 0, 1.2);
    h_Sig1_alpha->Sumw2();

    TH1D *h_Sig50_alpha = new TH1D("h_Sig50_alpha", "", 24, 0, 1.2);
    h_Sig50_alpha->Sumw2();

    TH1D *h_Sig150_alpha = new TH1D("h_Sig150_alpha", "", 24, 0, 1.2);
    h_Sig150_alpha->Sumw2();

    TH1D *h_Sig1_alpha_cutedMET = new TH1D("h_Sig1_alpha_cutedMET", "", 24, 0, 1.2);
    h_Sig1_alpha_cutedMET->Sumw2();

    TH1D *h_Sig50_alpha_cutedMET = new TH1D("h_Sig50_alpha_cutedMET", "", 24, 0, 1.2);
    h_Sig50_alpha_cutedMET->Sumw2();

    TH1D *h_Sig150_alpha_cutedMET = new TH1D("h_Sig150_alpha_cutedMET", "", 24, 0, 1.2);
    h_Sig150_alpha_cutedMET->Sumw2();

    Int_t I_Mx1_weight, I_Mx50_weight, I_Mx150_weight;

    float_t f_Mx1_Met, f_Mx50_Met, f_Mx150_Met;

    float_t f_Mx1_dilepPT, f_Mx50_dilepPT, f_Mx150_dilepPT;

    vector<float> *v_Mx1_alpha = new vector<float>();
    vector<float> *v_Mx50_alpha = new vector<float>();
    vector<float> *v_Mx150_alpha = new vector<float>();

    v_Mx1_alpha->clear();
    v_Mx50_alpha->clear();
    v_Mx150_alpha->clear();

    vector<float> *v_Mx1_MetdeltaPhi = new vector<float>();
    vector<float> *v_Mx50_MetdeltaPhi = new vector<float>();
    vector<float> *v_Mx150_MetdeltaPhi = new vector<float>();

    v_Mx1_MetdeltaPhi->clear();
    v_Mx50_MetdeltaPhi->clear();
    v_Mx150_MetdeltaPhi->clear();

    vector<float> *v_Mx1_nTrack = new vector<float>();
    vector<float> *v_Mx50_nTrack = new vector<float>();
    vector<float> *v_Mx150_nTrack = new vector<float>();

    v_Mx1_nTrack->clear();
    v_Mx50_nTrack->clear();
    v_Mx150_nTrack->clear();

    float METcut = 130;

    TTree *T_Mx2_1;
    Mx2_1->GetObject("T_tree", T_Mx2_1);
    T_Mx2_1->SetBranchAddress("I_weight", &I_Mx1_weight);
    T_Mx2_1->SetBranchAddress("f_Met", &f_Mx1_Met);
    T_Mx2_1->SetBranchAddress("f_dileptonPT", &f_Mx1_dilepPT);
    T_Mx2_1->SetBranchAddress("v_MetdeltaPhi", &v_Mx1_MetdeltaPhi);
    T_Mx2_1->SetBranchAddress("v_N_Tracks", &v_Mx1_nTrack);
    T_Mx2_1->SetBranchAddress("v_fakealpha", &v_Mx1_alpha);
    for (int evt = 0; evt < T_Mx2_1->GetEntries(); evt++)
    {
        T_Mx2_1->GetEntry(evt);
        if (v_Mx1_alpha->size() < 2)
        {
            continue;
        }
        for (size_t nele = 0; nele < v_Mx1_MetdeltaPhi->size(); nele++)
        {
            h_Sig1_deltaPhi->Fill((*v_Mx1_MetdeltaPhi)[nele], I_Mx1_weight);
        }

        for (size_t njet = 0; njet < v_Mx1_alpha->size(); njet++)
        {
            h_Sig1_alpha->Fill((*v_Mx1_alpha)[njet], I_Mx1_weight);
        }

        h_Sig1_MET_dileptonPT->Fill(f_Mx1_Met, f_Mx1_dilepPT, I_Mx1_weight);
        h_Sig1_dileptonPT->Fill(f_Mx1_dilepPT, I_Mx1_weight);
        if (f_Mx1_Met < METcut)
        {
            continue;
        }
        for (size_t nele = 0; nele < v_Mx1_MetdeltaPhi->size(); nele++)
        {
            h_Sig1_deltaPhi_cutedMET->Fill((*v_Mx1_MetdeltaPhi)[nele], I_Mx1_weight);
        }
        for (size_t njet = 0; njet < v_Mx1_alpha->size(); njet++)
        {
            h_Sig1_alpha_cutedMET->Fill((*v_Mx1_alpha)[njet], I_Mx1_weight);
        }
        h_Sig1_dileptonPT_cutedMET->Fill(f_Mx1_dilepPT, I_Mx1_weight);
    }

    TTree *T_Mx2_50;
    Mx2_50->GetObject("T_tree", T_Mx2_50);
    T_Mx2_50->SetBranchAddress("I_weight", &I_Mx50_weight);
    T_Mx2_50->SetBranchAddress("f_Met", &f_Mx50_Met);
    T_Mx2_50->SetBranchAddress("f_dileptonPT", &f_Mx50_dilepPT);
    T_Mx2_50->SetBranchAddress("v_MetdeltaPhi", &v_Mx50_MetdeltaPhi);
    T_Mx2_50->SetBranchAddress("v_N_Tracks", &v_Mx50_nTrack);
    T_Mx2_50->SetBranchAddress("v_fakealpha", &v_Mx50_alpha);
    for (int evt = 0; evt < T_Mx2_50->GetEntries(); evt++)
    {
        T_Mx2_50->GetEntry(evt);
        if (v_Mx50_alpha->size() < 2)
        {
            continue;
        }
        for (size_t nele = 0; nele < v_Mx50_MetdeltaPhi->size(); nele++)
        {
            h_Sig50_deltaPhi->Fill((*v_Mx50_MetdeltaPhi)[nele], I_Mx50_weight);
        }
        for (size_t njet = 0; njet < v_Mx50_alpha->size(); njet++)
        {
            h_Sig50_alpha->Fill((*v_Mx50_alpha)[njet], I_Mx50_weight);
        }
        h_Sig50_MET_dileptonPT->Fill(f_Mx50_Met, f_Mx50_dilepPT, I_Mx50_weight);
        h_Sig50_dileptonPT->Fill(f_Mx50_dilepPT, I_Mx50_weight);
        if (f_Mx50_Met < METcut)
        {
            continue;
        }
        for (size_t nele = 0; nele < v_Mx50_MetdeltaPhi->size(); nele++)
        {
            h_Sig50_deltaPhi_cutedMET->Fill((*v_Mx50_MetdeltaPhi)[nele], I_Mx50_weight);
        }
        for (size_t njet = 0; njet < v_Mx50_alpha->size(); njet++)
        {
            h_Sig50_alpha_cutedMET->Fill((*v_Mx50_alpha)[njet], I_Mx50_weight);
        }
        h_Sig50_dileptonPT_cutedMET->Fill(f_Mx50_dilepPT, I_Mx50_weight);
    }

    TTree *T_Mx2_150;
    Mx2_150->GetObject("T_tree", T_Mx2_150);
    T_Mx2_150->SetBranchAddress("I_weight", &I_Mx150_weight);
    T_Mx2_150->SetBranchAddress("f_Met", &f_Mx150_Met);
    T_Mx2_150->SetBranchAddress("f_dileptonPT", &f_Mx150_dilepPT);
    T_Mx2_150->SetBranchAddress("v_MetdeltaPhi", &v_Mx150_MetdeltaPhi);
    T_Mx2_150->SetBranchAddress("v_N_Tracks", &v_Mx150_nTrack);
    T_Mx2_150->SetBranchAddress("v_fakealpha", &v_Mx150_alpha);
    for (int evt = 0; evt < T_Mx2_150->GetEntries(); evt++)
    {
        T_Mx2_150->GetEntry(evt);
        if (v_Mx150_alpha->size() < 2)
        {
            continue;
        }
        for (size_t nele = 0; nele < v_Mx150_MetdeltaPhi->size(); nele++)
        {
            h_Sig150_deltaPhi->Fill((*v_Mx150_MetdeltaPhi)[nele], I_Mx150_weight);
        }
        for (size_t njet = 0; njet < v_Mx150_alpha->size(); njet++)
        {
            h_Sig150_alpha->Fill((*v_Mx150_alpha)[njet], I_Mx150_weight);
        }
        h_Sig150_MET_dileptonPT->Fill(f_Mx150_Met, f_Mx150_dilepPT, I_Mx150_weight);
        h_Sig150_dileptonPT->Fill(f_Mx150_dilepPT, I_Mx150_weight);
        if (f_Mx150_Met < METcut)
        {
            continue;
        }
        for (size_t nele = 0; nele < v_Mx150_MetdeltaPhi->size(); nele++)
        {
            h_Sig150_deltaPhi_cutedMET->Fill((*v_Mx150_MetdeltaPhi)[nele], I_Mx150_weight);
        }
        for (size_t njet = 0; njet < v_Mx150_alpha->size(); njet++)
        {
            h_Sig150_alpha_cutedMET->Fill((*v_Mx150_alpha)[njet], I_Mx150_weight);
        }
        h_Sig150_dileptonPT_cutedMET->Fill(f_Mx150_dilepPT, I_Mx150_weight);
    }
    h_Sig1_MET_dileptonPT->GetXaxis()->SetTitle("Di-leptonPT");
    h_Sig1_MET_dileptonPT->GetYaxis()->SetTitle("MET");

    h_Sig50_MET_dileptonPT->GetXaxis()->SetTitle("Di-leptonPT");
    h_Sig50_MET_dileptonPT->GetYaxis()->SetTitle("MET");

    h_Sig150_MET_dileptonPT->GetXaxis()->SetTitle("Di-leptonPT");
    h_Sig150_MET_dileptonPT->GetYaxis()->SetTitle("MET");

    h_Sig1_dileptonPT_cutedMET->GetXaxis()->SetTitle("Di-leptonPT");
    h_Sig1_dileptonPT_cutedMET->GetYaxis()->SetTitle("Normalized/Event");
    h_Sig1_dileptonPT_cutedMET->SetLineColor(kRed);

    h_Sig50_dileptonPT_cutedMET->GetXaxis()->SetTitle("Di-leptonPT");
    h_Sig50_dileptonPT_cutedMET->GetYaxis()->SetTitle("Normalized/Event");
    h_Sig50_dileptonPT_cutedMET->SetLineColor(kRed);

    h_Sig150_dileptonPT_cutedMET->GetXaxis()->SetTitle("Di-leptonPT");
    h_Sig150_dileptonPT_cutedMET->GetYaxis()->SetTitle("Normalized/Event");
    h_Sig150_dileptonPT_cutedMET->SetLineColor(kRed);

    h_Sig1_deltaPhi_cutedMET->GetXaxis()->SetTitle("Deltaphi");
    h_Sig1_deltaPhi_cutedMET->GetYaxis()->SetTitle("Normalized/nele");
    h_Sig1_deltaPhi_cutedMET->SetLineColor(kRed);

    h_Sig50_deltaPhi_cutedMET->GetXaxis()->SetTitle("Deltaphi");
    h_Sig50_deltaPhi_cutedMET->GetYaxis()->SetTitle("Normalized/nele");
    h_Sig50_deltaPhi_cutedMET->SetLineColor(kRed);

    h_Sig150_deltaPhi_cutedMET->GetXaxis()->SetTitle("Deltaphi");
    h_Sig150_deltaPhi_cutedMET->GetYaxis()->SetTitle("Normalized/nele");
    h_Sig150_deltaPhi_cutedMET->SetLineColor(kRed);

    h_Sig1_alpha_cutedMET->GetXaxis()->SetTitle("#alpha_{3D}");
    h_Sig1_alpha_cutedMET->GetYaxis()->SetTitle("Normalized/nJet");
    h_Sig1_alpha_cutedMET->SetLineColor(kRed);

    h_Sig50_alpha_cutedMET->GetXaxis()->SetTitle("#alpha_{3D}");
    h_Sig50_alpha_cutedMET->GetYaxis()->SetTitle("Normalized/nJet");
    h_Sig50_alpha_cutedMET->SetLineColor(kRed);

    h_Sig150_alpha_cutedMET->GetXaxis()->SetTitle("#alpha_{3D}");
    h_Sig150_alpha_cutedMET->GetYaxis()->SetTitle("Normalized/nJet");
    h_Sig150_alpha_cutedMET->SetLineColor(kRed);


    // h_Sig150_dileptonPT_cutedMET->DrawNormalized("h");
    // h_Sig150_dileptonPT->DrawNormalized("same");
    //  h_Sig150_MET_dileptonPT->Draw("colz");
    h_Sig50_alpha_cutedMET->Draw("h");
    h_Sig50_alpha->Draw("same");

    TLegend *l0 = new TLegend(0.4, 0.4, 0.90, 0.80);
    l0->SetBorderSize(0);
    l0->SetFillStyle(0);
    l0->SetTextSize(0.03);
    l0->SetHeader("");
    l0->AddEntry(h_Sig1_dileptonPT, "Any MET", "l");
    l0->AddEntry(h_Sig1_dileptonPT_cutedMET, "Event MET > 130 GeV", "l");
    l0->Draw();

    gStyle->SetOptStat(0);

    double corr_Sig1_MET_dileptonPT = h_Sig1_MET_dileptonPT->GetCorrelationFactor();
    double corr_Sig50_MET_dileptonPT = h_Sig50_MET_dileptonPT->GetCorrelationFactor();
    double corr_Sig150_MET_dileptonPT = h_Sig150_MET_dileptonPT->GetCorrelationFactor();

    cout << "Sig1 :  correlation between MET and dilepton PT = " << corr_Sig1_MET_dileptonPT << endl;
    cout << "Sig50 :  correlation between  MET and dilepton PT = " << corr_Sig50_MET_dileptonPT << endl;
    cout << "Sig150 :  correlation between MET and dilepton PT = " << corr_Sig150_MET_dileptonPT << endl;
}