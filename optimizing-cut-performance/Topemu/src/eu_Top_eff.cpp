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
#include <cstring>
#include "./../../../lib/Cross_section.h"
using namespace std;

//------------------
// Calculate weight
//------------------
TFile *TTTo2L2Nufile = new TFile("/home/kuanyu/Documents/root_file/Ztoemu/2016BKGMC/top/eu_top_emu_TTTo2L2Nu.root");
TFile *Top_TTWJetsToLNufile = new TFile("/home/kuanyu/Documents/root_file/Ztoemu/2016BKGMC/top/eu_top_emu_TTWJetsToLNu.root");
TFile *Top_TTWJetsToQQfile = new TFile("/home/kuanyu/Documents/root_file/Ztoemu/2016BKGMC/top/eu_top_emu_TTWJetsToQQ.root");
TFile *Top_TTZToQQfile = new TFile("/home/kuanyu/Documents/root_file/Ztoemu/2016BKGMC/top/eu_top_emu_TTZToQQ.root");
TFile *Top_TTZToLLNuNufile = new TFile("/home/kuanyu/Documents/root_file/Ztoemu/2016BKGMC/top/eu_top_emu_TTZToLLNuNu.root");
TFile *Top_tW_antitopfile = new TFile("/home/kuanyu/Documents/root_file/Ztoemu/2016BKGMC/top/eu_top_emu_tW_antitop.root");
TFile *Top_tW_topfile = new TFile("/home/kuanyu/Documents/root_file/Ztoemu/2016BKGMC/top/eu_top_emu_tW_top.root");

TH1D *TTTo2L2Nu_sumevt = ((TH1D *)TTTo2L2Nufile->Get("Event_Variable/h_totevent"));
TH1D *TTWJetsToLNu_sumevt = ((TH1D *)Top_TTWJetsToLNufile->Get("Event_Variable/h_totevent"));   
TH1D *TTWJetsToQQ_sumevt = ((TH1D *)Top_TTWJetsToQQfile->Get("Event_Variable/h_totevent"));
TH1D *TTZToQQ_sumevt = ((TH1D *)Top_TTZToQQfile->Get("Event_Variable/h_totevent"));
TH1D *TTZToLLNuNu_sumevt = ((TH1D *)Top_TTZToLLNuNufile->Get("Event_Variable/h_totevent"));
TH1D *tW_antitop_sumevt = ((TH1D *)Top_tW_antitopfile->Get("Event_Variable/h_totevent"));
TH1D *tW_top_sumevt = ((TH1D *)Top_tW_topfile->Get("Event_Variable/h_totevent"));

TH1D *TTTo2L2Nu_eepass = ((TH1D *)TTTo2L2Nufile->Get("Event_Variable/h_eu_npass"));
TH1D *TTWJetsToLNu_eepass = ((TH1D *)Top_TTWJetsToLNufile->Get("Event_Variable/h_eu_npass"));
TH1D *TTWJetsToQQ_eepass = ((TH1D *)Top_TTWJetsToQQfile->Get("Event_Variable/h_eu_npass"));
TH1D *TTZToQQ_eepass = ((TH1D *)Top_TTZToQQfile->Get("Event_Variable/h_eu_npass"));
TH1D *TTZToLLNuNu_eepass = ((TH1D *)Top_TTZToLLNuNufile->Get("Event_Variable/h_eu_npass"));
TH1D *tW_antitop_eepass = ((TH1D *)Top_tW_antitopfile->Get("Event_Variable/h_eu_npass"));
TH1D *tW_top_eepass = ((TH1D *)Top_tW_topfile->Get("Event_Variable/h_eu_npass"));

int TTTo2L2Nu_totevt = TTTo2L2Nu_sumevt->Integral();
int TTWJetsToLNu_totevt = TTWJetsToLNu_sumevt->Integral();
int TTWJetsToQQ_totevt = TTWJetsToQQ_sumevt->Integral();
int TTZToQQ_totevt = TTZToQQ_sumevt->Integral();
int TTZToLLNuNu_totevt = TTZToLLNuNu_sumevt->Integral();
int tW_antitop_totevt = tW_antitop_sumevt->Integral();
int tW_top_totevt = tW_top_sumevt->Integral();

//---------------------
// Define TopWeight
//---------------------
double TTTo2L2NuWeight = (GlobalConstants::Lumi2016) * ((GlobalConstants::TTTo2L2Nu) / (TTTo2L2Nu_totevt)) * 1000;
double ST_tW_topWeight = (GlobalConstants::Lumi2016) * (GlobalConstants::ST_tW_top_5fCS / (tW_top_totevt)) * 1000;
double ST_tW_antitopWeight = (GlobalConstants::Lumi2016) * (GlobalConstants::ST_tW_antitop_5fCS / (tW_antitop_totevt)) * 1000;
double TTWJetsToLNuWeight = (GlobalConstants::Lumi2016) * (GlobalConstants::TTWJetsToLNu / (TTWJetsToLNu_totevt)) * 1000;
double TTWJetsToQQWeight = (GlobalConstants::Lumi2016) * (GlobalConstants::TTWJetsToQQ / (TTWJetsToQQ_totevt)) * 1000;
double TTZToQQWeight = (GlobalConstants::Lumi2016) * (GlobalConstants::TTZToQQ / (TTZToQQ_totevt)) * 1000;
double TTZToLLNuNuWeight = (GlobalConstants::Lumi2016) * (GlobalConstants::TTZToLLNuNu / (TTZToLLNuNu_totevt)) * 1000;

void eu_Top_eff(TString outputfile = "./output/Top_eu_output.root")
{

    TTTo2L2Nu_eepass->Scale(TTTo2L2NuWeight);
    TTWJetsToLNu_eepass->Scale(TTWJetsToLNuWeight);
    TTWJetsToQQ_eepass->Scale(TTWJetsToQQWeight);
    TTZToQQ_eepass->Scale(TTZToQQWeight);
    TTZToLLNuNu_eepass->Scale(TTZToLLNuNuWeight);
    tW_antitop_eepass->Scale(ST_tW_antitopWeight);
    tW_top_eepass->Scale(ST_tW_topWeight);

    TH1D *h_eu_pass = (TH1D *)TTTo2L2Nu_eepass->Clone("h_eu_pass");
    h_eu_pass->Add(TTWJetsToLNu_eepass);
    h_eu_pass->Add(TTWJetsToQQ_eepass);
    h_eu_pass->Add(TTZToQQ_eepass);
    h_eu_pass->Add(TTZToLLNuNu_eepass);
    h_eu_pass->Add(tW_antitop_eepass);
    h_eu_pass->Add(tW_top_eepass);

    h_eu_pass->Draw();

    TFile *outfile = TFile::Open(outputfile, "RECREATE");
    outfile->cd();
    h_eu_pass->Write();
    outfile->Close();

    // cout << getWeight(file) << endl;
    // cout << "TTTo2L2NuWeight = " << TTTo2L2NuWeight << endl;
}
int main(int argc, char **argv)
{
    if (argc == 1)
    {
        eu_Top_eff();
    }
    else if (argc == 3)
    {
        eu_Top_eff(argv[1]);
    }
    else
    {
        cout << "argc" << argc << endl;
        cout << "ERROR" << endl;
    }
}