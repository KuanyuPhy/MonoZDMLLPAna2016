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
#include "./../../../lib/Cross_section.h"
#include "./../../../lib/kuan_ana_utils.h"
using namespace std;

void uu_HT_alpha(const char *scanalpha_step = "tmp", TString outputfile = "./output/tmp.root")
// void uu_HT_alpha()
{
    double alphacut = atoi(scanalpha_step) * 0.05;

    /*Open source root file*/
    MergeBFiles merge_bfiles;
    MergeWeight merge_weight(&merge_bfiles);

    // int sumstep = 20;
    double METcut = 120.;

    // TH1D *h_Bg_nJet_cut[sumstep];
    // TH1D *h_Bg_nJet_[sumstep];
    // TH1D *h_Bg_alpha = new TH1D("h_Bg_alpha", "", 20, 0, 1);

    TH1D *h_Bg_nJet = new TH1D("h_Bg_nJet", "", 30, 0., 30.);
    TH1D *h_Bg_nJet_cuted = new TH1D("h_Bg_nJet_cuted", "at least two jets pass alpha cut", 30, 0., 30.);

    /*for (int i = 0; i < 20; i++)
    {
        h_Bg_nJet_[i] = new TH1D(Form("h_Bg_nJet_%i", i + 1), "", 30, 0, 30);
        h_Bg_nJet_cut[i] = new TH1D(Form("h_Bg_nJet_cut_%i", i + 1), "", 30, 0, 30);
    }*/

    float_t HT;

    float_t f_ht0_Met, f_ht70_Met, f_ht100_Met, f_ht200_Met, f_ht400_Met, f_ht600_Met, f_ht800_Met,
        f_ht1200_Met, f_ht2500_Met;

    Int_t I_ht0_nJet, I_ht70_nJet, I_ht100_nJet, I_ht200_nJet, I_ht400_nJet, I_ht600_nJet,
        I_ht800_nJet, I_ht1200_nJet, I_ht2500_nJet;

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

    vector<float> *v_ht0_jetcsv = new vector<float>();
    vector<float> *v_ht70_jetcsv = new vector<float>();
    vector<float> *v_ht100_jetcsv = new vector<float>();
    vector<float> *v_ht200_jetcsv = new vector<float>();
    vector<float> *v_ht400_jetcsv = new vector<float>();
    vector<float> *v_ht600_jetcsv = new vector<float>();
    vector<float> *v_ht800_jetcsv = new vector<float>();
    vector<float> *v_ht1200_jetcsv = new vector<float>();
    vector<float> *v_ht2500_jetcsv = new vector<float>();

    v_ht0_jetcsv->clear();
    v_ht70_jetcsv->clear();
    v_ht100_jetcsv->clear();
    v_ht200_jetcsv->clear();
    v_ht400_jetcsv->clear();
    v_ht600_jetcsv->clear();
    v_ht800_jetcsv->clear();
    v_ht1200_jetcsv->clear();
    v_ht2500_jetcsv->clear();

    vector<float> *v_ht0_Jethadronflavor = new vector<float>();
    vector<float> *v_ht70_Jethadronflavor = new vector<float>();
    vector<float> *v_ht100_Jethadronflavor = new vector<float>();
    vector<float> *v_ht200_Jethadronflavor = new vector<float>();
    vector<float> *v_ht400_Jethadronflavor = new vector<float>();
    vector<float> *v_ht600_Jethadronflavor = new vector<float>();
    vector<float> *v_ht800_Jethadronflavor = new vector<float>();
    vector<float> *v_ht1200_Jethadronflavor = new vector<float>();
    vector<float> *v_ht2500_Jethadronflavor = new vector<float>();

    v_ht0_Jethadronflavor->clear();
    v_ht70_Jethadronflavor->clear();
    v_ht100_Jethadronflavor->clear();
    v_ht200_Jethadronflavor->clear();
    v_ht400_Jethadronflavor->clear();
    v_ht600_Jethadronflavor->clear();
    v_ht800_Jethadronflavor->clear();
    v_ht1200_Jethadronflavor->clear();
    v_ht2500_Jethadronflavor->clear();

    TTree *T_inclusive;
    merge_bfiles.uu_DYincli->GetObject("T_tree", T_inclusive);
    T_inclusive->SetBranchAddress("I_weight", &I_ht0_weight);
    T_inclusive->SetBranchAddress("f_HT", &HT);
    T_inclusive->SetBranchAddress("f_Met", &f_ht0_Met);
    T_inclusive->SetBranchAddress("I_nJets", &I_ht0_nJet);
    T_inclusive->SetBranchAddress("v_fakealpha", &v_ht0_alpha);
    T_inclusive->SetBranchAddress("f_thinjetCSV", &v_ht0_jetcsv);
    T_inclusive->SetBranchAddress("v_fakeJethadronflavor", &v_ht0_Jethadronflavor);
    cout << "alphacut = " << alphacut << endl;
    for (int evt = 0; evt < T_inclusive->GetEntries(); evt++)
    {
        T_inclusive->GetEntry(evt);

        if (f_ht0_Met <= METcut)
        {
            continue;
        }

        int jet_passalpha_cut = 0;
        for (int ijet = 0; ijet < v_ht0_alpha->size(); ijet++)
        {
            // for_inclusive_sample(HT, (*v_ht0_alpha)[i], merge_weight, I_ht0_weight, h_Bg_alpha);
            if ((*v_ht0_alpha)[ijet] < alphacut)
            {
                jet_passalpha_cut++;
            }
        } /*End of alpha loop*/

        // if (jet_passalpha_cut == 0)
        // {
        //     continue;
        // }

        uu_for_inclusive_sample(HT, jet_passalpha_cut, merge_weight, I_ht0_weight, h_Bg_nJet);
        if (jet_passalpha_cut < 2)
        {
            continue;
        }
        // for_inclusive_sample(HT, I_ht0_nJet, I_ht0_weight, h_Bg_nJet_cut);
        uu_for_inclusive_sample(HT, jet_passalpha_cut, merge_weight, I_ht0_weight, h_Bg_nJet_cuted);
    }

    TTree *T_HT100;
    merge_bfiles.uu_DYHT100->GetObject("T_tree", T_HT100);
    T_HT100->SetBranchAddress("I_weight", &I_ht100_weight);
    T_HT100->SetBranchAddress("f_Met", &f_ht100_Met);
    T_HT100->SetBranchAddress("I_nJets", &I_ht100_nJet);
    T_HT100->SetBranchAddress("v_fakealpha", &v_ht100_alpha);
    T_HT100->SetBranchAddress("f_thinjetCSV", &v_ht100_jetcsv);
    T_HT100->SetBranchAddress("v_fakeJethadronflavor", &v_ht100_Jethadronflavor);
    for (int evt = 0; evt < T_HT100->GetEntries(); evt++)
    {
        T_HT100->GetEntry(evt);

        if (f_ht100_Met <= METcut)
        {
            continue;
        }

        int jet_passalpha_cut = 0;
        for (int ijet = 0; ijet < v_ht100_alpha->size(); ijet++)
        {
            // h_Bg_alpha->Fill((*v_ht100_alpha)[i], I_ht100_weight * merge_weight.HT100Weight);
            if ((*v_ht100_alpha)[ijet] < alphacut)
            {
                jet_passalpha_cut++;
            }
        } /*End of alpha loop*/

        // if (jet_passalpha_cut == 0)
        // {
        //     continue;
        // }

        h_Bg_nJet->Fill(jet_passalpha_cut, I_ht100_weight * merge_weight.uu_HT100Weight);
        if (jet_passalpha_cut < 2)
        {
            continue;
        }
        h_Bg_nJet_cuted->Fill(jet_passalpha_cut, I_ht100_weight * merge_weight.uu_HT100Weight);
    }
    TTree *T_HT200;
    merge_bfiles.uu_DYHT200->GetObject("T_tree", T_HT200);
    T_HT200->SetBranchAddress("I_weight", &I_ht200_weight);
    T_HT200->SetBranchAddress("f_Met", &f_ht200_Met);
    T_HT200->SetBranchAddress("I_nJets", &I_ht200_nJet);
    T_HT200->SetBranchAddress("v_fakealpha", &v_ht200_alpha);
    T_HT200->SetBranchAddress("f_thinjetCSV", &v_ht200_jetcsv);
    T_HT200->SetBranchAddress("v_fakeJethadronflavor", &v_ht200_Jethadronflavor);
    for (int evt = 0; evt < T_HT200->GetEntries(); evt++)
    {
        T_HT200->GetEntry(evt);

        if (f_ht200_Met <= METcut)
        {
            continue;
        }

        int jet_passalpha_cut = 0;
        for (int ijet = 0; ijet < v_ht200_alpha->size(); ijet++)
        {
            // h_Bg_alpha->Fill((*v_ht200_alpha)[i], I_ht200_weight * merge_weight.HT200Weight);
            if ((*v_ht200_alpha)[ijet] < alphacut)
            {
                jet_passalpha_cut++;
            }
        }

        // if (jet_passalpha_cut == 0)
        // {
        //     continue;
        // }

        h_Bg_nJet->Fill(jet_passalpha_cut, I_ht200_weight * merge_weight.uu_HT200Weight);
        if (jet_passalpha_cut < 2)
        {
            continue;
        }
        h_Bg_nJet_cuted->Fill(jet_passalpha_cut, I_ht200_weight * merge_weight.uu_HT200Weight);
    }
    TTree *T_HT400;
    merge_bfiles.uu_DYHT400->GetObject("T_tree", T_HT400);
    T_HT400->SetBranchAddress("I_weight", &I_ht400_weight);
    T_HT400->SetBranchAddress("f_Met", &f_ht400_Met);
    T_HT400->SetBranchAddress("I_nJets", &I_ht400_nJet);
    T_HT400->SetBranchAddress("v_fakealpha", &v_ht400_alpha);
    T_HT400->SetBranchAddress("f_thinjetCSV", &v_ht400_jetcsv);
    T_HT400->SetBranchAddress("v_fakeJethadronflavor", &v_ht400_Jethadronflavor);
    for (int evt = 0; evt < T_HT400->GetEntries(); evt++)
    {
        T_HT400->GetEntry(evt);

        if (f_ht400_Met <= METcut)
        {
            continue;
        }

        int jet_passalpha_cut = 0;
        for (int ijet = 0; ijet < v_ht400_alpha->size(); ijet++)
        {
            // h_Bg_alpha->Fill((*v_ht400_alpha)[i], I_ht400_weight * merge_weight.HT400Weight);
            if ((*v_ht400_alpha)[ijet] < alphacut)
            {
                jet_passalpha_cut++;
            }
        }

        // if (jet_passalpha_cut == 0)
        // {
        //     continue;
        // }

        h_Bg_nJet->Fill(jet_passalpha_cut, I_ht400_weight * merge_weight.uu_HT400Weight);
        if (jet_passalpha_cut < 2)
        {
            continue;
        }
        h_Bg_nJet_cuted->Fill(jet_passalpha_cut, I_ht400_weight * merge_weight.uu_HT400Weight);
    }
    TTree *T_HT600;
    merge_bfiles.uu_DYHT600->GetObject("T_tree", T_HT600);
    T_HT600->SetBranchAddress("I_weight", &I_ht600_weight);
    T_HT600->SetBranchAddress("f_Met", &f_ht600_Met);
    T_HT600->SetBranchAddress("I_nJets", &I_ht600_nJet);
    T_HT600->SetBranchAddress("v_fakealpha", &v_ht600_alpha);
    T_HT600->SetBranchAddress("f_thinjetCSV", &v_ht600_jetcsv);
    T_HT600->SetBranchAddress("v_fakeJethadronflavor", &v_ht600_Jethadronflavor);
    for (int evt = 0; evt < T_HT600->GetEntries(); evt++)
    {
        T_HT600->GetEntry(evt);

        if (f_ht600_Met <= METcut)
        {
            continue;
        }

        int jet_passalpha_cut = 0;
        for (int ijet = 0; ijet < v_ht600_alpha->size(); ijet++)
        {
            // h_Bg_alpha->Fill((*v_ht600_alpha)[i], I_ht600_weight * merge_weight.HT600Weight);
            if ((*v_ht600_alpha)[ijet] < alphacut)
            {
                jet_passalpha_cut++;
            }
        }

        // if (jet_passalpha_cut == 0)
        // {
        //     continue;
        // }

        h_Bg_nJet->Fill(jet_passalpha_cut, I_ht600_weight * merge_weight.uu_HT600Weight);

        if (jet_passalpha_cut < 2)
        {
            continue;
        }
        h_Bg_nJet_cuted->Fill(jet_passalpha_cut, I_ht600_weight * merge_weight.uu_HT600Weight);
    }
    TTree *T_HT800;
    merge_bfiles.uu_DYHT800->GetObject("T_tree", T_HT800);
    T_HT800->SetBranchAddress("I_weight", &I_ht800_weight);
    T_HT800->SetBranchAddress("f_Met", &f_ht800_Met);
    T_HT800->SetBranchAddress("I_nJets", &I_ht800_nJet);
    T_HT800->SetBranchAddress("v_fakealpha", &v_ht800_alpha);
    T_HT800->SetBranchAddress("f_thinjetCSV", &v_ht800_jetcsv);
    T_HT800->SetBranchAddress("v_fakeJethadronflavor", &v_ht800_Jethadronflavor);
    for (int evt = 0; evt < T_HT800->GetEntries(); evt++)
    {
        T_HT800->GetEntry(evt);

        if (f_ht800_Met <= METcut)
        {
            continue;
        }

        int jet_passalpha_cut = 0;
        for (int ijet = 0; ijet < v_ht800_alpha->size(); ijet++)
        {
            // h_Bg_alpha->Fill((*v_ht800_alpha)[i], I_ht800_weight * merge_weight.HT800Weight);
            if ((*v_ht800_alpha)[ijet] < alphacut)
            {
                jet_passalpha_cut++;
            }
        }

        /*if (jet_passalpha_cut == 0)
        {
            continue;
        }*/

        h_Bg_nJet->Fill(jet_passalpha_cut, I_ht800_weight * merge_weight.uu_HT800Weight);
        if (jet_passalpha_cut < 2)
        {
            continue;
        }
        h_Bg_nJet_cuted->Fill(jet_passalpha_cut, I_ht800_weight * merge_weight.uu_HT800Weight);
    }
    TTree *T_HT1200;
    merge_bfiles.uu_DYHT1200->GetObject("T_tree", T_HT1200);
    T_HT1200->SetBranchAddress("I_weight", &I_ht1200_weight);
    T_HT1200->SetBranchAddress("f_Met", &f_ht1200_Met);
    T_HT1200->SetBranchAddress("I_nJets", &I_ht1200_nJet);
    T_HT1200->SetBranchAddress("v_fakealpha", &v_ht1200_alpha);
    T_HT1200->SetBranchAddress("f_thinjetCSV", &v_ht1200_jetcsv);
    T_HT1200->SetBranchAddress("v_fakeJethadronflavor", &v_ht1200_Jethadronflavor);
    for (int evt = 0; evt < T_HT1200->GetEntries(); evt++)
    {
        T_HT1200->GetEntry(evt);

        if (f_ht1200_Met <= METcut)
        {
            continue;
        }

        int jet_passalpha_cut = 0;
        for (int ijet = 0; ijet < v_ht1200_alpha->size(); ijet++)
        {
            // h_Bg_alpha->Fill((*v_ht1200_alpha)[i], I_ht1200_weight * merge_weight.HT1200Weight);
            if ((*v_ht1200_alpha)[ijet] < alphacut)
            {
                jet_passalpha_cut++;
            }
        }

        // if (jet_passalpha_cut == 0)
        // {
        //     continue;
        // }

        h_Bg_nJet->Fill(jet_passalpha_cut, I_ht1200_weight * merge_weight.uu_HT1200Weight);
        if (jet_passalpha_cut < 2)
        {
            continue;
        }
        h_Bg_nJet_cuted->Fill(jet_passalpha_cut, I_ht1200_weight * merge_weight.uu_HT1200Weight);
    }

    TTree *T_HT2500;
    merge_bfiles.uu_DYHT2500->GetObject("T_tree", T_HT2500);
    T_HT2500->SetBranchAddress("I_weight", &I_ht2500_weight);
    T_HT2500->SetBranchAddress("f_Met", &f_ht2500_Met);
    T_HT2500->SetBranchAddress("I_nJets", &I_ht2500_nJet);
    T_HT2500->SetBranchAddress("v_fakealpha", &v_ht2500_alpha);
    T_HT2500->SetBranchAddress("f_thinjetCSV", &v_ht2500_jetcsv);
    T_HT2500->SetBranchAddress("v_fakeJethadronflavor", &v_ht2500_Jethadronflavor);
    for (int evt = 0; evt < T_HT2500->GetEntries(); evt++)
    {
        T_HT2500->GetEntry(evt);

        if (f_ht2500_Met <= METcut)
        {
            continue;
        }

        int jet_passalpha_cut = 0;
        for (int ijet = 0; ijet < v_ht2500_alpha->size(); ijet++)
        {
            // h_Bg_alpha->Fill((*v_ht2500_alpha)[i], I_ht2500_weight * merge_weight.HT2500Weight);
            if ((*v_ht2500_alpha)[ijet] < alphacut)
            {
                jet_passalpha_cut++;
            }
        }

        // if (jet_passalpha_cut == 0)
        // {
        //     continue;
        // }

        h_Bg_nJet->Fill(jet_passalpha_cut, I_ht2500_weight * merge_weight.uu_HT2500Weight);
        if (jet_passalpha_cut < 2)
        {
            continue;
        }
        h_Bg_nJet_cuted->Fill(jet_passalpha_cut, I_ht2500_weight * merge_weight.uu_HT2500Weight);
    }

    // TString outputfile = "./output/tmp.root";
    TFile *outfile_HT0 = TFile::Open(outputfile, "RECREATE");
    h_Bg_nJet->Write();
    h_Bg_nJet_cuted->Write();
    outfile_HT0->Close();
}
int main(int argc, char *argv[])
{
    if (argc == 3)
    {
        uu_HT_alpha(argv[1], argv[2]);
    }
    else
    {
        cout << "ERROR" << endl;
    }
}
