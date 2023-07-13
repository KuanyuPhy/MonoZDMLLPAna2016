#include "TFile.h"
#include <iostream>
#include "TTree.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <TH1D.h>
#include <string>
#include <TAttLine.h>
#include <TStyle.h>
#include "./../../../lib/kuan_ana_utils.h"

void ee_punzi()
{
    const char *dirMerge = "/home/kuanyu/Documents/CMS/Background_Estimate/cut_opt/punzi/alpha";

    TFile *ee_bg_alphacut1 = TFile::Open(Form("%s/%s", dirMerge, "bg_alpha1.root"));
    TFile *ee_bg_alphacut2 = TFile::Open(Form("%s/%s", dirMerge, "bg_alpha2.root"));
    TFile *ee_bg_alphacut3 = TFile::Open(Form("%s/%s", dirMerge, "bg_alpha3.root"));
    TFile *ee_bg_alphacut4 = TFile::Open(Form("%s/%s", dirMerge, "bg_alpha4.root"));
    TFile *ee_bg_alphacut5 = TFile::Open(Form("%s/%s", dirMerge, "bg_alpha5.root"));
    TFile *ee_bg_alphacut6 = TFile::Open(Form("%s/%s", dirMerge, "bg_alpha6.root"));
    TFile *ee_bg_alphacut7 = TFile::Open(Form("%s/%s", dirMerge, "bg_alpha7.root"));
    TFile *ee_bg_alphacut8 = TFile::Open(Form("%s/%s", dirMerge, "bg_alpha8.root"));
    TFile *ee_bg_alphacut9 = TFile::Open(Form("%s/%s", dirMerge, "bg_alpha9.root"));
    TFile *ee_bg_alphacut10 = TFile::Open(Form("%s/%s", dirMerge, "bg_alpha10.root"));
    TFile *ee_bg_alphacut11 = TFile::Open(Form("%s/%s", dirMerge, "bg_alpha11.root"));
    TFile *ee_bg_alphacut12 = TFile::Open(Form("%s/%s", dirMerge, "bg_alpha12.root"));
    TFile *ee_bg_alphacut13 = TFile::Open(Form("%s/%s", dirMerge, "bg_alpha13.root"));
    TFile *ee_bg_alphacut14 = TFile::Open(Form("%s/%s", dirMerge, "bg_alpha14.root"));
    TFile *ee_bg_alphacut15 = TFile::Open(Form("%s/%s", dirMerge, "bg_alpha15.root"));
    TFile *ee_bg_alphacut16 = TFile::Open(Form("%s/%s", dirMerge, "bg_alpha16.root"));
    TFile *ee_bg_alphacut17 = TFile::Open(Form("%s/%s", dirMerge, "bg_alpha17.root"));
    TFile *ee_bg_alphacut18 = TFile::Open(Form("%s/%s", dirMerge, "bg_alpha18.root"));
    TFile *ee_bg_alphacut19 = TFile::Open(Form("%s/%s", dirMerge, "bg_alpha19.root"));
    TFile *ee_bg_alphacut20 = TFile::Open(Form("%s/%s", dirMerge, "bg_alpha20.root"));

    // TH1D *ee_bg_alphacut_nJets[20];
    // for(int i=0; i<20; i++)
    // {
    //     ee_bg_alphacut_nJets[i] = ee_bg_alphacut%i->Get<TH1D>("h_Bg_nJet");
    // }

    TH1D *ee_bg_alphacut1_nJets = ee_bg_alphacut1->Get<TH1D>("h_Bg_nJet");
    TH1D *ee_bg_alphacut2_nJets = ee_bg_alphacut2->Get<TH1D>("h_Bg_nJet");
    TH1D *ee_bg_alphacut3_nJets = ee_bg_alphacut3->Get<TH1D>("h_Bg_nJet");
    TH1D *ee_bg_alphacut4_nJets = ee_bg_alphacut4->Get<TH1D>("h_Bg_nJet");
    TH1D *ee_bg_alphacut5_nJets = ee_bg_alphacut5->Get<TH1D>("h_Bg_nJet");
    TH1D *ee_bg_alphacut6_nJets = ee_bg_alphacut6->Get<TH1D>("h_Bg_nJet");
    TH1D *ee_bg_alphacut7_nJets = ee_bg_alphacut7->Get<TH1D>("h_Bg_nJet");
    TH1D *ee_bg_alphacut8_nJets = ee_bg_alphacut8->Get<TH1D>("h_Bg_nJet");
    TH1D *ee_bg_alphacut9_nJets = ee_bg_alphacut9->Get<TH1D>("h_Bg_nJet");
    TH1D *ee_bg_alphacut10_nJets = ee_bg_alphacut10->Get<TH1D>("h_Bg_nJet");
    TH1D *ee_bg_alphacut11_nJets = ee_bg_alphacut11->Get<TH1D>("h_Bg_nJet");
    TH1D *ee_bg_alphacut12_nJets = ee_bg_alphacut12->Get<TH1D>("h_Bg_nJet");
    TH1D *ee_bg_alphacut13_nJets = ee_bg_alphacut13->Get<TH1D>("h_Bg_nJet");
    TH1D *ee_bg_alphacut14_nJets = ee_bg_alphacut14->Get<TH1D>("h_Bg_nJet");
    TH1D *ee_bg_alphacut15_nJets = ee_bg_alphacut15->Get<TH1D>("h_Bg_nJet");
    TH1D *ee_bg_alphacut16_nJets = ee_bg_alphacut16->Get<TH1D>("h_Bg_nJet");
    TH1D *ee_bg_alphacut17_nJets = ee_bg_alphacut17->Get<TH1D>("h_Bg_nJet");
    TH1D *ee_bg_alphacut18_nJets = ee_bg_alphacut18->Get<TH1D>("h_Bg_nJet");
    TH1D *ee_bg_alphacut19_nJets = ee_bg_alphacut19->Get<TH1D>("h_Bg_nJet");
    TH1D *ee_bg_alphacut20_nJets = ee_bg_alphacut20->Get<TH1D>("h_Bg_nJet");

    std::vector<double> nBg_alphacut;

    nBg_alphacut.push_back(ee_bg_alphacut1_nJets->Integral(3., 30.));
    nBg_alphacut.push_back(ee_bg_alphacut2_nJets->Integral(3., 30.));
    nBg_alphacut.push_back(ee_bg_alphacut3_nJets->Integral(3., 30.));
    nBg_alphacut.push_back(ee_bg_alphacut4_nJets->Integral(3., 30.));
    nBg_alphacut.push_back(ee_bg_alphacut5_nJets->Integral(3., 30.));
    nBg_alphacut.push_back(ee_bg_alphacut6_nJets->Integral(3., 30.));
    nBg_alphacut.push_back(ee_bg_alphacut7_nJets->Integral(3., 30.));
    nBg_alphacut.push_back(ee_bg_alphacut8_nJets->Integral(3., 30.));
    nBg_alphacut.push_back(ee_bg_alphacut9_nJets->Integral(3., 30.));
    nBg_alphacut.push_back(ee_bg_alphacut10_nJets->Integral(3., 30.));
    nBg_alphacut.push_back(ee_bg_alphacut11_nJets->Integral(3., 30.));
    nBg_alphacut.push_back(ee_bg_alphacut12_nJets->Integral(3., 30.));
    nBg_alphacut.push_back(ee_bg_alphacut13_nJets->Integral(3., 30.));
    nBg_alphacut.push_back(ee_bg_alphacut14_nJets->Integral(3., 30.));
    nBg_alphacut.push_back(ee_bg_alphacut15_nJets->Integral(3., 30.));
    nBg_alphacut.push_back(ee_bg_alphacut16_nJets->Integral(3., 30.));
    nBg_alphacut.push_back(ee_bg_alphacut17_nJets->Integral(3., 30.));
    nBg_alphacut.push_back(ee_bg_alphacut18_nJets->Integral(3., 30.));
    nBg_alphacut.push_back(ee_bg_alphacut19_nJets->Integral(3., 30.));
    nBg_alphacut.push_back(ee_bg_alphacut20_nJets->Integral(3., 30.));

    std::cout << "nBg_alphacut.size = " << nBg_alphacut.size() << std::endl;

    for (int i = 0; i < nBg_alphacut.size(); i++)
    {
        std::cout << nBg_alphacut[i] << std::endl;
    }

    /*For Signal*/
    TFile *ee_Sig1_file = TFile::Open("/home/kuanyu/Documents/root_file/Ztoee/ee_Mx2_1_old_remove_0alpha.root");
    TFile *ee_Sig50_file = TFile::Open("/home/kuanyu/Documents/root_file/Ztoee/ee_Mx2_50_old_remove_0alpha.root");
    TFile *ee_Sig150_file = TFile::Open("/home/kuanyu/Documents/root_file/Ztoee/ee_Mx2_150_old_remove_0alpha.root");

    float_t f_Sig1_Met, f_Sig50_Met, f_Sig150_Met;

    Int_t I_Sig1_weight, I_Sig50_weight, I_Sig150_weight;

    std::vector<float> *v_Sig1_alpha = new std::vector<float>();
    std::vector<float> *v_Sig50_alpha = new std::vector<float>();
    std::vector<float> *v_Sig150_alpha = new std::vector<float>();

    v_Sig1_alpha->clear();
    v_Sig50_alpha->clear();
    v_Sig150_alpha->clear();

    int sumstep = 20;

    TH1D *h_Sig1_nJet[sumstep];
    TH1D *h_Sig1_nJet_cuted[sumstep];

    TH1D *h_Sig50_nJet[sumstep];
    TH1D *h_Sig50_nJet_cuted[sumstep];

    TH1D *h_Sig150_nJet[sumstep];
    TH1D *h_Sig150_nJet_cuted[sumstep];

    for (int i = 0; i < 20; i++)
    {
        h_Sig1_nJet[i] = new TH1D(Form("h_Sig1_nJet_%i", i + 1), "", 30, 0., 30.);
        h_Sig1_nJet_cuted[i] = new TH1D(Form("h_Sig1_nJet_cuted_%i", i + 1), "", 30, 0., 30.);

        h_Sig50_nJet[i] = new TH1D(Form("h_Sig50_nJet_%i", i + 1), "", 30, 0., 30.);
        h_Sig50_nJet_cuted[i] = new TH1D(Form("h_Sig50_nJet_cuted_%i", i + 1), "", 30, 0., 30.);

        h_Sig150_nJet[i] = new TH1D(Form("h_Sig150_nJet_%i", i + 1), "", 30, 0., 30.);
        h_Sig150_nJet_cuted[i] = new TH1D(Form("h_Sig150_nJet_cuted_%i", i + 1), "", 30, 0., 30.);
    }

    double METcut = 140.;

    for (int i = 0; i < 20; i++)
    {
        double AlphaCut = (i + 1) * 0.05;
        std::cout << "alpha cut = " << AlphaCut << std::endl;

        TTree *T_ee_Sig1;
        ee_Sig1_file->GetObject("T_tree", T_ee_Sig1);
        T_ee_Sig1->SetBranchAddress("I_weight", &I_Sig1_weight);
        T_ee_Sig1->SetBranchAddress("f_Met", &f_Sig1_Met);
        T_ee_Sig1->SetBranchAddress("v_fakealpha3", &v_Sig1_alpha);
        for (int evt = 0; evt < T_ee_Sig1->GetEntries(); evt++)
        {
            T_ee_Sig1->GetEntry(evt);

            if (f_Sig1_Met <= METcut)
            {
                continue;
            }
            int jet_passalpha_cut = 0;
            for (int ijet = 0; ijet < v_Sig1_alpha->size(); ijet++)
            {
                if ((*v_Sig1_alpha)[ijet] < AlphaCut)
                {
                    jet_passalpha_cut++;
                }
            }
            if (jet_passalpha_cut != 0)
            {
                std::cout << "Sig150 njet cut = " << jet_passalpha_cut << " Sig150 weight = " << I_Sig1_weight << std::endl;
            }
            h_Sig1_nJet[i]->Fill(jet_passalpha_cut, I_Sig1_weight);
        }

        TTree *T_ee_Sig50;
        ee_Sig50_file->GetObject("T_tree", T_ee_Sig50);
        T_ee_Sig50->SetBranchAddress("I_weight", &I_Sig50_weight);
        T_ee_Sig50->SetBranchAddress("f_Met", &f_Sig50_Met);
        T_ee_Sig50->SetBranchAddress("v_fakealpha3", &v_Sig50_alpha);
        for (int evt = 0; evt < T_ee_Sig50->GetEntries(); evt++)
        {
            T_ee_Sig50->GetEntry(evt);

            if (f_Sig50_Met <= METcut)
            {
                continue;
            }
            int jet_passalpha_cut = 0;
            for (int ijet = 0; ijet < v_Sig50_alpha->size(); ijet++)
            {
                if ((*v_Sig50_alpha)[ijet] < AlphaCut)
                {
                    jet_passalpha_cut++;
                }
            }
            h_Sig50_nJet[i]->Fill(jet_passalpha_cut, I_Sig50_weight);
        }

        TTree *T_ee_Sig150;
        ee_Sig150_file->GetObject("T_tree", T_ee_Sig150);
        T_ee_Sig150->SetBranchAddress("I_weight", &I_Sig150_weight);
        T_ee_Sig150->SetBranchAddress("f_Met", &f_Sig150_Met);
        T_ee_Sig150->SetBranchAddress("v_fakealpha3", &v_Sig150_alpha);
        for (int evt = 0; evt < T_ee_Sig150->GetEntries(); evt++)
        {
            T_ee_Sig150->GetEntry(evt);
            if (f_Sig150_Met <= METcut)
            {
                continue;
            }
            int jet_passalpha_cut = 0;
            for (int ijet = 0; ijet < v_Sig150_alpha->size(); ijet++)
            {
                if ((*v_Sig150_alpha)[ijet] < AlphaCut)
                {
                    jet_passalpha_cut++;
                }
            }
            h_Sig150_nJet[i]->Fill(jet_passalpha_cut, I_Sig150_weight);
        }
    } // Loop of alpha cut

    /*Calculate Signal Eff*/
    std::vector<double> v_eff_Sig1;
    std::vector<double> v_eff_Sig50;
    std::vector<double> v_eff_Sig150;

    /*Punzi Signific*/
    std::vector<double> v_punzi_Sig1;
    std::vector<double> v_punzi_Sig50;
    std::vector<double> v_punzi_Sig150;

    TH1D *h_punzi_Sig1 = new TH1D("h_punzi_Sig1", "", 20, 0., 20.);
    TH1D *h_punzi_Sig50 = new TH1D("h_punzi_Sig50", "", 20, 0., 20.);
    TH1D *h_punzi_Sig150 = new TH1D("h_punzi_Sig150", "", 20, 0., 20.);

    for (int i = 0; i < 20; i++)
    {
        double eff_Sig1 = static_cast<double>(h_Sig1_nJet[i]->Integral(3., 30.)) / (h_Sig1_nJet[i]->Integral(1., 30.));
        double eff_Sig50 = static_cast<double>(h_Sig50_nJet[i]->Integral(3., 30.)) / (h_Sig50_nJet[i]->Integral(1., 30.));
        double eff_Sig150 = static_cast<double>(h_Sig150_nJet[i]->Integral(3., 30.)) / (h_Sig150_nJet[i]->Integral(1., 30.));

        v_eff_Sig1.push_back(eff_Sig1);
        v_eff_Sig50.push_back(eff_Sig50);
        v_eff_Sig150.push_back(eff_Sig150);

        std::cout << "eff Sig1 = " << eff_Sig1 << std::endl;
        std::cout << "eff Sig50 = " << eff_Sig50 << std::endl;
        std::cout << "eff Sig150 = " << eff_Sig150 << std::endl;

        double punzi_Sig1 = static_cast<double>(punzi(eff_Sig1, nBg_alphacut[i]));
        double punzi_Sig50 = static_cast<double>(punzi(eff_Sig50, nBg_alphacut[i]));
        double punzi_Sig150 = static_cast<double>(punzi(eff_Sig150, nBg_alphacut[i]));

        std::cout << "punzi Sig1 = " << punzi_Sig1 << std::endl;
        std::cout << "punzi Sig50 = " << punzi_Sig50 << std::endl;
        std::cout << "punzi Sig150 = " << punzi_Sig150 << std::endl;

        h_punzi_Sig1->SetBinContent(i + 1, punzi_Sig1);
        h_punzi_Sig50->SetBinContent(i + 1, punzi_Sig50);
        h_punzi_Sig150->SetBinContent(i + 1, punzi_Sig150);
    }

    TString outputfile = "./../alpha/ee_alpha_punzi.root";
    TFile *outfile = TFile::Open(outputfile, "RECREATE");
    h_punzi_Sig1->Write();
    h_punzi_Sig50->Write();
    h_punzi_Sig150->Write();
    h_Sig1_nJet[0]->Write();
    outfile->Close();

    // h_punzi_Sig1->Draw("text45");

    ee_bg_alphacut1->Close();
    ee_bg_alphacut2->Close();
    ee_bg_alphacut3->Close();
    ee_bg_alphacut4->Close();
    ee_bg_alphacut5->Close();
    ee_bg_alphacut6->Close();
    ee_bg_alphacut7->Close();
    ee_bg_alphacut8->Close();
    ee_bg_alphacut9->Close();
    ee_bg_alphacut10->Close();
    ee_bg_alphacut11->Close();
    ee_bg_alphacut12->Close();
    ee_bg_alphacut13->Close();
    ee_bg_alphacut14->Close();
    ee_bg_alphacut15->Close();
    ee_bg_alphacut16->Close();
    ee_bg_alphacut17->Close();
    ee_bg_alphacut18->Close();
    ee_bg_alphacut19->Close();
    ee_bg_alphacut20->Close();

    ee_Sig1_file->Close();
    ee_Sig50_file->Close();
    ee_Sig150_file->Close();
}

int main()
{
    ee_punzi();

    return 0;
}