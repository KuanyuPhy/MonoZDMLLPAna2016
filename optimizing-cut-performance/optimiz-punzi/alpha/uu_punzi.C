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

void uu_punzi()
{
    const char *dirMerge = "/home/kuanyu/Documents/CMS/Background_Estimate/cut_opt/punzi/alpha";

    TFile *uu_bg_alphacut1 = TFile::Open(Form("%s/%s", dirMerge, "bg_alpha1.root"));
    TFile *uu_bg_alphacut2 = TFile::Open(Form("%s/%s", dirMerge, "bg_alpha2.root"));
    TFile *uu_bg_alphacut3 = TFile::Open(Form("%s/%s", dirMerge, "bg_alpha3.root"));
    TFile *uu_bg_alphacut4 = TFile::Open(Form("%s/%s", dirMerge, "bg_alpha4.root"));
    TFile *uu_bg_alphacut5 = TFile::Open(Form("%s/%s", dirMerge, "bg_alpha5.root"));
    TFile *uu_bg_alphacut6 = TFile::Open(Form("%s/%s", dirMerge, "bg_alpha6.root"));
    TFile *uu_bg_alphacut7 = TFile::Open(Form("%s/%s", dirMerge, "bg_alpha7.root"));
    TFile *uu_bg_alphacut8 = TFile::Open(Form("%s/%s", dirMerge, "bg_alpha8.root"));
    TFile *uu_bg_alphacut9 = TFile::Open(Form("%s/%s", dirMerge, "bg_alpha9.root"));
    TFile *uu_bg_alphacut10 = TFile::Open(Form("%s/%s", dirMerge, "bg_alpha10.root"));
    TFile *uu_bg_alphacut11 = TFile::Open(Form("%s/%s", dirMerge, "bg_alpha11.root"));
    TFile *uu_bg_alphacut12 = TFile::Open(Form("%s/%s", dirMerge, "bg_alpha12.root"));
    TFile *uu_bg_alphacut13 = TFile::Open(Form("%s/%s", dirMerge, "bg_alpha13.root"));
    TFile *uu_bg_alphacut14 = TFile::Open(Form("%s/%s", dirMerge, "bg_alpha14.root"));
    TFile *uu_bg_alphacut15 = TFile::Open(Form("%s/%s", dirMerge, "bg_alpha15.root"));
    TFile *uu_bg_alphacut16 = TFile::Open(Form("%s/%s", dirMerge, "bg_alpha16.root"));
    TFile *uu_bg_alphacut17 = TFile::Open(Form("%s/%s", dirMerge, "bg_alpha17.root"));
    TFile *uu_bg_alphacut18 = TFile::Open(Form("%s/%s", dirMerge, "bg_alpha18.root"));
    TFile *uu_bg_alphacut19 = TFile::Open(Form("%s/%s", dirMerge, "bg_alpha19.root"));
    TFile *uu_bg_alphacut20 = TFile::Open(Form("%s/%s", dirMerge, "bg_alpha20.root"));

    // TH1D *uu_bg_alphacut_nJets[20];
    // for(int i=0; i<20; i++)
    // {
    //     uu_bg_alphacut_nJets[i] = uu_bg_alphacut%i->Get<TH1D>("h_Bg_nJet");
    // }

    TH1D *uu_bg_alphacut1_nJets = uu_bg_alphacut1->Get<TH1D>("h_Bg_nJet");
    TH1D *uu_bg_alphacut2_nJets = uu_bg_alphacut2->Get<TH1D>("h_Bg_nJet");
    TH1D *uu_bg_alphacut3_nJets = uu_bg_alphacut3->Get<TH1D>("h_Bg_nJet");
    TH1D *uu_bg_alphacut4_nJets = uu_bg_alphacut4->Get<TH1D>("h_Bg_nJet");
    TH1D *uu_bg_alphacut5_nJets = uu_bg_alphacut5->Get<TH1D>("h_Bg_nJet");
    TH1D *uu_bg_alphacut6_nJets = uu_bg_alphacut6->Get<TH1D>("h_Bg_nJet");
    TH1D *uu_bg_alphacut7_nJets = uu_bg_alphacut7->Get<TH1D>("h_Bg_nJet");
    TH1D *uu_bg_alphacut8_nJets = uu_bg_alphacut8->Get<TH1D>("h_Bg_nJet");
    TH1D *uu_bg_alphacut9_nJets = uu_bg_alphacut9->Get<TH1D>("h_Bg_nJet");
    TH1D *uu_bg_alphacut10_nJets = uu_bg_alphacut10->Get<TH1D>("h_Bg_nJet");
    TH1D *uu_bg_alphacut11_nJets = uu_bg_alphacut11->Get<TH1D>("h_Bg_nJet");
    TH1D *uu_bg_alphacut12_nJets = uu_bg_alphacut12->Get<TH1D>("h_Bg_nJet");
    TH1D *uu_bg_alphacut13_nJets = uu_bg_alphacut13->Get<TH1D>("h_Bg_nJet");
    TH1D *uu_bg_alphacut14_nJets = uu_bg_alphacut14->Get<TH1D>("h_Bg_nJet");
    TH1D *uu_bg_alphacut15_nJets = uu_bg_alphacut15->Get<TH1D>("h_Bg_nJet");
    TH1D *uu_bg_alphacut16_nJets = uu_bg_alphacut16->Get<TH1D>("h_Bg_nJet");
    TH1D *uu_bg_alphacut17_nJets = uu_bg_alphacut17->Get<TH1D>("h_Bg_nJet");
    TH1D *uu_bg_alphacut18_nJets = uu_bg_alphacut18->Get<TH1D>("h_Bg_nJet");
    TH1D *uu_bg_alphacut19_nJets = uu_bg_alphacut19->Get<TH1D>("h_Bg_nJet");
    TH1D *uu_bg_alphacut20_nJets = uu_bg_alphacut20->Get<TH1D>("h_Bg_nJet");

    std::vector<double> nBg_alphacut;

    nBg_alphacut.push_back(uu_bg_alphacut1_nJets->Integral(2., 30.));
    nBg_alphacut.push_back(uu_bg_alphacut2_nJets->Integral(2., 30.));
    nBg_alphacut.push_back(uu_bg_alphacut3_nJets->Integral(2., 30.));
    nBg_alphacut.push_back(uu_bg_alphacut4_nJets->Integral(2., 30.));
    nBg_alphacut.push_back(uu_bg_alphacut5_nJets->Integral(2., 30.));
    nBg_alphacut.push_back(uu_bg_alphacut6_nJets->Integral(2., 30.));
    nBg_alphacut.push_back(uu_bg_alphacut7_nJets->Integral(2., 30.));
    nBg_alphacut.push_back(uu_bg_alphacut8_nJets->Integral(2., 30.));
    nBg_alphacut.push_back(uu_bg_alphacut9_nJets->Integral(2., 30.));
    nBg_alphacut.push_back(uu_bg_alphacut10_nJets->Integral(2., 30.));
    nBg_alphacut.push_back(uu_bg_alphacut11_nJets->Integral(2., 30.));
    nBg_alphacut.push_back(uu_bg_alphacut12_nJets->Integral(2., 30.));
    nBg_alphacut.push_back(uu_bg_alphacut13_nJets->Integral(2., 30.));
    nBg_alphacut.push_back(uu_bg_alphacut14_nJets->Integral(2., 30.));
    nBg_alphacut.push_back(uu_bg_alphacut15_nJets->Integral(2., 30.));
    nBg_alphacut.push_back(uu_bg_alphacut16_nJets->Integral(2., 30.));
    nBg_alphacut.push_back(uu_bg_alphacut17_nJets->Integral(2., 30.));
    nBg_alphacut.push_back(uu_bg_alphacut18_nJets->Integral(2., 30.));
    nBg_alphacut.push_back(uu_bg_alphacut19_nJets->Integral(2., 30.));
    nBg_alphacut.push_back(uu_bg_alphacut20_nJets->Integral(2., 30.));

    std::cout << "nBg_alphacut.size = " << nBg_alphacut.size() << std::endl;

    for (int i = 0; i < nBg_alphacut.size(); i++)
    {
        std::cout << nBg_alphacut[i] << std::endl;
    }

    /*For Signal*/
    TFile *uu_Sig1_file = TFile::Open("/home/kuanyu/Documents/root_file/Ztouu/Mu_Mx1_old_remove_0alpha.root");
    TFile *uu_Sig50_file = TFile::Open("/home/kuanyu/Documents/root_file/Ztouu/Mu_Mx50_old_remove_0alpha.root");
    TFile *uu_Sig150_file = TFile::Open("/home/kuanyu/Documents/root_file/Ztouu/Mu_Mx150_old_remove_0alpha.root");

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

    double METcut = 120.;

    for (int i = 0; i < 20; i++)
    {
        double AlphaCut = (i + 1) * 0.05;
        std::cout << "alpha cut = " << AlphaCut << std::endl;

        TTree *T_uu_Sig1;
        uu_Sig1_file->GetObject("T_tree", T_uu_Sig1);
        T_uu_Sig1->SetBranchAddress("I_weight", &I_Sig1_weight);
        T_uu_Sig1->SetBranchAddress("f_Met", &f_Sig1_Met);
        T_uu_Sig1->SetBranchAddress("v_fakealpha", &v_Sig1_alpha);
        for (int evt = 0; evt < T_uu_Sig1->GetEntries(); evt++)
        {
            T_uu_Sig1->GetEntry(evt);

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
            h_Sig1_nJet[i]->Fill(jet_passalpha_cut, I_Sig1_weight);
        }

        TTree *T_uu_Sig50;
        uu_Sig50_file->GetObject("T_tree", T_uu_Sig50);
        T_uu_Sig50->SetBranchAddress("I_weight", &I_Sig50_weight);
        T_uu_Sig50->SetBranchAddress("f_Met", &f_Sig50_Met);
        T_uu_Sig50->SetBranchAddress("v_fakealpha", &v_Sig50_alpha);
        for (int evt = 0; evt < T_uu_Sig50->GetEntries(); evt++)
        {
            T_uu_Sig50->GetEntry(evt);

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

        TTree *T_uu_Sig150;
        uu_Sig150_file->GetObject("T_tree", T_uu_Sig150);
        T_uu_Sig150->SetBranchAddress("I_weight", &I_Sig150_weight);
        T_uu_Sig150->SetBranchAddress("f_Met", &f_Sig150_Met);
        T_uu_Sig150->SetBranchAddress("v_fakealpha", &v_Sig150_alpha);
        for (int evt = 0; evt < T_uu_Sig150->GetEntries(); evt++)
        {
            T_uu_Sig150->GetEntry(evt);
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
        double eff_Sig1 = static_cast<double>(h_Sig1_nJet[i]->Integral(3., 30.)) / (h_Sig1_nJet[i]->Integral(2., 30.));
        double eff_Sig50 = static_cast<double>(h_Sig50_nJet[i]->Integral(3., 30.)) / (h_Sig50_nJet[i]->Integral(2., 30.));
        double eff_Sig150 = static_cast<double>(h_Sig150_nJet[i]->Integral(3., 30.)) / (h_Sig150_nJet[i]->Integral(2., 30.));

        v_eff_Sig1.push_back(eff_Sig1);
        v_eff_Sig50.push_back(eff_Sig50);
        v_eff_Sig150.push_back(eff_Sig150);

        double punzi_Sig1 = static_cast<double>(punzi(eff_Sig1, nBg_alphacut[i]));
        double punzi_Sig50 = static_cast<double>(punzi(eff_Sig50, nBg_alphacut[i]));
        double punzi_Sig150 = static_cast<double>(punzi(eff_Sig150, nBg_alphacut[i]));

        std::cout << "punzi Sig1 = " << punzi_Sig1 << std::endl;

        h_punzi_Sig1->SetBinContent(i + 1, punzi_Sig1);
        h_punzi_Sig50->SetBinContent(i + 1, punzi_Sig50);
        h_punzi_Sig150->SetBinContent(i + 1, punzi_Sig150);
    }
    TString outputfile = "./../alpha/uu_alpha_punzi.root";
    TFile *outfile = TFile::Open(outputfile, "RECREATE");
    h_punzi_Sig1->Write();
    h_punzi_Sig50->Write();
    h_punzi_Sig150->Write();
    outfile->Close();

    // h_punzi_Sig1->Draw("text45");

    uu_bg_alphacut1->Close();
    uu_bg_alphacut2->Close();
    uu_bg_alphacut3->Close();
    uu_bg_alphacut4->Close();
    uu_bg_alphacut5->Close();
    uu_bg_alphacut6->Close();
    uu_bg_alphacut7->Close();
    uu_bg_alphacut8->Close();
    uu_bg_alphacut9->Close();
    uu_bg_alphacut10->Close();
    uu_bg_alphacut11->Close();
    uu_bg_alphacut12->Close();
    uu_bg_alphacut13->Close();
    uu_bg_alphacut14->Close();
    uu_bg_alphacut15->Close();
    uu_bg_alphacut16->Close();
    uu_bg_alphacut17->Close();
    uu_bg_alphacut18->Close();
    uu_bg_alphacut19->Close();
    uu_bg_alphacut20->Close();

    uu_Sig1_file->Close();
    uu_Sig50_file->Close();
    uu_Sig150_file->Close();
}

int main()
{
    uu_punzi();

    return 0;
}