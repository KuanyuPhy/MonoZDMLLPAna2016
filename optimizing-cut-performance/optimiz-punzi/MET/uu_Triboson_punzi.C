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

void uu_Triboson_punzi(const char *scanMet_step = "tmp", TString outputfile = "./output/tmp.root")
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

    Int_t I_WWZ_weight, I_WZZ_weight, I_ZZZ_weight;

    float_t f_WWZ_met, f_WZZ_met, f_ZZZ_met;

    vector<float> *v_WWZ_alpha = new vector<float>();
    vector<float> *v_WZZ_alpha = new vector<float>();
    vector<float> *v_ZZZ_alpha = new vector<float>();

    v_WWZ_alpha->clear();
    v_WZZ_alpha->clear();
    v_ZZZ_alpha->clear();

    TTree *T_tree;
    merge_bfiles.uu_triboson_WWZfile->GetObject("T_tree", T_tree);
    T_tree->SetBranchAddress("I_weight", &I_WWZ_weight);
    T_tree->SetBranchAddress("f_Met", &f_WWZ_met);
    T_tree->SetBranchAddress("v_fakealpha", &v_WWZ_alpha);
    for (int evt = 0; evt < T_tree->GetEntries(); evt++)
    {
        T_tree->GetEntry(evt);
        //-------------------
        // Scan Met
        //-------------------
        h_pass_Bg->Fill(atoi(scanMet_step), I_WWZ_weight * merge_weight.uu_WWZWeight);
        if (f_WWZ_met > metcut)
        {
            h_pass_Bg_nMetcut->Fill(atoi(scanMet_step), I_WWZ_weight * merge_weight.uu_WWZWeight);
        }
    }
    TTree *T_tree2;
    merge_bfiles.uu_triboson_WZZfile->GetObject("T_tree", T_tree2);
    T_tree2->SetBranchAddress("I_weight", &I_WZZ_weight);
    T_tree2->SetBranchAddress("f_Met", &f_WZZ_met);
    T_tree2->SetBranchAddress("v_fakealpha", &v_WZZ_alpha);
    for (int evt = 0; evt < T_tree2->GetEntries(); evt++)
    {
        T_tree2->GetEntry(evt);
        //-------------------
        // Scan Met
        //-------------------
        h_pass_Bg->Fill(atoi(scanMet_step), I_WZZ_weight * merge_weight.uu_WZZWeight);
        if (f_WZZ_met > metcut)
        {
            h_pass_Bg_nMetcut->Fill(atoi(scanMet_step), I_WZZ_weight * merge_weight.uu_WZZWeight);
        }
    }
    TTree *T_tree3;
    merge_bfiles.uu_triboson_ZZZfile->GetObject("T_tree", T_tree3);
    T_tree3->SetBranchAddress("I_weight", &I_ZZZ_weight);
    T_tree3->SetBranchAddress("f_Met", &f_ZZZ_met);
    T_tree3->SetBranchAddress("v_fakealpha", &v_ZZZ_alpha);
    for (int evt = 0; evt < T_tree3->GetEntries(); evt++)
    {
        T_tree3->GetEntry(evt);
        //-------------------
        // Scan Met
        //-------------------
        h_pass_Bg->Fill(atoi(scanMet_step), I_ZZZ_weight * merge_weight.uu_ZZZWeight);
        if (f_ZZZ_met > metcut)
        {
            h_pass_Bg_nMetcut->Fill(atoi(scanMet_step), I_ZZZ_weight * merge_weight.uu_ZZZWeight);
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
        uu_Triboson_punzi(argv[1], argv[2]);
    }
    else
    {
        cout << "ERROR" << endl;
    }
}