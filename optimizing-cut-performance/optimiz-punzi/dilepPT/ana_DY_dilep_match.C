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

void ana_DY_dilep_match()
{
    MergeBFiles merge_bfiles;
    MergeWeight merge_weight(&merge_bfiles);

    TH1D *h_inclu_dilepPT = new TH1D("h_inclu_dilepPT", "", 1000, 0, 1000);
    h_inclu_dilepPT->Sumw2();

    TH1D *h_ht0_dilepPT = new TH1D("h_ht0_dilepPT", "", 1000, 0, 1000);
    h_ht0_dilepPT->Sumw2();

    TH1D *h_ht70_dilepPT = new TH1D("h_ht70_dilepPT", "", 1000, 0, 1000);
    h_ht70_dilepPT->Sumw2();

    TH1D *h_ht70_dilepPT_match = new TH1D("h_ht70_dilepPT_match", "", 1000, 0, 1000);
    h_ht70_dilepPT_match->Sumw2();

    TH1D *h_ht70_dilepMass = new TH1D("h_ht70_dilepMass", "", 200, 0, 200);
    h_ht70_dilepMass->Sumw2();

    TH1D *h_ht100_dilepPT = new TH1D("h_ht100_dilepPT", "", 1000, 0, 1000);
    h_ht100_dilepPT->Sumw2();

    TH1D *h_ht100_dilepPT_match = new TH1D("h_ht100_dilepPT_match", "", 1000, 0, 1000);
    h_ht100_dilepPT_match->Sumw2();

    TH1D *h_ht200_dilepPT = new TH1D("h_ht200_dilepPT", "", 1000, 0, 1000);
    h_ht200_dilepPT->Sumw2();

    TH1D *h_ht200_dilepPT_match = new TH1D("h_ht200_dilepPT_match", "", 1000, 0, 1000);
    h_ht200_dilepPT_match->Sumw2();

    TH1D *h_ht400_dilepPT = new TH1D("h_ht400_dilepPT", "", 1000, 0, 1000);
    h_ht400_dilepPT->Sumw2();

    TH1D *h_ht400_dilepPT_match = new TH1D("h_ht400_dilepPT_match", "", 1000, 0, 1000);
    h_ht400_dilepPT_match->Sumw2();

    TH1D *h_ht600_dilepPT = new TH1D("h_ht600_dilepPT", "", 1000, 0, 1000);
    h_ht600_dilepPT->Sumw2();

    TH1D *h_ht800_dilepPT = new TH1D("h_ht800_dilepPT", "", 1000, 0, 1000);
    h_ht800_dilepPT->Sumw2();

    TH1D *h_ht1200_dilepPT = new TH1D("h_ht1200_dilepPT", "", 1000, 0, 1000);
    h_ht1200_dilepPT->Sumw2();

    TH1D *h_ht2500_dilepPT = new TH1D("h_ht2500_dilepPT", "", 1000, 0, 1000);
    h_ht2500_dilepPT->Sumw2();

    float_t HT;

    Int_t I_ht0_weight, I_ht70_weight, I_ht100_weight, I_ht200_weight, I_ht400_weight, I_ht600_weight,
        I_ht800_weight, I_ht1200_weight, I_ht2500_weight;

    float_t f_ht0_dilepPT, f_ht70_dilepPT, f_ht100_dilepPT, f_ht200_dilepPT, f_ht400_dilepPT, f_ht600_dilepPT, f_ht800_dilepPT,
        f_ht1200_dilepPT, f_ht2500_dilepPT;

    float_t f_ht0_dilepMass;

    vector<int> *v_ht0_genParId = new vector<int>();
    v_ht0_genParId->clear();

    vector<int> *v_ht0_genMomParId = new vector<int>();
    v_ht0_genMomParId->clear();

    TTree *T_inclusive;
    merge_bfiles.ee_DYincli->GetObject("T_tree", T_inclusive);
    T_inclusive->SetBranchAddress("I_weight", &I_ht0_weight);
    T_inclusive->SetBranchAddress("f_HT", &HT);
    T_inclusive->SetBranchAddress("f_dileptonPT", &f_ht0_dilepPT);
    T_inclusive->SetBranchAddress("f_dileptonmass", &f_ht0_dilepMass);
    T_inclusive->SetBranchAddress("v_match_parid", &v_ht0_genParId);
    T_inclusive->SetBranchAddress("v_match_momparid", &v_ht0_genMomParId);
    for (int evt = 0; evt < T_inclusive->GetEntries(); evt++)
    {
        T_inclusive->GetEntry(evt);
        // ee_for_inclusive_sample(HT,f_ht0_dilepPT , merge_weight, I_ht0_weight, h_pass_Bg);
        // h_inclu_dilepPT->Fill(f_ht0_dilepPT, I_ht0_weight *);

        //cout << "gen size = " << v_ht0_genParId->size() << endl;

        /* for (int ijet = 0; ijet < v_ht0_alpha3->size(); ijet++)
        {
            ee_for_inclusive_sample(HT, (*v_ht0_alpha3)[ijet], merge_weight, I_ht0_weight, h_bg_alpha3);
        }
        */
        if (HT < 70)
        {

            h_ht0_dilepPT->Fill(f_ht0_dilepPT, I_ht0_weight * merge_weight.ee_HT0Weight);
        }
        else if (HT >= 70 && HT < 100)
        {
            h_ht70_dilepPT->Fill(f_ht0_dilepPT, I_ht0_weight * merge_weight.ee_HT70Weight);
            for (int ipar = 0; ipar < v_ht0_genParId->size(); ipar++)
            {
                if (abs((*v_ht0_genParId)[ipar]) == 11 && (*v_ht0_genMomParId)[ipar] == 23)
                {
                    h_ht70_dilepPT_match->Fill(f_ht0_dilepPT, I_ht0_weight * merge_weight.ee_HT70Weight);
                }
                continue;
            }
            // h_ht70_dilepMass->Fill(f_ht0_dilepMass, I_ht0_weight * merge_weight.ee_HT70Weight);
        }
        else if (HT >= 100 && HT < 200)
        {
            h_ht100_dilepPT->Fill(f_ht0_dilepPT, I_ht0_weight * merge_weight.ee_HT100Weight);
             for (int ipar = 0; ipar < v_ht0_genParId->size(); ipar++)
            {
                if (abs((*v_ht0_genParId)[ipar]) == 11 && (*v_ht0_genMomParId)[ipar] == 23)
                {
                    h_ht100_dilepPT_match->Fill(f_ht0_dilepPT, I_ht0_weight * merge_weight.ee_HT100Weight);
                }
                continue;
            }
        }
        else if (HT >= 200 && HT < 400)
        {
            h_ht200_dilepPT->Fill(f_ht0_dilepPT, I_ht0_weight * merge_weight.ee_HT200Weight);
        }
        else if (HT >= 400 && HT < 600)
        {
            h_ht400_dilepPT->Fill(f_ht0_dilepPT, I_ht0_weight * merge_weight.ee_HT400Weight);
        }
        else if (HT >= 600 && HT < 800)
        {
            h_ht600_dilepPT->Fill(f_ht0_dilepPT, I_ht0_weight * merge_weight.ee_HT600Weight);
        }
        else if (HT >= 800 && HT < 1200)
        {
            h_ht800_dilepPT->Fill(f_ht0_dilepPT, I_ht0_weight * merge_weight.ee_HT800Weight);
        }
        else if (HT >= 1200 && HT < 2500)
        {
            h_ht1200_dilepPT->Fill(f_ht0_dilepPT, I_ht0_weight * merge_weight.ee_HT1200Weight);
        }
        else if (HT >= 2500)
        {
            h_ht2500_dilepPT->Fill(f_ht0_dilepPT, I_ht0_weight * merge_weight.ee_HT2500Weight);
        }
    }

    /*
    TTree *T_HT100;
    merge_bfiles.ee_DYHT100->GetObject("T_tree", T_HT100);
    T_HT100->SetBranchAddress("I_weight", &I_ht100_weight);
    T_HT100->SetBranchAddress("f_dileptonPT", &f_ht100_dilepPT);
    for (int evt = 0; evt < T_HT100->GetEntries(); evt++)
    {
        T_HT100->GetEntry(evt);
        h_ht100_dilepPT->Fill(f_ht100_dilepPT, I_ht100_weight* merge_weight.ee_HT100Weight);
    }
    TTree *T_HT200;
    merge_bfiles.ee_DYHT200->GetObject("T_tree", T_HT200);
    T_HT200->SetBranchAddress("I_weight", &I_ht200_weight);
    T_HT200->SetBranchAddress("f_dileptonPT", &f_ht200_dilepPT);
    for (int evt = 0; evt < T_HT200->GetEntries(); evt++)
    {
        T_HT200->GetEntry(evt);
        h_ht200_dilepPT->Fill(f_ht200_dilepPT, I_ht200_weight* merge_weight.ee_HT200Weight);
    }
    TTree *T_HT400;
    merge_bfiles.ee_DYHT400->GetObject("T_tree", T_HT400);
    T_HT400->SetBranchAddress("I_weight", &I_ht400_weight);
    T_HT400->SetBranchAddress("f_dileptonPT", &f_ht400_dilepPT);
    for (int evt = 0; evt < T_HT400->GetEntries(); evt++)
    {
        T_HT400->GetEntry(evt);
        h_ht400_dilepPT->Fill(f_ht400_dilepPT, I_ht400_weight* merge_weight.ee_HT400Weight);
    }
    TTree *T_HT600;
    merge_bfiles.ee_DYHT600->GetObject("T_tree", T_HT600);
    T_HT600->SetBranchAddress("I_weight", &I_ht600_weight);
    T_HT600->SetBranchAddress("f_dileptonPT", &f_ht600_dilepPT);
    for (int evt = 0; evt < T_HT600->GetEntries(); evt++)
    {
        T_HT600->GetEntry(evt);
        h_ht600_dilepPT->Fill(f_ht600_dilepPT, I_ht600_weight* merge_weight.ee_HT600Weight);
    }
    TTree *T_HT800;
    merge_bfiles.ee_DYHT800->GetObject("T_tree", T_HT800);
    T_HT800->SetBranchAddress("I_weight", &I_ht800_weight);
    T_HT800->SetBranchAddress("f_dileptonPT", &f_ht800_dilepPT);
    for (int evt = 0; evt < T_HT800->GetEntries(); evt++)
    {
        T_HT800->GetEntry(evt);
        h_ht800_dilepPT->Fill(f_ht800_dilepPT, I_ht800_weight* merge_weight.ee_HT800Weight);
    }
    TTree *T_HT1200;
    merge_bfiles.ee_DYHT1200->GetObject("T_tree", T_HT1200);
    T_HT1200->SetBranchAddress("I_weight", &I_ht1200_weight);
    T_HT1200->SetBranchAddress("f_dileptonPT", &f_ht1200_dilepPT);
    for (int evt = 0; evt < T_HT1200->GetEntries(); evt++)
    {
        T_HT1200->GetEntry(evt);
        h_ht1200_dilepPT->Fill(f_ht1200_dilepPT, I_ht1200_weight* merge_weight.ee_HT1200Weight);
    }
    TTree *T_HT2500;
    merge_bfiles.ee_DYHT2500->GetObject("T_tree", T_HT2500);
    T_HT2500->SetBranchAddress("I_weight", &I_ht2500_weight);
    T_HT2500->SetBranchAddress("f_dileptonPT", &f_ht2500_dilepPT);
    for (int evt = 0; evt < T_HT2500->GetEntries(); evt++)
    {
        T_HT2500->GetEntry(evt);
        h_ht2500_dilepPT->Fill(f_ht2500_dilepPT, I_ht2500_weight* merge_weight.ee_HT2500Weight);
    }*/

    h_ht0_dilepPT->SetLineWidth(2);
    h_ht70_dilepPT->SetLineWidth(2);
    h_ht100_dilepPT->SetLineWidth(2);
    h_ht200_dilepPT->SetLineWidth(2);
    h_ht400_dilepPT->SetLineWidth(2);
    h_ht600_dilepPT->SetLineWidth(2);
    h_ht800_dilepPT->SetLineWidth(2);
    h_ht1200_dilepPT->SetLineWidth(2);
    h_ht2500_dilepPT->SetLineWidth(2);

    h_ht0_dilepPT->SetLineColor(kAzure);
    h_ht70_dilepPT->SetLineColor(kViolet);
    h_ht100_dilepPT->SetLineColor(kRed);
    h_ht200_dilepPT->SetLineColor(kOrange);
    h_ht400_dilepPT->SetLineColor(kGreen);
    h_ht600_dilepPT->SetLineColor(kGray);
    h_ht800_dilepPT->SetLineColor(kPink);
    h_ht1200_dilepPT->SetLineColor(kSpring);
    h_ht2500_dilepPT->SetLineColor(kCyan);

    h_ht70_dilepMass->SetLineColor(kViolet);
    h_ht70_dilepPT_match->SetLineColor(kViolet);

    h_ht100_dilepPT->GetXaxis()->SetRangeUser(0, 400);
    h_ht100_dilepPT->GetYaxis()->SetTitle("nEvent");
    h_ht100_dilepPT->GetXaxis()->SetTitle("p_{T,ll}(GeV)");

    h_ht70_dilepPT->GetXaxis()->SetRangeUser(0, 400);
    h_ht70_dilepPT->GetYaxis()->SetTitle("nEvent");
    h_ht70_dilepPT->GetXaxis()->SetTitle("p_{T,ll}(GeV)");

    h_ht70_dilepPT_match->GetXaxis()->SetRangeUser(0, 400);
    h_ht70_dilepPT_match->GetYaxis()->SetTitle("nEvent");
    h_ht70_dilepPT_match->GetXaxis()->SetTitle("p_{T,ll}(GeV)");

    h_ht0_dilepPT->GetXaxis()->SetRangeUser(0, 140);
    h_ht0_dilepPT->GetYaxis()->SetTitle("nEvent");
    h_ht0_dilepPT->GetXaxis()->SetTitle("p_{T,ll}(GeV)");

    h_ht70_dilepMass->GetXaxis()->SetRangeUser(50, 150);
    h_ht70_dilepMass->GetYaxis()->SetTitle("nEvent");
    h_ht70_dilepMass->GetXaxis()->SetTitle("M_{ll}(GeV)");

    TH1D *h_htall_dilepPT = (TH1D *)h_ht0_dilepPT->Clone();
    h_htall_dilepPT->Add(h_ht70_dilepPT);
    h_htall_dilepPT->Add(h_ht100_dilepPT);
    h_htall_dilepPT->Add(h_ht200_dilepPT);
    h_htall_dilepPT->Add(h_ht400_dilepPT);
    h_htall_dilepPT->Add(h_ht600_dilepPT);
    h_htall_dilepPT->Add(h_ht800_dilepPT);
    h_htall_dilepPT->Add(h_ht1200_dilepPT);
    h_htall_dilepPT->Add(h_ht2500_dilepPT);

    h_htall_dilepPT->GetXaxis()->SetRangeUser(0, 250);

    auto canv = new TCanvas("canv", "canv", 800, 600);

    /*
    h_ht0_dilepPT->Draw("same");

    TLegend *l1 = new TLegend(0.5, 0.55, 0.7, 0.85);
    l1->SetBorderSize(0);
    l1->SetFillStyle(0);
    l1->SetTextSize(0.03);
    l1->AddEntry(h_ht0_dilepPT, "HT0to70", "l");
    l1->Draw();
    */
    
    h_ht70_dilepPT->Draw();
    // h_ht70_dilepMass->Draw();

    //h_ht100_dilepPT->Draw("same");
    //h_ht200_dilepPT->Draw("same");
    //h_ht400_dilepPT->Draw("same");
    //h_ht600_dilepPT->Draw("same");
    //h_ht800_dilepPT->Draw("same");
    //h_ht1200_dilepPT->Draw("same");
    //h_ht2500_dilepPT->Draw("same");

    TLegend *l1 = new TLegend(0.5, 0.55, 0.7, 0.85);
    l1->SetBorderSize(0);
    l1->SetFillStyle(0);
    l1->SetTextSize(0.03);
    l1->AddEntry(h_ht70_dilepPT, "HT70to100", "l");
    //l1->AddEntry(h_ht100_dilepPT, "HT100to200", "l");
    //l1->AddEntry(h_ht200_dilepPT, "HT200to400", "l");
    //l1->AddEntry(h_ht400_dilepPT, "HT400to600", "l");
    //l1->AddEntry(h_ht600_dilepPT, "HT600to800", "l");
    //l1->AddEntry(h_ht800_dilepPT, "HT800to1200", "l");
    //l1->AddEntry(h_ht1200_dilepPT, "HT1200to2500", "l");
    //l1->AddEntry(h_ht2500_dilepPT, "HT2500toInf", "l");
    l1->Draw();
    

    gStyle->SetOptStat(0);

    /*

    canv->Divide(3, 3);
    canv->cd(1);
    h_inclu_dilepPT->Draw();
    canv->cd(2);
    h_ht70_dilepPT->Draw();
    canv->cd(3);
    h_ht100_dilepPT->Draw();
    canv->cd(4);
    h_ht200_dilepPT->Draw();
    canv->cd(5);
    h_ht400_dilepPT->Draw();
    canv->cd(6);
    h_ht600_dilepPT->Draw();
    canv->cd(7);
    h_ht800_dilepPT->Draw();
    canv->cd(8);
    h_ht1200_dilepPT->Draw();
    canv->cd(9);
    h_ht2500_dilepPT->Draw();
    */
    /*
    TLegend *l1 = new TLegend(0.5, 0.55, 0.7, 0.85);
    l1->SetBorderSize(0);
    l1->SetFillStyle(0);
    l1->SetTextSize(0.03);
    l1->AddEntry(h_ht70_dilepPT, "HT0toInf", "l");
    l1->Draw();
    h_htall_dilepPT->Draw();
    */

    // canv->SaveAs("DY_HT0to70_dilepPT_nocut.png");
    //  canv->SaveAs("DY_HTall_dilepPT2.png");
    canv->SaveAs("DY_HT70_dilepPT_nocut.png");
    //    h_ht0_dilepPT->SetLineColor(kBlue);
    //    h_ht70_dilepPT->SetLineColor(kPurple);
}