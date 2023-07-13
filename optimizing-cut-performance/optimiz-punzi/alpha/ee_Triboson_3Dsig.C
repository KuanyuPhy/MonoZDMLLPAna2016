#include "TFile.h"
#include <iostream>
#include "TTree.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <TH1D.h>
#include <string>
#include <TCanvas.h>
#include <TAttLine.h>
#include <TStyle.h>
#include "./../../../lib/Cross_section.h"
#include "./../../../lib/kuan_ana_utils.h"
using namespace std;
void ee_Triboson_3Dsig()
{ /*Open source root file*/
    MergeBFiles merge_bfiles;
    MergeWeight merge_weight(&merge_bfiles);

    TH1D *h_Triboson_3Dsig = new TH1D("h_Triboson_3Dsig", "", 200, -10., 10.);
    TH1D *h_bg_alpha3 = new TH1D("h_bg_alpha3", "", 20, 0, 1.);

    Int_t I_WWZ_weight, I_WZZ_weight, I_ZZZ_weight;

    float_t f_WWZ_met, f_WZZ_met, f_ZZZ_met;

    vector<float> *v_WWZ_log3Dsig = new vector<float>();
    vector<float> *v_WZZ_log3Dsig = new vector<float>();
    vector<float> *v_ZZZ_log3Dsig = new vector<float>();

    v_WWZ_log3Dsig->clear();
    v_WZZ_log3Dsig->clear();
    v_ZZZ_log3Dsig->clear();

    vector<float> *v_WWZ_alpha3 = new vector<float>();
    vector<float> *v_WZZ_alpha3 = new vector<float>();
    vector<float> *v_ZZZ_alpha3 = new vector<float>();

    v_WWZ_alpha3->clear();
    v_WZZ_alpha3->clear();
    v_ZZZ_alpha3->clear();

    double METcut = 140.;

    TTree *T_tree;
    merge_bfiles.ee_triboson_WWZfile->GetObject("T_tree", T_tree);
    T_tree->SetBranchAddress("I_weight", &I_WWZ_weight);
    T_tree->SetBranchAddress("f_Met", &f_WWZ_met);

    T_tree->SetBranchAddress("v_Chi3Dlog", &v_WWZ_log3Dsig);
    T_tree->SetBranchAddress("v_fakealpha3", &v_WWZ_alpha3);
    for (int evt = 0; evt < T_tree->GetEntries(); evt++)
    {
        T_tree->GetEntry(evt);
        for (int itrk = 0; itrk < v_WWZ_log3Dsig->size(); itrk++)
        {
            h_Triboson_3Dsig->Fill((*v_WWZ_log3Dsig)[itrk], I_WWZ_weight * merge_weight.ee_WWZWeight);
        }
        if (f_WWZ_met <= METcut)
        {
            continue;
        }

        for (int ijet = 0; ijet < v_WWZ_alpha3->size(); ijet++)
        {
            h_bg_alpha3->Fill((*v_WWZ_alpha3)[ijet], I_WWZ_weight * merge_weight.ee_WWZWeight);
        }
    }
    TTree *T_tree2;
    merge_bfiles.ee_triboson_WZZfile->GetObject("T_tree", T_tree2);
    T_tree2->SetBranchAddress("I_weight", &I_WZZ_weight);
    T_tree2->SetBranchAddress("f_Met", &f_WZZ_met);

    T_tree2->SetBranchAddress("v_Chi3Dlog", &v_WZZ_log3Dsig);
    T_tree2->SetBranchAddress("v_fakealpha3", &v_WZZ_alpha3);
    for (int evt = 0; evt < T_tree2->GetEntries(); evt++)
    {
        T_tree2->GetEntry(evt);
        for (int itrk = 0; itrk < v_WZZ_log3Dsig->size(); itrk++)
        {
            h_Triboson_3Dsig->Fill((*v_WZZ_log3Dsig)[itrk], I_WZZ_weight * merge_weight.ee_WZZWeight);
        }
        if (f_WZZ_met <= METcut)
        {
            continue;
        }
        for (int ijet = 0; ijet < v_WZZ_alpha3->size(); ijet++)
        {
            h_bg_alpha3->Fill((*v_WZZ_alpha3)[ijet], I_WZZ_weight * merge_weight.ee_WZZWeight);
        }
    }

    TTree *T_tree3;
    merge_bfiles.ee_triboson_ZZZfile->GetObject("T_tree", T_tree3);
    T_tree3->SetBranchAddress("I_weight", &I_ZZZ_weight);
    T_tree3->SetBranchAddress("f_Met", &f_ZZZ_met);

    T_tree3->SetBranchAddress("v_Chi3Dlog", &v_ZZZ_log3Dsig);
    T_tree3->SetBranchAddress("v_fakealpha3", &v_ZZZ_alpha3);
    for (int evt = 0; evt < T_tree3->GetEntries(); evt++)
    {
        T_tree3->GetEntry(evt);
        for (int itrk = 0; itrk < v_ZZZ_log3Dsig->size(); itrk++)
        {
            h_Triboson_3Dsig->Fill((*v_ZZZ_log3Dsig)[itrk], I_ZZZ_weight * merge_weight.ee_ZZZWeight);
        }
        if (f_ZZZ_met <= METcut)
        {
            continue;
        }

        for (int ijet = 0; ijet < v_ZZZ_alpha3->size(); ijet++)
        {
            h_bg_alpha3->Fill((*v_ZZZ_alpha3)[ijet], I_ZZZ_weight * merge_weight.ee_ZZZWeight);
        }
    }

    TString outputfile = "./ee_Triboson3Dsig.root";

    TFile *outfile_HT0 = TFile::Open(outputfile, "RECREATE");
    h_bg_alpha3->Write();
    h_Triboson_3Dsig->Write();
    outfile_HT0->Close();
}