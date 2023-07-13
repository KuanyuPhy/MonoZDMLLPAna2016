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
#include "./../../../lib/kuan_ana_utils.h"
using namespace std;

void uu_DY_punzi(const char *scanMet_step = "tmp", TString outputfile = "./output/tmp.root")
{

    MergeBFiles merge_bfiles;
    MergeWeight merge_weight(&merge_bfiles);

    //---------------------
    // Met cut
    //---------------------
    float metcut = atoi(scanMet_step) * 10;
    cout << "metcut" << metcut << endl;

    TH1D *h_pass_Bg = new TH1D("h_pass_Bg", "", 160, 0, 160);
    h_pass_Bg->Sumw2();

    TH1D *h_pass_Bg_nMetcut = new TH1D("h_pass_Bg_nMetcut", "", 160, 0, 160);
    h_pass_Bg_nMetcut->Sumw2();

    float_t HT;

    float_t f_ht0_Met, f_ht70_Met, f_ht100_Met, f_ht200_Met, f_ht400_Met, f_ht600_Met, f_ht800_Met,
        f_ht1200_Met, f_ht2500_Met;

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
    merge_bfiles.uu_DYincli->GetObject("T_tree", T_inclusive);
    T_inclusive->SetBranchAddress("I_weight", &I_ht0_weight);
    T_inclusive->SetBranchAddress("f_HT", &HT);
    T_inclusive->SetBranchAddress("f_Met", &f_ht0_Met);
    T_inclusive->SetBranchAddress("v_fakealpha", &v_ht0_alpha);
    for (int evt = 0; evt < T_inclusive->GetEntries(); evt++)
    {
        T_inclusive->GetEntry(evt);
        //-------------------
        // Scan Met
        //-------------------
        uu_for_inclusive_sample(HT, atoi(scanMet_step), merge_weight, I_ht0_weight, h_pass_Bg);
        if (f_ht0_Met > metcut)
        {
            uu_for_inclusive_sample(HT, atoi(scanMet_step), merge_weight, I_ht0_weight, h_pass_Bg_nMetcut);
        }
    }
    TTree *T_HT100;
    merge_bfiles.uu_DYHT100->GetObject("T_tree", T_HT100);
    T_HT100->SetBranchAddress("I_weight", &I_ht100_weight);
    T_HT100->SetBranchAddress("f_Met", &f_ht100_Met);
    T_HT100->SetBranchAddress("v_fakealpha", &v_ht100_alpha);
    for (int evt = 0; evt < T_HT100->GetEntries(); evt++)
    {
        T_HT100->GetEntry(evt);
        //-------------------
        // Scan Met
        //-------------------
        h_pass_Bg->Fill(atoi(scanMet_step), I_ht100_weight * merge_weight.uu_HT100Weight);
        if (f_ht100_Met > metcut)
        {
            h_pass_Bg_nMetcut->Fill(atoi(scanMet_step), I_ht100_weight * merge_weight.uu_HT100Weight);
        }
    }
    TTree *T_HT200;
    merge_bfiles.uu_DYHT200->GetObject("T_tree", T_HT200);
    T_HT200->SetBranchAddress("I_weight", &I_ht200_weight);
    T_HT200->SetBranchAddress("f_Met", &f_ht200_Met);
    T_HT200->SetBranchAddress("v_fakealpha", &v_ht200_alpha);
    for (int evt = 0; evt < T_HT200->GetEntries(); evt++)
    {
        T_HT200->GetEntry(evt);
        //-------------------
        // Scan Met
        //-------------------
        h_pass_Bg->Fill(atoi(scanMet_step), I_ht200_weight * merge_weight.uu_HT200Weight);
        if (f_ht200_Met > metcut)
        {
            h_pass_Bg_nMetcut->Fill(atoi(scanMet_step), I_ht200_weight * merge_weight.uu_HT200Weight);
        }
    }
    TTree *T_HT400;
    merge_bfiles.uu_DYHT400->GetObject("T_tree", T_HT400);
    T_HT400->SetBranchAddress("I_weight", &I_ht400_weight);
    T_HT400->SetBranchAddress("f_Met", &f_ht400_Met);
    T_HT400->SetBranchAddress("v_fakealpha", &v_ht400_alpha);
    for (int evt = 0; evt < T_HT400->GetEntries(); evt++)
    {
        T_HT400->GetEntry(evt);
        //-------------------
        // Scan Met
        //-------------------
        h_pass_Bg->Fill(atoi(scanMet_step), I_ht400_weight * merge_weight.uu_HT400Weight);
        if (f_ht400_Met > metcut)
        {
            h_pass_Bg_nMetcut->Fill(atoi(scanMet_step), I_ht400_weight * merge_weight.uu_HT400Weight);
        }
    }
    TTree *T_HT600;
    merge_bfiles.uu_DYHT600->GetObject("T_tree", T_HT600);
    T_HT600->SetBranchAddress("I_weight", &I_ht600_weight);
    T_HT600->SetBranchAddress("f_Met", &f_ht600_Met);
    T_HT600->SetBranchAddress("v_fakealpha", &v_ht600_alpha);
    for (int evt = 0; evt < T_HT600->GetEntries(); evt++)
    {
        T_HT600->GetEntry(evt);
        //-------------------
        // Scan Met
        //-------------------
        h_pass_Bg->Fill(atoi(scanMet_step), I_ht600_weight * merge_weight.uu_HT600Weight);
        if (f_ht600_Met > metcut)
        {
            h_pass_Bg_nMetcut->Fill(atoi(scanMet_step), I_ht600_weight * merge_weight.uu_HT600Weight);
        }
    }
    TTree *T_HT800;
    merge_bfiles.uu_DYHT800->GetObject("T_tree", T_HT800);
    T_HT800->SetBranchAddress("I_weight", &I_ht800_weight);
    T_HT800->SetBranchAddress("f_Met", &f_ht800_Met);
    T_HT800->SetBranchAddress("v_fakealpha", &v_ht800_alpha);
    for (int evt = 0; evt < T_HT800->GetEntries(); evt++)
    {
        T_HT800->GetEntry(evt);
        //-------------------
        // Scan Met
        //-------------------
        h_pass_Bg->Fill(atoi(scanMet_step), I_ht800_weight * merge_weight.uu_HT800Weight);
        if (f_ht800_Met > metcut)
        {
            h_pass_Bg_nMetcut->Fill(atoi(scanMet_step), I_ht800_weight * merge_weight.uu_HT800Weight);
        }
    }
    TTree *T_HT1200;
    merge_bfiles.uu_DYHT1200->GetObject("T_tree", T_HT1200);
    T_HT1200->SetBranchAddress("I_weight", &I_ht1200_weight);
    T_HT1200->SetBranchAddress("f_Met", &f_ht1200_Met);
    T_HT1200->SetBranchAddress("v_fakealpha", &v_ht1200_alpha);
    for (int evt = 0; evt < T_HT1200->GetEntries(); evt++)
    {
        T_HT1200->GetEntry(evt);
        //-------------------
        // Scan Met
        //-------------------
        h_pass_Bg->Fill(atoi(scanMet_step), I_ht1200_weight * merge_weight.uu_HT1200Weight);
        if (f_ht1200_Met > metcut)
        {
            h_pass_Bg_nMetcut->Fill(atoi(scanMet_step), I_ht1200_weight * merge_weight.uu_HT1200Weight);
        }
    }
    TTree *T_HT2500;
    merge_bfiles.uu_DYHT2500->GetObject("T_tree", T_HT2500);
    T_HT2500->SetBranchAddress("I_weight", &I_ht2500_weight);
    T_HT2500->SetBranchAddress("f_Met", &f_ht2500_Met);
    T_HT2500->SetBranchAddress("v_fakealpha", &v_ht2500_alpha);
    for (int evt = 0; evt < T_HT2500->GetEntries(); evt++)
    {
        T_HT2500->GetEntry(evt);
        //-------------------
        // Scan Met
        //-------------------
        h_pass_Bg->Fill(atoi(scanMet_step), I_ht2500_weight * merge_weight.uu_HT2500Weight);
        if (f_ht2500_Met > metcut)
        {
            h_pass_Bg_nMetcut->Fill(atoi(scanMet_step), I_ht2500_weight * merge_weight.uu_HT2500Weight);
        }
    }

    TFile *outfile_HT0 = TFile::Open(outputfile, "RECREATE");
    h_pass_Bg->Write();
    h_pass_Bg_nMetcut->Write();
    outfile_HT0->Close();
}
int main(int argc, char *argv[])
{
    if (argc == 3)
    {
        uu_DY_punzi(argv[1], argv[2]);
    }
    else
    {
        cout << "ERROR" << endl;
    }
}