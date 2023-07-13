#include <iostream>
#include <sstream>
#include <TTree.h>
#include <TMath.h>
#include <TFile.h>
#include <TH3D.h>
#include <TROOT.h>
#include <TCanvas.h>
#include <TString.h>
#include <TLegend.h>
#include <TLatex.h>
#include <TAxis.h>
#include <TLine.h>
#include <TError.h>
#include "TLegend.h"
#include <vector>
#include <cstring>
#include "/home/kuanyu/Documents/CMS/Background_Estimate/lib/Cross_section.h"
using namespace std;

//------------------
// Calculate weight
//------------------
TFile *DYincli = new TFile("/home/kuanyu/Documents/root_file/Ztoee/2016BKGMC/DY/ee_DYincli.root");
TFile *DYHT100 = new TFile("/home/kuanyu/Documents/root_file/Ztoee/2016BKGMC/DY/ee_ht100.root");
TFile *DYHT200 = new TFile("/home/kuanyu/Documents/root_file/Ztoee/2016BKGMC/DY/ee_ht200.root");
TFile *DYHT400 = new TFile("/home/kuanyu/Documents/root_file/Ztoee/2016BKGMC/DY/ee_ht400.root");
TFile *DYHT600 = new TFile("/home/kuanyu/Documents/root_file/Ztoee/2016BKGMC/DY/ee_ht600.root");
TFile *DYHT800 = new TFile("/home/kuanyu/Documents/root_file/Ztoee/2016BKGMC/DY/ee_ht800.root");
TFile *DYHT1200 = new TFile("/home/kuanyu/Documents/root_file/Ztoee/2016BKGMC/DY/ee_ht1200.root");
TFile *DYHT2500 = new TFile("/home/kuanyu/Documents/root_file/Ztoee/2016BKGMC/DY/ee_ht2500.root");

TH1D *h_HT_eventCout = ((TH1D *)DYincli->Get("Event_Variable/h_HT_eventCout"));
TH1D *DYHT100_sumevt = ((TH1D *)DYHT100->Get("Event_Variable/h_totevent"));
TH1D *DYHT200_sumevt = ((TH1D *)DYHT200->Get("Event_Variable/h_totevent"));
TH1D *DYHT400_sumevt = ((TH1D *)DYHT400->Get("Event_Variable/h_totevent"));
TH1D *DYHT600_sumevt = ((TH1D *)DYHT600->Get("Event_Variable/h_totevent"));
TH1D *DYHT800_sumevt = ((TH1D *)DYHT800->Get("Event_Variable/h_totevent"));
TH1D *DYHT1200_sumevt = ((TH1D *)DYHT1200->Get("Event_Variable/h_totevent"));
TH1D *DYHT2500_sumevt = ((TH1D *)DYHT2500->Get("Event_Variable/h_totevent"));

double HT0_70_event = h_HT_eventCout->GetBinContent(2);
double HT70_100_event = h_HT_eventCout->GetBinContent(3);
double HT100_200_event = h_HT_eventCout->GetBinContent(4);
double HT200_400_event = h_HT_eventCout->GetBinContent(5);
double HT400_600_event = h_HT_eventCout->GetBinContent(6);
double HT600_800_event = h_HT_eventCout->GetBinContent(7);
double HT800_1200_event = h_HT_eventCout->GetBinContent(8);
double HT1200_2500_event = h_HT_eventCout->GetBinContent(9);
double HT2500_Inf_event = h_HT_eventCout->GetBinContent(10);

double DYHT100_totevt = DYHT100_sumevt->Integral();
double DYHT200_totevt = DYHT200_sumevt->Integral();
double DYHT400_totevt = DYHT400_sumevt->Integral();
double DYHT600_totevt = DYHT600_sumevt->Integral();
double DYHT800_totevt = DYHT800_sumevt->Integral();
double DYHT1200_totevt = DYHT1200_sumevt->Integral();
double DYHT2500_totevt = DYHT2500_sumevt->Integral();

//---------------------
// Define Weight
//---------------------

double HT0Weight = (GlobalConstants::Lumi2016) * (GlobalConstants::HT0CS / (HT0_70_event)) * 1000;
double HT70Weight = (GlobalConstants::Lumi2016) * (GlobalConstants::HT70CS / (HT70_100_event)) * 1000;
double HT100Weight = (GlobalConstants::Lumi2016) * (GlobalConstants::HT100CS / (DYHT100_totevt + HT100_200_event)) * 1000;
double HT200Weight = (GlobalConstants::Lumi2016) * (GlobalConstants::HT200CS / (DYHT200_totevt + HT200_400_event)) * 1000;
double HT400Weight = (GlobalConstants::Lumi2016) * (GlobalConstants::HT400CS / (DYHT400_totevt + HT400_600_event)) * 1000;
double HT600Weight = (GlobalConstants::Lumi2016) * (GlobalConstants::HT600CS / (DYHT600_totevt + HT600_800_event)) * 1000;
double HT800Weight = (GlobalConstants::Lumi2016) * (GlobalConstants::HT800CS / (DYHT800_totevt + HT800_1200_event)) * 1000;
double HT1200Weight = (GlobalConstants::Lumi2016) * (GlobalConstants::HT1200CS / (DYHT1200_totevt + HT1200_2500_event)) * 1000;
double HT2500Weight = (GlobalConstants::Lumi2016) * (GlobalConstants::HT2500CS / (DYHT2500_totevt + HT2500_Inf_event)) * 1000;

void for_inclusive_sample(float HT, float i_tmp, double Weight, TH1D *h_tmp)
{
    if (HT < 70)
    {
        h_tmp->Fill(i_tmp, HT0Weight);
    }
    else if (HT >= 70 && HT < 100)
    {
        h_tmp->Fill(i_tmp, HT70Weight);
    }
    else if (HT >= 100 && HT < 200)
    {
        h_tmp->Fill(i_tmp, HT100Weight);
    }
    else if (HT >= 200 && HT < 400)
    {
        h_tmp->Fill(i_tmp, HT200Weight);
    }
    else if (HT >= 400 && HT < 600)
    {
        h_tmp->Fill(i_tmp, HT400Weight);
    }
    else if (HT >= 600 && HT < 800)
    {
        h_tmp->Fill(i_tmp, HT600Weight);
    }
    else if (HT >= 800 && HT < 1200)
    {
        h_tmp->Fill(i_tmp, HT800Weight);
    }
    else if (HT >= 1200 && HT < 2500)
    {
        h_tmp->Fill(i_tmp, HT1200Weight);
    }
    else if (HT >= 2500)
    {
        h_tmp->Fill(i_tmp, HT2500Weight);
    }
}

void Scan_DY_bg(const char *scanMet_step = "tmp", TString outputfile = "output.root")
{
    //---------------------
    // dilepton cut
    //---------------------
    float Metcut = 0.;
    float dilepton_cut = atoi(scanMet_step) * 10;
    cout << "dilepton cut" << dilepton_cut << endl;

    TH1D *h_pass_bg = new TH1D("h_pass_bg", "", 110, 1, 110);
    h_pass_bg->Sumw2();

    TH1D *h_pass_Bg_nDilepPTcut = new TH1D("h_pass_Bg_nDilepPTcut", "", 110, 1, 110);
    h_pass_Bg_nDilepPTcut->Sumw2();

    float_t HT;

    float_t f_ht0_Met, f_ht70_Met, f_ht100_Met, f_ht200_Met, f_ht400_Met, f_ht600_Met, f_ht800_Met,
        f_ht1200_Met, f_ht2500_Met;

    float_t f_ht0_dilepPT, f_ht70_dilepPT, f_ht100_dilepPT, f_ht200_dilepPT, f_ht400_dilepPT, f_ht600_dilepPT, f_ht800_dilepPT,
        f_ht1200_dilepPT, f_ht2500_dilepPT;

    Int_t I_ht0_weight, I_ht70_weight, I_ht100_weight, I_ht200_weight, I_ht400_weight, I_ht600_weight,
        I_ht800_weight, I_ht1200_weight, I_ht2500_weight;

    vector<float> *v_ht0_alpha = new vector<float>();
    vector<float> *v_ht70_alpha = new vector<float>();
    vector<float> *v_ht100_alpha = new vector<float>();
    vector<float> *v_ht200_alpha = new vector<float>();
    vector<float> *v_ht400_alpha = new vector<float>();
    vector<float> *v_ht600_alpha = new vector<float>();
    vector<float> *v_ht800_alpha = new vector<float>();
    vector<float> *v_ht1200_alpha = new vector<float>();
    vector<float> *v_ht2500_alpha = new vector<float>();

    v_ht0_alpha->clear();
    v_ht70_alpha->clear();
    v_ht100_alpha->clear();
    v_ht200_alpha->clear();
    v_ht400_alpha->clear();
    v_ht600_alpha->clear();
    v_ht800_alpha->clear();
    v_ht1200_alpha->clear();
    v_ht2500_alpha->clear();

    TTree *T_inclusive;
    DYincli->GetObject("T_tree", T_inclusive);
    T_inclusive->SetBranchAddress("I_weight", &I_ht0_weight);
    T_inclusive->SetBranchAddress("f_HT", &HT);
    T_inclusive->SetBranchAddress("f_dileptonPT", &f_ht0_dilepPT);
    T_inclusive->SetBranchAddress("f_Met", &f_ht0_Met);
    for (int evt = 0; evt < T_inclusive->GetEntries(); evt++)
    {
        T_inclusive->GetEntry(evt);
        if (f_ht0_Met <= Metcut)
        {
            continue;
        }
        for_inclusive_sample(HT, atoi(scanMet_step), I_ht0_weight, h_pass_bg);
        //-------------------
        // Scan dilepton
        //-------------------
        if (f_ht0_dilepPT > dilepton_cut)
        {
            for_inclusive_sample(HT, atoi(scanMet_step),I_ht0_weight,  h_pass_Bg_nDilepPTcut);
        }
    }
    TTree *T_HT100;
    DYHT100->GetObject("T_tree", T_HT100);
    T_HT100->SetBranchAddress("I_weight", &I_ht100_weight);
    T_HT100->SetBranchAddress("f_Met", &f_ht100_Met);
    T_HT100->SetBranchAddress("f_dileptonPT", &f_ht100_dilepPT);
    T_HT100->SetBranchAddress("v_fakealpha", &v_ht100_alpha);
    for (int evt = 0; evt < T_HT100->GetEntries(); evt++)
    {
        T_HT100->GetEntry(evt);
        if (f_ht100_Met <= Metcut)
        {
            continue;
        }
        h_pass_bg->Fill(atoi(scanMet_step), I_ht100_weight * HT100Weight);
        //-------------------
        // Scan Met
        //-------------------
        // h_pass_DY->Fill(i, I_ht100_weight * HT100Weight);
        if (f_ht100_dilepPT > dilepton_cut)
        {
            h_pass_Bg_nDilepPTcut->Fill(atoi(scanMet_step), I_ht100_weight * HT100Weight);
        }
    }
    TTree *T_HT200;
    DYHT200->GetObject("T_tree", T_HT200);
    T_HT200->SetBranchAddress("I_weight", &I_ht200_weight);
    T_HT200->SetBranchAddress("f_Met", &f_ht200_Met);
    T_HT200->SetBranchAddress("f_dileptonPT", &f_ht200_dilepPT);
    T_HT200->SetBranchAddress("v_fakealpha", &v_ht200_alpha);
    for (int evt = 0; evt < T_HT200->GetEntries(); evt++)
    {
        T_HT200->GetEntry(evt);
        if (f_ht200_Met <= Metcut)
        {
            continue;
        }
        h_pass_bg->Fill(atoi(scanMet_step), I_ht200_weight * HT200Weight);
        //-------------------
        // Scan Met
        //-------------------
        // h_pass_DY->Fill(i, I_ht200_weight * HT200Weight);
        if (f_ht200_dilepPT > dilepton_cut)
        {
            h_pass_Bg_nDilepPTcut->Fill(atoi(scanMet_step), I_ht200_weight * HT200Weight);
        }
    }
    TTree *T_HT400;
    DYHT400->GetObject("T_tree", T_HT400);
    T_HT400->SetBranchAddress("I_weight", &I_ht400_weight);
    T_HT400->SetBranchAddress("f_Met", &f_ht400_Met);
    T_inclusive->SetBranchAddress("f_dileptonPT", &f_ht400_dilepPT);
    T_HT400->SetBranchAddress("v_fakealpha", &v_ht400_alpha);
    for (int evt = 0; evt < T_HT400->GetEntries(); evt++)
    {
        T_HT400->GetEntry(evt);
        if (f_ht400_Met <= Metcut)
        {
            continue;
        }
        h_pass_bg->Fill(atoi(scanMet_step), I_ht400_weight * HT400Weight);
        //-------------------
        // Scan Met
        //-------------------
        // h_pass_DY->Fill(i, I_ht400_weight * HT400Weight);
        if (f_ht400_dilepPT > dilepton_cut)
        {
            h_pass_Bg_nDilepPTcut->Fill(atoi(scanMet_step), I_ht400_weight * HT400Weight);
        }
    }
    TTree *T_HT600;
    DYHT600->GetObject("T_tree", T_HT600);
    T_HT600->SetBranchAddress("I_weight", &I_ht600_weight);
    T_HT600->SetBranchAddress("f_Met", &f_ht600_Met);
    T_HT600->SetBranchAddress("f_dileptonPT", &f_ht600_dilepPT);
    T_HT600->SetBranchAddress("v_fakealpha", &v_ht600_alpha);
    for (int evt = 0; evt < T_HT600->GetEntries(); evt++)
    {
        T_HT600->GetEntry(evt);
        if (f_ht600_Met <= Metcut)
        {
            continue;
        }
        h_pass_bg->Fill(atoi(scanMet_step), I_ht600_weight * HT600Weight);
        //-------------------
        // Scan Met
        //-------------------
        // h_pass_DY->Fill(i, I_ht600_weight * HT600Weight);
        if (f_ht600_dilepPT > dilepton_cut)
        {
            h_pass_Bg_nDilepPTcut->Fill(atoi(scanMet_step), I_ht600_weight * HT600Weight);
        }
    }
    TTree *T_HT800;
    DYHT800->GetObject("T_tree", T_HT800);
    T_HT800->SetBranchAddress("I_weight", &I_ht800_weight);
    T_HT800->SetBranchAddress("f_Met", &f_ht800_Met);
    T_HT800->SetBranchAddress("f_dileptonPT", &f_ht800_dilepPT);
    T_HT800->SetBranchAddress("v_fakealpha", &v_ht800_alpha);
    for (int evt = 0; evt < T_HT800->GetEntries(); evt++)
    {
        T_HT800->GetEntry(evt);
        if (f_ht800_Met <= Metcut)
        {
            continue;
        }
        h_pass_bg->Fill(atoi(scanMet_step), I_ht800_weight * HT800Weight);
        //-------------------
        // Scan Met
        //-------------------
        // h_pass_DY->Fill(i, I_ht800_weight * HT800Weight);
        if (f_ht800_dilepPT > dilepton_cut)
        {
            h_pass_Bg_nDilepPTcut->Fill(atoi(scanMet_step), I_ht800_weight * HT800Weight);
        }
    }
    TTree *T_HT1200;
    DYHT1200->GetObject("T_tree", T_HT1200);
    T_HT1200->SetBranchAddress("I_weight", &I_ht1200_weight);
    T_HT1200->SetBranchAddress("f_Met", &f_ht1200_Met);
    T_HT1200->SetBranchAddress("f_dileptonPT", &f_ht1200_dilepPT);
    T_HT1200->SetBranchAddress("v_fakealpha", &v_ht1200_alpha);
    for (int evt = 0; evt < T_HT1200->GetEntries(); evt++)
    {
        T_HT1200->GetEntry(evt);
        if (f_ht1200_Met <= Metcut)
        {
            continue;
        }
        h_pass_bg->Fill(atoi(scanMet_step), I_ht1200_weight * HT1200Weight);
        //-------------------
        // Scan Met
        //-------------------
        // h_pass_DY->Fill(i, I_ht1200_weight * HT1200Weight);
        if (f_ht1200_dilepPT > dilepton_cut)
        {
            h_pass_Bg_nDilepPTcut->Fill(atoi(scanMet_step), I_ht1200_weight * HT1200Weight);
        }
    }
    TTree *T_HT2500;
    DYHT2500->GetObject("T_tree", T_HT2500);
    T_HT2500->SetBranchAddress("I_weight", &I_ht2500_weight);
    T_HT2500->SetBranchAddress("f_Met", &f_ht2500_Met);
    T_HT2500->SetBranchAddress("f_dileptonPT", &f_ht2500_dilepPT);
    T_HT2500->SetBranchAddress("v_fakealpha", &v_ht2500_alpha);
    for (int evt = 0; evt < T_HT2500->GetEntries(); evt++)
    {
        T_HT2500->GetEntry(evt);
        if (f_ht2500_Met <= Metcut)
        {
            continue;
        }
        h_pass_bg->Fill(atoi(scanMet_step), I_ht2500_weight * HT2500Weight);
        //-------------------
        // Scan Met
        //-------------------
        // h_pass_DY->Fill(i, I_ht2500_weight * HT2500Weight);
        if (f_ht2500_dilepPT > dilepton_cut)
        {
            h_pass_Bg_nDilepPTcut->Fill(atoi(scanMet_step), I_ht2500_weight * HT2500Weight);
        }
    }

    TFile *outfile_HT0 = TFile::Open(outputfile, "RECREATE");
    h_pass_bg->Write();
    h_pass_Bg_nDilepPTcut->Write();
    outfile_HT0->Close();

    // cout << typeid(inputFile).name() << endl;
}

int main(int argc, char **argv)
{
    if (argc == 1)
    {
        Scan_DY_bg();
    }
    else if (argc == 3)
    {
        Scan_DY_bg(argv[1], argv[2]);
    }
    else
    {
        cout << "argc" << argc << endl;
        cout << "ERROR" << endl;
    }
}