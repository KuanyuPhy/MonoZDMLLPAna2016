#include "TFile.h"
#include <iostream>
#include "TTree.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <TH1D.h>
#include <string>
#include <TAttLine.h>
#include <TStyle.h>
#include "./../../../lib/Cross_section.h"
#include "./../../../lib/kuan_ana_utils.h"
using namespace std;

void uu_Diboson_alpha(const char *scanalpha_step = "tmp", TString outputfile = "./output/tmp.root")
{
    double alphacut = atoi(scanalpha_step) * 0.05;

    /*Open source root file*/
    MergeBFiles merge_bfiles;
    MergeWeight merge_weight(&merge_bfiles);

    // int sumstep = 20;
    double METcut = 120.;

    // TH1D *h_Bg_nJet_cut[sumstep];
    // TH1D *h_Bg_nJet_[sumstep];
    // TH1D *h_Bg_alpha = new TH1D("h_Bg_alpha", "", 20, 0, 1);

    TH1D *h_Bg_nJet = new TH1D("h_Bg_nJet", "", 30, 0., 30.);
    TH1D *h_Bg_nJet_cuted = new TH1D("h_Bg_nJet_cuted", "at least two jets pass alpha cut", 30, 0., 30.);

    Int_t f_gg_ZZ_2e2mu_weight, f_gg_ZZ_2e2nu_weight, f_gg_ZZ_2e2tau_weight, f_gg_ZZ_2mu2nu_weight,
        f_gg_ZZ_2mu2tau_weight, f_gg_ZZ_4e_weight, f_gg_ZZ_4mu_weight, f_gg_ZZ_4tau_weight, f_gg_WW_2L2Nu_weight,
        f_qq_WW_2L2Nu_weight, f_qq_WZ_2L2Q_weight, f_qq_WZ_3LNu_weight, f_qq_ZZ_2L2Nu_weight, f_qq_ZZ_2L2Q_weight,
        f_qq_ZZ_4L_weight;

    float_t f_gg_ZZ_2e2mu_met, f_gg_ZZ_2e2nu_met, f_gg_ZZ_2e2tau_met, f_gg_ZZ_2mu2nu_met,
        f_gg_ZZ_2mu2tau_met, f_gg_ZZ_4e_met, f_gg_ZZ_4mu_met, f_gg_ZZ_4tau_met, f_gg_WW_2L2Nu_met,
        f_qq_WW_2L2Nu_met, f_qq_WZ_2L2Q_met, f_qq_WZ_3LNu_met, f_qq_ZZ_2L2Nu_met, f_qq_ZZ_2L2Q_met,
        f_qq_ZZ_4L_met;

    vector<float> *v_gg_ZZ_2e2mu_alpha = new vector<float>();
    vector<float> *v_gg_ZZ_2e2nu_alpha = new vector<float>();
    vector<float> *v_gg_ZZ_2e2tau_alpha = new vector<float>();
    vector<float> *v_gg_ZZ_2mu2nu_alpha = new vector<float>();
    vector<float> *v_gg_ZZ_2mu2tau_alpha = new vector<float>();
    vector<float> *v_gg_ZZ_4e_alpha = new vector<float>();
    vector<float> *v_gg_ZZ_4mu_alpha = new vector<float>();
    vector<float> *v_gg_ZZ_4tau_alpha = new vector<float>();
    vector<float> *v_gg_WW_2L2Nu_alpha = new vector<float>();
    vector<float> *v_qq_WW_2L2Nu_alpha = new vector<float>();
    vector<float> *v_qq_WZ_2L2Q_alpha = new vector<float>();
    vector<float> *v_qq_WZ_3LNu_alpha = new vector<float>();
    vector<float> *v_qq_ZZ_2L2Nu_alpha = new vector<float>();
    vector<float> *v_qq_ZZ_2L2Q_alpha = new vector<float>();
    vector<float> *v_qq_ZZ_4L_alpha = new vector<float>();

    v_gg_ZZ_2e2mu_alpha->clear();
    v_gg_ZZ_2e2nu_alpha->clear();
    v_gg_ZZ_2e2tau_alpha->clear();
    v_gg_ZZ_2mu2nu_alpha->clear();
    v_gg_ZZ_2mu2tau_alpha->clear();
    v_gg_ZZ_4e_alpha->clear();
    v_gg_ZZ_4mu_alpha->clear();
    v_gg_ZZ_4tau_alpha->clear();
    v_gg_WW_2L2Nu_alpha->clear();
    v_qq_WW_2L2Nu_alpha->clear();
    v_qq_WZ_2L2Q_alpha->clear();
    v_qq_WZ_3LNu_alpha->clear();
    v_qq_ZZ_2L2Nu_alpha->clear();
    v_qq_ZZ_2L2Q_alpha->clear();
    v_qq_ZZ_4L_alpha->clear();

    vector<float> *v_gg_ZZ_2e2mu_jetCSV = new vector<float>();
    vector<float> *v_gg_ZZ_2e2nu_jetCSV = new vector<float>();
    vector<float> *v_gg_ZZ_2e2tau_jetCSV = new vector<float>();
    vector<float> *v_gg_ZZ_2mu2nu_jetCSV = new vector<float>();
    vector<float> *v_gg_ZZ_2mu2tau_jetCSV = new vector<float>();
    vector<float> *v_gg_ZZ_4e_jetCSV = new vector<float>();
    vector<float> *v_gg_ZZ_4mu_jetCSV = new vector<float>();
    vector<float> *v_gg_ZZ_4tau_jetCSV = new vector<float>();
    vector<float> *v_gg_WW_2L2Nu_jetCSV = new vector<float>();
    vector<float> *v_qq_WW_2L2Nu_jetCSV = new vector<float>();
    vector<float> *v_qq_WZ_2L2Q_jetCSV = new vector<float>();
    vector<float> *v_qq_WZ_3LNu_jetCSV = new vector<float>();
    vector<float> *v_qq_ZZ_2L2Nu_jetCSV = new vector<float>();
    vector<float> *v_qq_ZZ_2L2Q_jetCSV = new vector<float>();
    vector<float> *v_qq_ZZ_4L_jetCSV = new vector<float>();

    v_gg_ZZ_2e2mu_jetCSV->clear();
    v_gg_ZZ_2e2nu_jetCSV->clear();
    v_gg_ZZ_2e2tau_jetCSV->clear();
    v_gg_ZZ_2mu2nu_jetCSV->clear();
    v_gg_ZZ_2mu2tau_jetCSV->clear();
    v_gg_ZZ_4e_jetCSV->clear();
    v_gg_ZZ_4mu_jetCSV->clear();
    v_gg_ZZ_4tau_jetCSV->clear();
    v_gg_WW_2L2Nu_jetCSV->clear();
    v_qq_WW_2L2Nu_jetCSV->clear();
    v_qq_WZ_2L2Q_jetCSV->clear();
    v_qq_WZ_3LNu_jetCSV->clear();
    v_qq_ZZ_2L2Nu_jetCSV->clear();
    v_qq_ZZ_2L2Q_jetCSV->clear();
    v_qq_ZZ_4L_jetCSV->clear();

    vector<float> *v_gg_ZZ_2e2mu_Jethadronflavor = new vector<float>();
    vector<float> *v_gg_ZZ_2e2nu_Jethadronflavor = new vector<float>();
    vector<float> *v_gg_ZZ_2e2tau_Jethadronflavor = new vector<float>();
    vector<float> *v_gg_ZZ_2mu2nu_Jethadronflavor = new vector<float>();
    vector<float> *v_gg_ZZ_2mu2tau_Jethadronflavor = new vector<float>();
    vector<float> *v_gg_ZZ_4e_Jethadronflavor = new vector<float>();
    vector<float> *v_gg_ZZ_4mu_Jethadronflavor = new vector<float>();
    vector<float> *v_gg_ZZ_4tau_Jethadronflavor = new vector<float>();
    vector<float> *v_gg_WW_2L2Nu_Jethadronflavor = new vector<float>();
    vector<float> *v_qq_WW_2L2Nu_Jethadronflavor = new vector<float>();
    vector<float> *v_qq_WZ_2L2Q_Jethadronflavor = new vector<float>();
    vector<float> *v_qq_WZ_3LNu_Jethadronflavor = new vector<float>();
    vector<float> *v_qq_ZZ_2L2Nu_Jethadronflavor = new vector<float>();
    vector<float> *v_qq_ZZ_2L2Q_Jethadronflavor = new vector<float>();
    vector<float> *v_qq_ZZ_4L_Jethadronflavor = new vector<float>();

    v_gg_ZZ_2e2mu_Jethadronflavor->clear();
    v_gg_ZZ_2e2nu_Jethadronflavor->clear();
    v_gg_ZZ_2e2tau_Jethadronflavor->clear();
    v_gg_ZZ_2mu2nu_Jethadronflavor->clear();
    v_gg_ZZ_2mu2tau_Jethadronflavor->clear();
    v_gg_ZZ_4e_Jethadronflavor->clear();
    v_gg_ZZ_4mu_Jethadronflavor->clear();
    v_gg_ZZ_4tau_Jethadronflavor->clear();
    v_gg_WW_2L2Nu_Jethadronflavor->clear();
    v_qq_WW_2L2Nu_Jethadronflavor->clear();
    v_qq_WZ_2L2Q_Jethadronflavor->clear();
    v_qq_WZ_3LNu_Jethadronflavor->clear();
    v_qq_ZZ_2L2Nu_Jethadronflavor->clear();
    v_qq_ZZ_2L2Q_Jethadronflavor->clear();
    v_qq_ZZ_4L_Jethadronflavor->clear();

    TTree *T_event;
    merge_bfiles.uu_diboson_gg_ZZ_2e2mu->GetObject("T_tree", T_event);
    T_event->SetBranchAddress("I_weight", &f_gg_ZZ_2e2mu_weight);
    T_event->SetBranchAddress("f_Met", &f_gg_ZZ_2e2mu_met);
    T_event->SetBranchAddress("v_fakealpha3", &v_gg_ZZ_2e2mu_alpha);
    T_event->SetBranchAddress("f_thinjetCSV", &v_gg_ZZ_2e2mu_jetCSV);
    T_event->SetBranchAddress("v_fakeJethadronflavor", &v_gg_ZZ_2e2mu_Jethadronflavor);
    for (int evt = 0; evt < T_event->GetEntries(); evt++)
    {
        T_event->GetEntry(evt);

        if (f_gg_ZZ_2e2mu_met <= METcut)
        {
            continue;
        }

        int jet_passalpha_cut = 0;
        for (int ijet = 0; ijet < v_gg_ZZ_2e2mu_alpha->size(); ijet++)
        {
            // h_Bg_alpha->Fill((*v_gg_ZZ_2e2mu_alpha)[i], f_gg_ZZ_2e2mu_weight * diboson_gg_ZZ_2e2mu_Weight);
            if ((*v_gg_ZZ_2e2mu_alpha)[ijet] < alphacut)
            {
                jet_passalpha_cut++;
            }
        }

        // if (jet_passalpha_cut == 0)
        // {
        //     continue;
        // }

        h_Bg_nJet->Fill(jet_passalpha_cut, f_gg_ZZ_2e2mu_weight * merge_weight.uu_diboson_gg_ZZ_2e2mu_Weight);
        if (jet_passalpha_cut < 2)
        {
            continue;
        }
        h_Bg_nJet_cuted->Fill(jet_passalpha_cut, f_gg_ZZ_2e2mu_weight * merge_weight.uu_diboson_gg_ZZ_2e2mu_Weight);
    }

    TTree *T_event1;
    merge_bfiles.uu_diboson_gg_ZZ_2e2nu->GetObject("T_tree", T_event1);
    T_event1->SetBranchAddress("I_weight", &f_gg_ZZ_2e2nu_weight);
    T_event1->SetBranchAddress("f_Met", &f_gg_ZZ_2e2nu_met);
    T_event1->SetBranchAddress("v_fakealpha3", &v_gg_ZZ_2e2nu_alpha);
    T_event1->SetBranchAddress("f_thinjetCSV", &v_gg_ZZ_2e2nu_jetCSV);
    T_event1->SetBranchAddress("v_fakeJethadronflavor", &v_gg_ZZ_2e2nu_Jethadronflavor);
    for (int evt = 0; evt < T_event1->GetEntries(); evt++)
    {
        T_event1->GetEntry(evt);

        if (f_gg_ZZ_2e2nu_met <= METcut)
        {
            continue;
        }

        int jet_passalpha_cut = 0;
        for (int ijet = 0; ijet < v_gg_ZZ_2e2nu_alpha->size(); ijet++)
        {
            // h_Bg_alpha->Fill((*v_gg_ZZ_2e2nu_alpha)[i], f_gg_ZZ_2e2nu_weight * diboson_gg_ZZ_2e2nu_Weight);
            if ((*v_gg_ZZ_2e2nu_alpha)[ijet] < alphacut)
            {
                jet_passalpha_cut++;
            }
        }

        // if (jet_passalpha_cut == 0)
        // {
        //     continue;
        // }

        h_Bg_nJet->Fill(jet_passalpha_cut, f_gg_ZZ_2e2nu_weight * merge_weight.uu_diboson_gg_ZZ_2e2nu_Weight);
        if (jet_passalpha_cut < 2)
        {
            continue;
        }
        h_Bg_nJet_cuted->Fill(jet_passalpha_cut, f_gg_ZZ_2e2nu_weight * merge_weight.uu_diboson_gg_ZZ_2e2nu_Weight);
    }

    TTree *T_event2;
    merge_bfiles.uu_diboson_gg_ZZ_2e2tau->GetObject("T_tree", T_event2);
    T_event2->SetBranchAddress("I_weight", &f_gg_ZZ_2e2tau_weight);
    T_event2->SetBranchAddress("f_Met", &f_gg_ZZ_2e2tau_met);
    T_event2->SetBranchAddress("v_fakealpha3", &v_gg_ZZ_2e2tau_alpha);
    T_event2->SetBranchAddress("f_thinjetCSV", &v_gg_ZZ_2e2tau_jetCSV);
    T_event2->SetBranchAddress("v_fakeJethadronflavor", &v_gg_ZZ_2e2tau_Jethadronflavor);

    for (int evt = 0; evt < T_event2->GetEntries(); evt++)
    {
        T_event2->GetEntry(evt);

        if (f_gg_ZZ_2e2tau_met <= METcut)
        {
            continue;
        }

        int jet_passalpha_cut = 0;
        for (int ijet = 0; ijet < v_gg_ZZ_2e2tau_alpha->size(); ijet++)
        {

            // h_Bg_alpha->Fill((*v_gg_ZZ_2e2tau_alpha)[i], f_gg_ZZ_2e2tau_weight * diboson_gg_ZZ_2e2tau_Weight);
            if ((*v_gg_ZZ_2e2tau_alpha)[ijet] < alphacut)
            {
                jet_passalpha_cut++;
            }
        }

        // if (jet_passalpha_cut == 0)
        // {
        //     continue;
        // }

        h_Bg_nJet->Fill(jet_passalpha_cut, f_gg_ZZ_2e2tau_weight * merge_weight.uu_diboson_gg_ZZ_2e2tau_Weight);
        if (jet_passalpha_cut < 2)
        {
            continue;
        }
        h_Bg_nJet_cuted->Fill(jet_passalpha_cut, f_gg_ZZ_2e2tau_weight * merge_weight.uu_diboson_gg_ZZ_2e2tau_Weight);
    }

    TTree *T_event3;
    merge_bfiles.uu_diboson_gg_ZZ_2mu2nu->GetObject("T_tree", T_event3);
    T_event3->SetBranchAddress("I_weight", &f_gg_ZZ_2mu2nu_weight);
    T_event3->SetBranchAddress("f_Met", &f_gg_ZZ_2mu2nu_met);
    T_event3->SetBranchAddress("v_fakealpha3", &v_gg_ZZ_2mu2nu_alpha);
    T_event3->SetBranchAddress("f_thinjetCSV", &v_gg_ZZ_2mu2nu_jetCSV);
    T_event3->SetBranchAddress("v_fakeJethadronflavor", &v_gg_ZZ_2mu2nu_Jethadronflavor);
    for (int evt = 0; evt < T_event3->GetEntries(); evt++)
    {
        T_event3->GetEntry(evt);

        if (f_gg_ZZ_2mu2nu_met <= METcut)
        {
            continue;
        }

        int jet_passalpha_cut = 0;
        for (int ijet = 0; ijet < v_gg_ZZ_2mu2nu_alpha->size(); ijet++)
        {
            // h_Bg_alpha->Fill((*v_gg_ZZ_2mu2nu_alpha)[i], f_gg_ZZ_2mu2nu_weight * diboson_gg_ZZ_2mu2nu_Weight);
            if ((*v_gg_ZZ_2mu2nu_alpha)[ijet] < alphacut)
            {
                jet_passalpha_cut++;
            }
        }

        // if (jet_passalpha_cut == 0)
        // {
        //     continue;
        // }

        h_Bg_nJet->Fill(jet_passalpha_cut, f_gg_ZZ_2mu2nu_weight * merge_weight.uu_diboson_gg_ZZ_2mu2nu_Weight);
        if (jet_passalpha_cut < 2)
        {
            continue;
        }
        h_Bg_nJet_cuted->Fill(jet_passalpha_cut, f_gg_ZZ_2mu2nu_weight * merge_weight.uu_diboson_gg_ZZ_2mu2nu_Weight);
    }

    TTree *T_event4;
    merge_bfiles.uu_diboson_gg_ZZ_2mu2tau->GetObject("T_tree", T_event4);
    T_event4->SetBranchAddress("I_weight", &f_gg_ZZ_2mu2tau_weight);
    T_event4->SetBranchAddress("f_Met", &f_gg_ZZ_2mu2tau_met);
    T_event4->SetBranchAddress("v_fakealpha3", &v_gg_ZZ_2mu2tau_alpha);
    T_event4->SetBranchAddress("f_thinjetCSV", &v_gg_ZZ_2mu2tau_jetCSV);
    T_event4->SetBranchAddress("v_fakeJethadronflavor", &v_gg_ZZ_2mu2tau_Jethadronflavor);

    for (int evt = 0; evt < T_event4->GetEntries(); evt++)
    {
        T_event4->GetEntry(evt);

        if (f_gg_ZZ_2mu2tau_met <= METcut)
        {
            continue;
        }

        int jet_passalpha_cut = 0;
        for (int ijet = 0; ijet < v_gg_ZZ_2mu2tau_alpha->size(); ijet++)
        {
            // h_Bg_alpha->Fill((*v_gg_ZZ_2mu2tau_alpha)[i], f_gg_ZZ_2mu2tau_weight * diboson_gg_ZZ_2mu2tau_Weight);
            if ((*v_gg_ZZ_2mu2tau_alpha)[ijet] < alphacut)
            {
                jet_passalpha_cut++;
            }
        }

        // if (jet_passalpha_cut == 0)
        // {
        //     continue;
        // }

        h_Bg_nJet->Fill(jet_passalpha_cut, f_gg_ZZ_2mu2tau_weight * merge_weight.uu_diboson_gg_ZZ_2mu2tau_Weight);
        if (jet_passalpha_cut < 2)
        {
            continue;
        }
        h_Bg_nJet_cuted->Fill(jet_passalpha_cut, f_gg_ZZ_2mu2tau_weight * merge_weight.uu_diboson_gg_ZZ_2mu2tau_Weight);
    }

    TTree *T_event5;
    merge_bfiles.uu_diboson_gg_ZZ_4e->GetObject("T_tree", T_event5);
    T_event5->SetBranchAddress("I_weight", &f_gg_ZZ_4e_weight);
    T_event5->SetBranchAddress("f_Met", &f_gg_ZZ_4e_met);
    T_event5->SetBranchAddress("v_fakealpha3", &v_gg_ZZ_4e_alpha);
    T_event5->SetBranchAddress("f_thinjetCSV", &v_gg_ZZ_4e_jetCSV);
    T_event5->SetBranchAddress("v_fakeJethadronflavor", &v_gg_ZZ_4e_Jethadronflavor);

    for (int evt = 0; evt < T_event5->GetEntries(); evt++)
    {
        T_event5->GetEntry(evt);

        if (f_gg_ZZ_4e_met <= METcut)
        {
            continue;
        }

        int jet_passalpha_cut = 0;
        for (int ijet = 0; ijet < v_gg_ZZ_4e_alpha->size(); ijet++)
        {
            // h_Bg_alpha->Fill((*v_gg_ZZ_4e_alpha)[i], f_gg_ZZ_4e_weight * diboson_gg_ZZ_4e_Weight);
            if ((*v_gg_ZZ_4e_alpha)[ijet] < alphacut)
            {
                jet_passalpha_cut++;
            }
        }

        // if (jet_passalpha_cut == 0)
        // {
        //     continue;
        // }

        h_Bg_nJet->Fill(jet_passalpha_cut, f_gg_ZZ_4e_weight * merge_weight.uu_diboson_gg_ZZ_4e_Weight);
        if (jet_passalpha_cut < 2)
        {
            continue;
        }
        h_Bg_nJet_cuted->Fill(jet_passalpha_cut, f_gg_ZZ_4e_weight * merge_weight.uu_diboson_gg_ZZ_4e_Weight);
    }

    TTree *T_event6;
    merge_bfiles.uu_diboson_gg_ZZ_4mu->GetObject("T_tree", T_event6);
    T_event6->SetBranchAddress("I_weight", &f_gg_ZZ_4mu_weight);
    T_event6->SetBranchAddress("f_Met", &f_gg_ZZ_4mu_met);
    T_event6->SetBranchAddress("v_fakealpha3", &v_gg_ZZ_4mu_alpha);
    T_event6->SetBranchAddress("f_thinjetCSV", &v_gg_ZZ_4mu_jetCSV);
    T_event6->SetBranchAddress("v_fakeJethadronflavor", &v_gg_ZZ_4mu_Jethadronflavor);

    for (int evt = 0; evt < T_event6->GetEntries(); evt++)
    {
        T_event6->GetEntry(evt);

        if (f_gg_ZZ_4mu_met <= METcut)
        {
            continue;
        }

        int jet_passalpha_cut = 0;
        for (int ijet = 0; ijet < v_gg_ZZ_4mu_alpha->size(); ijet++)
        {

            // h_Bg_alpha->Fill((*v_gg_ZZ_4mu_alpha)[i], f_gg_ZZ_4mu_weight * diboson_gg_ZZ_4mu_Weight);
            if ((*v_gg_ZZ_4mu_alpha)[ijet] < alphacut)
            {
                jet_passalpha_cut++;
            }
        }

        // if (jet_passalpha_cut == 0)
        // {
        //     continue;
        // }

        h_Bg_nJet->Fill(jet_passalpha_cut, f_gg_ZZ_4mu_weight * merge_weight.uu_diboson_gg_ZZ_4mu_Weight);
        if (jet_passalpha_cut < 2)
        {
            continue;
        }
        h_Bg_nJet_cuted->Fill(jet_passalpha_cut, f_gg_ZZ_4mu_weight * merge_weight.uu_diboson_gg_ZZ_4mu_Weight);
    }

    TTree *T_event7;
    merge_bfiles.uu_diboson_gg_ZZ_4tau->GetObject("T_tree", T_event7);
    T_event7->SetBranchAddress("I_weight", &f_gg_ZZ_4tau_weight);
    T_event7->SetBranchAddress("f_Met", &f_gg_ZZ_4tau_met);
    T_event7->SetBranchAddress("v_fakealpha3", &v_gg_ZZ_4tau_alpha);
    T_event7->SetBranchAddress("f_thinjetCSV", &v_gg_ZZ_4tau_jetCSV);
    T_event7->SetBranchAddress("v_fakeJethadronflavor", &v_gg_ZZ_4tau_Jethadronflavor);

    for (int evt = 0; evt < T_event7->GetEntries(); evt++)
    {
        T_event7->GetEntry(evt);

        if (f_gg_ZZ_4tau_met <= METcut)
        {
            continue;
        }

        int jet_passalpha_cut = 0;
        for (int ijet = 0; ijet < v_gg_ZZ_4tau_alpha->size(); ijet++)
        {

            // h_Bg_alpha->Fill((*v_gg_ZZ_4tau_alpha)[i], f_gg_ZZ_4tau_weight * diboson_gg_ZZ_4tau_Weight);
            if ((*v_gg_ZZ_4tau_alpha)[ijet] < alphacut)
            {
                jet_passalpha_cut++;
            }
        }

        // if (jet_passalpha_cut == 0)
        // {
        //     continue;
        // }

        h_Bg_nJet->Fill(jet_passalpha_cut, f_gg_ZZ_4tau_weight * merge_weight.uu_diboson_gg_ZZ_4tau_Weight);
        if (jet_passalpha_cut < 2)
        {
            continue;
        }
        h_Bg_nJet_cuted->Fill(jet_passalpha_cut, f_gg_ZZ_4tau_weight * merge_weight.uu_diboson_gg_ZZ_4tau_Weight);
    }

    TTree *T_event8;
    merge_bfiles.uu_diboson_gg_WW_2L2Nu->GetObject("T_tree", T_event8);
    T_event8->SetBranchAddress("I_weight", &f_gg_WW_2L2Nu_weight);
    T_event8->SetBranchAddress("f_Met", &f_gg_WW_2L2Nu_met);
    T_event8->SetBranchAddress("v_fakealpha3", &v_gg_WW_2L2Nu_alpha);
    T_event8->SetBranchAddress("f_thinjetCSV", &v_gg_WW_2L2Nu_jetCSV);
    T_event8->SetBranchAddress("v_fakeJethadronflavor", &v_gg_WW_2L2Nu_Jethadronflavor);

    for (int evt = 0; evt < T_event8->GetEntries(); evt++)
    {
        T_event8->GetEntry(evt);

        if (f_gg_WW_2L2Nu_met <= METcut)
        {
            continue;
        }

        int jet_passalpha_cut = 0;
        for (int ijet = 0; ijet < v_gg_WW_2L2Nu_alpha->size(); ijet++)
        {

            // h_Bg_alpha->Fill((*v_gg_WW_2L2Nu_alpha)[i], f_gg_WW_2L2Nu_weight * diboson_gg_WW_2L2Nu_Weight);
            if ((*v_gg_WW_2L2Nu_alpha)[ijet] < alphacut)
            {
                jet_passalpha_cut++;
            }
        }

        // if (jet_passalpha_cut == 0)
        // {
        //     continue;
        // }

        h_Bg_nJet->Fill(jet_passalpha_cut, f_gg_WW_2L2Nu_weight * merge_weight.uu_diboson_gg_WW_2L2Nu_Weight);
        if (jet_passalpha_cut < 2)
        {
            continue;
        }
        h_Bg_nJet_cuted->Fill(jet_passalpha_cut, f_gg_WW_2L2Nu_weight * merge_weight.uu_diboson_gg_WW_2L2Nu_Weight);
    }

    TTree *T_event9;
    merge_bfiles.uu_diboson_qq_WW_2L2Nu->GetObject("T_tree", T_event9);
    T_event9->SetBranchAddress("I_weight", &f_qq_WW_2L2Nu_weight);
    T_event9->SetBranchAddress("f_Met", &f_qq_WW_2L2Nu_met);
    T_event9->SetBranchAddress("v_fakealpha3", &v_qq_WW_2L2Nu_alpha);
    T_event9->SetBranchAddress("f_thinjetCSV", &v_qq_WW_2L2Nu_jetCSV);
    T_event9->SetBranchAddress("v_fakeJethadronflavor", &v_qq_WW_2L2Nu_Jethadronflavor);

    for (int evt = 0; evt < T_event9->GetEntries(); evt++)
    {
        T_event9->GetEntry(evt);

        if (f_qq_WW_2L2Nu_met <= METcut)
        {
            continue;
        }

        int jet_passalpha_cut = 0;
        for (int ijet = 0; ijet < v_qq_WW_2L2Nu_alpha->size(); ijet++)
        {

            // h_Bg_alpha->Fill((*v_qq_WW_2L2Nu_alpha)[i], f_qq_WW_2L2Nu_weight * diboson_qq_WW_2L2Nu_Weight);
            if ((*v_qq_WW_2L2Nu_alpha)[ijet] < alphacut)
            {
                jet_passalpha_cut++;
            }
        }

        // if (jet_passalpha_cut == 0)
        // {
        //     continue;
        // }

        h_Bg_nJet->Fill(jet_passalpha_cut, f_qq_WW_2L2Nu_weight * merge_weight.uu_diboson_qq_WW_2L2Nu_Weight);
        if (jet_passalpha_cut < 2)
        {
            continue;
        }
        h_Bg_nJet_cuted->Fill(jet_passalpha_cut, f_qq_WW_2L2Nu_weight * merge_weight.uu_diboson_qq_WW_2L2Nu_Weight);
    }

    TTree *T_event10;
    merge_bfiles.uu_diboson_qq_WZ_2L2Q->GetObject("T_tree", T_event10);
    T_event10->SetBranchAddress("I_weight", &f_qq_WZ_2L2Q_weight);
    T_event10->SetBranchAddress("f_Met", &f_qq_WZ_2L2Q_met);
    T_event10->SetBranchAddress("v_fakealpha3", &v_qq_WZ_2L2Q_alpha);
    T_event10->SetBranchAddress("f_thinjetCSV", &v_qq_WZ_2L2Q_jetCSV);
    T_event10->SetBranchAddress("v_fakeJethadronflavor", &v_qq_WZ_2L2Q_Jethadronflavor);

    for (int evt = 0; evt < T_event10->GetEntries(); evt++)
    {
        T_event10->GetEntry(evt);

        if (f_qq_WZ_2L2Q_met <= METcut)
        {
            continue;
        }

        int jet_passalpha_cut = 0;
        for (int ijet = 0; ijet < v_qq_WZ_2L2Q_alpha->size(); ijet++)
        {

            // h_Bg_alpha->Fill((*v_qq_WZ_2L2Q_alpha)[i], f_qq_WZ_2L2Q_weight * diboson_qq_WZ_2L2Q_Weight);
            if ((*v_qq_WZ_2L2Q_alpha)[ijet] < alphacut)
            {
                jet_passalpha_cut++;
            }
        }

        // if (jet_passalpha_cut == 0)
        // {
        //     continue;
        // }

        h_Bg_nJet->Fill(jet_passalpha_cut, f_qq_WZ_2L2Q_weight * merge_weight.uu_diboson_qq_WZ_2L2Q_Weight);
        if (jet_passalpha_cut < 2)
        {
            continue;
        }
        h_Bg_nJet_cuted->Fill(jet_passalpha_cut, f_qq_WZ_2L2Q_weight * merge_weight.uu_diboson_qq_WZ_2L2Q_Weight);
    }

    TTree *T_event11;
    merge_bfiles.uu_diboson_qq_WZ_3LNu->GetObject("T_tree", T_event11);
    T_event11->SetBranchAddress("I_weight", &f_qq_WZ_3LNu_weight);
    T_event11->SetBranchAddress("f_Met", &f_qq_WZ_3LNu_met);
    T_event11->SetBranchAddress("v_fakealpha3", &v_qq_WZ_3LNu_alpha);
    T_event11->SetBranchAddress("f_thinjetCSV", &v_qq_WZ_3LNu_jetCSV);
    T_event11->SetBranchAddress("v_fakeJethadronflavor", &v_qq_WZ_3LNu_Jethadronflavor);

    for (int evt = 0; evt < T_event11->GetEntries(); evt++)
    {
        T_event11->GetEntry(evt);

        if (f_qq_WZ_3LNu_met <= METcut)
        {
            continue;
        }

        int jet_passalpha_cut = 0;
        for (int ijet = 0; ijet < v_qq_WZ_3LNu_alpha->size(); ijet++)
        {

            // h_Bg_alpha->Fill((*v_qq_WZ_3LNu_alpha)[i], f_qq_WZ_3LNu_weight * diboson_qq_WZ_3LNu_Weight);
            if ((*v_qq_WZ_3LNu_alpha)[ijet] < alphacut)
            {
                jet_passalpha_cut++;
            }
        }

        // if (jet_passalpha_cut == 0)
        // {
        //     continue;
        // }

        h_Bg_nJet->Fill(jet_passalpha_cut, f_qq_WZ_3LNu_weight * merge_weight.uu_diboson_qq_WZ_3LNu_Weight);
        if (jet_passalpha_cut < 2)
        {
            continue;
        }
        h_Bg_nJet_cuted->Fill(jet_passalpha_cut, f_qq_WZ_3LNu_weight * merge_weight.uu_diboson_qq_WZ_3LNu_Weight);
    }

    TTree *T_event12;
    merge_bfiles.uu_diboson_qq_ZZ_2L2Nu->GetObject("T_tree", T_event12);
    T_event12->SetBranchAddress("I_weight", &f_qq_ZZ_2L2Nu_weight);
    T_event12->SetBranchAddress("f_Met", &f_qq_ZZ_2L2Nu_met);
    T_event12->SetBranchAddress("v_fakealpha3", &v_qq_ZZ_2L2Nu_alpha);
    T_event12->SetBranchAddress("f_thinjetCSV", &v_qq_ZZ_2L2Nu_jetCSV);
    T_event12->SetBranchAddress("v_fakeJethadronflavor", &v_qq_ZZ_2L2Nu_Jethadronflavor);

    for (int evt = 0; evt < T_event12->GetEntries(); evt++)
    {
        T_event12->GetEntry(evt);

        if (f_qq_ZZ_2L2Nu_met <= METcut)
        {
            continue;
        }

        int jet_passalpha_cut = 0;
        for (int ijet = 0; ijet < v_qq_ZZ_2L2Nu_alpha->size(); ijet++)
        {

            // h_Bg_alpha->Fill((*v_qq_ZZ_2L2Nu_alpha)[i], f_qq_ZZ_2L2Nu_weight * diboson_qq_ZZ_2L2Nu_Weight);
            if ((*v_qq_ZZ_2L2Nu_alpha)[ijet] < alphacut)
            {
                jet_passalpha_cut++;
            }
        }

        // if (jet_passalpha_cut == 0)
        // {
        //     continue;
        // }

        h_Bg_nJet->Fill(jet_passalpha_cut, f_qq_ZZ_2L2Nu_weight * merge_weight.uu_diboson_qq_ZZ_2L2Nu_Weight);
        if (jet_passalpha_cut < 2)
        {
            continue;
        }
        h_Bg_nJet_cuted->Fill(jet_passalpha_cut, f_qq_ZZ_2L2Nu_weight * merge_weight.uu_diboson_qq_ZZ_2L2Nu_Weight);
    }

    TTree *T_event13;
    merge_bfiles.uu_diboson_qq_ZZ_2L2Q->GetObject("T_tree", T_event13);
    T_event13->SetBranchAddress("I_weight", &f_qq_ZZ_2L2Q_weight);
    T_event13->SetBranchAddress("f_Met", &f_qq_ZZ_2L2Q_met);
    T_event13->SetBranchAddress("v_fakealpha3", &v_qq_ZZ_2L2Q_alpha);
    T_event13->SetBranchAddress("f_thinjetCSV", &v_qq_ZZ_2L2Q_jetCSV);
    T_event13->SetBranchAddress("v_fakeJethadronflavor", &v_qq_ZZ_2L2Q_Jethadronflavor);

    for (int evt = 0; evt < T_event13->GetEntries(); evt++)
    {
        T_event13->GetEntry(evt);

        if (f_qq_ZZ_2L2Q_met <= METcut)
        {
            continue;
        }

        int jet_passalpha_cut = 0;
        for (int ijet = 0; ijet < v_qq_ZZ_2L2Q_alpha->size(); ijet++)
        {

            // h_Bg_alpha->Fill((*v_qq_ZZ_2L2Q_alpha)[i], f_qq_ZZ_2L2Q_weight * diboson_qq_ZZ_2L2Q_Weight);
            if ((*v_qq_ZZ_2L2Q_alpha)[ijet] < alphacut)
            {
                jet_passalpha_cut++;
            }
        }

        // if (jet_passalpha_cut == 0)
        // {
        //     continue;
        // }

        h_Bg_nJet->Fill(jet_passalpha_cut, f_qq_ZZ_2L2Q_weight * merge_weight.uu_diboson_qq_ZZ_2L2Q_Weight);

        if (jet_passalpha_cut < 2)
        {
            continue;
        }
        h_Bg_nJet_cuted->Fill(jet_passalpha_cut, f_qq_ZZ_2L2Q_weight * merge_weight.uu_diboson_qq_ZZ_2L2Q_Weight);
    }

    TTree *T_event14;
    merge_bfiles.uu_diboson_qq_ZZ_4L->GetObject("T_tree", T_event14);
    T_event14->SetBranchAddress("I_weight", &f_qq_ZZ_4L_weight);
    T_event14->SetBranchAddress("f_Met", &f_qq_ZZ_4L_met);
    T_event14->SetBranchAddress("v_fakealpha3", &v_qq_ZZ_4L_alpha);
    T_event14->SetBranchAddress("f_thinjetCSV", &v_qq_ZZ_4L_jetCSV);
    T_event14->SetBranchAddress("v_fakeJethadronflavor", &v_qq_ZZ_4L_Jethadronflavor);
    for (int evt = 0; evt < T_event14->GetEntries(); evt++)
    {
        T_event14->GetEntry(evt);

        if (f_qq_ZZ_4L_met <= METcut)
        {
            continue;
        }

        int jet_passalpha_cut = 0;
        for (int ijet = 0; ijet < v_qq_ZZ_4L_alpha->size(); ijet++)
        {

            // h_Bg_alpha->Fill((*v_qq_ZZ_4L_alpha)[i], f_qq_ZZ_4L_weight * diboson_qq_ZZ_4L_Weight);
            if ((*v_qq_ZZ_4L_alpha)[ijet] < alphacut)
            {
                jet_passalpha_cut++;
            }
        }

        // if (jet_passalpha_cut == 0)
        // {
        //     continue;
        // }

        h_Bg_nJet->Fill(jet_passalpha_cut, f_qq_ZZ_4L_weight * merge_weight.uu_diboson_qq_ZZ_4L_Weight);

        if (jet_passalpha_cut < 2)
        {
            continue;
        }
        h_Bg_nJet_cuted->Fill(jet_passalpha_cut, f_qq_ZZ_4L_weight * merge_weight.uu_diboson_qq_ZZ_4L_Weight);
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
        uu_Diboson_alpha(argv[1], argv[2]);
    }
    else
    {
        cout << "ERROR" << endl;
    }
}
