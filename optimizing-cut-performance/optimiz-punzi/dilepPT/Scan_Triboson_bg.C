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
TFile *triboson_WWZfile = TFile::Open("/home/kuanyu/Documents/root_file/Ztoee/2016BKGMC/triboson/ee_triboson_WWZ.root");
TFile *triboson_WZZfile = TFile::Open("/home/kuanyu/Documents/root_file/Ztoee/2016BKGMC/triboson/ee_triboson_WZZ.root");
TFile *triboson_ZZZfile = TFile::Open("/home/kuanyu/Documents/root_file/Ztoee/2016BKGMC/triboson/ee_triboson_ZZZ.root");

TH1D *WWZ_sumevt = ((TH1D *)triboson_WWZfile->Get("Event_Variable/h_totevent"));
TH1D *WZZ_sumevt = ((TH1D *)triboson_WZZfile->Get("Event_Variable/h_totevent"));
TH1D *ZZZ_sumevt = ((TH1D *)triboson_ZZZfile->Get("Event_Variable/h_totevent"));

double WWZ_totevt = WWZ_sumevt->Integral();
double WZZ_totevt = WZZ_sumevt->Integral();
double ZZZ_totevt = ZZZ_sumevt->Integral();

//---------------------
// Define Triboson Weight
//---------------------
double WWZWeight = (GlobalConstants::Lumi2016) * (GlobalConstants::WWZ_TuneCUETP8M1 / (WWZ_totevt)) * 1000;
double WZZWeight = (GlobalConstants::Lumi2016) * (GlobalConstants::WZZ_TuneCUETP8M1 / (WZZ_totevt)) * 1000;
double ZZZWeight = (GlobalConstants::Lumi2016) * (GlobalConstants::ZZZ_TuneCUETP8M1 / (ZZZ_totevt)) * 1000;

void Scan_Triboson_bg(const char *scanMet_step = "tmp", TString outputfile = "output.root")
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

    Int_t I_WWZ_weight, I_WZZ_weight, I_ZZZ_weight;

    float_t f_WWZ_met, f_WZZ_met, f_ZZZ_met;

    float_t f_WWZ_dilepPT, f_WZZ_dilepPT, f_ZZZ_dilepPT;

    vector<float> *v_WWZ_alpha = new vector<float>();
    vector<float> *v_WZZ_alpha = new vector<float>();
    vector<float> *v_ZZZ_alpha = new vector<float>();

    v_WWZ_alpha->clear();
    v_WZZ_alpha->clear();
    v_ZZZ_alpha->clear();

    TTree *T_tree;
    triboson_WWZfile->GetObject("T_tree", T_tree);
    T_tree->SetBranchAddress("I_weight", &I_WWZ_weight);
    T_tree->SetBranchAddress("f_Met", &f_WWZ_met);
    T_tree->SetBranchAddress("f_dileptonPT", &f_WWZ_dilepPT);
    T_tree->SetBranchAddress("v_fakealpha", &v_WWZ_alpha);
    for (int evt = 0; evt < T_tree->GetEntries(); evt++)
    {
        T_tree->GetEntry(evt);
        if (f_WWZ_met <= Metcut)
        {
            continue;
        }
        h_pass_bg->Fill(atoi(scanMet_step), I_WWZ_weight * WWZWeight);
        //-------------------
        // Scan dilepton PT
        //-------------------
        if (f_WWZ_dilepPT > dilepton_cut)
        {
            h_pass_Bg_nDilepPTcut->Fill(atoi(scanMet_step), I_WWZ_weight * WWZWeight);
        }
    }
    TTree *T_tree2;
    triboson_WZZfile->GetObject("T_tree", T_tree2);
    T_tree2->SetBranchAddress("I_weight", &I_WZZ_weight);
    T_tree2->SetBranchAddress("f_Met", &f_WZZ_met);
    T_tree2->SetBranchAddress("f_dileptonPT", &f_WZZ_dilepPT);
    T_tree2->SetBranchAddress("v_fakealpha", &v_WZZ_alpha);
    for (int evt = 0; evt < T_tree2->GetEntries(); evt++)
    {
        T_tree2->GetEntry(evt);
        if (f_WZZ_met <= Metcut)
        {
            continue;
        }
        h_pass_bg->Fill(atoi(scanMet_step), I_WZZ_weight * WZZWeight);
        //-------------------
        // Scan dilepton PT
        //-------------------
        if (f_WZZ_dilepPT > dilepton_cut)
        {
            h_pass_Bg_nDilepPTcut->Fill(atoi(scanMet_step), I_WZZ_weight * WZZWeight);
        }
    }
    TTree *T_tree3;
    triboson_ZZZfile->GetObject("T_tree", T_tree3);
    T_tree3->SetBranchAddress("I_weight", &I_ZZZ_weight);
    T_tree3->SetBranchAddress("f_Met", &f_ZZZ_met);
    T_tree3->SetBranchAddress("f_dileptonPT", &f_ZZZ_dilepPT);
    T_tree3->SetBranchAddress("v_fakealpha", &v_ZZZ_alpha);
    for (int evt = 0; evt < T_tree3->GetEntries(); evt++)
    {
        T_tree3->GetEntry(evt);
        if (f_ZZZ_met <= Metcut)
        {
            continue;
        }
        h_pass_bg->Fill(atoi(scanMet_step), I_ZZZ_weight * ZZZWeight);
        //-------------------
        // Scan dilepton PT
        //-------------------
        if (f_ZZZ_dilepPT > dilepton_cut)
        {
            h_pass_Bg_nDilepPTcut->Fill(atoi(scanMet_step), I_ZZZ_weight * ZZZWeight);
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
        Scan_Triboson_bg();
    }
    else if (argc == 3)
    {
        Scan_Triboson_bg(argv[1], argv[2]);
    }
    else
    {
        cout << "argc" << argc << endl;
        cout << "ERROR" << endl;
    }
}