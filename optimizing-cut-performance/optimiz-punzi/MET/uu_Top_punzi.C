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

void uu_Top_punzi(const char *scanMet_step = "tmp", TString outputfile = "./output/tmp.root")
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

    TTree *T_TTTo2L2Nu_tree;
    merge_bfiles.uu_TTTo2L2Nufile->GetObject("T_tree", T_TTTo2L2Nu_tree);
    T_TTTo2L2Nu_tree->SetBranchAddress("I_weight", &I_TTTo2L2Nu_weight);
    T_TTTo2L2Nu_tree->SetBranchAddress("f_Met", &f_TTTo2L2Nu_met);
    T_TTTo2L2Nu_tree->SetBranchAddress("v_fakealpha", &v_TTTo2L2Nu_alpha);
    for (int evt = 0; evt < T_TTTo2L2Nu_tree->GetEntries(); evt++)
    {
        T_TTTo2L2Nu_tree->GetEntry(evt);
        //-------------------
        // Scan Met
        //-------------------
        h_pass_Bg->Fill(atoi(scanMet_step), I_TTTo2L2Nu_weight * merge_weight.uu_TTTo2L2NuWeight);
        if (f_TTTo2L2Nu_met > metcut)
        {
            h_pass_Bg_nMetcut->Fill(atoi(scanMet_step), I_TTTo2L2Nu_weight * merge_weight.uu_TTTo2L2NuWeight);
        }
    }
    TTree *T_ST_tW_top_tree;
    merge_bfiles.uu_Top_tW_topfile->GetObject("T_tree", T_ST_tW_top_tree);
    T_ST_tW_top_tree->SetBranchAddress("I_weight", &I_ST_tW_top_weight);
    T_ST_tW_top_tree->SetBranchAddress("f_Met", &f_ST_tW_top_met);
    T_ST_tW_top_tree->SetBranchAddress("v_fakealpha", &v_ST_tW_top_alpha);
    for (int evt = 0; evt < T_ST_tW_top_tree->GetEntries(); evt++)
    {
        T_ST_tW_top_tree->GetEntry(evt);
        //-------------------
        // Scan Met
        //-------------------
        h_pass_Bg->Fill(atoi(scanMet_step), I_ST_tW_top_weight * merge_weight.uu_ST_tW_topWeight);
        if (f_ST_tW_top_met > metcut)
        {
            h_pass_Bg_nMetcut->Fill(atoi(scanMet_step), I_ST_tW_top_weight * merge_weight.uu_ST_tW_topWeight);
        }
    }
    TTree *T_ST_tW_antitop_tree;
    merge_bfiles.uu_Top_tW_antitopfile->GetObject("T_tree", T_ST_tW_antitop_tree);
    T_ST_tW_antitop_tree->SetBranchAddress("I_weight", &I_ST_tW_antitop_weight);
    T_ST_tW_antitop_tree->SetBranchAddress("f_Met", &f_ST_tW_antitop_met);
    T_ST_tW_antitop_tree->SetBranchAddress("v_fakealpha", &v_ST_tW_antitop_alpha);
    for (int evt = 0; evt < T_ST_tW_antitop_tree->GetEntries(); evt++)
    {
        T_ST_tW_antitop_tree->GetEntry(evt);
        //-------------------
        // Scan Met
        //-------------------
        h_pass_Bg->Fill(atoi(scanMet_step), I_ST_tW_antitop_weight * merge_weight.uu_ST_tW_antitopWeight);
        if (f_ST_tW_antitop_met > metcut)
        {
            h_pass_Bg_nMetcut->Fill(atoi(scanMet_step), I_ST_tW_antitop_weight * merge_weight.uu_ST_tW_antitopWeight);
        }
    }
    TTree *T_TTWJetsToLNu_tree;
    merge_bfiles.uu_Top_TTWJetsToLNufile->GetObject("T_tree", T_TTWJetsToLNu_tree);
    T_TTWJetsToLNu_tree->SetBranchAddress("I_weight", &I_TTWJetsToLNu_weight);
    T_TTWJetsToLNu_tree->SetBranchAddress("f_Met", &f_TTWJetsToLNu_met);
    T_TTWJetsToLNu_tree->SetBranchAddress("v_fakealpha", &v_TTWJetsToLNu_alpha);
    for (int evt = 0; evt < T_TTWJetsToLNu_tree->GetEntries(); evt++)
    {
        T_TTWJetsToLNu_tree->GetEntry(evt);
        //-------------------
        // Scan Met
        //-------------------
        h_pass_Bg->Fill(atoi(scanMet_step), I_TTWJetsToLNu_weight * merge_weight.uu_TTWJetsToLNuWeight);
        if (f_TTWJetsToLNu_met > metcut)
        {
            h_pass_Bg_nMetcut->Fill(atoi(scanMet_step), I_TTWJetsToLNu_weight * merge_weight.uu_TTWJetsToLNuWeight);
        }
    }
    TTree *T_TTWJetsToQQ_tree;
    merge_bfiles.uu_Top_TTWJetsToQQfile->GetObject("T_tree", T_TTWJetsToQQ_tree);
    T_TTWJetsToQQ_tree->SetBranchAddress("I_weight", &I_TTWJetsToQQ_weight);
    T_TTWJetsToQQ_tree->SetBranchAddress("f_Met", &f_TTWJetsToQQ_met);
    T_TTWJetsToQQ_tree->SetBranchAddress("v_fakealpha", &v_TTWJetsToQQ_alpha);
    for (int evt = 0; evt < T_TTWJetsToQQ_tree->GetEntries(); evt++)
    {
        T_TTWJetsToQQ_tree->GetEntry(evt);
        //-------------------
        // Scan Met
        //-------------------
        h_pass_Bg->Fill(atoi(scanMet_step), I_TTWJetsToQQ_weight * merge_weight.uu_TTWJetsToQQWeight);
        if (f_TTWJetsToQQ_met > metcut)
        {
            h_pass_Bg_nMetcut->Fill(atoi(scanMet_step), I_TTWJetsToQQ_weight * merge_weight.uu_TTWJetsToQQWeight);
        }
    }
    TTree *T_TTZToQQ_tree;
    merge_bfiles.uu_Top_TTZToQQfile->GetObject("T_tree", T_TTZToQQ_tree);
    T_TTZToQQ_tree->SetBranchAddress("I_weight", &I_TTZToQQ_weight);
    T_TTZToQQ_tree->SetBranchAddress("f_Met", &f_TTZToQQ_met);
    T_TTZToQQ_tree->SetBranchAddress("v_fakealpha", &v_TTZToQQ_alpha);
    for (int evt = 0; evt < T_TTZToQQ_tree->GetEntries(); evt++)
    {
        T_TTZToQQ_tree->GetEntry(evt);
        //-------------------
        // Scan Met
        //-------------------
        h_pass_Bg->Fill(atoi(scanMet_step), I_TTZToQQ_weight * merge_weight.uu_TTZToQQWeight);
        if (f_TTZToQQ_met > metcut)
        {
            h_pass_Bg_nMetcut->Fill(atoi(scanMet_step), I_TTZToQQ_weight * merge_weight.uu_TTZToQQWeight);
        }
    }

    TTree *T_TTZToLLNuNu_tree;
    merge_bfiles.uu_Top_TTZToLLNuNufile->GetObject("T_tree", T_TTZToLLNuNu_tree);
    T_TTZToLLNuNu_tree->SetBranchAddress("I_weight", &I_TTZToLLNuNu_weight);
    T_TTZToLLNuNu_tree->SetBranchAddress("f_Met", &f_TTZToLLNuNu_met);
    T_TTZToLLNuNu_tree->SetBranchAddress("v_fakealpha", &v_TTZToLLNuNu_alpha);
    for (int evt = 0; evt < T_TTZToLLNuNu_tree->GetEntries(); evt++)
    {
        T_TTZToLLNuNu_tree->GetEntry(evt);
        //-------------------
        // Scan Met
        //-------------------
        h_pass_Bg->Fill(atoi(scanMet_step), I_TTZToLLNuNu_weight * merge_weight.uu_TTZToLLNuNuWeight);

        if (f_TTZToLLNuNu_met > metcut)
        {
            h_pass_Bg_nMetcut->Fill(atoi(scanMet_step), I_TTZToLLNuNu_weight * merge_weight.uu_TTZToLLNuNuWeight);
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
        uu_Top_punzi(argv[1], argv[2]);
    }
    else
    {
        cout << "ERROR" << endl;
    }
}