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
#include <TGraph.h>
#include <TError.h>
#include "TLegend.h"
#include <cstring>
#include "./../../../lib/tdrstyle.C"
#include "./../../../lib/CMS_lumi.h"
using namespace std;

void ee_Sig_eff()
{

    //------------------
    // Calculate weight
    //------------------
    TFile *Sig_Mx2_1file = new TFile("/home/kuanyu/Documents/root_file/Ztoee/ee_Mx2_1_old_remove_0alpha.root");
    TFile *Sig_Mx2_50file = new TFile("/home/kuanyu/Documents/root_file/Ztoee/ee_Mx2_50_old_remove_0alpha.root");
    TFile *Sig_Mx2_150file = new TFile("/home/kuanyu/Documents/root_file/Ztoee/ee_Mx2_150_old_remove_0alpha.root");

    TH1D *Sig_Mx2_1_eepass = ((TH1D *)Sig_Mx2_1file->Get("Event_Variable/h_ee_npass"));
    TH1D *Sig_Mx2_50_eepass = ((TH1D *)Sig_Mx2_50file->Get("Event_Variable/h_ee_npass"));
    TH1D *Sig_Mx2_150_eepass = ((TH1D *)Sig_Mx2_150file->Get("Event_Variable/h_ee_npass"));

    TH1D *h_Sig_Mx2_1_pass_offline = new TH1D("h_Sig_Mx2_1_pass_offline", "", 12, 0, 12);
    TH1D *h_Sig_Mx2_50_pass_offline = new TH1D("h_Sig_Mx2_50_pass_offline", "", 12, 0, 12);
    TH1D *h_Sig_Mx2_150_pass_offline = new TH1D("h_Sig_Mx2_150_pass_offline", "", 12, 0, 12);

    TH1D *h_ee21_pass = (TH1D *)Sig_Mx2_1_eepass->Clone("h_ee_pass");
    TH1D *h_ee250_pass = (TH1D *)Sig_Mx2_50_eepass->Clone("h_ee_pass");
    TH1D *h_ee2150_pass = (TH1D *)Sig_Mx2_150_eepass->Clone("h_ee_pass");

    Int_t I_Mx1_weight, I_Mx50_weight, I_Mx150_weight;

    float_t f_Mx1_Met, f_Mx50_Met, f_Mx150_Met;

    float_t f_Mx1_dilepton_PT, f_Mx50_dilepton_PT, f_Mx150_dilepton_PT;

    vector<float> *v_Mx1_alpha = new vector<float>();
    vector<float> *v_Mx50_alpha = new vector<float>();
    vector<float> *v_Mx150_alpha = new vector<float>();

    v_Mx1_alpha->clear();
    v_Mx50_alpha->clear();
    v_Mx150_alpha->clear();

    vector<double> v_Mx21_evtpass;
    vector<double> v_Mx250_evtpass;
    vector<double> v_Mx2150_evtpass;

    v_Mx21_evtpass.clear();
    v_Mx250_evtpass.clear();
    v_Mx2150_evtpass.clear();

    /*Fill pass evt in vector*/

    int nBinx = h_ee21_pass->GetNbinsX();
    for (int i = 0; i < nBinx - 2; i++)
    {
        // cout << "i = " << i << "h_ee21_pass[i] = " << h_ee21_pass->GetBinContent(i + 1) << endl;
        if ((i + 1) > 2)
        {
            v_Mx21_evtpass.push_back(h_ee21_pass->GetBinContent(i + 1));
            v_Mx250_evtpass.push_back(h_ee250_pass->GetBinContent(i + 1));
            v_Mx2150_evtpass.push_back(h_ee2150_pass->GetBinContent(i + 1));
        }
        continue;
    }

    // cout<<nBinx<<endl;

    int npass_Mx21_alpha = 0;
    int npass_Mx250_alpha = 0;
    int npass_Mx2150_alpha = 0;

    int npass_Mx21_Met = 0;
    int npass_Mx250_Met = 0;
    int npass_Mx2150_Met = 0;

    TTree *T_Mx2_1;
    Sig_Mx2_1file->GetObject("T_tree", T_Mx2_1);
    T_Mx2_1->SetBranchAddress("I_weight", &I_Mx1_weight);
    T_Mx2_1->SetBranchAddress("f_Met", &f_Mx1_Met);
    T_Mx2_1->SetBranchAddress("f_dileptonPT", &f_Mx1_dilepton_PT);
    T_Mx2_1->SetBranchAddress("v_fakealpha", &v_Mx1_alpha);
    for (int evt = 0; evt < T_Mx2_1->GetEntries(); evt++)
    {
        T_Mx2_1->GetEntry(evt);
        if (v_Mx1_alpha->size() < 2)
        {
            continue;
        }
        h_Sig_Mx2_1_pass_offline->Fill(9, I_Mx1_weight);

        if (f_Mx1_Met <= 140.)
        {
            continue;
        }
        h_Sig_Mx2_1_pass_offline->Fill(10, I_Mx1_weight);
        if (f_Mx1_dilepton_PT < 60.)
        {
            continue;
        }
        h_Sig_Mx2_1_pass_offline->Fill(11, I_Mx1_weight);
    } // End of Mx2_1 Entries loop

    TTree *T_Mx2_50;
    Sig_Mx2_50file->GetObject("T_tree", T_Mx2_50);
    T_Mx2_50->SetBranchAddress("I_weight", &I_Mx50_weight);
    T_Mx2_50->SetBranchAddress("f_Met", &f_Mx50_Met);
    T_Mx2_50->SetBranchAddress("f_dileptonPT", &f_Mx50_dilepton_PT);
    T_Mx2_50->SetBranchAddress("v_fakealpha", &v_Mx50_alpha);
    for (int evt = 0; evt < T_Mx2_50->GetEntries(); evt++)
    {
        T_Mx2_50->GetEntry(evt);
        if (v_Mx50_alpha->size() < 2)
        {
            continue;
        }
        h_Sig_Mx2_50_pass_offline->Fill(9, I_Mx50_weight);

        if (f_Mx50_Met <= 140.)
        {
            continue;
        }
        h_Sig_Mx2_50_pass_offline->Fill(10, I_Mx50_weight);
        if (f_Mx50_dilepton_PT < 60.)
        {
            continue;
        }
        h_Sig_Mx2_50_pass_offline->Fill(11, I_Mx50_weight);

    } // End of Mx2_50 Entries loop
    TTree *T_Mx2_150;
    Sig_Mx2_150file->GetObject("T_tree", T_Mx2_150);
    T_Mx2_150->SetBranchAddress("I_weight", &I_Mx150_weight);
    T_Mx2_150->SetBranchAddress("f_Met", &f_Mx150_Met);
    T_Mx2_150->SetBranchAddress("f_dileptonPT", &f_Mx150_dilepton_PT);
    T_Mx2_150->SetBranchAddress("v_fakealpha", &v_Mx150_alpha);
    for (int evt = 0; evt < T_Mx2_150->GetEntries(); evt++)
    {
        T_Mx2_150->GetEntry(evt);
        if (v_Mx150_alpha->size() < 2)
        {
            continue;
        }
        h_Sig_Mx2_150_pass_offline->Fill(9, I_Mx150_weight);

        if (f_Mx150_Met <= 140.)
        {
            continue;
        }
        h_Sig_Mx2_150_pass_offline->Fill(10, I_Mx150_weight);
        if (f_Mx150_dilepton_PT < 60.)
        {
            continue;
        }
        h_Sig_Mx2_150_pass_offline->Fill(11, I_Mx150_weight);

    } // End of Mx2_150 Entries loop

    v_Mx21_evtpass.push_back(h_Sig_Mx2_1_pass_offline->GetBinContent(10));
    v_Mx21_evtpass.push_back(h_Sig_Mx2_1_pass_offline->GetBinContent(11));
    v_Mx21_evtpass.push_back(h_Sig_Mx2_1_pass_offline->GetBinContent(12));

    v_Mx250_evtpass.push_back(h_Sig_Mx2_50_pass_offline->GetBinContent(10));
    v_Mx250_evtpass.push_back(h_Sig_Mx2_50_pass_offline->GetBinContent(11));
    v_Mx250_evtpass.push_back(h_Sig_Mx2_50_pass_offline->GetBinContent(12));

    v_Mx2150_evtpass.push_back(h_Sig_Mx2_150_pass_offline->GetBinContent(10));
    v_Mx2150_evtpass.push_back(h_Sig_Mx2_150_pass_offline->GetBinContent(11));
    v_Mx2150_evtpass.push_back(h_Sig_Mx2_150_pass_offline->GetBinContent(12));


    /*for (auto it : v_Mx2150_evtpass)
    {
        cout << it << endl;
    }*/
    cout << "size = " << v_Mx2150_evtpass.size() << endl;
    Int_t n = 9;
    Double_t x_Mx21[n], y_Mx21[n];
    Double_t x_Mx250[n], y_Mx250[n];
    Double_t x_Mx2150[n], y_Mx2150[n];

    for (Int_t i = 0; i < n; i++)
    {
        x_Mx21[i] = i;
        x_Mx250[i] = i;
        x_Mx2150[i] = i;
        double Mx2_1eff = (v_Mx21_evtpass[i]) / (h_ee21_pass->GetBinContent(2));
        double Mx2_50eff = (v_Mx250_evtpass[i]) / (h_ee250_pass->GetBinContent(2));
        double Mx2_150eff = (v_Mx2150_evtpass[i]) / (h_ee2150_pass->GetBinContent(2));

        cout << "Mx2_1eff" << Mx2_1eff << endl;
        cout << "Mx2_50eff" << Mx2_50eff << endl;
        cout << "Mx2_150eff" << Mx2_150eff << endl;
        cout << endl;
        y_Mx21[i] = Mx2_1eff;
        y_Mx250[i] = Mx2_50eff;
        y_Mx2150[i] = Mx2_150eff;
    }

    int W = 600;
    int H = 600;

    int H_ref = 600;
    int W_ref = 600;

    float T = 0.08 * H_ref;
    float B = 0.12 * H_ref;
    float L = 0.12 * W_ref;
    float R = 0.04 * W_ref;

    // visualize the fitting result
    setTDRStyle();
    auto c1 = new TCanvas("c", "c", 800, 800);
    c1->cd();
    c1->SetRightMargin(0.08);
    //c1->SetBottomMargin(0.5);
    c1->SetTopMargin(0.07);
    c1->SetLeftMargin(0.12);

    auto pad1 = new TPad("pad1", " ", 0, 0.3, 1, 1.0);
    pad1->SetTopMargin(0.08);
    pad1->SetRightMargin(0.05);
    pad1->SetLeftMargin(0.13);
    pad1->SetBottomMargin(0.2);
    pad1->Draw();
    pad1->cd();

    TGraph *grMx21 = new TGraph(n, x_Mx21, y_Mx21);
    TGraph *grMx250 = new TGraph(n, x_Mx250, y_Mx250);
    TGraph *grMx2150 = new TGraph(n, x_Mx2150, y_Mx2150);
    // gr1->Draw("AL*");
    grMx21->GetYaxis()->SetTitle("Signal efficiency");
    grMx21->GetXaxis()->SetTitle("Cut Step");

    char *efflable[9] = {"Good Vertex selection ",
                         "The pT for Leading and trailing Lepton selection",
                         "Dilepton mass selection", "Reduce Diboson background selection",
                         "Reduce tau background selection ", "Number of selected Jet selection",
                         "Number of selected Track selection", "MET selection","Dilepton PT selection"};
    TH1F *h_Mx21_eff = new TH1F("h_Mx21_eff", "", n, x_Mx21[0], x_Mx21[n - 1]);
    TH1F *h_Mx250_eff = new TH1F("h_Mx250_eff", "", n, x_Mx250[0], x_Mx250[n - 1]);
    TH1F *h_Mx2150_eff = new TH1F("h_Mx2150_eff", "", n, x_Mx2150[0], x_Mx2150[n - 1]);
    for (int i = 1; i <= n; i++)
    {
        h_Mx21_eff->GetXaxis()->SetBinLabel(i, efflable[i - 1]);
        h_Mx250_eff->GetXaxis()->SetBinLabel(i, efflable[i - 1]);
        h_Mx2150_eff->GetXaxis()->SetBinLabel(i, efflable[i - 1]);
    }

    // h->SetMaximum(12);
    h_Mx21_eff->GetYaxis()->SetTitle("Signal efficiency");
    h_Mx250_eff->GetYaxis()->SetTitle("Signal efficiency");
    h_Mx2150_eff->GetYaxis()->SetTitle("Signal efficiency");

    h_Mx250_eff->GetXaxis()->SetLabelSize(0.05);
    // h_Mx20_eff->GetXaxis()->SetTitle("Cut Step");

    h_Mx250_eff->Draw();

    grMx21->SetLineWidth(2);
    grMx21->SetLineColor(kRed);

    grMx250->SetLineWidth(2);
    grMx250->SetLineColor(kGray + 2);

    grMx2150->SetLineWidth(2);
    grMx2150->SetLineColor(kBlue);

    grMx21->Draw("L*");

    gStyle->SetOptStat(0);
    // h_Sig_Mx2_1_pass_offline->Draw("text");

    // TFile *outfile = TFile::Open(outputfile, "RECREATE");
    // outfile->cd();
    // h_ee_pass->Write();
    // outfile->Close();
}

int main(int argc, char **argv)
{
    if (argc == 1)
    {
        ee_Sig_eff();
    }
    else if (argc == 3)
    {
        ee_Sig_eff();
    }
    else
    {
        cout << "argc" << argc << endl;
        cout << "ERROR" << endl;
    }
}