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

void ee_Top_alpha(const char *scanalpha_step = "tmp", TString outputfile = "./output/tmp.root")
// void ee_HT_alpha()
{
    double alphacut = atoi(scanalpha_step) * 0.05;

    /*Open source root file*/
    MergeBFiles merge_bfiles;
    MergeWeight merge_weight(&merge_bfiles);

    double METcut = 140.;

    TH1D *h_Bg_nJet = new TH1D("h_Bg_nJet", "", 30, 0., 30.);
    TH1D *h_Bg_nJet_cuted = new TH1D("h_Bg_nJet_cuted", "at least two jets pass alpha cut", 30, 0., 30.);

    cout << "alphacut = " << alphacut << endl;

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

    vector<float> *v_TTTo2L2Nu_alpha = new vector<float>();
    vector<float> *v_ST_tW_top_alpha = new vector<float>();
    vector<float> *v_ST_tW_antitop_alpha = new vector<float>();
    vector<float> *v_TTWJetsToLNu_alpha = new vector<float>();
    vector<float> *v_TTWJetsToQQ_alpha = new vector<float>();
    vector<float> *v_TTZToQQ_alpha = new vector<float>();
    vector<float> *v_TTZToLLNuNu_alpha = new vector<float>();

    v_TTTo2L2Nu_alpha->clear();
    v_ST_tW_top_alpha->clear();
    v_ST_tW_antitop_alpha->clear();
    v_TTWJetsToLNu_alpha->clear();
    v_TTWJetsToQQ_alpha->clear();
    v_TTZToQQ_alpha->clear();
    v_TTZToLLNuNu_alpha->clear();

    vector<float> *v_TTTo2L2Nu_jetCSV = new vector<float>();
    vector<float> *v_ST_tW_top_jetCSV = new vector<float>();
    vector<float> *v_ST_tW_antitop_jetCSV = new vector<float>();
    vector<float> *v_TTWJetsToLNu_jetCSV = new vector<float>();
    vector<float> *v_TTWJetsToQQ_jetCSV = new vector<float>();
    vector<float> *v_TTZToQQ_jetCSV = new vector<float>();
    vector<float> *v_TTZToLLNuNu_jetCSV = new vector<float>();

    v_TTTo2L2Nu_jetCSV->clear();
    v_ST_tW_top_jetCSV->clear();
    v_ST_tW_antitop_jetCSV->clear();
    v_TTWJetsToLNu_jetCSV->clear();
    v_TTWJetsToQQ_jetCSV->clear();
    v_TTZToQQ_jetCSV->clear();
    v_TTZToLLNuNu_jetCSV->clear();

    vector<float> *v_TTTo2L2Nu_Jethadronflavor = new vector<float>();
    vector<float> *v_ST_tW_top_Jethadronflavor = new vector<float>();
    vector<float> *v_ST_tW_antitop_Jethadronflavor = new vector<float>();
    vector<float> *v_TTWJetsToLNu_Jethadronflavor = new vector<float>();
    vector<float> *v_TTWJetsToQQ_Jethadronflavor = new vector<float>();
    vector<float> *v_TTZToQQ_Jethadronflavor = new vector<float>();
    vector<float> *v_TTZToLLNuNu_Jethadronflavor = new vector<float>();

    v_TTTo2L2Nu_Jethadronflavor->clear();
    v_ST_tW_top_Jethadronflavor->clear();
    v_ST_tW_antitop_Jethadronflavor->clear();
    v_TTWJetsToLNu_Jethadronflavor->clear();
    v_TTWJetsToQQ_Jethadronflavor->clear();
    v_TTZToQQ_Jethadronflavor->clear();
    v_TTZToLLNuNu_Jethadronflavor->clear();

    TTree *T_TTTo2L2Nu_tree;
    merge_bfiles.ee_TTTo2L2Nufile->GetObject("T_tree", T_TTTo2L2Nu_tree);
    T_TTTo2L2Nu_tree->SetBranchAddress("I_weight", &I_TTTo2L2Nu_weight);
    T_TTTo2L2Nu_tree->SetBranchAddress("f_Met", &f_TTTo2L2Nu_met);
    T_TTTo2L2Nu_tree->SetBranchAddress("v_fakealpha3", &v_TTTo2L2Nu_alpha);
    T_TTTo2L2Nu_tree->SetBranchAddress("f_thinjetCSV", &v_TTTo2L2Nu_jetCSV);
    T_TTTo2L2Nu_tree->SetBranchAddress("v_fakeJethadronflavor", &v_TTTo2L2Nu_Jethadronflavor);
    for (int evt = 0; evt < T_TTTo2L2Nu_tree->GetEntries(); evt++)
    {
        T_TTTo2L2Nu_tree->GetEntry(evt);

        if (f_TTTo2L2Nu_met <= METcut)
        {
            continue;
        }

        int jet_passalpha_cut = 0;
        for (int ijet = 0; ijet < v_TTTo2L2Nu_alpha->size(); ijet++)
        {
            // h_Bg_alpha->Fill((*v_TTTo2L2Nu_alpha)[i], I_TTTo2L2Nu_weight * TTTo2L2NuWeight);
            if ((*v_TTTo2L2Nu_alpha)[ijet] < alphacut)
            {
                jet_passalpha_cut++;
            }
        }

        // if (jet_passalpha_cut == 0)
        // {
        //     continue;
        // }

        h_Bg_nJet->Fill(jet_passalpha_cut, I_TTTo2L2Nu_weight * merge_weight.ee_TTTo2L2NuWeight);

        if (jet_passalpha_cut < 2)
        {
            continue;
        }
        h_Bg_nJet_cuted->Fill(jet_passalpha_cut, I_TTTo2L2Nu_weight * merge_weight.ee_TTTo2L2NuWeight);
    }
    TTree *T_ST_tW_top_tree;
    merge_bfiles.ee_Top_tW_topfile->GetObject("T_tree", T_ST_tW_top_tree);
    T_ST_tW_top_tree->SetBranchAddress("I_weight", &I_ST_tW_top_weight);
    T_ST_tW_top_tree->SetBranchAddress("f_Met", &f_ST_tW_top_met);
    T_ST_tW_top_tree->SetBranchAddress("v_fakealpha3", &v_ST_tW_top_alpha);
    T_ST_tW_top_tree->SetBranchAddress("f_thinjetCSV", &v_ST_tW_top_jetCSV);
    T_ST_tW_top_tree->SetBranchAddress("v_fakeJethadronflavor", &v_ST_tW_top_Jethadronflavor);
    for (int evt = 0; evt < T_ST_tW_top_tree->GetEntries(); evt++)
    {
        T_ST_tW_top_tree->GetEntry(evt);

        if (f_ST_tW_top_met <= METcut)
        {
            continue;
        }

        int jet_passalpha_cut = 0;
        for (int ijet = 0; ijet < v_ST_tW_top_alpha->size(); ijet++)
        {
            // h_Bg_alpha->Fill((*v_ST_tW_top_alpha)[i], I_ST_tW_top_weight * ST_tW_topWeight);
            if ((*v_ST_tW_top_alpha)[ijet] < alphacut)
            {
                jet_passalpha_cut++;
            }
        }

        // if (jet_passalpha_cut == 0)
        // {
        //     continue;
        // }

        h_Bg_nJet->Fill(jet_passalpha_cut, I_ST_tW_top_weight * merge_weight.ee_ST_tW_topWeight);

        if (jet_passalpha_cut < 2)
        {
            continue;
        }
        h_Bg_nJet_cuted->Fill(jet_passalpha_cut, I_ST_tW_top_weight * merge_weight.ee_ST_tW_topWeight);
    }
    TTree *T_ST_tW_antitop_tree;
    merge_bfiles.ee_Top_tW_antitopfile->GetObject("T_tree", T_ST_tW_antitop_tree);
    T_ST_tW_antitop_tree->SetBranchAddress("I_weight", &I_ST_tW_antitop_weight);
    T_ST_tW_antitop_tree->SetBranchAddress("f_Met", &f_ST_tW_antitop_met);
    T_ST_tW_antitop_tree->SetBranchAddress("v_fakealpha3", &v_ST_tW_antitop_alpha);
    T_ST_tW_antitop_tree->SetBranchAddress("f_thinjetCSV", &v_ST_tW_antitop_jetCSV);
    T_ST_tW_antitop_tree->SetBranchAddress("v_fakeJethadronflavor", &v_ST_tW_antitop_Jethadronflavor);
    for (int evt = 0; evt < T_ST_tW_antitop_tree->GetEntries(); evt++)
    {
        T_ST_tW_antitop_tree->GetEntry(evt);

        if (f_ST_tW_antitop_met <= METcut)
        {
            continue;
        }

        int jet_passalpha_cut = 0;
        for (int ijet = 0; ijet < v_ST_tW_antitop_alpha->size(); ijet++)
        {
            // h_Bg_alpha->Fill((*v_ST_tW_antitop_alpha)[i], I_ST_tW_antitop_weight * ST_tW_antitopWeight);
            if ((*v_ST_tW_antitop_alpha)[ijet] < alphacut)
            {
                jet_passalpha_cut++;
            }
        }

        // if (jet_passalpha_cut == 0)
        // {
        //     continue;
        // }

        h_Bg_nJet->Fill(jet_passalpha_cut, I_ST_tW_antitop_weight * merge_weight.ee_ST_tW_antitopWeight);

        if (jet_passalpha_cut < 2)
        {
            continue;
        }
        h_Bg_nJet_cuted->Fill(jet_passalpha_cut, I_ST_tW_antitop_weight * merge_weight.ee_ST_tW_antitopWeight);
    }
    TTree *T_TTWJetsToLNu_tree;
    merge_bfiles.ee_Top_TTWJetsToLNufile->GetObject("T_tree", T_TTWJetsToLNu_tree);
    T_TTWJetsToLNu_tree->SetBranchAddress("I_weight", &I_TTWJetsToLNu_weight);
    T_TTWJetsToLNu_tree->SetBranchAddress("f_Met", &f_TTWJetsToLNu_met);
    T_TTWJetsToLNu_tree->SetBranchAddress("v_fakealpha3", &v_TTWJetsToLNu_alpha);
    T_TTWJetsToLNu_tree->SetBranchAddress("f_thinjetCSV", &v_TTWJetsToLNu_jetCSV);
    T_TTWJetsToLNu_tree->SetBranchAddress("v_fakeJethadronflavor", &v_TTWJetsToLNu_Jethadronflavor);
    for (int evt = 0; evt < T_TTWJetsToLNu_tree->GetEntries(); evt++)
    {
        T_TTWJetsToLNu_tree->GetEntry(evt);

        if (f_TTWJetsToLNu_met <= METcut)
        {
            continue;
        }

        int jet_passalpha_cut = 0;
        for (int ijet = 0; ijet < v_TTWJetsToLNu_alpha->size(); ijet++)
        {
            // h_Bg_alpha->Fill((*v_TTWJetsToLNu_alpha)[i], I_TTWJetsToLNu_weight * TTWJetsToLNuWeight);
            if ((*v_TTWJetsToLNu_alpha)[ijet] < alphacut)
            {
                jet_passalpha_cut++;
            }
        }

        // if (jet_passalpha_cut == 0)
        // {
        //     continue;
        // }

        h_Bg_nJet->Fill(jet_passalpha_cut, I_TTWJetsToLNu_weight * merge_weight.ee_TTWJetsToLNuWeight);

        if (jet_passalpha_cut < 2)
        {
            continue;
        }
        h_Bg_nJet_cuted->Fill(jet_passalpha_cut, I_TTWJetsToLNu_weight * merge_weight.ee_TTWJetsToLNuWeight);
    }
    TTree *T_TTWJetsToQQ_tree;
    merge_bfiles.ee_Top_TTWJetsToQQfile->GetObject("T_tree", T_TTWJetsToQQ_tree);
    T_TTWJetsToQQ_tree->SetBranchAddress("I_weight", &I_TTWJetsToQQ_weight);
    T_TTWJetsToQQ_tree->SetBranchAddress("f_Met", &f_TTWJetsToQQ_met);
    T_TTWJetsToQQ_tree->SetBranchAddress("v_fakealpha3", &v_TTWJetsToQQ_alpha);
    T_TTWJetsToQQ_tree->SetBranchAddress("f_thinjetCSV", &v_TTWJetsToQQ_jetCSV);
    T_TTWJetsToQQ_tree->SetBranchAddress("v_fakeJethadronflavor", &v_TTWJetsToQQ_Jethadronflavor);
    for (int evt = 0; evt < T_TTWJetsToQQ_tree->GetEntries(); evt++)
    {
        T_TTWJetsToQQ_tree->GetEntry(evt);

        if (f_TTWJetsToQQ_met <= METcut)
        {
            continue;
        }

        int jet_passalpha_cut = 0;
        for (int ijet = 0; ijet < v_TTWJetsToQQ_alpha->size(); ijet++)
        {
            // h_Bg_alpha->Fill((*v_TTWJetsToQQ_alpha)[i], I_TTWJetsToQQ_weight * TTWJetsToQQWeight);
            if ((*v_TTWJetsToQQ_alpha)[ijet] < alphacut)
            {
                jet_passalpha_cut++;
            }
        }

        // if (jet_passalpha_cut == 0)
        // {
        //     continue;
        // }

        h_Bg_nJet->Fill(jet_passalpha_cut, I_TTWJetsToQQ_weight * merge_weight.ee_TTWJetsToQQWeight);

        if (jet_passalpha_cut < 2)
        {
            continue;
        }
        h_Bg_nJet_cuted->Fill(jet_passalpha_cut, I_TTWJetsToQQ_weight * merge_weight.ee_TTWJetsToQQWeight);
    }
    TTree *T_TTZToQQ_tree;
    merge_bfiles.ee_Top_TTZToQQfile->GetObject("T_tree", T_TTZToQQ_tree);
    T_TTZToQQ_tree->SetBranchAddress("I_weight", &I_TTZToQQ_weight);
    T_TTZToQQ_tree->SetBranchAddress("f_Met", &f_TTZToQQ_met);
    T_TTZToQQ_tree->SetBranchAddress("v_fakealpha3", &v_TTZToQQ_alpha);
    T_TTZToQQ_tree->SetBranchAddress("f_thinjetCSV", &v_TTZToQQ_jetCSV);
    T_TTZToQQ_tree->SetBranchAddress("v_fakeJethadronflavor", &v_TTZToQQ_Jethadronflavor);
    for (int evt = 0; evt < T_TTZToQQ_tree->GetEntries(); evt++)
    {
        T_TTZToQQ_tree->GetEntry(evt);

        if (f_TTZToQQ_met <= METcut)
        {
            continue;
        }

        int jet_passalpha_cut = 0;
        for (int ijet = 0; ijet < v_TTZToQQ_alpha->size(); ijet++)
        {
            // h_Bg_alpha->Fill((*v_TTZToQQ_alpha)[i], I_TTZToQQ_weight * TTZToQQWeight);
            if ((*v_TTZToQQ_alpha)[ijet] < alphacut)
            {
                jet_passalpha_cut++;
            }
        }

        // if (jet_passalpha_cut == 0)
        // {
        //     continue;
        // }

        h_Bg_nJet->Fill(jet_passalpha_cut, I_TTZToQQ_weight * merge_weight.ee_TTZToQQWeight);
        if (jet_passalpha_cut < 2)
        {
            continue;
        }
        h_Bg_nJet_cuted->Fill(jet_passalpha_cut, I_TTZToQQ_weight * merge_weight.ee_TTZToQQWeight);
    }
    TTree *T_TTZToLLNuNu_tree;
    merge_bfiles.ee_Top_TTZToLLNuNufile->GetObject("T_tree", T_TTZToLLNuNu_tree);
    T_TTZToLLNuNu_tree->SetBranchAddress("I_weight", &I_TTZToLLNuNu_weight);
    T_TTZToLLNuNu_tree->SetBranchAddress("f_Met", &f_TTZToLLNuNu_met);
    T_TTZToLLNuNu_tree->SetBranchAddress("v_fakealpha3", &v_TTZToLLNuNu_alpha);
    T_TTZToLLNuNu_tree->SetBranchAddress("f_thinjetCSV", &v_TTZToLLNuNu_jetCSV);
    T_TTZToLLNuNu_tree->SetBranchAddress("v_fakeJethadronflavor", &v_TTZToLLNuNu_Jethadronflavor);
    for (int evt = 0; evt < T_TTZToLLNuNu_tree->GetEntries(); evt++)
    {
        T_TTZToLLNuNu_tree->GetEntry(evt);

        if (f_TTZToLLNuNu_met <= METcut)
        {
            continue;
        }

        int jet_passalpha_cut = 0;
        for (int ijet = 0; ijet < v_TTZToLLNuNu_alpha->size(); ijet++)
        {
            // h_Bg_alpha->Fill((*v_TTZToLLNuNu_alpha)[i], I_TTZToLLNuNu_weight * TTZToLLNuNuWeight);
            if ((*v_TTZToLLNuNu_alpha)[ijet] < alphacut)
            {
                jet_passalpha_cut++;
            }
        }

        // if (jet_passalpha_cut == 0)
        // {
        //     continue;
        // }

        h_Bg_nJet->Fill(jet_passalpha_cut, I_TTZToLLNuNu_weight * merge_weight.ee_TTZToLLNuNuWeight);

        if (jet_passalpha_cut < 2)
        {
            continue;
        }
        h_Bg_nJet_cuted->Fill(jet_passalpha_cut, I_TTZToLLNuNu_weight * merge_weight.ee_TTZToLLNuNuWeight);
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
        ee_Top_alpha(argv[1], argv[2]);
    }
    else
    {
        cout << "ERROR" << endl;
    }
}
