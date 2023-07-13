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

void ee_Top_3Dsig()
{ /*Open source root file*/
    MergeBFiles merge_bfiles;
    MergeWeight merge_weight(&merge_bfiles);

    TH1D *h_Top_3Dsig = new TH1D("h_Top_3Dsig", "", 200, -10., 10.);
    TH1D *h_bg_alpha3 = new TH1D("h_bg_alpha3", "", 20, 0, 1.);

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

    vector<float> *v_TTTo2L2Nu_log3Dsig = new vector<float>();
    vector<float> *v_ST_tW_top_log3Dsig = new vector<float>();
    vector<float> *v_ST_tW_antitop_log3Dsig = new vector<float>();
    vector<float> *v_TTWJetsToLNu_log3Dsig = new vector<float>();
    vector<float> *v_TTWJetsToQQ_log3Dsig = new vector<float>();
    vector<float> *v_TTZToQQ_log3Dsig = new vector<float>();
    vector<float> *v_TTZToLLNuNu_log3Dsig = new vector<float>();

    v_TTTo2L2Nu_log3Dsig->clear();
    v_ST_tW_top_log3Dsig->clear();
    v_ST_tW_antitop_log3Dsig->clear();
    v_TTWJetsToLNu_log3Dsig->clear();
    v_TTWJetsToQQ_log3Dsig->clear();
    v_TTZToQQ_log3Dsig->clear();
    v_TTZToLLNuNu_log3Dsig->clear();

    vector<float> *v_TTTo2L2Nu_alpha3 = new vector<float>();
    vector<float> *v_ST_tW_top_alpha3 = new vector<float>();
    vector<float> *v_ST_tW_antitop_alpha3 = new vector<float>();
    vector<float> *v_TTWJetsToLNu_alpha3 = new vector<float>();
    vector<float> *v_TTWJetsToQQ_alpha3 = new vector<float>();
    vector<float> *v_TTZToQQ_alpha3 = new vector<float>();
    vector<float> *v_TTZToLLNuNu_alpha3 = new vector<float>();

    v_TTTo2L2Nu_alpha3->clear();
    v_ST_tW_top_alpha3->clear();
    v_ST_tW_antitop_alpha3->clear();
    v_TTWJetsToLNu_alpha3->clear();
    v_TTWJetsToQQ_alpha3->clear();
    v_TTZToQQ_alpha3->clear();
    v_TTZToLLNuNu_alpha3->clear();

    double METcut = 140.;

    TTree *T_TTTo2L2Nu_tree;
    merge_bfiles.ee_TTTo2L2Nufile->GetObject("T_tree", T_TTTo2L2Nu_tree);
    T_TTTo2L2Nu_tree->SetBranchAddress("I_weight", &I_TTTo2L2Nu_weight);
    T_TTTo2L2Nu_tree->SetBranchAddress("f_Met", &f_TTTo2L2Nu_met);
    T_TTTo2L2Nu_tree->SetBranchAddress("v_Chi3Dlog", &v_TTTo2L2Nu_log3Dsig);
    T_TTTo2L2Nu_tree->SetBranchAddress("v_fakealpha3", &v_TTTo2L2Nu_alpha3);
    for (int evt = 0; evt < T_TTTo2L2Nu_tree->GetEntries(); evt++)
    {
        T_TTTo2L2Nu_tree->GetEntry(evt);

        for (int itrk = 0; itrk < v_TTTo2L2Nu_log3Dsig->size(); itrk++)
        {
            h_Top_3Dsig->Fill((*v_TTTo2L2Nu_log3Dsig)[itrk], I_TTTo2L2Nu_weight * merge_weight.ee_TTTo2L2NuWeight);
        }
        if (f_TTTo2L2Nu_met <= METcut)
        {
            continue;
        }
        for (int ijet = 0; ijet < v_TTTo2L2Nu_alpha3->size(); ijet++)
        {
            h_bg_alpha3->Fill((*v_TTTo2L2Nu_alpha3)[ijet], I_TTTo2L2Nu_weight * merge_weight.ee_TTTo2L2NuWeight);
        }
    }
    TTree *T_ST_tW_top_tree;
    merge_bfiles.ee_Top_tW_topfile->GetObject("T_tree", T_ST_tW_top_tree);
    T_ST_tW_top_tree->SetBranchAddress("I_weight", &I_ST_tW_top_weight);
    T_ST_tW_top_tree->SetBranchAddress("f_Met", &f_ST_tW_top_met);
    T_ST_tW_top_tree->SetBranchAddress("v_Chi3Dlog", &v_ST_tW_top_log3Dsig);
    T_ST_tW_top_tree->SetBranchAddress("v_fakealpha3", &v_ST_tW_top_alpha3);
    for (int evt = 0; evt < T_ST_tW_top_tree->GetEntries(); evt++)
    {
        T_ST_tW_top_tree->GetEntry(evt);

        for (int itrk = 0; itrk < v_ST_tW_top_log3Dsig->size(); itrk++)
        {
            h_Top_3Dsig->Fill((*v_ST_tW_top_log3Dsig)[itrk], I_ST_tW_top_weight * merge_weight.ee_ST_tW_topWeight);
        }
        if (f_ST_tW_top_met <= METcut)
        {
            continue;
        }
        for (int ijet = 0; ijet < v_ST_tW_top_alpha3->size(); ijet++)
        {
            h_bg_alpha3->Fill((*v_ST_tW_top_alpha3)[ijet], I_ST_tW_top_weight * merge_weight.ee_ST_tW_topWeight);
        }
    }
    TTree *T_ST_tW_antitop_tree;
    merge_bfiles.ee_Top_tW_antitopfile->GetObject("T_tree", T_ST_tW_antitop_tree);
    T_ST_tW_antitop_tree->SetBranchAddress("I_weight", &I_ST_tW_antitop_weight);
    T_ST_tW_antitop_tree->SetBranchAddress("f_Met", &f_ST_tW_antitop_met);
    T_ST_tW_antitop_tree->SetBranchAddress("v_Chi3Dlog", &v_ST_tW_antitop_log3Dsig);
    T_ST_tW_antitop_tree->SetBranchAddress("v_fakealpha3", &v_ST_tW_antitop_alpha3);
    for (int evt = 0; evt < T_ST_tW_antitop_tree->GetEntries(); evt++)
    {
        T_ST_tW_antitop_tree->GetEntry(evt);
        for (int itrk = 0; itrk < v_ST_tW_antitop_log3Dsig->size(); itrk++)
        {
            h_Top_3Dsig->Fill((*v_ST_tW_antitop_log3Dsig)[itrk], I_ST_tW_antitop_weight * merge_weight.ee_ST_tW_antitopWeight);
        }

        if (f_ST_tW_antitop_met <= METcut)
        {
            continue;
        }

        for (int ijet = 0; ijet < v_ST_tW_antitop_alpha3->size(); ijet++)
        {
            h_bg_alpha3->Fill((*v_ST_tW_antitop_alpha3)[ijet], I_ST_tW_antitop_weight * merge_weight.ee_ST_tW_antitopWeight);
        }
    }
    TTree *T_TTWJetsToLNu_tree;
    merge_bfiles.ee_Top_TTWJetsToLNufile->GetObject("T_tree", T_TTWJetsToLNu_tree);
    T_TTWJetsToLNu_tree->SetBranchAddress("I_weight", &I_TTWJetsToLNu_weight);
    T_TTWJetsToLNu_tree->SetBranchAddress("f_Met", &f_TTWJetsToLNu_met);
    T_TTWJetsToLNu_tree->SetBranchAddress("v_Chi3Dlog", &v_TTWJetsToLNu_log3Dsig);
    T_TTWJetsToLNu_tree->SetBranchAddress("v_fakealpha3", &v_TTWJetsToLNu_alpha3);
    for (int evt = 0; evt < T_TTWJetsToLNu_tree->GetEntries(); evt++)
    {
        T_TTWJetsToLNu_tree->GetEntry(evt);
        for (int itrk = 0; itrk < v_TTWJetsToLNu_log3Dsig->size(); itrk++)
        {
            h_Top_3Dsig->Fill((*v_TTWJetsToLNu_log3Dsig)[itrk], I_TTWJetsToLNu_weight * merge_weight.ee_TTWJetsToLNuWeight);
        }

        if (f_TTWJetsToLNu_met <= METcut)
        {
            continue;
        }

        for (int ijet = 0; ijet < v_TTWJetsToLNu_alpha3->size(); ijet++)
        {
            h_bg_alpha3->Fill((*v_TTWJetsToLNu_alpha3)[ijet], I_TTWJetsToLNu_weight * merge_weight.ee_TTWJetsToLNuWeight);
        }
    }
    TTree *T_TTWJetsToQQ_tree;
    merge_bfiles.ee_Top_TTWJetsToQQfile->GetObject("T_tree", T_TTWJetsToQQ_tree);
    T_TTWJetsToQQ_tree->SetBranchAddress("I_weight", &I_TTWJetsToQQ_weight);
    T_TTWJetsToQQ_tree->SetBranchAddress("f_Met", &f_TTWJetsToQQ_met);
    T_TTWJetsToQQ_tree->SetBranchAddress("v_Chi3Dlog", &v_TTWJetsToQQ_log3Dsig);
    T_TTWJetsToQQ_tree->SetBranchAddress("v_fakealpha3", &v_TTWJetsToQQ_alpha3);
    for (int evt = 0; evt < T_TTWJetsToQQ_tree->GetEntries(); evt++)
    {
        T_TTWJetsToQQ_tree->GetEntry(evt);

        for (int itrk = 0; itrk < v_TTWJetsToQQ_log3Dsig->size(); itrk++)
        {
            h_Top_3Dsig->Fill((*v_TTWJetsToQQ_log3Dsig)[itrk], I_TTWJetsToQQ_weight * merge_weight.ee_TTWJetsToQQWeight);
        }

        if (f_TTWJetsToQQ_met <= METcut)
        {
            continue;
        }

        for (int ijet = 0; ijet < v_TTWJetsToQQ_alpha3->size(); ijet++)
        {
            h_bg_alpha3->Fill((*v_TTWJetsToQQ_alpha3)[ijet], I_TTWJetsToQQ_weight * merge_weight.ee_TTWJetsToQQWeight);
        }
    }
    TTree *T_TTZToQQ_tree;
    merge_bfiles.ee_Top_TTZToQQfile->GetObject("T_tree", T_TTZToQQ_tree);
    T_TTZToQQ_tree->SetBranchAddress("I_weight", &I_TTZToQQ_weight);
    T_TTZToQQ_tree->SetBranchAddress("f_Met", &f_TTZToQQ_met);
    T_TTZToQQ_tree->SetBranchAddress("v_Chi3Dlog", &v_TTZToQQ_log3Dsig);
    T_TTZToQQ_tree->SetBranchAddress("v_fakealpha3", &v_TTZToQQ_alpha3);
    for (int evt = 0; evt < T_TTZToQQ_tree->GetEntries(); evt++)
    {
        T_TTZToQQ_tree->GetEntry(evt);

        for (int itrk = 0; itrk < v_TTZToQQ_log3Dsig->size(); itrk++)
        {
            h_Top_3Dsig->Fill((*v_TTZToQQ_log3Dsig)[itrk], I_TTZToQQ_weight * merge_weight.ee_TTZToQQWeight);
        }

        if (f_TTZToQQ_met <= METcut)
        {
            continue;
        }

        for (int ijet = 0; ijet < v_TTZToQQ_alpha3->size(); ijet++)
        {
            h_bg_alpha3->Fill((*v_TTZToQQ_alpha3)[ijet], I_TTZToQQ_weight * merge_weight.ee_TTZToQQWeight);
        }
    }

    TTree *T_TTZToLLNuNu_tree;
    merge_bfiles.ee_Top_TTZToLLNuNufile->GetObject("T_tree", T_TTZToLLNuNu_tree);
    T_TTZToLLNuNu_tree->SetBranchAddress("I_weight", &I_TTZToLLNuNu_weight);
    T_TTZToLLNuNu_tree->SetBranchAddress("f_Met", &f_TTZToLLNuNu_met);
    T_TTZToLLNuNu_tree->SetBranchAddress("v_Chi3Dlog", &v_TTZToLLNuNu_log3Dsig);
    T_TTZToLLNuNu_tree->SetBranchAddress("v_fakealpha3", &v_TTZToLLNuNu_alpha3);
    for (int evt = 0; evt < T_TTZToLLNuNu_tree->GetEntries(); evt++)
    {
        T_TTZToLLNuNu_tree->GetEntry(evt);

        for (int itrk = 0; itrk < v_TTZToLLNuNu_log3Dsig->size(); itrk++)
        {
            h_Top_3Dsig->Fill((*v_TTZToLLNuNu_log3Dsig)[itrk], I_TTZToLLNuNu_weight * merge_weight.ee_TTZToLLNuNuWeight);
        }
        if (f_TTZToLLNuNu_met <= METcut)
        {
            continue;
        }
        for (int ijet = 0; ijet < v_TTZToLLNuNu_alpha3->size(); ijet++)
        {
            h_bg_alpha3->Fill((*v_TTZToLLNuNu_alpha3)[ijet], I_TTZToLLNuNu_weight * merge_weight.ee_TTZToLLNuNuWeight);
        }
    }
    h_Top_3Dsig->Draw();
    TString outputfile = "./ee_Top3Dsig.root";

    TFile *outfile_HT0 = TFile::Open(outputfile, "RECREATE");
    h_Top_3Dsig->Write();
    h_bg_alpha3->Write();
    outfile_HT0->Close();
}