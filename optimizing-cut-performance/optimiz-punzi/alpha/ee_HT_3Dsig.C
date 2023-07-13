#include "TFile.h"
#include <iostream>
#include "TTree.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <TH1D.h>
#include <string>
#include <TAttLine.h>
#include <TStyle.h>
#include <TCanvas.h>
#include "./../../../lib/Cross_section.h"
#include "./../../../lib/kuan_ana_utils.h"
using namespace std;

void ee_HT_3Dsig()
{
    /*Open source root file*/
    MergeBFiles merge_bfiles;
    MergeWeight merge_weight(&merge_bfiles);

    TH1D *h_DY_3Dsig = new TH1D("h_DY_3Dsig", "", 200, -10., 10.);
    TH1D *h_bg_alpha3 = new TH1D("h_bg_alpha3", "", 20, 0, 1.);

    float_t HT;

    float_t f_ht0_Met, f_ht70_Met, f_ht100_Met, f_ht200_Met, f_ht400_Met, f_ht600_Met, f_ht800_Met,
        f_ht1200_Met, f_ht2500_Met;

    Int_t I_ht0_nJet, I_ht70_nJet, I_ht100_nJet, I_ht200_nJet, I_ht400_nJet, I_ht600_nJet,
        I_ht800_nJet, I_ht1200_nJet, I_ht2500_nJet;

    Int_t I_ht0_weight, I_ht70_weight, I_ht100_weight, I_ht200_weight, I_ht400_weight, I_ht600_weight,
        I_ht800_weight, I_ht1200_weight, I_ht2500_weight;

    vector<float> *v_ht0_log3Dsig = new vector<float>();
    vector<float> *v_ht70_log3Dsig = new vector<float>();
    vector<float> *v_ht100_log3Dsig = new vector<float>();
    vector<float> *v_ht200_log3Dsig = new vector<float>();
    vector<float> *v_ht400_log3Dsig = new vector<float>();
    vector<float> *v_ht600_log3Dsig = new vector<float>();
    vector<float> *v_ht800_log3Dsig = new vector<float>();
    vector<float> *v_ht1200_log3Dsig = new vector<float>();
    vector<float> *v_ht2500_log3Dsig = new vector<float>();

    v_ht0_log3Dsig->clear();
    v_ht70_log3Dsig->clear();
    v_ht100_log3Dsig->clear();
    v_ht200_log3Dsig->clear();
    v_ht400_log3Dsig->clear();
    v_ht600_log3Dsig->clear();
    v_ht800_log3Dsig->clear();
    v_ht1200_log3Dsig->clear();
    v_ht2500_log3Dsig->clear();

    vector<float> *v_ht0_alpha3 = new vector<float>();
    vector<float> *v_ht70_alpha3 = new vector<float>();
    vector<float> *v_ht100_alpha3 = new vector<float>();
    vector<float> *v_ht200_alpha3 = new vector<float>();
    vector<float> *v_ht400_alpha3 = new vector<float>();
    vector<float> *v_ht600_alpha3 = new vector<float>();
    vector<float> *v_ht800_alpha3 = new vector<float>();
    vector<float> *v_ht1200_alpha3 = new vector<float>();
    vector<float> *v_ht2500_alpha3 = new vector<float>();

    v_ht0_alpha3->clear();
    v_ht70_alpha3->clear();
    v_ht100_alpha3->clear();
    v_ht200_alpha3->clear();
    v_ht400_alpha3->clear();
    v_ht600_alpha3->clear();
    v_ht800_alpha3->clear();
    v_ht1200_alpha3->clear();
    v_ht2500_alpha3->clear();

    double METcut = 140.;

    TTree *T_inclusive;
    merge_bfiles.ee_DYincli->GetObject("T_tree", T_inclusive);
    T_inclusive->SetBranchAddress("I_weight", &I_ht0_weight);
    T_inclusive->SetBranchAddress("f_HT", &HT);
    T_inclusive->SetBranchAddress("f_Met", &f_ht0_Met);
    T_inclusive->SetBranchAddress("I_nJets", &I_ht0_nJet);
    T_inclusive->SetBranchAddress("v_Chi3Dlog", &v_ht0_log3Dsig);
    T_inclusive->SetBranchAddress("v_fakealpha3", &v_ht0_alpha3);
    for (int evt = 0; evt < T_inclusive->GetEntries(); evt++)
    {
        T_inclusive->GetEntry(evt);

        for (int itrk = 0; itrk < v_ht0_log3Dsig->size(); itrk++)
        {
            ee_for_inclusive_sample(HT, (*v_ht0_log3Dsig)[itrk], merge_weight, I_ht0_weight, h_DY_3Dsig);
        }

        if (f_ht0_Met <= METcut)
        {
            continue;
        }
        for (int ijet = 0; ijet < v_ht0_alpha3->size(); ijet++)
        {
            ee_for_inclusive_sample(HT, (*v_ht0_alpha3)[ijet], merge_weight, I_ht0_weight, h_bg_alpha3);
        }
    }

    TTree *T_HT100;
    merge_bfiles.ee_DYHT100->GetObject("T_tree", T_HT100);
    T_HT100->SetBranchAddress("I_weight", &I_ht100_weight);
    T_HT100->SetBranchAddress("f_Met", &f_ht100_Met);
    T_HT100->SetBranchAddress("I_nJets", &I_ht100_nJet);
    T_HT100->SetBranchAddress("v_Chi3Dlog", &v_ht100_log3Dsig);
    T_HT100->SetBranchAddress("v_fakealpha3", &v_ht100_alpha3);
    for (int evt = 0; evt < T_HT100->GetEntries(); evt++)
    {
        T_HT100->GetEntry(evt);

        for (int itrk = 0; itrk < v_ht100_log3Dsig->size(); itrk++)
        {
            h_DY_3Dsig->Fill((*v_ht100_log3Dsig)[itrk], I_ht100_weight * merge_weight.ee_HT100Weight);
        }

        if (f_ht100_Met <= METcut)
        {
            continue;
        }
        for (int ijet = 0; ijet < v_ht100_alpha3->size(); ijet++)
        {
            h_bg_alpha3->Fill((*v_ht100_alpha3)[ijet], I_ht100_weight * merge_weight.ee_HT100Weight);
        }
    }
    TTree *T_HT200;
    merge_bfiles.ee_DYHT200->GetObject("T_tree", T_HT200);
    T_HT200->SetBranchAddress("I_weight", &I_ht200_weight);
    T_HT200->SetBranchAddress("f_Met", &f_ht200_Met);
    T_HT200->SetBranchAddress("I_nJets", &I_ht200_nJet);
    T_HT200->SetBranchAddress("v_Chi3Dlog", &v_ht200_log3Dsig);
    T_HT200->SetBranchAddress("v_fakealpha3", &v_ht200_alpha3);
    for (int evt = 0; evt < T_HT200->GetEntries(); evt++)
    {
        T_HT200->GetEntry(evt);

        for (int itrk = 0; itrk < v_ht200_log3Dsig->size(); itrk++)
        {
            h_DY_3Dsig->Fill((*v_ht200_log3Dsig)[itrk], I_ht200_weight * merge_weight.ee_HT200Weight);
        }
        if (f_ht200_Met <= METcut)
        {
            continue;
        }

        for (int ijet = 0; ijet < v_ht200_alpha3->size(); ijet++)
        {
            h_bg_alpha3->Fill((*v_ht200_alpha3)[ijet], I_ht200_weight * merge_weight.ee_HT200Weight);
        }
    }

    TTree *T_HT400;
    merge_bfiles.ee_DYHT400->GetObject("T_tree", T_HT400);
    T_HT400->SetBranchAddress("I_weight", &I_ht400_weight);
    T_HT400->SetBranchAddress("f_Met", &f_ht400_Met);
    T_HT400->SetBranchAddress("I_nJets", &I_ht400_nJet);
    T_HT400->SetBranchAddress("v_Chi3Dlog", &v_ht400_log3Dsig);
    T_HT400->SetBranchAddress("v_fakealpha3", &v_ht400_alpha3);
    for (int evt = 0; evt < T_HT400->GetEntries(); evt++)
    {
        T_HT400->GetEntry(evt);

        for (int itrk = 0; itrk < v_ht400_log3Dsig->size(); itrk++)
        {
            h_DY_3Dsig->Fill((*v_ht400_log3Dsig)[itrk], I_ht400_weight * merge_weight.ee_HT400Weight);
        }

        if (f_ht400_Met <= METcut)
        {
            continue;
        }

        for (int ijet = 0; ijet < v_ht400_alpha3->size(); ijet++)
        {
            h_bg_alpha3->Fill((*v_ht400_alpha3)[ijet], I_ht400_weight * merge_weight.ee_HT400Weight);
        }
    }
    TTree *T_HT600;
    merge_bfiles.ee_DYHT600->GetObject("T_tree", T_HT600);
    T_HT600->SetBranchAddress("I_weight", &I_ht600_weight);
    T_HT600->SetBranchAddress("f_Met", &f_ht600_Met);
    T_HT600->SetBranchAddress("I_nJets", &I_ht600_nJet);
    T_HT600->SetBranchAddress("v_Chi3Dlog", &v_ht600_log3Dsig);
    T_HT600->SetBranchAddress("v_fakealpha3", &v_ht600_alpha3);
    for (int evt = 0; evt < T_HT600->GetEntries(); evt++)
    {
        T_HT600->GetEntry(evt);

        for (int itrk = 0; itrk < v_ht600_log3Dsig->size(); itrk++)
        {
            h_DY_3Dsig->Fill((*v_ht600_log3Dsig)[itrk], I_ht600_weight * merge_weight.ee_HT600Weight);
        }

        if (f_ht600_Met <= METcut)
        {
            continue;
        }

        for (int ijet = 0; ijet < v_ht600_alpha3->size(); ijet++)
        {
            h_bg_alpha3->Fill((*v_ht600_alpha3)[ijet], I_ht600_weight * merge_weight.ee_HT600Weight);
        }
    }
    TTree *T_HT800;
    merge_bfiles.ee_DYHT800->GetObject("T_tree", T_HT800);
    T_HT800->SetBranchAddress("I_weight", &I_ht800_weight);
    T_HT800->SetBranchAddress("f_Met", &f_ht800_Met);
    T_HT800->SetBranchAddress("I_nJets", &I_ht800_nJet);
    T_HT800->SetBranchAddress("v_Chi3Dlog", &v_ht800_log3Dsig);
    T_HT800->SetBranchAddress("v_fakealpha3", &v_ht800_alpha3);
    for (int evt = 0; evt < T_HT800->GetEntries(); evt++)
    {
        T_HT800->GetEntry(evt);

        for (int itrk = 0; itrk < v_ht800_log3Dsig->size(); itrk++)
        {
            h_DY_3Dsig->Fill((*v_ht800_log3Dsig)[itrk], I_ht800_weight * merge_weight.ee_HT800Weight);
        }
        if (f_ht800_Met <= METcut)
        {
            continue;
        }
        for (int ijet = 0; ijet < v_ht800_alpha3->size(); ijet++)
        {
            h_bg_alpha3->Fill((*v_ht800_alpha3)[ijet], I_ht800_weight * merge_weight.ee_HT800Weight);
        }
    }
    TTree *T_HT1200;
    merge_bfiles.ee_DYHT1200->GetObject("T_tree", T_HT1200);
    T_HT1200->SetBranchAddress("I_weight", &I_ht1200_weight);
    T_HT1200->SetBranchAddress("f_Met", &f_ht1200_Met);
    T_HT1200->SetBranchAddress("I_nJets", &I_ht1200_nJet);
    T_HT1200->SetBranchAddress("v_Chi3Dlog", &v_ht1200_log3Dsig);
    T_HT1200->SetBranchAddress("v_fakealpha3", &v_ht1200_alpha3);
    for (int evt = 0; evt < T_HT1200->GetEntries(); evt++)
    {
        T_HT1200->GetEntry(evt);

        for (int itrk = 0; itrk < v_ht1200_log3Dsig->size(); itrk++)
        {
            h_DY_3Dsig->Fill((*v_ht1200_log3Dsig)[itrk], I_ht1200_weight * merge_weight.ee_HT1200Weight);
        }
        if (f_ht1200_Met <= METcut)
        {
            continue;
        }
        for (int ijet = 0; ijet < v_ht1200_alpha3->size(); ijet++)
        {
            h_bg_alpha3->Fill((*v_ht1200_alpha3)[ijet], I_ht1200_weight * merge_weight.ee_HT1200Weight);
        }
    }
    TTree *T_HT2500;
    merge_bfiles.ee_DYHT2500->GetObject("T_tree", T_HT2500);
    T_HT2500->SetBranchAddress("I_weight", &I_ht2500_weight);
    T_HT2500->SetBranchAddress("f_Met", &f_ht2500_Met);
    T_HT2500->SetBranchAddress("I_nJets", &I_ht2500_nJet);
    T_HT2500->SetBranchAddress("v_Chi3Dlog", &v_ht2500_log3Dsig);
    T_HT2500->SetBranchAddress("v_fakealpha3", &v_ht2500_alpha3);
    for (int evt = 0; evt < T_HT2500->GetEntries(); evt++)
    {
        T_HT2500->GetEntry(evt);

        for (int itrk = 0; itrk < v_ht2500_log3Dsig->size(); itrk++)
        {
            h_DY_3Dsig->Fill((*v_ht2500_log3Dsig)[itrk], I_ht2500_weight * merge_weight.ee_HT2500Weight);
        }
        if (f_ht2500_Met <= METcut)
        {
            continue;
        }
        for (int ijet = 0; ijet < v_ht2500_alpha3->size(); ijet++)
        {
            h_bg_alpha3->Fill((*v_ht2500_alpha3)[ijet], I_ht2500_weight * merge_weight.ee_HT2500Weight);
        }
    }
    TString outputfile = "./ee_HT3Dsig.root";

    TFile *outfile_HT0 = TFile::Open(outputfile, "RECREATE");
    h_DY_3Dsig->Write();
    h_bg_alpha3->Write();
    outfile_HT0->Close();
}
