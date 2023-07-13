#include "TFile.h"
#include <iostream>
#include "TTree.h"
#include <TLegend.h>
#include <TCanvas.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <TH1D.h>
#include <string>
#include <TAttLine.h>
#include <TStyle.h>
using namespace std;

void draw_3Dsig()
{
    TFile *ee_DY_file = TFile::Open("./ee_HT3Dsig.root");
    TFile *ee_Top_file = TFile::Open("./ee_Top3Dsig.root");
    TFile *ee_Diboson_file = TFile::Open("./ee_Dibosonsig.root");
    TFile *ee_Triboson_file = TFile::Open("./ee_Triboson3Dsig.root");

    TH1D *h_ee_DY_3Dsig = ee_DY_file->Get<TH1D>("h_DY_3Dsig");
    TH1D *h_ee_Top_3Dsig = ee_Top_file->Get<TH1D>("h_Top_3Dsig");
    TH1D *h_ee_Diboson_3Dsig = ee_Diboson_file->Get<TH1D>("h_Diboson_3Dsig");
    TH1D *h_ee_Triboson_3Dsig = ee_Triboson_file->Get<TH1D>("h_Triboson_3Dsig");

    TH1D *h_ee_DY_alpha3 = ee_DY_file->Get<TH1D>("h_bg_alpha3");
    TH1D *h_ee_Top_alpha3 = ee_Top_file->Get<TH1D>("h_bg_alpha3");
    TH1D *h_ee_Diboson_alpha3 = ee_Diboson_file->Get<TH1D>("h_bg_alpha3");
    TH1D *h_ee_Triboson_alpha3 = ee_Triboson_file->Get<TH1D>("h_bg_alpha3");

    TFile *Mx2_1 = new TFile("/home/kuanyu/Documents/root_file/Ztoee/ee_Mx2_1_old_remove_0alpha.root");
    TFile *Mx2_50 = new TFile("/home/kuanyu/Documents/root_file/Ztoee/ee_Mx2_50_old_remove_0alpha.root");
    TFile *Mx2_150 = new TFile("/home/kuanyu/Documents/root_file/Ztoee/ee_Mx2_150_old_remove_0alpha.root");

    TH1D *h_SigMx21_3Dsig = new TH1D("h_SigMx21_3Dsig", "", 200, -10., 10.);
    TH1D *h_SigMx250_3Dsig = new TH1D("h_SigMx250_3Dsig", "", 200, -10., 10.);
    TH1D *h_SigMx2150_3Dsig = new TH1D("h_SigMx2150_3Dsig", "", 200, -10., 10.);

    TH1D *h_SigMx21_alpha3 = new TH1D("h_SigMx21_alpha3", "", 20, 0, 1.);
    TH1D *h_SigMx250_alpha3 = new TH1D("h_SigMx250_alpha3", "", 20, 0, 1.);
    TH1D *h_SigMx2150_alpha3 = new TH1D("h_SigMx2150_alpha3", "", 20, 0, 1.);

    Int_t I_Mx1_weight, I_Mx50_weight, I_Mx150_weight;

    Float_t f_Mx1_met, f_Mx50_met, f_Mx150_met;

    vector<float> *v_Mx1_log3Dsig = new vector<float>();
    vector<float> *v_Mx50_log3Dsig = new vector<float>();
    vector<float> *v_Mx150_log3Dsig = new vector<float>();

    v_Mx1_log3Dsig->clear();
    v_Mx50_log3Dsig->clear();
    v_Mx150_log3Dsig->clear();

    vector<float> *v_Mx1_alpha3 = new vector<float>();
    vector<float> *v_Mx50_alpha3 = new vector<float>();
    vector<float> *v_Mx150_alpha3 = new vector<float>();

    v_Mx1_alpha3->clear();
    v_Mx50_alpha3->clear();
    v_Mx150_alpha3->clear();

    double METcut = 140.;

    TTree *T_Mx2_1;
    Mx2_1->GetObject("T_tree", T_Mx2_1);
    T_Mx2_1->SetBranchAddress("I_weight", &I_Mx1_weight);
    T_Mx2_1->SetBranchAddress("f_Met", &f_Mx1_met);
    T_Mx2_1->SetBranchAddress("v_Chi3Dlog", &v_Mx1_log3Dsig);
    T_Mx2_1->SetBranchAddress("v_fakealpha3", &v_Mx1_alpha3);
    for (int evt = 0; evt < T_Mx2_1->GetEntries(); evt++)
    {
        T_Mx2_1->GetEntry(evt);

        for (int itrk = 0; itrk < v_Mx1_log3Dsig->size(); itrk++)
        {
            h_SigMx21_3Dsig->Fill((*v_Mx1_log3Dsig)[itrk], I_Mx1_weight);
        }

        if (f_Mx1_met <= METcut)
        {
            continue;
        }
        for (int ijet = 0; ijet < v_Mx1_alpha3->size(); ijet++)
        {
            h_SigMx21_alpha3->Fill((*v_Mx1_alpha3)[ijet], I_Mx1_weight);
        }
    }
    TTree *T_Mx2_50;
    Mx2_50->GetObject("T_tree", T_Mx2_50);
    T_Mx2_50->SetBranchAddress("I_weight", &I_Mx50_weight);
    T_Mx2_50->SetBranchAddress("f_Met", &f_Mx50_met);
    T_Mx2_50->SetBranchAddress("v_Chi3Dlog", &v_Mx50_log3Dsig);
    T_Mx2_50->SetBranchAddress("v_fakealpha3", &v_Mx50_alpha3);
    for (int evt = 0; evt < T_Mx2_50->GetEntries(); evt++)
    {
        T_Mx2_50->GetEntry(evt);
        for (int itrk = 0; itrk < v_Mx50_log3Dsig->size(); itrk++)
        {
            h_SigMx250_3Dsig->Fill((*v_Mx50_log3Dsig)[itrk], I_Mx50_weight);
        }
        if (f_Mx50_met <= METcut)
        {
            continue;
        }
        for (int ijet = 0; ijet < v_Mx50_alpha3->size(); ijet++)
        {
            h_SigMx250_alpha3->Fill((*v_Mx50_alpha3)[ijet], I_Mx50_weight);
        }
    }

    TTree *T_Mx2_150;
    Mx2_150->GetObject("T_tree", T_Mx2_150);
    T_Mx2_150->SetBranchAddress("I_weight", &I_Mx150_weight);
    T_Mx2_150->SetBranchAddress("f_Met", &f_Mx150_met);
    T_Mx2_150->SetBranchAddress("v_Chi3Dlog", &v_Mx150_log3Dsig);
    T_Mx2_150->SetBranchAddress("v_fakealpha3", &v_Mx150_alpha3);
    for (int evt = 0; evt < T_Mx2_150->GetEntries(); evt++)
    {
        T_Mx2_150->GetEntry(evt);
        for (int itrk = 0; itrk < v_Mx150_log3Dsig->size(); itrk++)
        {
            h_SigMx2150_3Dsig->Fill((*v_Mx150_log3Dsig)[itrk], I_Mx150_weight);
        }
        if (f_Mx150_met <= METcut)
        {
            continue;
        }
        for (int ijet = 0; ijet < v_Mx150_alpha3->size(); ijet++)
        {
            h_SigMx2150_alpha3->Fill((*v_Mx150_alpha3)[ijet], I_Mx150_weight);
        }
    }

    /*
    TH1D *h_2016bkg_3Dsig = (TH1D *)h_ee_DY_3Dsig->Clone("h_2016bkg_3Dsig");

    h_2016bkg_3Dsig->Add(h_ee_Top_3Dsig);
    h_2016bkg_3Dsig->Add(h_ee_Diboson_3Dsig);
    h_2016bkg_3Dsig->Add(h_ee_Triboson_3Dsig);

    h_2016bkg_3Dsig->SetLineColor(kGreen + 3);
    h_2016bkg_3Dsig->SetFillColor(kGreen + 3);

    h_SigMx21_3Dsig->SetLineWidth(2);
    h_SigMx2150_3Dsig->SetLineWidth(2);
    h_SigMx250_3Dsig->SetLineWidth(2);

    h_SigMx21_3Dsig->SetLineColor(kRed);
    h_SigMx250_3Dsig->SetLineColor(kGray + 2);
    h_SigMx2150_3Dsig->SetLineColor(kBlue);

    h_2016bkg_3Dsig->SetFillStyle(3001);

    h_2016bkg_3Dsig->GetXaxis()->SetNdivisions(6, 5, 0);
    h_2016bkg_3Dsig->GetXaxis()->SetTitleOffset(1.5);
    h_2016bkg_3Dsig->GetXaxis()->SetRangeUser(-3.,4.);
    h_2016bkg_3Dsig->GetXaxis()->SetTitle("log_{10}(#Chi_{3D})");
    h_2016bkg_3Dsig->GetYaxis()->SetNdivisions(6, 5, 0);
    h_2016bkg_3Dsig->GetYaxis()->SetTitleOffset(1.5);
    h_2016bkg_3Dsig->GetYaxis()->SetTitle("nTracks / Normalized");

    h_2016bkg_3Dsig->DrawNormalized("h e");
    h_SigMx21_3Dsig->DrawNormalized("h e same");
    h_SigMx250_3Dsig->DrawNormalized("h e same");
    h_SigMx2150_3Dsig->DrawNormalized("h e same");

    TLegend *l1 = new TLegend(0.5, 0.7, 0.90, 0.90);
    l1->SetBorderSize(0);
    l1->SetFillStyle(0);
    l1->SetTextSize(0.03);
    l1->AddEntry(h_2016bkg_3Dsig, "2016 MC background", "f");
    l1->AddEntry(h_SigMx21_3Dsig, "m_{#chi_{2}} = 1 GeV, c#tau = 1 mm", "lE");
    l1->AddEntry(h_SigMx250_3Dsig, "m_{#chi_{2}} = 50 GeV, c#tau = 10 mm", "lE");
    l1->AddEntry(h_SigMx2150_3Dsig, "m_{#chi_{2}} = 150 GeV, c#tau = 1 mm", "lE");
    l1->Draw();
    */

    TH1D *h_2016bkg_alpha3 = (TH1D *)h_ee_DY_alpha3->Clone("h_2016bkg_alpha3");

    h_2016bkg_alpha3->Add(h_ee_Top_alpha3);
    h_2016bkg_alpha3->Add(h_ee_Diboson_alpha3);
    h_2016bkg_alpha3->Add(h_ee_Triboson_alpha3);

    h_2016bkg_alpha3->SetLineColor(kGreen + 3);
    h_2016bkg_alpha3->SetFillColor(kGreen + 3);

    h_SigMx21_alpha3->SetLineWidth(2);
    h_SigMx2150_alpha3->SetLineWidth(2);
    h_SigMx250_alpha3->SetLineWidth(2);

    h_SigMx21_alpha3->SetLineColor(kRed);
    h_SigMx250_alpha3->SetLineColor(kGray + 2);
    h_SigMx2150_alpha3->SetLineColor(kBlue);

    h_2016bkg_alpha3->SetFillStyle(3001);

    h_SigMx21_alpha3->GetXaxis()->SetNdivisions(6, 5, 0);
    h_SigMx21_alpha3->GetXaxis()->SetTitleOffset(1.5);;
    h_SigMx21_alpha3->GetXaxis()->SetTitle("#alpha_{3D}");
    h_SigMx21_alpha3->GetYaxis()->SetNdivisions(6, 5, 0);
    h_SigMx21_alpha3->GetYaxis()->SetTitleOffset(1.5);
    h_SigMx21_alpha3->GetYaxis()->SetTitle("nJet / Normalized");


    h_SigMx21_alpha3->DrawNormalized("h e ");
    h_2016bkg_alpha3->DrawNormalized("h e same");
    
    h_SigMx250_alpha3->DrawNormalized("h e same");
    h_SigMx2150_alpha3->DrawNormalized("h e same");

    TLegend *l1 = new TLegend(0.5, 0.7, 0.90, 0.90);
    l1->SetBorderSize(0);
    l1->SetFillStyle(0);
    l1->SetTextSize(0.03);
    l1->AddEntry(h_2016bkg_alpha3, "2016 MC background", "f");
    l1->AddEntry(h_SigMx21_alpha3, "m_{#chi_{2}} = 1 GeV, c#tau = 1 mm", "lE");
    l1->AddEntry(h_SigMx250_alpha3, "m_{#chi_{2}} = 50 GeV, c#tau = 10 mm", "lE");
    l1->AddEntry(h_SigMx2150_alpha3, "m_{#chi_{2}} = 150 GeV, c#tau = 1 mm", "lE");
    l1->Draw();

    gStyle->SetOptStat(0);

    // h_2016bkg_3Dsig->Draw("h");
}