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
    float jetpt, jeteta, jetntrk, jetalpha;

public:
    ThinJet() {}
    ThinJet(const float &a, const float &b, const float &c, const float &d) : jetpt(a), jeteta(b), jetntrk(c), jetalpha(d) {}

    Float_t GetPt() const { return jetpt; }
    Float_t GetEta() const { return jeteta; }
    Float_t GetNtrk() const { return jetntrk; }
    Float_t GetAlpha() const { return jetalpha; }

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

TFile *TTTo2L2Nufile = new TFile("/home/kuanyu/Documents/root_file/Ztoemu/2016BKGMC/top/eu_top_emu_TTTo2L2Nu.root");
TFile *Top_TTWJetsToLNufile = new TFile("/home/kuanyu/Documents/root_file/Ztoemu/2016BKGMC/top/eu_top_emu_TTWJetsToLNu.root");
TFile *Top_TTWJetsToQQfile = new TFile("/home/kuanyu/Documents/root_file/Ztoemu/2016BKGMC/top/eu_top_emu_TTWJetsToQQ.root");
TFile *Top_TTZToQQfile = new TFile("/home/kuanyu/Documents/root_file/Ztoemu/2016BKGMC/top/eu_top_emu_TTZToQQ.root");
TFile *Top_TTZToLLNuNufile = new TFile("/home/kuanyu/Documents/root_file/Ztoemu/2016BKGMC/top/eu_top_emu_TTZToLLNuNu.root");
TFile *Top_tW_antitopfile = new TFile("/home/kuanyu/Documents/root_file/Ztoemu/2016BKGMC/top/eu_top_emu_tW_antitop.root");
TFile *Top_tW_topfile = new TFile("/home/kuanyu/Documents/root_file/Ztoemu/2016BKGMC/top/eu_top_emu_tW_top.root");

TH1D *TTTo2L2Nu_sumevt = ((TH1D *)TTTo2L2Nufile->Get("Event_Variable/h_totevent"));
TH1D *TTWJetsToLNu_sumevt = ((TH1D *)Top_TTWJetsToLNufile->Get("Event_Variable/h_totevent"));
TH1D *TTWJetsToQQ_sumevt = ((TH1D *)Top_TTWJetsToQQfile->Get("Event_Variable/h_totevent"));
TH1D *TTZToQQ_sumevt = ((TH1D *)Top_TTZToQQfile->Get("Event_Variable/h_totevent"));
TH1D *TTZToLLNuNu_sumevt = ((TH1D *)Top_TTZToLLNuNufile->Get("Event_Variable/h_totevent"));
TH1D *tW_antitop_sumevt = ((TH1D *)Top_tW_antitopfile->Get("Event_Variable/h_totevent"));
TH1D *tW_top_sumevt = ((TH1D *)Top_tW_topfile->Get("Event_Variable/h_totevent"));

double TTTo2L2Nu_totevt = TTTo2L2Nu_sumevt->Integral();
double TTWJetsToLNu_totevt = TTWJetsToLNu_sumevt->Integral();
double TTWJetsToQQ_totevt = TTWJetsToQQ_sumevt->Integral();
double TTZToQQ_totevt = TTZToQQ_sumevt->Integral();
double TTZToLLNuNu_totevt = TTZToLLNuNu_sumevt->Integral();
double tW_antitop_totevt = tW_antitop_sumevt->Integral();
double tW_top_totevt = tW_top_sumevt->Integral();

//---------------------
// Define Weight
//---------------------
double TTTo2L2NuWeight = (GlobalConstants::Lumi2016) * ((GlobalConstants::TTTo2L2Nu) / (TTTo2L2Nu_totevt)) * 1000;
double ST_tW_topWeight = (GlobalConstants::Lumi2016) * (GlobalConstants::ST_tW_top_5fCS / (tW_top_totevt)) * 1000;
double ST_tW_antitopWeight = (GlobalConstants::Lumi2016) * (GlobalConstants::ST_tW_antitop_5fCS / (tW_antitop_totevt)) * 1000;
double TTWJetsToLNuWeight = (GlobalConstants::Lumi2016) * (GlobalConstants::TTWJetsToLNu / (TTWJetsToLNu_totevt)) * 1000;
double TTWJetsToQQWeight = (GlobalConstants::Lumi2016) * (GlobalConstants::TTWJetsToQQ / (TTWJetsToQQ_totevt)) * 1000;
double TTZToQQWeight = (GlobalConstants::Lumi2016) * (GlobalConstants::TTZToQQ / (TTZToQQ_totevt)) * 1000;
double TTZToLLNuNuWeight = (GlobalConstants::Lumi2016) * (GlobalConstants::TTZToLLNuNu / (TTZToLLNuNu_totevt)) * 1000;

void Top_eu_corr()
{

    TH2D *h_Top_MET_dileptonPT = new TH2D("h_Top_MET_dileptonPT", "", 150, 0, 1500, 100, 0, 1000);
    h_Top_MET_dileptonPT->Sumw2();

    TH1D *h_Top_dileptonPT = new TH1D("h_Top_dileptonPT", "", 100, 0, 1000);
    h_Top_dileptonPT->Sumw2();

    TH1D *h_Top_dileptonPT_cutedMET = new TH1D("h_Top_dileptonPT_cutedMET", "", 100, 0, 1000);
    h_Top_dileptonPT_cutedMET->Sumw2();

    TH2D *h_Top_JetPT_ntrk = new TH2D("h_Top_JetPT_ntrk", "", 150, 0, 1500, 30., 0, 30.);
    h_Top_JetPT_ntrk->Sumw2();

    TH2D *h_Top_ntrk_JetPT = new TH2D("h_Top_ntrk_JetPT", "", 30., 0, 30., 150, 0, 1500);
    h_Top_ntrk_JetPT->Sumw2();

    TH2D *h_Top_JetPT_JetEta = new TH2D("h_Top_JetPT_JetEta", "", 150, 0., 1500., 30., -3., 3.);
    h_Top_JetPT_JetEta->Sumw2();

    TH2D *h_Top_ntrk_JetEta = new TH2D("h_Top_ntrk_JetEta", "", 30., 0., 30., 30., -3., 3.);
    h_Top_ntrk_JetEta->Sumw2();

    TH2D *h_Top_alpha_JetEta = new TH2D("h_Top_alpha_JetEta", "", 24, 0., 1.2, 30., -3., 3.);
    h_Top_alpha_JetEta->Sumw2();

    TH2D *h_Top_alpha_JetPT = new TH2D("h_Top_alpha_JetPT", "", 24, 0., 1.2, 150., 0., 1500.);
    h_Top_alpha_JetPT->Sumw2();

    TH2D *h_Top_alpha_ntrk = new TH2D("h_Top_alpha_ntrk", "", 24, 0., 1.2, 30., 0, 30.);
    h_Top_alpha_ntrk->Sumw2();

    TH1D *h_Top_ntrk = new TH1D("h_Top_ntrk", "", 30., 0, 30.);
    h_Top_ntrk->Sumw2();

    TH1D *h_Top_JetPT = new TH1D("h_Top_JetPT", "", 150, 0, 1500);
    h_Top_JetPT->Sumw2();

    //-------------------------
    // Create TProfile
    //-------------------------
    TProfile *h_ntrk_prof = new TProfile("h_ntrk_prof", "profile track multiplicity", 30., 0, 30.);
    h_ntrk_prof->Sumw2();

    TProfile *h_JetPt_prof = new TProfile("h_JetPt_prof", "profile Jet Pt", 150, 0, 1500);
    h_JetPt_prof->Sumw2();

    Int_t I_TTTo2L2Nu_weight;
    Int_t I_ST_tW_top_weight;
    Int_t I_ST_tW_antitop_weight;
    Int_t I_TTWJetsToLNu_weight;
    Int_t I_TTWJetsToQQ_weight;
    Int_t I_TTZToQQ_weight;
    Int_t I_TTZToLLNuNu_weight;

    float_t f_TTTo2L2Nu_met;
    float_t f_ST_tW_top_met;
    float_t f_ST_tW_antitop_met;
    float_t f_TTWJetsToLNu_met;
    float_t f_TTWJetsToQQ_met;
    float_t f_TTZToQQ_met;
    float_t f_TTZToLLNuNu_met;

    float_t f_TTTo2L2Nu_dileppt;
    float_t f_ST_tW_top_dileppt;
    float_t f_ST_tW_antitop_dileppt;
    float_t f_TTWJetsToLNu_dileppt;
    float_t f_TTWJetsToQQ_dileppt;
    float_t f_TTZToQQ_dileppt;
    float_t f_TTZToLLNuNu_dileppt;

    vector<float> *v_TTTo2L2Nu_JetPT = new vector<float>();
    vector<float> *v_ST_tW_top_JetPT = new vector<float>();
    vector<float> *v_ST_tW_antitop_JetPT = new vector<float>();
    vector<float> *v_TTWJetsToLNu_JetPT = new vector<float>();
    vector<float> *v_TTWJetsToQQ_JetPT = new vector<float>();
    vector<float> *v_TTZToQQ_JetPT = new vector<float>();
    vector<float> *v_TTZToLLNuNu_JetPT = new vector<float>();

    vector<float> *v_TTTo2L2Nu_JetEta = new vector<float>();
    vector<float> *v_ST_tW_top_JetEta = new vector<float>();
    vector<float> *v_ST_tW_antitop_JetEta = new vector<float>();
    vector<float> *v_TTWJetsToLNu_JetEta = new vector<float>();
    vector<float> *v_TTWJetsToQQ_JetEta = new vector<float>();
    vector<float> *v_TTZToQQ_JetEta = new vector<float>();
    vector<float> *v_TTZToLLNuNu_JetEta = new vector<float>();

    vector<float> *v_TTTo2L2Nu_nTrack = new vector<float>();
    vector<float> *v_ST_tW_top_nTrack = new vector<float>();
    vector<float> *v_ST_tW_antitop_nTrack = new vector<float>();
    vector<float> *v_TTWJetsToLNu_nTrack = new vector<float>();
    vector<float> *v_TTWJetsToQQ_nTrack = new vector<float>();
    vector<float> *v_TTZToQQ_nTrack = new vector<float>();
    vector<float> *v_TTZToLLNuNu_nTrack = new vector<float>();

    vector<float> *v_TTTo2L2Nu_alpha = new vector<float>();
    vector<float> *v_ST_tW_top_alpha = new vector<float>();
    vector<float> *v_ST_tW_antitop_alpha = new vector<float>();
    vector<float> *v_TTWJetsToLNu_alpha = new vector<float>();
    vector<float> *v_TTWJetsToQQ_alpha = new vector<float>();
    vector<float> *v_TTZToQQ_alpha = new vector<float>();
    vector<float> *v_TTZToLLNuNu_alpha = new vector<float>();

    v_TTTo2L2Nu_nTrack->clear();
    v_ST_tW_top_nTrack->clear();
    v_ST_tW_antitop_nTrack->clear();
    v_TTWJetsToLNu_nTrack->clear();
    v_TTWJetsToQQ_nTrack->clear();
    v_TTZToQQ_nTrack->clear();
    v_TTZToLLNuNu_nTrack->clear();

    v_TTTo2L2Nu_JetPT->clear();
    v_ST_tW_top_JetPT->clear();
    v_ST_tW_antitop_JetPT->clear();
    v_TTWJetsToLNu_JetPT->clear();
    v_TTWJetsToQQ_JetPT->clear();
    v_TTZToQQ_JetPT->clear();
    v_TTZToLLNuNu_JetPT->clear();

    v_TTTo2L2Nu_JetEta->clear();
    v_ST_tW_top_JetEta->clear();
    v_ST_tW_antitop_JetEta->clear();
    v_TTWJetsToLNu_JetEta->clear();
    v_TTWJetsToQQ_JetEta->clear();
    v_TTZToQQ_JetEta->clear();
    v_TTZToLLNuNu_JetEta->clear();

    v_TTTo2L2Nu_alpha->clear();
    v_ST_tW_top_alpha->clear();
    v_ST_tW_antitop_alpha->clear();
    v_TTWJetsToLNu_alpha->clear();
    v_TTWJetsToQQ_alpha->clear();
    v_TTZToQQ_alpha->clear();
    v_TTZToLLNuNu_alpha->clear();

    //----------------------
    // Alias some cut
    //----------------------
    double METcut = 130.;

    double DilepPTcut = 60.;

    TTree *T_TTTo2L2Nu_tree;
    TTTo2L2Nufile->GetObject("T_tree", T_TTTo2L2Nu_tree);
    T_TTTo2L2Nu_tree->SetBranchAddress("I_weight", &I_TTTo2L2Nu_weight);
    T_TTTo2L2Nu_tree->SetBranchAddress("v_N_Tracks", &v_TTTo2L2Nu_nTrack);
    T_TTTo2L2Nu_tree->SetBranchAddress("f_Met", &f_TTTo2L2Nu_met);
    T_TTTo2L2Nu_tree->SetBranchAddress("f_dileptonPT", &f_TTTo2L2Nu_dileppt);
    T_TTTo2L2Nu_tree->SetBranchAddress("v_fakeJetPt", &v_TTTo2L2Nu_JetPT);
    T_TTTo2L2Nu_tree->SetBranchAddress("v_fakeJetEta", &v_TTTo2L2Nu_JetEta);
    T_TTTo2L2Nu_tree->SetBranchAddress("v_fakealpha", &v_TTTo2L2Nu_alpha);
    for (int evt = 0; evt < T_TTTo2L2Nu_tree->GetEntries(); evt++)
    {
        T_TTTo2L2Nu_tree->GetEntry(evt);
        vector<ThinJet> v_thinjet;
        v_thinjet.clear();
        if (v_TTTo2L2Nu_nTrack->size() < 2)
        {
            continue;
        }
        for (size_t i = 0; i < v_TTTo2L2Nu_nTrack->size(); i++)
        {
            v_thinjet.push_back(ThinJet((*v_TTTo2L2Nu_JetPT)[i], (*v_TTTo2L2Nu_JetEta)[i], (*v_TTTo2L2Nu_nTrack)[i], (*v_TTTo2L2Nu_alpha)[i]));
        }
        sort(v_thinjet.begin(), v_thinjet.end(), greater<ThinJet>());
        double TTTo2L2Nu_eventWeight = I_TTTo2L2Nu_weight * TTTo2L2NuWeight;

        h_Top_MET_dileptonPT->Fill(f_TTTo2L2Nu_met, f_TTTo2L2Nu_dileppt, TTTo2L2Nu_eventWeight);
        h_Top_dileptonPT->Fill(f_TTTo2L2Nu_dileppt, TTTo2L2Nu_eventWeight);
        if (f_TTTo2L2Nu_met < METcut)
        {
            continue;
        }
        h_Top_dileptonPT_cutedMET->Fill(f_TTTo2L2Nu_dileppt, TTTo2L2Nu_eventWeight);
        if (f_TTTo2L2Nu_dileppt < DilepPTcut)
        {
            continue;
        }

        for (size_t ijet = 0; ijet < 2; ijet++)
        {
            h_Top_JetPT_ntrk->Fill(v_thinjet[ijet].GetPt(), v_thinjet[ijet].GetNtrk(), TTTo2L2Nu_eventWeight);
            h_Top_ntrk_JetPT->Fill(v_thinjet[ijet].GetNtrk(), v_thinjet[ijet].GetPt(), TTTo2L2Nu_eventWeight);

            h_Top_JetPT_JetEta->Fill(v_thinjet[ijet].GetPt(), v_thinjet[ijet].GetEta(), TTTo2L2Nu_eventWeight);
            h_Top_ntrk_JetEta->Fill(v_thinjet[ijet].GetNtrk(), v_thinjet[ijet].GetEta(), TTTo2L2Nu_eventWeight);

            h_Top_alpha_ntrk->Fill(v_thinjet[ijet].GetAlpha(), v_thinjet[ijet].GetNtrk(), TTTo2L2Nu_eventWeight);
            h_Top_alpha_JetPT->Fill(v_thinjet[ijet].GetAlpha(), v_thinjet[ijet].GetPt(), TTTo2L2Nu_eventWeight);
            h_Top_alpha_JetEta->Fill(v_thinjet[ijet].GetAlpha(), v_thinjet[ijet].GetEta(), TTTo2L2Nu_eventWeight);

            h_Top_JetPT->Fill(v_thinjet[ijet].GetPt(), TTTo2L2Nu_eventWeight);
            h_Top_ntrk->Fill(v_thinjet[ijet].GetNtrk(), TTTo2L2Nu_eventWeight);

            // For TProfile
            h_ntrk_prof->Fill(v_thinjet[ijet].GetNtrk(), TTTo2L2Nu_eventWeight);
            h_JetPt_prof->Fill(v_thinjet[ijet].GetPt(), TTTo2L2Nu_eventWeight);
        }
    }
    TTree *T_ST_tW_top_tree;
    Top_tW_topfile->GetObject("T_tree", T_ST_tW_top_tree);
    T_ST_tW_top_tree->SetBranchAddress("I_weight", &I_ST_tW_top_weight);
    T_ST_tW_top_tree->SetBranchAddress("v_N_Tracks", &v_ST_tW_top_nTrack);
    T_ST_tW_top_tree->SetBranchAddress("f_Met", &f_ST_tW_top_met);
    T_ST_tW_top_tree->SetBranchAddress("f_dileptonPT", &f_ST_tW_top_dileppt);
    T_ST_tW_top_tree->SetBranchAddress("v_fakeJetPt", &v_ST_tW_top_JetPT);
    T_ST_tW_top_tree->SetBranchAddress("v_fakeJetEta", &v_ST_tW_top_JetEta);
    T_ST_tW_top_tree->SetBranchAddress("v_fakealpha", &v_ST_tW_top_alpha);
    for (int evt = 0; evt < T_ST_tW_top_tree->GetEntries(); evt++)
    {
        T_ST_tW_top_tree->GetEntry(evt);
        vector<ThinJet> v_thinjet;
        v_thinjet.clear();
        if (v_ST_tW_top_nTrack->size() < 2)
        {
            continue;
        }
        for (size_t i = 0; i < v_ST_tW_top_nTrack->size(); i++)
        {
            v_thinjet.push_back(ThinJet((*v_ST_tW_top_JetPT)[i], (*v_ST_tW_top_JetEta)[i], (*v_ST_tW_top_nTrack)[i], (*v_ST_tW_top_alpha)[i]));
        }
        sort(v_thinjet.begin(), v_thinjet.end(), greater<ThinJet>());

        double ST_tW_top_eventWeight = I_ST_tW_top_weight * ST_tW_topWeight;

        h_Top_MET_dileptonPT->Fill(f_ST_tW_top_met, f_ST_tW_top_dileppt, ST_tW_top_eventWeight);
        h_Top_dileptonPT->Fill(f_ST_tW_top_dileppt, ST_tW_top_eventWeight);
        if (f_ST_tW_top_met < METcut)
        {
            continue;
        }
        h_Top_dileptonPT_cutedMET->Fill(f_ST_tW_top_dileppt, ST_tW_top_eventWeight);
        if (f_ST_tW_top_dileppt < DilepPTcut)
        {
            continue;
        }
        for (size_t ijet = 0; ijet < 2; ijet++)
        {
            h_Top_JetPT_ntrk->Fill(v_thinjet[ijet].GetPt(), v_thinjet[ijet].GetNtrk(), ST_tW_top_eventWeight);
            h_Top_ntrk_JetPT->Fill(v_thinjet[ijet].GetNtrk(), v_thinjet[ijet].GetPt(), ST_tW_top_eventWeight);

            h_Top_JetPT_JetEta->Fill(v_thinjet[ijet].GetPt(), v_thinjet[ijet].GetEta(), ST_tW_top_eventWeight);
            h_Top_ntrk_JetEta->Fill(v_thinjet[ijet].GetNtrk(), v_thinjet[ijet].GetEta(), ST_tW_top_eventWeight);

            h_Top_alpha_ntrk->Fill(v_thinjet[ijet].GetAlpha(), v_thinjet[ijet].GetNtrk(), ST_tW_top_eventWeight);
            h_Top_alpha_JetPT->Fill(v_thinjet[ijet].GetAlpha(), v_thinjet[ijet].GetPt(), ST_tW_top_eventWeight);
            h_Top_alpha_JetEta->Fill(v_thinjet[ijet].GetAlpha(), v_thinjet[ijet].GetEta(), ST_tW_top_eventWeight);

            h_Top_JetPT->Fill(v_thinjet[ijet].GetPt(), ST_tW_top_eventWeight);
            h_Top_ntrk->Fill(v_thinjet[ijet].GetNtrk(), ST_tW_top_eventWeight);

            // For TProfile
            h_ntrk_prof->Fill(v_thinjet[ijet].GetNtrk(), ST_tW_top_eventWeight);
            h_JetPt_prof->Fill(v_thinjet[ijet].GetPt(), ST_tW_top_eventWeight);
        }
    }
    TTree *T_ST_tW_antitop_tree;
    Top_tW_antitopfile->GetObject("T_tree", T_ST_tW_antitop_tree);
    T_ST_tW_antitop_tree->SetBranchAddress("I_weight", &I_ST_tW_antitop_weight);
    T_ST_tW_antitop_tree->SetBranchAddress("v_N_Tracks", &v_ST_tW_antitop_nTrack);
    T_ST_tW_antitop_tree->SetBranchAddress("f_Met", &f_ST_tW_antitop_met);
    T_ST_tW_antitop_tree->SetBranchAddress("f_dileptonPT", &f_ST_tW_antitop_dileppt);
    T_ST_tW_antitop_tree->SetBranchAddress("v_fakeJetPt", &v_ST_tW_antitop_JetPT);
    T_ST_tW_antitop_tree->SetBranchAddress("v_fakeJetEta", &v_ST_tW_antitop_JetEta);
    T_ST_tW_antitop_tree->SetBranchAddress("v_fakealpha", &v_ST_tW_antitop_alpha);
    for (int evt = 0; evt < T_ST_tW_antitop_tree->GetEntries(); evt++)
    {
        T_ST_tW_antitop_tree->GetEntry(evt);
        vector<ThinJet> v_thinjet;
        v_thinjet.clear();
        if (v_ST_tW_antitop_nTrack->size() < 2)
        {
            continue;
        }
        for (size_t i = 0; i < v_ST_tW_antitop_nTrack->size(); i++)
        {
            v_thinjet.push_back(ThinJet((*v_ST_tW_antitop_JetPT)[i], (*v_ST_tW_antitop_JetEta)[i], (*v_ST_tW_antitop_nTrack)[i], (*v_ST_tW_antitop_alpha)[i]));
        }
        sort(v_thinjet.begin(), v_thinjet.end(), greater<ThinJet>());
        double ST_tW_antitop_eventWeight = I_ST_tW_antitop_weight * ST_tW_antitopWeight;

        h_Top_MET_dileptonPT->Fill(f_ST_tW_antitop_met, f_ST_tW_antitop_dileppt, ST_tW_antitop_eventWeight);
        h_Top_dileptonPT->Fill(f_ST_tW_antitop_dileppt, ST_tW_antitop_eventWeight);
        if (f_ST_tW_antitop_met < METcut)
        {
            continue;
        }
        h_Top_dileptonPT_cutedMET->Fill(f_ST_tW_antitop_dileppt, ST_tW_antitop_eventWeight);
        if (f_ST_tW_antitop_dileppt < DilepPTcut)
        {
            continue;
        }

        for (size_t ijet = 0; ijet < 2; ijet++)
        {
            h_Top_JetPT_ntrk->Fill(v_thinjet[ijet].GetPt(), v_thinjet[ijet].GetNtrk(), ST_tW_antitop_eventWeight);
            h_Top_ntrk_JetPT->Fill(v_thinjet[ijet].GetNtrk(), v_thinjet[ijet].GetPt(), ST_tW_antitop_eventWeight);

            h_Top_JetPT_JetEta->Fill(v_thinjet[ijet].GetPt(), v_thinjet[ijet].GetEta(), ST_tW_antitop_eventWeight);
            h_Top_ntrk_JetEta->Fill(v_thinjet[ijet].GetNtrk(), v_thinjet[ijet].GetEta(), ST_tW_antitop_eventWeight);

            h_Top_alpha_ntrk->Fill(v_thinjet[ijet].GetAlpha(), v_thinjet[ijet].GetNtrk(), ST_tW_antitop_eventWeight);
            h_Top_alpha_JetPT->Fill(v_thinjet[ijet].GetAlpha(), v_thinjet[ijet].GetPt(), ST_tW_antitop_eventWeight);
            h_Top_alpha_JetEta->Fill(v_thinjet[ijet].GetAlpha(), v_thinjet[ijet].GetEta(), ST_tW_antitop_eventWeight);

            h_Top_JetPT->Fill(v_thinjet[ijet].GetPt(), ST_tW_antitop_eventWeight);
            h_Top_ntrk->Fill(v_thinjet[ijet].GetNtrk(), ST_tW_antitop_eventWeight);

            // For TProfile
            h_ntrk_prof->Fill(v_thinjet[ijet].GetNtrk(), ST_tW_antitop_eventWeight);
            h_JetPt_prof->Fill(v_thinjet[ijet].GetPt(), ST_tW_antitop_eventWeight);
        }
    }
    TTree *T_TTWJetsToLNu_tree;
    Top_TTWJetsToLNufile->GetObject("T_tree", T_TTWJetsToLNu_tree);
    T_TTWJetsToLNu_tree->SetBranchAddress("I_weight", &I_TTWJetsToLNu_weight);
    T_TTWJetsToLNu_tree->SetBranchAddress("v_N_Tracks", &v_TTWJetsToLNu_nTrack);
    T_TTWJetsToLNu_tree->SetBranchAddress("f_Met", &f_TTWJetsToLNu_met);
    T_TTWJetsToLNu_tree->SetBranchAddress("f_dileptonPT", &f_TTWJetsToLNu_dileppt);
    T_TTWJetsToLNu_tree->SetBranchAddress("v_fakeJetPt", &v_TTWJetsToLNu_JetPT);
    T_TTWJetsToLNu_tree->SetBranchAddress("v_fakeJetEta", &v_TTWJetsToLNu_JetEta);
    T_TTWJetsToLNu_tree->SetBranchAddress("v_fakealpha", &v_TTWJetsToLNu_alpha);
    for (int evt = 0; evt < T_TTWJetsToLNu_tree->GetEntries(); evt++)
    {
        T_TTWJetsToLNu_tree->GetEntry(evt);
        vector<ThinJet> v_thinjet;
        v_thinjet.clear();
        if (v_TTWJetsToLNu_nTrack->size() < 2)
        {
            continue;
        }
        for (size_t i = 0; i < v_TTWJetsToLNu_nTrack->size(); i++)
        {
            v_thinjet.push_back(ThinJet((*v_TTWJetsToLNu_JetPT)[i], (*v_TTWJetsToLNu_JetEta)[i], (*v_TTWJetsToLNu_nTrack)[i], (*v_TTWJetsToLNu_alpha)[i]));
        }
        sort(v_thinjet.begin(), v_thinjet.end(), greater<ThinJet>());
        double TTWJetsToLNu_eventWeight = I_TTWJetsToLNu_weight * TTWJetsToLNuWeight;

        h_Top_MET_dileptonPT->Fill(f_TTWJetsToLNu_met, f_TTWJetsToLNu_dileppt, TTWJetsToLNu_eventWeight);
        h_Top_dileptonPT->Fill(f_TTWJetsToLNu_dileppt, TTWJetsToLNu_eventWeight);
        if (f_TTWJetsToLNu_met < METcut)
        {
            continue;
        }
        h_Top_dileptonPT_cutedMET->Fill(f_TTWJetsToLNu_dileppt, TTWJetsToLNu_eventWeight);
        if (f_TTWJetsToLNu_dileppt < DilepPTcut)
        {
            continue;
        }
        for (size_t ijet = 0; ijet < 2; ijet++)
        {
            h_Top_JetPT_ntrk->Fill(v_thinjet[ijet].GetPt(), v_thinjet[ijet].GetNtrk(), TTWJetsToLNu_eventWeight);
            h_Top_ntrk_JetPT->Fill(v_thinjet[ijet].GetNtrk(), v_thinjet[ijet].GetPt(), TTWJetsToLNu_eventWeight);

            h_Top_JetPT_JetEta->Fill(v_thinjet[ijet].GetPt(), v_thinjet[ijet].GetEta(), TTWJetsToLNu_eventWeight);
            h_Top_ntrk_JetEta->Fill(v_thinjet[ijet].GetNtrk(), v_thinjet[ijet].GetEta(), TTWJetsToLNu_eventWeight);

            h_Top_alpha_ntrk->Fill(v_thinjet[ijet].GetAlpha(), v_thinjet[ijet].GetNtrk(), TTWJetsToLNu_eventWeight);
            h_Top_alpha_JetPT->Fill(v_thinjet[ijet].GetAlpha(), v_thinjet[ijet].GetPt(), TTWJetsToLNu_eventWeight);
            h_Top_alpha_JetEta->Fill(v_thinjet[ijet].GetAlpha(), v_thinjet[ijet].GetEta(), TTWJetsToLNu_eventWeight);

            h_Top_JetPT->Fill(v_thinjet[ijet].GetPt(), TTWJetsToLNu_eventWeight);
            h_Top_ntrk->Fill(v_thinjet[ijet].GetNtrk(), TTWJetsToLNu_eventWeight);

            // For TProfile
            h_ntrk_prof->Fill(v_thinjet[ijet].GetNtrk(), TTWJetsToLNu_eventWeight);
            h_JetPt_prof->Fill(v_thinjet[ijet].GetPt(), TTWJetsToLNu_eventWeight);
        }
    }
    TTree *T_TTWJetsToQQ_tree;
    Top_TTWJetsToQQfile->GetObject("T_tree", T_TTWJetsToQQ_tree);
    T_TTWJetsToQQ_tree->SetBranchAddress("I_weight", &I_TTWJetsToQQ_weight);
    T_TTWJetsToQQ_tree->SetBranchAddress("v_N_Tracks", &v_TTWJetsToQQ_nTrack);
    T_TTWJetsToQQ_tree->SetBranchAddress("f_Met", &f_TTWJetsToQQ_met);
    T_TTWJetsToQQ_tree->SetBranchAddress("f_dileptonPT", &f_TTWJetsToQQ_dileppt);
    T_TTWJetsToQQ_tree->SetBranchAddress("v_fakeJetPt", &v_TTWJetsToQQ_JetPT);
    T_TTWJetsToQQ_tree->SetBranchAddress("v_fakeJetEta", &v_TTWJetsToQQ_JetEta);
    T_TTWJetsToQQ_tree->SetBranchAddress("v_fakealpha", &v_TTWJetsToQQ_alpha);
    for (int evt = 0; evt < T_TTWJetsToQQ_tree->GetEntries(); evt++)
    {
        T_TTWJetsToQQ_tree->GetEntry(evt);
        vector<ThinJet> v_thinjet;
        v_thinjet.clear();
        if (v_TTWJetsToQQ_nTrack->size() < 2)
        {
            continue;
        }
        for (size_t i = 0; i < v_TTWJetsToQQ_nTrack->size(); i++)
        {
            v_thinjet.push_back(ThinJet((*v_TTWJetsToQQ_JetPT)[i], (*v_TTWJetsToQQ_JetEta)[i], (*v_TTWJetsToQQ_nTrack)[i], (*v_TTWJetsToQQ_alpha)[i]));
        }
        sort(v_thinjet.begin(), v_thinjet.end(), greater<ThinJet>());
        double TTWJetsToQQ_eventWeight = I_TTWJetsToQQ_weight * TTWJetsToQQWeight;

        h_Top_MET_dileptonPT->Fill(f_TTWJetsToQQ_met, f_TTWJetsToQQ_dileppt, TTWJetsToQQ_eventWeight);
        h_Top_dileptonPT->Fill(f_TTWJetsToQQ_dileppt, TTWJetsToQQ_eventWeight);
        if (f_TTWJetsToQQ_met < METcut)
        {
            continue;
        }
        h_Top_dileptonPT_cutedMET->Fill(f_TTWJetsToQQ_dileppt, TTWJetsToQQ_eventWeight);
        if (f_TTWJetsToQQ_dileppt < DilepPTcut)
        {
            continue;
        }

        for (size_t ijet = 0; ijet < 2; ijet++)
        {
            h_Top_JetPT_ntrk->Fill(v_thinjet[ijet].GetPt(), v_thinjet[ijet].GetNtrk(), TTWJetsToQQ_eventWeight);
            h_Top_ntrk_JetPT->Fill(v_thinjet[ijet].GetNtrk(), v_thinjet[ijet].GetPt(), TTWJetsToQQ_eventWeight);

            h_Top_JetPT_JetEta->Fill(v_thinjet[ijet].GetPt(), v_thinjet[ijet].GetEta(), TTWJetsToQQ_eventWeight);
            h_Top_ntrk_JetEta->Fill(v_thinjet[ijet].GetNtrk(), v_thinjet[ijet].GetEta(), TTWJetsToQQ_eventWeight);

            h_Top_alpha_ntrk->Fill(v_thinjet[ijet].GetAlpha(), v_thinjet[ijet].GetNtrk(), TTWJetsToQQ_eventWeight);
            h_Top_alpha_JetPT->Fill(v_thinjet[ijet].GetAlpha(), v_thinjet[ijet].GetPt(), TTWJetsToQQ_eventWeight);
            h_Top_alpha_JetEta->Fill(v_thinjet[ijet].GetAlpha(), v_thinjet[ijet].GetEta(), TTWJetsToQQ_eventWeight);

            h_Top_JetPT->Fill(v_thinjet[ijet].GetPt(), TTWJetsToQQ_eventWeight);
            h_Top_ntrk->Fill(v_thinjet[ijet].GetNtrk(), TTWJetsToQQ_eventWeight);

            // For TProfile
            h_ntrk_prof->Fill(v_thinjet[ijet].GetNtrk(), TTWJetsToQQ_eventWeight);
            h_JetPt_prof->Fill(v_thinjet[ijet].GetPt(), TTWJetsToQQ_eventWeight);
        }
    }
    TTree *T_TTZToQQ_tree;
    Top_TTZToQQfile->GetObject("T_tree", T_TTZToQQ_tree);
    T_TTZToQQ_tree->SetBranchAddress("I_weight", &I_TTZToQQ_weight);
    T_TTZToQQ_tree->SetBranchAddress("v_N_Tracks", &v_TTZToQQ_nTrack);
    T_TTZToQQ_tree->SetBranchAddress("f_Met", &f_TTZToQQ_met);
    T_TTZToQQ_tree->SetBranchAddress("f_dileptonPT", &f_TTZToQQ_dileppt);
    T_TTZToQQ_tree->SetBranchAddress("v_fakeJetPt", &v_TTZToQQ_JetPT);
    T_TTZToQQ_tree->SetBranchAddress("v_fakeJetEta", &v_TTZToQQ_JetEta);
    T_TTZToQQ_tree->SetBranchAddress("v_fakealpha", &v_TTZToQQ_alpha);
    for (int evt = 0; evt < T_TTZToQQ_tree->GetEntries(); evt++)
    {
        T_TTZToQQ_tree->GetEntry(evt);
        vector<ThinJet> v_thinjet;
        v_thinjet.clear();
        if (v_TTZToQQ_nTrack->size() < 2)
        {
            continue;
        }
        for (size_t i = 0; i < v_TTZToQQ_nTrack->size(); i++)
        {
            v_thinjet.push_back(ThinJet((*v_TTZToQQ_JetPT)[i], (*v_TTZToQQ_JetEta)[i], (*v_TTZToQQ_nTrack)[i], (*v_TTZToQQ_alpha)[i]));
        }
        sort(v_thinjet.begin(), v_thinjet.end(), greater<ThinJet>());
        double TTZToQQ_eventWeight = I_TTZToQQ_weight * TTZToQQWeight;

        h_Top_MET_dileptonPT->Fill(f_TTZToQQ_met, f_TTZToQQ_dileppt, TTZToQQ_eventWeight);
        h_Top_dileptonPT->Fill(f_TTZToQQ_dileppt, TTZToQQ_eventWeight);
        if (f_TTZToQQ_met < METcut)
        {
            continue;
        }
        h_Top_dileptonPT_cutedMET->Fill(f_TTZToQQ_dileppt, TTZToQQ_eventWeight);
        if (f_TTZToQQ_dileppt < DilepPTcut)
        {
            continue;
        }

        for (size_t ijet = 0; ijet < 2; ijet++)
        {
            h_Top_JetPT_ntrk->Fill(v_thinjet[ijet].GetPt(), v_thinjet[ijet].GetNtrk(), TTZToQQ_eventWeight);
            h_Top_ntrk_JetPT->Fill(v_thinjet[ijet].GetNtrk(), v_thinjet[ijet].GetPt(), TTZToQQ_eventWeight);

            h_Top_JetPT_JetEta->Fill(v_thinjet[ijet].GetPt(), v_thinjet[ijet].GetEta(), TTZToQQ_eventWeight);
            h_Top_ntrk_JetEta->Fill(v_thinjet[ijet].GetNtrk(), v_thinjet[ijet].GetEta(), TTZToQQ_eventWeight);

            h_Top_alpha_ntrk->Fill(v_thinjet[ijet].GetAlpha(), v_thinjet[ijet].GetNtrk(), TTZToQQ_eventWeight);
            h_Top_alpha_JetPT->Fill(v_thinjet[ijet].GetAlpha(), v_thinjet[ijet].GetPt(), TTZToQQ_eventWeight);
            h_Top_alpha_JetEta->Fill(v_thinjet[ijet].GetAlpha(), v_thinjet[ijet].GetEta(), TTZToQQ_eventWeight);

            h_Top_JetPT->Fill(v_thinjet[ijet].GetPt(), TTZToQQ_eventWeight);
            h_Top_ntrk->Fill(v_thinjet[ijet].GetNtrk(), TTZToQQ_eventWeight);

            // For TProfile
            h_ntrk_prof->Fill(v_thinjet[ijet].GetNtrk(), TTZToQQ_eventWeight);
            h_JetPt_prof->Fill(v_thinjet[ijet].GetPt(), TTZToQQ_eventWeight);
        }
    }
    TTree *T_TTZToLLNuNu_tree;
    Top_TTZToLLNuNufile->GetObject("T_tree", T_TTZToLLNuNu_tree);
    T_TTZToLLNuNu_tree->SetBranchAddress("I_weight", &I_TTZToLLNuNu_weight);
    T_TTZToLLNuNu_tree->SetBranchAddress("v_N_Tracks", &v_TTZToLLNuNu_nTrack);
    T_TTZToLLNuNu_tree->SetBranchAddress("f_Met", &f_TTZToLLNuNu_met);
    T_TTZToLLNuNu_tree->SetBranchAddress("f_dileptonPT", &f_TTZToLLNuNu_dileppt);
    T_TTZToLLNuNu_tree->SetBranchAddress("v_fakeJetPt", &v_TTZToLLNuNu_JetPT);
    T_TTZToLLNuNu_tree->SetBranchAddress("v_fakeJetEta", &v_TTZToLLNuNu_JetEta);
    T_TTZToLLNuNu_tree->SetBranchAddress("v_fakealpha", &v_TTZToLLNuNu_alpha);
    for (int evt = 0; evt < T_TTZToLLNuNu_tree->GetEntries(); evt++)
    {
        T_TTZToLLNuNu_tree->GetEntry(evt);
        vector<ThinJet> v_thinjet;
        v_thinjet.clear();
        if (v_TTZToLLNuNu_nTrack->size() < 2)
        {
            continue;
        }
        for (size_t i = 0; i < v_TTZToLLNuNu_nTrack->size(); i++)
        {
            v_thinjet.push_back(ThinJet((*v_TTZToLLNuNu_JetPT)[i], (*v_TTZToLLNuNu_JetEta)[i], (*v_TTZToLLNuNu_nTrack)[i], (*v_TTZToLLNuNu_alpha)[i]));
        }
        sort(v_thinjet.begin(), v_thinjet.end(), greater<ThinJet>());
        double TTZToLLNuNu_eventWeight = I_TTZToLLNuNu_weight * TTZToLLNuNuWeight;
        h_Top_MET_dileptonPT->Fill(f_TTZToLLNuNu_met, f_TTZToLLNuNu_dileppt, TTZToLLNuNu_eventWeight);
        h_Top_dileptonPT->Fill(f_TTZToLLNuNu_dileppt, TTZToLLNuNu_eventWeight);
        if (f_TTZToLLNuNu_met < METcut)
        {
            continue;
        }
        h_Top_dileptonPT_cutedMET->Fill(f_TTZToLLNuNu_dileppt, TTZToLLNuNu_eventWeight);
        if (f_TTZToLLNuNu_dileppt < DilepPTcut)
        {
            continue;
        }

        for (size_t ijet = 0; ijet < 2; ijet++)
        {
            h_Top_JetPT_ntrk->Fill(v_thinjet[ijet].GetPt(), v_thinjet[ijet].GetNtrk(), TTZToLLNuNu_eventWeight);
            h_Top_ntrk_JetPT->Fill(v_thinjet[ijet].GetNtrk(), v_thinjet[ijet].GetPt(), TTZToLLNuNu_eventWeight);

            h_Top_JetPT_JetEta->Fill(v_thinjet[ijet].GetPt(), v_thinjet[ijet].GetEta(), TTZToLLNuNu_eventWeight);
            h_Top_ntrk_JetEta->Fill(v_thinjet[ijet].GetNtrk(), v_thinjet[ijet].GetEta(), TTZToLLNuNu_eventWeight);

            h_Top_alpha_ntrk->Fill(v_thinjet[ijet].GetAlpha(), v_thinjet[ijet].GetNtrk(), TTZToLLNuNu_eventWeight);
            h_Top_alpha_JetPT->Fill(v_thinjet[ijet].GetAlpha(), v_thinjet[ijet].GetPt(), TTZToLLNuNu_eventWeight);
            h_Top_alpha_JetEta->Fill(v_thinjet[ijet].GetAlpha(), v_thinjet[ijet].GetEta(), TTZToLLNuNu_eventWeight);

            h_Top_JetPT->Fill(v_thinjet[ijet].GetPt(), TTZToLLNuNu_eventWeight);
            h_Top_ntrk->Fill(v_thinjet[ijet].GetNtrk(), TTZToLLNuNu_eventWeight);

            // For TProfile
            h_ntrk_prof->Fill(v_thinjet[ijet].GetNtrk(), TTZToLLNuNu_eventWeight);
            h_JetPt_prof->Fill(v_thinjet[ijet].GetPt(), TTZToLLNuNu_eventWeight);
        }
    }

    h_Top_JetPT_ntrk->SetTitle("Top to emu (Jet PT vs Track multiplicity)");
    h_Top_JetPT_JetEta->SetTitle("Top to emu (Jet PT vs Jet #eta)");
    h_Top_ntrk_JetEta->SetTitle("Top to emu (Track multiplicity vs Jet #eta)");

    h_Top_JetPT_ntrk->GetXaxis()->SetTitle("Jet PT");
    h_Top_JetPT_ntrk->GetYaxis()->SetTitle("Track multiplicity");

    h_Top_JetPT_JetEta->GetXaxis()->SetTitle("Jet PT");
    h_Top_JetPT_JetEta->GetYaxis()->SetTitle("Jet #eta");

    h_Top_ntrk_JetEta->GetXaxis()->SetTitle("Track multiplicity");
    h_Top_ntrk_JetEta->GetYaxis()->SetTitle("Jet #eta");

    h_Top_MET_dileptonPT->GetXaxis()->SetTitle("MET");
    h_Top_MET_dileptonPT->GetYaxis()->SetTitle("Di-leptonPT");

    h_Top_dileptonPT->SetLineWidth(2);
    h_Top_dileptonPT_cutedMET->SetLineWidth(2);
    h_Top_dileptonPT_cutedMET->SetLineColor(kRed + 1);

    h_Top_dileptonPT->GetXaxis()->SetTitle("Di-leptonPT");
    h_Top_dileptonPT->GetYaxis()->SetTitle("Nomalized");

    h_Top_alpha_ntrk->GetXaxis()->SetTitle("#alpha_{3D}");
    h_Top_alpha_ntrk->GetYaxis()->SetTitle("nTrk");

    h_Top_alpha_JetPT->GetXaxis()->SetTitle("#alpha_{3D}");
    h_Top_alpha_JetPT->GetYaxis()->SetTitle("Jet PT");

    h_Top_alpha_JetEta->GetXaxis()->SetTitle("#alpha_{3D}");
    h_Top_alpha_JetEta->GetYaxis()->SetTitle("Jet#eta");
    // h_Top_JetPT_ntrk->Draw("colz");

    h_Top_alpha_JetEta->Draw("colz");
    // h_Top_dileptonPT->DrawNormalized("h");
    // h_Top_dileptonPT_cutedMET->DrawNormalized("h same");

    /*
    TLegend *l0 = new TLegend(0.4, 0.4, 0.90, 0.80);
    l0->SetBorderSize(0);
    l0->SetFillStyle(0);
    l0->SetTextSize(0.03);
    l0->SetHeader("Top to e mu");
    l0->AddEntry(h_Top_dileptonPT, "Any MET", "l");
    l0->AddEntry(h_Top_dileptonPT_cutedMET, "Event MET > 130 GeV", "l");
    l0->Draw();*/

    gStyle->SetOptStat(0);
    // gPad->SetLogx();
    // h_ntrk_prof->Draw();
    double corr_MET_dileptonPT = h_Top_MET_dileptonPT->GetCorrelationFactor();
    double corr_JetPt_ntrk = h_Top_JetPT_ntrk->GetCorrelationFactor();
    double corr_ntrk_JetPt = h_Top_ntrk_JetPT->GetCorrelationFactor();
    double corr_JetPt_JetEta = h_Top_JetPT_JetEta->GetCorrelationFactor();
    double corr_ntrk_JetEta = h_Top_ntrk_JetEta->GetCorrelationFactor();

    double corr_alpha_ntrk = h_Top_alpha_ntrk->GetCorrelationFactor();
    double corr_alpha_JetPT = h_Top_alpha_JetPT->GetCorrelationFactor();
    double corr_alpha_JetEta = h_Top_alpha_JetEta->GetCorrelationFactor();
    


    cout << "correlation between MET and dilepton PT = " << corr_MET_dileptonPT << endl;
    cout << "correlation between Jet PT and ntrk = " << corr_JetPt_ntrk << endl;
    cout << "correlation between ntrk and Jet PT = " << corr_ntrk_JetPt << endl;
    cout << "correlation between Jet PT and JetEta = " << corr_JetPt_JetEta << endl;
    cout << "correlation between ntrk and JetEta = " << corr_ntrk_JetEta << endl;
    
    cout << "correlation between alpha and ntrk = " << corr_alpha_ntrk << endl;
    cout << "correlation between alpha and Jet PT = " << corr_alpha_JetPT << endl;
    cout << "correlation between alpha and JetEta = " << corr_alpha_JetEta << endl;
}