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

void ee_Diboson_3Dsig()
{ /*Open source root file*/
    MergeBFiles merge_bfiles;
    MergeWeight merge_weight(&merge_bfiles);

    TH1D *h_Diboson_3Dsig = new TH1D("h_Diboson_3Dsig", "", 200, -10., 10.);
    TH1D *h_bg_alpha3 = new TH1D("h_bg_alpha3", "", 20, 0, 1.);

    Int_t f_gg_ZZ_2e2mu_weight, f_gg_ZZ_2e2nu_weight, f_gg_ZZ_2e2tau_weight, f_gg_ZZ_2mu2nu_weight,
        f_gg_ZZ_2mu2tau_weight, f_gg_ZZ_4e_weight, f_gg_ZZ_4mu_weight, f_gg_ZZ_4tau_weight, f_gg_WW_2L2Nu_weight,
        f_qq_WW_2L2Nu_weight, f_qq_WZ_2L2Q_weight, f_qq_WZ_3LNu_weight, f_qq_ZZ_2L2Nu_weight, f_qq_ZZ_2L2Q_weight,
        f_qq_ZZ_4L_weight;

    float_t f_gg_ZZ_2e2mu_met, f_gg_ZZ_2e2nu_met, f_gg_ZZ_2e2tau_met, f_gg_ZZ_2mu2nu_met,
        f_gg_ZZ_2mu2tau_met, f_gg_ZZ_4e_met, f_gg_ZZ_4mu_met, f_gg_ZZ_4tau_met, f_gg_WW_2L2Nu_met,
        f_qq_WW_2L2Nu_met, f_qq_WZ_2L2Q_met, f_qq_WZ_3LNu_met, f_qq_ZZ_2L2Nu_met, f_qq_ZZ_2L2Q_met,
        f_qq_ZZ_4L_met;

    vector<float> *v_gg_ZZ_2e2mu_log3Dsig = new vector<float>();
    vector<float> *v_gg_ZZ_2e2nu_log3Dsig = new vector<float>();
    vector<float> *v_gg_ZZ_2e2tau_log3Dsig = new vector<float>();
    vector<float> *v_gg_ZZ_2mu2nu_log3Dsig = new vector<float>();
    vector<float> *v_gg_ZZ_2mu2tau_log3Dsig = new vector<float>();
    vector<float> *v_gg_ZZ_4e_log3Dsig = new vector<float>();
    vector<float> *v_gg_ZZ_4mu_log3Dsig = new vector<float>();
    vector<float> *v_gg_ZZ_4tau_log3Dsig = new vector<float>();
    vector<float> *v_gg_WW_2L2Nu_log3Dsig = new vector<float>();
    vector<float> *v_qq_WW_2L2Nu_log3Dsig = new vector<float>();
    vector<float> *v_qq_WZ_2L2Q_log3Dsig = new vector<float>();
    vector<float> *v_qq_WZ_3LNu_log3Dsig = new vector<float>();
    vector<float> *v_qq_ZZ_2L2Nu_log3Dsig = new vector<float>();
    vector<float> *v_qq_ZZ_2L2Q_log3Dsig = new vector<float>();
    vector<float> *v_qq_ZZ_4L_log3Dsig = new vector<float>();

    v_gg_ZZ_2e2mu_log3Dsig->clear();
    v_gg_ZZ_2e2nu_log3Dsig->clear();
    v_gg_ZZ_2e2tau_log3Dsig->clear();
    v_gg_ZZ_2mu2nu_log3Dsig->clear();
    v_gg_ZZ_2mu2tau_log3Dsig->clear();
    v_gg_ZZ_4e_log3Dsig->clear();
    v_gg_ZZ_4mu_log3Dsig->clear();
    v_gg_ZZ_4tau_log3Dsig->clear();
    v_gg_WW_2L2Nu_log3Dsig->clear();
    v_qq_WW_2L2Nu_log3Dsig->clear();
    v_qq_WZ_2L2Q_log3Dsig->clear();
    v_qq_WZ_3LNu_log3Dsig->clear();
    v_qq_ZZ_2L2Nu_log3Dsig->clear();
    v_qq_ZZ_2L2Q_log3Dsig->clear();
    v_qq_ZZ_4L_log3Dsig->clear();

    vector<float> *v_gg_ZZ_2e2mu_alpha3 = new vector<float>();
    vector<float> *v_gg_ZZ_2e2nu_alpha3 = new vector<float>();
    vector<float> *v_gg_ZZ_2e2tau_alpha3 = new vector<float>();
    vector<float> *v_gg_ZZ_2mu2nu_alpha3 = new vector<float>();
    vector<float> *v_gg_ZZ_2mu2tau_alpha3 = new vector<float>();
    vector<float> *v_gg_ZZ_4e_alpha3 = new vector<float>();
    vector<float> *v_gg_ZZ_4mu_alpha3 = new vector<float>();
    vector<float> *v_gg_ZZ_4tau_alpha3 = new vector<float>();
    vector<float> *v_gg_WW_2L2Nu_alpha3 = new vector<float>();
    vector<float> *v_qq_WW_2L2Nu_alpha3 = new vector<float>();
    vector<float> *v_qq_WZ_2L2Q_alpha3 = new vector<float>();
    vector<float> *v_qq_WZ_3LNu_alpha3 = new vector<float>();
    vector<float> *v_qq_ZZ_2L2Nu_alpha3 = new vector<float>();
    vector<float> *v_qq_ZZ_2L2Q_alpha3 = new vector<float>();
    vector<float> *v_qq_ZZ_4L_alpha3 = new vector<float>();

    v_gg_ZZ_2e2mu_alpha3->clear();
    v_gg_ZZ_2e2nu_alpha3->clear();
    v_gg_ZZ_2e2tau_alpha3->clear();
    v_gg_ZZ_2mu2nu_alpha3->clear();
    v_gg_ZZ_2mu2tau_alpha3->clear();
    v_gg_ZZ_4e_alpha3->clear();
    v_gg_ZZ_4mu_alpha3->clear();
    v_gg_ZZ_4tau_alpha3->clear();
    v_gg_WW_2L2Nu_alpha3->clear();
    v_qq_WW_2L2Nu_alpha3->clear();
    v_qq_WZ_2L2Q_alpha3->clear();
    v_qq_WZ_3LNu_alpha3->clear();
    v_qq_ZZ_2L2Nu_alpha3->clear();
    v_qq_ZZ_2L2Q_alpha3->clear();
    v_qq_ZZ_4L_alpha3->clear();

   double METcut = 140.;

    TTree *T_event;
    merge_bfiles.ee_diboson_gg_ZZ_2e2mu->GetObject("T_tree", T_event);
    T_event->SetBranchAddress("I_weight", &f_gg_ZZ_2e2mu_weight);
    T_event->SetBranchAddress("f_Met", &f_gg_ZZ_2e2mu_met);

    T_event->SetBranchAddress("v_Chi3Dlog", &v_gg_ZZ_2e2mu_log3Dsig);
    T_event->SetBranchAddress("v_fakealpha3", &v_gg_ZZ_2e2mu_alpha3);
    for (int evt = 0; evt < T_event->GetEntries(); evt++)
    {
        T_event->GetEntry(evt);

        for (int itrk = 0; itrk < v_gg_ZZ_2e2mu_log3Dsig->size(); itrk++)
        {
            h_Diboson_3Dsig->Fill((*v_gg_ZZ_2e2mu_log3Dsig)[itrk], f_gg_ZZ_2e2mu_weight * merge_weight.ee_diboson_gg_ZZ_2e2mu_Weight);
        }
        if (f_gg_ZZ_2e2mu_met <= METcut)
        {
            continue;
        }
        for (int ijet = 0; ijet < v_gg_ZZ_2e2mu_alpha3->size(); ijet++)
        {
            h_bg_alpha3->Fill((*v_gg_ZZ_2e2mu_alpha3)[ijet], f_gg_ZZ_2e2mu_weight * merge_weight.ee_diboson_gg_ZZ_2e2mu_Weight);
        }
    }
    TTree *T_event1;
    merge_bfiles.ee_diboson_gg_ZZ_2e2nu->GetObject("T_tree", T_event1);
    T_event1->SetBranchAddress("I_weight", &f_gg_ZZ_2e2nu_weight);
    T_event1->SetBranchAddress("f_Met", &f_gg_ZZ_2e2nu_met);

    T_event1->SetBranchAddress("v_Chi3Dlog", &v_gg_ZZ_2e2nu_log3Dsig);
    T_event1->SetBranchAddress("v_fakealpha3", &v_gg_ZZ_2e2nu_alpha3);
    for (int evt = 0; evt < T_event1->GetEntries(); evt++)
    {
        T_event1->GetEntry(evt);

        for (int itrk = 0; itrk < v_gg_ZZ_2e2mu_log3Dsig->size(); itrk++)
        {
            h_Diboson_3Dsig->Fill((*v_gg_ZZ_2e2nu_log3Dsig)[itrk], f_gg_ZZ_2e2nu_weight * merge_weight.ee_diboson_gg_ZZ_2e2nu_Weight);
        }
        if (f_gg_ZZ_2e2nu_met <= METcut)
        {
            continue;
        }
        for (int ijet = 0; ijet < v_gg_ZZ_2e2nu_alpha3->size(); ijet++)
        {
            h_bg_alpha3->Fill((*v_gg_ZZ_2e2nu_alpha3)[ijet], f_gg_ZZ_2e2nu_weight * merge_weight.ee_diboson_gg_ZZ_2e2nu_Weight);
        }
    }
    TTree *T_event2;
    merge_bfiles.ee_diboson_gg_ZZ_2e2tau->GetObject("T_tree", T_event2);
    T_event2->SetBranchAddress("I_weight", &f_gg_ZZ_2e2tau_weight);
    T_event2->SetBranchAddress("f_Met", &f_gg_ZZ_2e2tau_met);

    T_event2->SetBranchAddress("v_Chi3Dlog", &v_gg_ZZ_2e2tau_log3Dsig);
    T_event2->SetBranchAddress("v_fakealpha3", &v_gg_ZZ_2e2tau_alpha3);
    for (int evt = 0; evt < T_event2->GetEntries(); evt++)
    {
        T_event2->GetEntry(evt);

        for (int itrk = 0; itrk < v_gg_ZZ_2e2tau_log3Dsig->size(); itrk++)
        {
            h_Diboson_3Dsig->Fill((*v_gg_ZZ_2e2tau_log3Dsig)[itrk], f_gg_ZZ_2e2tau_weight * merge_weight.ee_diboson_gg_ZZ_2e2tau_Weight);
        }
        if (f_gg_ZZ_2e2tau_met <= METcut)
        {
            continue;
        }
        for (int ijet = 0; ijet < v_gg_ZZ_2e2tau_alpha3->size(); ijet++)
        {
            h_bg_alpha3->Fill((*v_gg_ZZ_2e2tau_alpha3)[ijet], f_gg_ZZ_2e2tau_weight * merge_weight.ee_diboson_gg_ZZ_2e2tau_Weight);
        }
    }
    TTree *T_event3;
    merge_bfiles.ee_diboson_gg_ZZ_2mu2nu->GetObject("T_tree", T_event3);
    T_event3->SetBranchAddress("I_weight", &f_gg_ZZ_2mu2nu_weight);
    T_event3->SetBranchAddress("f_Met", &f_gg_ZZ_2mu2nu_met);

    T_event3->SetBranchAddress("v_Chi3Dlog", &v_gg_ZZ_2mu2nu_log3Dsig);
    T_event3->SetBranchAddress("v_fakealpha3", &v_gg_ZZ_2mu2nu_alpha3);
    for (int evt = 0; evt < T_event3->GetEntries(); evt++)
    {
        T_event3->GetEntry(evt);

        for (int itrk = 0; itrk < v_gg_ZZ_2mu2nu_log3Dsig->size(); itrk++)
        {
            h_Diboson_3Dsig->Fill((*v_gg_ZZ_2mu2nu_log3Dsig)[itrk], f_gg_ZZ_2mu2nu_weight * merge_weight.ee_diboson_gg_ZZ_2mu2nu_Weight);
        }
        if (f_gg_ZZ_2mu2nu_met <= METcut)
        {
            continue;
        }
        for (int ijet = 0; ijet < v_gg_ZZ_2mu2nu_alpha3->size(); ijet++)
        {
            h_bg_alpha3->Fill((*v_gg_ZZ_2mu2nu_alpha3)[ijet], f_gg_ZZ_2mu2nu_weight * merge_weight.ee_diboson_gg_ZZ_2mu2nu_Weight);
        }
    }
    TTree *T_event4;
    merge_bfiles.ee_diboson_gg_ZZ_2mu2tau->GetObject("T_tree", T_event4);
    T_event4->SetBranchAddress("I_weight", &f_gg_ZZ_2mu2tau_weight);
    T_event4->SetBranchAddress("f_Met", &f_gg_ZZ_2mu2tau_met);

    T_event4->SetBranchAddress("v_Chi3Dlog", &v_gg_ZZ_2mu2tau_log3Dsig);
    T_event4->SetBranchAddress("v_fakealpha3", &v_gg_ZZ_2mu2tau_alpha3);
    for (int evt = 0; evt < T_event4->GetEntries(); evt++)
    {
        T_event4->GetEntry(evt);

        for (int itrk = 0; itrk < v_gg_ZZ_2mu2tau_log3Dsig->size(); itrk++)
        {
            h_Diboson_3Dsig->Fill((*v_gg_ZZ_2mu2tau_log3Dsig)[itrk], f_gg_ZZ_2mu2tau_weight * merge_weight.ee_diboson_gg_ZZ_2mu2tau_Weight);
        }
        if (f_gg_ZZ_2mu2tau_met <= METcut)
        {
            continue;
        }
        for (int ijet = 0; ijet < v_gg_ZZ_2mu2tau_alpha3->size(); ijet++)
        {
            h_bg_alpha3->Fill((*v_gg_ZZ_2mu2tau_alpha3)[ijet], f_gg_ZZ_2mu2tau_weight * merge_weight.ee_diboson_gg_ZZ_2mu2tau_Weight);
        }
    }

    TTree *T_event5;
    merge_bfiles.ee_diboson_gg_ZZ_4e->GetObject("T_tree", T_event5);
    T_event5->SetBranchAddress("I_weight", &f_gg_ZZ_4e_weight);
    T_event5->SetBranchAddress("f_Met", &f_gg_ZZ_4e_met);

    T_event5->SetBranchAddress("v_Chi3Dlog", &v_gg_ZZ_4e_log3Dsig);
    T_event5->SetBranchAddress("v_fakealpha3", &v_gg_ZZ_4e_alpha3);
    for (int evt = 0; evt < T_event5->GetEntries(); evt++)
    {
        T_event5->GetEntry(evt);

        for (int itrk = 0; itrk < v_gg_ZZ_4e_log3Dsig->size(); itrk++)
        {
            h_Diboson_3Dsig->Fill((*v_gg_ZZ_4e_log3Dsig)[itrk], f_gg_ZZ_4e_weight * merge_weight.ee_diboson_gg_ZZ_4e_Weight);
        }
        if (f_gg_ZZ_4e_met <= METcut)
        {
            continue;
        }
        for (int ijet = 0; ijet < v_gg_ZZ_4e_alpha3->size(); ijet++)
        {
            h_bg_alpha3->Fill((*v_gg_ZZ_4e_alpha3)[ijet], f_gg_ZZ_4e_weight * merge_weight.ee_diboson_gg_ZZ_4e_Weight);
        }
    }
    TTree *T_event6;
    merge_bfiles.ee_diboson_gg_ZZ_4mu->GetObject("T_tree", T_event6);
    T_event6->SetBranchAddress("I_weight", &f_gg_ZZ_4mu_weight);
    T_event6->SetBranchAddress("f_Met", &f_gg_ZZ_4mu_met);

    T_event6->SetBranchAddress("v_Chi3Dlog", &v_gg_ZZ_4mu_log3Dsig);
    T_event6->SetBranchAddress("v_fakealpha3", &v_gg_ZZ_4mu_alpha3);
    for (int evt = 0; evt < T_event6->GetEntries(); evt++)
    {
        T_event6->GetEntry(evt);

        for (int itrk = 0; itrk < v_gg_ZZ_4mu_log3Dsig->size(); itrk++)
        {
            h_Diboson_3Dsig->Fill((*v_gg_ZZ_4mu_log3Dsig)[itrk], f_gg_ZZ_4mu_weight * merge_weight.ee_diboson_gg_ZZ_4mu_Weight);
        }
        if (f_gg_ZZ_4mu_met <= METcut)
        {
            continue;
        }
        for (int ijet = 0; ijet < v_gg_ZZ_4mu_alpha3->size(); ijet++)
        {
            h_bg_alpha3->Fill((*v_gg_ZZ_4mu_alpha3)[ijet], f_gg_ZZ_4mu_weight * merge_weight.ee_diboson_gg_ZZ_4mu_Weight);
        }
    }
    TTree *T_event7;
    merge_bfiles.ee_diboson_gg_ZZ_4tau->GetObject("T_tree", T_event7);
    T_event7->SetBranchAddress("I_weight", &f_gg_ZZ_4tau_weight);
    T_event7->SetBranchAddress("f_Met", &f_gg_ZZ_4tau_met);

    T_event7->SetBranchAddress("v_Chi3Dlog", &v_gg_ZZ_4tau_log3Dsig);
    T_event7->SetBranchAddress("v_fakealpha3", &v_gg_ZZ_4tau_alpha3);
    for (int evt = 0; evt < T_event7->GetEntries(); evt++)
    {
        T_event7->GetEntry(evt);

        for (int itrk = 0; itrk < v_gg_ZZ_4tau_log3Dsig->size(); itrk++)
        {
            h_Diboson_3Dsig->Fill((*v_gg_ZZ_4tau_log3Dsig)[itrk], f_gg_ZZ_4tau_weight * merge_weight.ee_diboson_gg_ZZ_4tau_Weight);
        }
        if (f_gg_ZZ_4tau_met <= METcut)
        {
            continue;
        }
        for (int ijet = 0; ijet < v_gg_ZZ_4tau_alpha3->size(); ijet++)
        {
            h_bg_alpha3->Fill((*v_gg_ZZ_4tau_alpha3)[ijet], f_gg_ZZ_4tau_weight * merge_weight.ee_diboson_gg_ZZ_4tau_Weight);
        }
    }
    TTree *T_event8;
    merge_bfiles.ee_diboson_gg_WW_2L2Nu->GetObject("T_tree", T_event8);
    T_event8->SetBranchAddress("I_weight", &f_gg_WW_2L2Nu_weight);
    T_event8->SetBranchAddress("f_Met", &f_gg_WW_2L2Nu_met);

    T_event8->SetBranchAddress("v_Chi3Dlog", &v_gg_WW_2L2Nu_log3Dsig);
    T_event8->SetBranchAddress("v_fakealpha3", &v_gg_WW_2L2Nu_alpha3);
    for (int evt = 0; evt < T_event8->GetEntries(); evt++)
    {
        T_event8->GetEntry(evt);

        for (int itrk = 0; itrk < v_gg_WW_2L2Nu_log3Dsig->size(); itrk++)
        {
            h_Diboson_3Dsig->Fill((*v_gg_WW_2L2Nu_log3Dsig)[itrk], f_gg_WW_2L2Nu_weight * merge_weight.ee_diboson_gg_WW_2L2Nu_Weight);
        }

        if (f_gg_WW_2L2Nu_met <= METcut)
        {
            continue;
        }
        for (int ijet = 0; ijet < v_gg_WW_2L2Nu_alpha3->size(); ijet++)
        {
            h_bg_alpha3->Fill((*v_gg_WW_2L2Nu_alpha3)[ijet], f_gg_WW_2L2Nu_weight * merge_weight.ee_diboson_gg_WW_2L2Nu_Weight);
        }
    }
    TTree *T_event9;
    merge_bfiles.ee_diboson_qq_WW_2L2Nu->GetObject("T_tree", T_event9);
    T_event9->SetBranchAddress("I_weight", &f_qq_WW_2L2Nu_weight);
    T_event9->SetBranchAddress("f_Met", &f_qq_WW_2L2Nu_met);

    T_event9->SetBranchAddress("v_Chi3Dlog", &v_qq_WW_2L2Nu_log3Dsig);
    T_event9->SetBranchAddress("v_fakealpha3", &v_qq_WW_2L2Nu_alpha3);
    for (int evt = 0; evt < T_event9->GetEntries(); evt++)
    {
        T_event9->GetEntry(evt);

        for (int itrk = 0; itrk < v_qq_WW_2L2Nu_log3Dsig->size(); itrk++)
        {
            h_Diboson_3Dsig->Fill((*v_qq_WW_2L2Nu_log3Dsig)[itrk], f_qq_WW_2L2Nu_weight * merge_weight.ee_diboson_qq_WW_2L2Nu_Weight);
        }
        if (f_qq_WW_2L2Nu_met <= METcut)
        {
            continue;
        }
        for (int ijet = 0; ijet < v_qq_WW_2L2Nu_alpha3->size(); ijet++)
        {
            h_bg_alpha3->Fill((*v_qq_WW_2L2Nu_alpha3)[ijet], f_qq_WW_2L2Nu_weight * merge_weight.ee_diboson_qq_WW_2L2Nu_Weight);
        }
    }
    TTree *T_event10;
    merge_bfiles.ee_diboson_qq_WZ_2L2Q->GetObject("T_tree", T_event10);
    T_event10->SetBranchAddress("I_weight", &f_qq_WZ_2L2Q_weight);
    T_event10->SetBranchAddress("f_Met", &f_qq_WZ_2L2Q_met);

    T_event10->SetBranchAddress("v_Chi3Dlog", &v_qq_WZ_2L2Q_log3Dsig);
    T_event10->SetBranchAddress("v_fakealpha3", &v_qq_WZ_2L2Q_alpha3);
    for (int evt = 0; evt < T_event10->GetEntries(); evt++)
    {
        T_event10->GetEntry(evt);

        for (int itrk = 0; itrk < v_qq_WZ_2L2Q_log3Dsig->size(); itrk++)
        {
            h_Diboson_3Dsig->Fill((*v_qq_WZ_2L2Q_log3Dsig)[itrk], f_qq_WZ_2L2Q_weight * merge_weight.ee_diboson_qq_WZ_2L2Q_Weight);
        }
        if (f_qq_WZ_2L2Q_met <= METcut)
        {
            continue;
        }
        for (int ijet = 0; ijet < v_qq_WZ_2L2Q_alpha3->size(); ijet++)
        {
            h_bg_alpha3->Fill((*v_qq_WZ_2L2Q_alpha3)[ijet], f_qq_WZ_2L2Q_weight * merge_weight.ee_diboson_qq_WZ_2L2Q_Weight);
        }
    }
    TTree *T_event11;
    merge_bfiles.ee_diboson_qq_WZ_3LNu->GetObject("T_tree", T_event11);
    T_event11->SetBranchAddress("I_weight", &f_qq_WZ_3LNu_weight);
    T_event11->SetBranchAddress("f_Met", &f_qq_WZ_3LNu_met);

    T_event11->SetBranchAddress("v_Chi3Dlog", &v_qq_WZ_3LNu_log3Dsig);
    T_event11->SetBranchAddress("v_fakealpha3", &v_qq_WZ_3LNu_alpha3);
    for (int evt = 0; evt < T_event11->GetEntries(); evt++)
    {
        T_event11->GetEntry(evt);

        for (int itrk = 0; itrk < v_qq_WZ_3LNu_log3Dsig->size(); itrk++)
        {
            h_Diboson_3Dsig->Fill((*v_qq_WZ_3LNu_log3Dsig)[itrk], f_qq_WZ_3LNu_weight * merge_weight.ee_diboson_qq_WZ_3LNu_Weight);
        }
        if (f_qq_WZ_3LNu_met <= METcut)
        {
            continue;
        }
        for (int ijet = 0; ijet < v_qq_WZ_3LNu_alpha3->size(); ijet++)
        {
            h_bg_alpha3->Fill((*v_qq_WZ_3LNu_alpha3)[ijet], f_qq_WZ_3LNu_weight * merge_weight.ee_diboson_qq_WZ_3LNu_Weight);
        }
    }
    TTree *T_event12;
    merge_bfiles.ee_diboson_qq_ZZ_2L2Nu->GetObject("T_tree", T_event12);
    T_event12->SetBranchAddress("I_weight", &f_qq_ZZ_2L2Nu_weight);
    T_event12->SetBranchAddress("f_Met", &f_qq_ZZ_2L2Nu_met);

    T_event12->SetBranchAddress("v_Chi3Dlog", &v_qq_ZZ_2L2Nu_log3Dsig);
    T_event12->SetBranchAddress("v_fakealpha3", &v_qq_ZZ_2L2Nu_alpha3);
    for (int evt = 0; evt < T_event12->GetEntries(); evt++)
    {
        T_event12->GetEntry(evt);

        for (int itrk = 0; itrk < v_qq_ZZ_2L2Nu_log3Dsig->size(); itrk++)
        {
            h_Diboson_3Dsig->Fill((*v_qq_ZZ_2L2Nu_log3Dsig)[itrk], f_qq_ZZ_2L2Nu_weight * merge_weight.ee_diboson_qq_ZZ_2L2Nu_Weight);
        }
        if (f_qq_ZZ_2L2Nu_met <= METcut)
        {
            continue;
        }
        for (int ijet = 0; ijet < v_qq_ZZ_2L2Nu_alpha3->size(); ijet++)
        {
            h_bg_alpha3->Fill((*v_qq_ZZ_2L2Nu_alpha3)[ijet], f_qq_ZZ_2L2Nu_weight * merge_weight.ee_diboson_qq_ZZ_2L2Nu_Weight);
        }
    }
    TTree *T_event13;
    merge_bfiles.ee_diboson_qq_ZZ_2L2Q->GetObject("T_tree", T_event13);
    T_event13->SetBranchAddress("I_weight", &f_qq_ZZ_2L2Q_weight);
    T_event13->SetBranchAddress("f_Met", &f_qq_ZZ_2L2Q_met);

    T_event13->SetBranchAddress("v_Chi3Dlog", &v_qq_ZZ_2L2Q_log3Dsig);
    T_event13->SetBranchAddress("v_fakealpha3", &v_qq_ZZ_2L2Q_alpha3);
    for (int evt = 0; evt < T_event13->GetEntries(); evt++)
    {
        T_event13->GetEntry(evt);

        for (int itrk = 0; itrk < v_qq_ZZ_2L2Q_log3Dsig->size(); itrk++)
        {
            h_Diboson_3Dsig->Fill((*v_qq_ZZ_2L2Q_log3Dsig)[itrk], f_qq_ZZ_2L2Q_weight * merge_weight.ee_diboson_qq_ZZ_2L2Q_Weight);
        }
        if (f_qq_ZZ_2L2Q_met <= METcut)
        {
            continue;
        }
        for (int ijet = 0; ijet < v_qq_ZZ_2L2Q_alpha3->size(); ijet++)
        {
            h_bg_alpha3->Fill((*v_qq_ZZ_2L2Q_alpha3)[ijet], f_qq_ZZ_2L2Q_weight * merge_weight.ee_diboson_qq_ZZ_2L2Q_Weight);
        }
    }
    TTree *T_event14;
    merge_bfiles.ee_diboson_qq_ZZ_4L->GetObject("T_tree", T_event14);
    T_event14->SetBranchAddress("I_weight", &f_qq_ZZ_4L_weight);
    T_event14->SetBranchAddress("f_Met", &f_qq_ZZ_4L_met);

    T_event14->SetBranchAddress("v_Chi3Dlog", &v_qq_ZZ_4L_log3Dsig);
    T_event14->SetBranchAddress("v_fakealpha3", &v_qq_ZZ_4L_alpha3);
    for (int evt = 0; evt < T_event14->GetEntries(); evt++)
    {
        T_event14->GetEntry(evt);

        for (int itrk = 0; itrk < v_qq_ZZ_4L_log3Dsig->size(); itrk++)
        {
            h_Diboson_3Dsig->Fill((*v_qq_ZZ_4L_log3Dsig)[itrk], f_qq_ZZ_4L_weight * merge_weight.ee_diboson_qq_ZZ_4L_Weight);
        }
        if (f_qq_ZZ_4L_met <= METcut)
        {
            continue;
        }

        for (int ijet = 0; ijet < v_qq_ZZ_4L_alpha3->size(); ijet++)
        {
            h_bg_alpha3->Fill((*v_qq_ZZ_4L_alpha3)[ijet], f_qq_ZZ_4L_weight * merge_weight.ee_diboson_qq_ZZ_4L_Weight);
        }
    }
    h_bg_alpha3->Draw();
    TString outputfile = "./ee_Dibosonsig.root";

    TFile *outfile_HT0 = TFile::Open(outputfile, "RECREATE");
    h_Diboson_3Dsig->Write();
    h_bg_alpha3->Write();
    outfile_HT0->Close();
}