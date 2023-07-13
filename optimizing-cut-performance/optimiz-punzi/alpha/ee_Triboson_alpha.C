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

void ee_Triboson_alpha(const char *scanalpha_step = "tmp", TString outputfile = "./output/tmp.root")
{
    double alphacut = atoi(scanalpha_step) * 0.05;

    /*Open source root file*/
    MergeBFiles merge_bfiles;
    MergeWeight merge_weight(&merge_bfiles);

    double METcut = 140.;

    TH1D *h_Bg_nJet = new TH1D("h_Bg_nJet", "", 30, 0., 30.);
    TH1D *h_Bg_nJet_cuted = new TH1D("h_Bg_nJet_cuted", "at least two jets pass alpha cut", 30, 0., 30.);

    Int_t I_WWZ_weight, I_WZZ_weight, I_ZZZ_weight;
    float_t f_WWZ_met, f_WZZ_met, f_ZZZ_met;

    vector<float> *v_WWZ_alpha = new vector<float>();
    vector<float> *v_WZZ_alpha = new vector<float>();
    vector<float> *v_ZZZ_alpha = new vector<float>();

    v_WWZ_alpha->clear();
    v_WZZ_alpha->clear();
    v_ZZZ_alpha->clear();

    TTree *T_tree;
    merge_bfiles.ee_triboson_WWZfile->GetObject("T_tree", T_tree);
    T_tree->SetBranchAddress("I_weight", &I_WWZ_weight);
    T_tree->SetBranchAddress("f_Met", &f_WWZ_met);
    T_tree->SetBranchAddress("v_fakealpha3", &v_WWZ_alpha);
    for (int evt = 0; evt < T_tree->GetEntries(); evt++)
    {
        T_tree->GetEntry(evt);

        if (f_WWZ_met <= METcut)
        {
            continue;
        }

        int jet_passalpha_cut = 0;
        for (int ijet = 0; ijet < v_WWZ_alpha->size(); ijet++)
        {
            // h_Bg_alpha->Fill((*v_WWZ_alpha)[i], I_WWZ_weight * merge_weight.ee_WWZWeight);
            if ((*v_WWZ_alpha)[ijet] < alphacut)
            {
                jet_passalpha_cut++;
            }
        }

        // if (jet_passalpha_cut == 0)
        // {
        //     continue;
        // }

        h_Bg_nJet->Fill(jet_passalpha_cut, I_WWZ_weight * merge_weight.ee_WWZWeight);

        if (jet_passalpha_cut < 2)
        {
            continue;
        }
        h_Bg_nJet_cuted->Fill(jet_passalpha_cut, I_WWZ_weight * merge_weight.ee_WWZWeight);
    }
    TTree *T_tree2;
    merge_bfiles.ee_triboson_WZZfile->GetObject("T_tree", T_tree2);
    T_tree2->SetBranchAddress("I_weight", &I_WZZ_weight);
    T_tree2->SetBranchAddress("f_Met", &f_WZZ_met);
    T_tree2->SetBranchAddress("v_fakealpha3", &v_WZZ_alpha);
    for (int evt = 0; evt < T_tree2->GetEntries(); evt++)
    {
        T_tree2->GetEntry(evt);

        if (f_WZZ_met <= METcut)
        {
            continue;
        }

        int jet_passalpha_cut = 0;
        for (int ijet = 0; ijet < v_WZZ_alpha->size(); ijet++)
        {
            // h_Bg_alpha->Fill((*v_WZZ_alpha)[i], I_WZZ_weight * merge_weight.ee_WZZWeight);
            if ((*v_WZZ_alpha)[ijet] < alphacut)
            {
                jet_passalpha_cut++;
            }
        }

        // if (jet_passalpha_cut == 0)
        // {
        //     continue;
        // }

        h_Bg_nJet->Fill(jet_passalpha_cut, I_WZZ_weight * merge_weight.ee_WZZWeight);

        if (jet_passalpha_cut < 2)
        {
            continue;
        }
        h_Bg_nJet_cuted->Fill(jet_passalpha_cut, I_WZZ_weight * merge_weight.ee_WZZWeight);
    }

    TTree *T_tree3;
    merge_bfiles.ee_triboson_ZZZfile->GetObject("T_tree", T_tree3);
    T_tree3->SetBranchAddress("I_weight", &I_ZZZ_weight);
    T_tree3->SetBranchAddress("f_Met", &f_ZZZ_met);
    T_tree3->SetBranchAddress("v_fakealpha3", &v_ZZZ_alpha);
    for (int evt = 0; evt < T_tree3->GetEntries(); evt++)
    {
        T_tree3->GetEntry(evt);

        if (f_ZZZ_met <= METcut)
        {
            continue;
        }

        int jet_passalpha_cut = 0;
        for (int ijet = 0; ijet < v_ZZZ_alpha->size(); ijet++)
        {
            // h_Bg_alpha->Fill((*v_ZZZ_alpha)[i], I_ZZZ_weight * merge_weight.ee_ZZZWeight);
            if ((*v_ZZZ_alpha)[ijet] < alphacut)
            {
                jet_passalpha_cut++;
            }
        }

        // if (jet_passalpha_cut == 0)
        // {
        //     continue;
        // }

        h_Bg_nJet->Fill(jet_passalpha_cut, I_ZZZ_weight * merge_weight.ee_ZZZWeight);
        if (jet_passalpha_cut < 2)
        {
            continue;
        }
        h_Bg_nJet_cuted->Fill(jet_passalpha_cut, I_ZZZ_weight * merge_weight.ee_ZZZWeight);
    }

    TFile *outfile_HT0 = TFile::Open(outputfile, "RECREATE");
    h_Bg_nJet->Write();
    h_Bg_nJet_cuted->Write();

    outfile_HT0->Close();
}
int main(int argc, char *argv[])
{
    if (argc == 3)
    {
        ee_Triboson_alpha(argv[1], argv[2]);
    }
    else
    {
        cout << "ERROR" << endl;
    }
}
