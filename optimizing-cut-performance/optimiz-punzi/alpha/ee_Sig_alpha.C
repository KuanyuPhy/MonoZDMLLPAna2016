#include <iostream>
#include <sstream>
#include <TTree.h>
#include <TMath.h>
#include <TFile.h>
#include <TH3D.h>
#include <TH2D.h>
#include <TGraph.h>
#include <TROOT.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TLatex.h>
#include <TAxis.h>
#include <TLine.h>
#include "./../../met/tdrstyle.C"
#include "./../../met/CMS_lumi.C"
using namespace std;
double punzi(double sigeff, double bg)
{
    return sigeff / (1 + TMath::Power(abs(bg), 0.5));
}

int sumstep = 20;

TFile *Mx2_1 = new TFile("/home/kuanyu/Documents/root_file/Ztoee/ee_Mx2_1_old_remove_0alpha.root");
TFile *Mx2_50 = new TFile("/home/kuanyu/Documents/root_file/Ztoee/ee_Mx2_50_old_remove_0alpha.root");
TFile *Mx2_150 = new TFile("/home/kuanyu/Documents/root_file/Ztoee/ee_Mx2_150_old_remove_0alpha.root");
TFile *Bgall = new TFile("./output/ee_bg_alpha2cut.root");
TH1D *h_bgall_alpha = ((TH1D *)Bgall->Get("h_Bg_alpha"));

void ee_Sig_alpha()
{
    setTDRStyle();

    TH1D *h_Sig1_nJet_cut[sumstep];
    TH1D *h_Sig1_nJet[sumstep];
    TH1D *h_Sig50_nJet_cut[sumstep];
    TH1D *h_Sig50_nJet[sumstep];
    TH1D *h_Sig150_nJet_cut[sumstep];
    TH1D *h_Sig150_nJet[sumstep];
    TH1D *h_Bgall[sumstep];
    TH1D *h_Bg_cut[sumstep];

    TH1D *h_Sig1_alpha = new TH1D("h_Sig1_alpha", "", 20, 0, 1);
    TH1D *h_Sig50_alpha = new TH1D("h_Sig50_alpha", "", 20, 0, 1);
    TH1D *h_Sig150_alpha = new TH1D("h_Sig150_alpha", "", 20, 0, 1);

    //-------------------------
    // CMS style
    //-------------------------
    writeExtraText = true;
    extraText = "Simulation";
    lumi_sqrtS = "13 TeV";

    for (int i = 0; i < sumstep; i++)
    {
        float alphacut = (i + 1) * 0.05;

        h_Sig1_nJet_cut[i] = new TH1D(Form("h_Sig1_nJet_cut%i", i + 1), "", 30, 0, 30);
        h_Sig1_nJet[i] = new TH1D(Form("h_Sig1_nJet_%i", i + 1), "", 30, 0, 30);
        h_Sig50_nJet_cut[i] = new TH1D(Form("h_Sig50_nJet_cut%i", i + 1), "", 30, 0, 30);
        h_Sig50_nJet[i] = new TH1D(Form("h_Sig50_nJet_%i", i + 1), "", 30, 0, 30);
        h_Sig150_nJet_cut[i] = new TH1D(Form("h_Sig150_nJet_cut%i", i + 1), "", 30, 0, 30);
        h_Sig150_nJet[i] = new TH1D(Form("h_Sig150_nJet_%i", i + 1), "", 30, 0, 30);

        h_Bgall[i] = ((TH1D *)Bgall->Get(Form("h_Bg_nJet_%i", i + 1)));
        h_Bg_cut[i] = ((TH1D *)Bgall->Get(Form("h_Bg_nJet_cut_%i", i + 1)));

        Int_t I_Mx1_weight, I_Mx50_weight, I_Mx150_weight;

        float_t f_Mx1_Met, f_Mx50_Met, f_Mx150_Met;

        Int_t I_Mx1_nThinJets, I_Mx50_nThinJets, I_Mx150_nThinJets;

        vector<float> *v_Mx1_alpha = new vector<float>();
        vector<float> *v_Mx50_alpha = new vector<float>();
        vector<float> *v_Mx150_alpha = new vector<float>();

        v_Mx1_alpha->clear();
        v_Mx50_alpha->clear();
        v_Mx150_alpha->clear();

        TTree *T_Mx2_1;
        Mx2_1->GetObject("T_tree", T_Mx2_1);
        T_Mx2_1->SetBranchAddress("I_weight", &I_Mx1_weight);
        T_Mx2_1->SetBranchAddress("f_Met", &f_Mx1_Met);
        T_Mx2_1->SetBranchAddress("I_nJets", &I_Mx1_nThinJets);
        T_Mx2_1->SetBranchAddress("v_fakealpha2", &v_Mx1_alpha);
        for (int evt = 0; evt < T_Mx2_1->GetEntries(); evt++)
        {
            T_Mx2_1->GetEntry(evt);
            int jet_passalpha_cut = 0;
            /*
            if (f_Mx1_Met < 140)
            {
                continue;
            }
            */
            for (int i = 0; i < v_Mx1_alpha->size(); i++)
            {
                h_Sig1_alpha->Fill((*v_Mx1_alpha)[i], I_Mx1_weight);
                if ((*v_Mx1_alpha)[i] < alphacut)
                {
                    jet_passalpha_cut++;
                }
            }
            
            if (jet_passalpha_cut == 0)
            {
                continue;
            }
            
            h_Sig1_nJet[i]->Fill(jet_passalpha_cut, I_Mx1_weight);
            if (jet_passalpha_cut < 2)
            {
                continue;
            }
            h_Sig1_nJet_cut[i]->Fill(jet_passalpha_cut, I_Mx1_weight);
        } // End of Mx2_1 Entries loop
        TTree *T_Mx2_50;
        Mx2_50->GetObject("T_tree", T_Mx2_50);
        T_Mx2_50->SetBranchAddress("I_weight", &I_Mx50_weight);
        T_Mx2_50->SetBranchAddress("f_Met", &f_Mx50_Met);
        T_Mx2_50->SetBranchAddress("I_nJets", &I_Mx50_nThinJets);
        T_Mx2_50->SetBranchAddress("v_fakealpha2", &v_Mx50_alpha);
        for (int evt = 0; evt < T_Mx2_50->GetEntries(); evt++)
        {
            T_Mx2_50->GetEntry(evt);
            int jet_passalpha_cut = 0;
            /*
            if (f_Mx50_Met < 140)
            {
                continue;
            }
            */
            for (int i = 0; i < v_Mx50_alpha->size(); i++)
            {
                h_Sig50_alpha->Fill((*v_Mx50_alpha)[i], I_Mx50_weight);
                if ((*v_Mx50_alpha)[i] < alphacut)
                {
                    jet_passalpha_cut++;
                }
            }
            
            if (jet_passalpha_cut == 0)
            {
                continue;
            }
            h_Sig50_nJet[i]->Fill(jet_passalpha_cut, I_Mx50_weight);
            if (jet_passalpha_cut < 2)
            {
                continue;
            }
            /*
            if (i == 5)
            {
                cout << "jet_passalpha_cut = " << jet_passalpha_cut << endl;
                cout << "Weight" << I_Mx50_weight << endl;
            }
            */
            h_Sig50_nJet_cut[i]->Fill(jet_passalpha_cut, I_Mx50_weight);
        } // End of Mx2_50 Entries loop
        TTree *T_Mx2_150;
        Mx2_150->GetObject("T_tree", T_Mx2_150);
        T_Mx2_150->SetBranchAddress("I_weight", &I_Mx150_weight);
        T_Mx2_150->SetBranchAddress("f_Met", &f_Mx150_Met);
        T_Mx2_150->SetBranchAddress("I_nJets", &I_Mx150_nThinJets);
        T_Mx2_150->SetBranchAddress("v_fakealpha2", &v_Mx150_alpha);
        for (int evt = 0; evt < T_Mx2_150->GetEntries(); evt++)
        {
            T_Mx2_150->GetEntry(evt);
            int jet_passalpha_cut = 0;
            /*
            if (f_Mx150_Met < 140)
            {
                continue;
            }
            */
            for (int i = 0; i < v_Mx150_alpha->size(); i++)
            {
                h_Sig150_alpha->Fill((*v_Mx150_alpha)[i], I_Mx150_weight);
                if ((*v_Mx150_alpha)[i] < alphacut)
                {
                    jet_passalpha_cut++;
                }
            }
            
            if (jet_passalpha_cut == 0)
            {
                continue;
            }
            
            h_Sig150_nJet[i]->Fill(jet_passalpha_cut, I_Mx150_weight);
            if (jet_passalpha_cut < 2)
            {
                continue;
            }
            h_Sig150_nJet_cut[i]->Fill(jet_passalpha_cut, I_Mx150_weight);
        } // End of Mx2_150 Entries loop
    }     // End of alphacut loop

    TH1D *h_punzisig1 = new TH1D("h_punzisig1", "", sumstep, 0, sumstep);
    TH1D *h_punzisig50 = new TH1D("h_punzisig50", "", sumstep, 0, sumstep);
    TH1D *h_punzisig150 = new TH1D("h_punzisig150", "", sumstep, 0, sumstep);

    double arr_sig1[sumstep];
    double arr_sig50[sumstep];
    double arr_sig150[sumstep];
    double arr_bgreject[sumstep];

    for (int i = 0; i < sumstep; i++)
    {
        double sig1eff = (h_Sig1_nJet_cut[i]->Integral() / (h_Sig1_nJet[i]->Integral()));
        double sig50eff = (h_Sig50_nJet_cut[i]->Integral() / (h_Sig50_nJet[i]->Integral()));
        double sig150eff = (h_Sig150_nJet_cut[i]->Integral() / (h_Sig150_nJet[i]->Integral()));
        double nbg = h_Bgall[i]->Integral();
        double bgeff = (h_Bg_cut[i]->Integral()) / (nbg);
        arr_sig1[i] = sig1eff;
        arr_sig50[i] = sig50eff;
        arr_sig150[i] = sig150eff;
        arr_bgreject[i] = 1 - bgeff;
        cout << "i" << i << endl;
        //cout << "sig1eff = " << sig1eff << "  arr_bgreject = " << arr_bgreject[i] << endl;
        cout << "sig1eff = " << sig1eff << endl;
        cout << "nbg" << nbg << endl;
        h_punzisig1->SetBinContent(i + 1, punzi(sig1eff, nbg));
        h_punzisig50->SetBinContent(i + 1, punzi(sig50eff, nbg));
        h_punzisig150->SetBinContent(i + 1, punzi(sig150eff, nbg));

        //------------------
        // ROC curve
        //------------------
        // h_ROCsig50->SetBinContent(i + 1, sig50eff, i + 1, 1 - bgeff);
        //cout << "punzi = " << punzi(sig50eff, nbg) << endl;
    }

    /*
    for (int i = 0; i < sumstep; i++)
    {
        double Total_Sig1_event = (h_Sig1_nJet[i]->Integral());
        int nbinx = h_Sig1_nJet[i]->GetNbinsX();
        //cout << "nbinx = " << nbinx << endl;
        double Sig1_passcut_event = 0.;
        for (int j = 2; j < nbinx; j++)
        {
            //cout << "i = " << j << endl;
            double Sig_value = h_Sig1_nJet[i]->GetBinContent(j + 1);
            Sig1_passcut_event = Sig1_passcut_event + Sig_value;
        }
        cout << "i = " << i << endl;
        cout << "sig1eff = " << (double)((Sig1_passcut_event) / (Total_Sig1_event)) << endl;
        arr_sig1[i]=(double)((Sig1_passcut_event) / (Total_Sig1_event));

    }
    */
    TGraph *ROC_MX1 = new TGraph(sumstep, arr_sig1, arr_bgreject);
    TGraph *ROC_MX50 = new TGraph(sumstep, arr_sig50, arr_bgreject);
    TGraph *ROC_MX150 = new TGraph(sumstep, arr_sig150, arr_bgreject);

    h_punzisig1->SetLineWidth(2);
    h_punzisig50->SetLineWidth(2);
    h_punzisig150->SetLineWidth(2);
    h_punzisig1->SetLineColor(kRed);
    h_punzisig50->SetLineColor(kGray + 2);
    h_punzisig150->SetLineColor(kBlue);

    h_Sig1_alpha->SetLineWidth(2);
    h_Sig50_alpha->SetLineWidth(2);
    h_Sig150_alpha->SetLineWidth(2);
    h_Sig1_alpha->SetLineColor(kRed);
    h_Sig50_alpha->SetLineColor(kBlack);
    h_Sig150_alpha->SetLineColor(kBlue);

    h_bgall_alpha->SetLineWidth(2);
    h_bgall_alpha->SetLineColor(kGreen + 3);
    h_bgall_alpha->SetFillColor(kGreen + 3);
    h_bgall_alpha->SetFillStyle(3001);

    int W = 800;
    int H = 600;

    int H_ref = 600;
    int W_ref = 800;

    float T = 0.08 * H_ref;
    float B = 0.12 * H_ref;
    float L = 0.12 * W_ref;
    float R = 0.04 * W_ref;

    auto c1 = new TCanvas("c1", "c1", 50, 50, W, H);
    c1->SetFillColor(0);
    c1->SetBorderMode(0);
    c1->SetFrameFillStyle(0);
    c1->SetFrameBorderMode(0);
    c1->SetLeftMargin(L / W);
    c1->SetRightMargin(R / W);
    c1->SetTopMargin(T / H);
    c1->SetBottomMargin(B / H);
    c1->SetTickx(0);
    c1->SetTicky(0);

    h_punzisig50->GetYaxis()->SetNdivisions(6, 5, 0);
    h_punzisig50->GetYaxis()->SetTitleOffset(1.5);
    h_punzisig50->GetYaxis()->SetTitle("punzi significance");
    h_punzisig50->GetYaxis()->SetTitleSize(0.04);
    h_punzisig50->GetYaxis()->SetLabelSize(0.04);
    h_punzisig50->GetXaxis()->SetNdivisions(6, 5, 0);
    h_punzisig50->GetXaxis()->SetTitle("nStep");
    h_punzisig50->GetXaxis()->SetTitleSize(0.04);
    h_punzisig50->GetXaxis()->SetLabelSize(0.04);

    h_punzisig1->GetYaxis()->SetNdivisions(6, 5, 0);
    h_punzisig1->GetYaxis()->SetTitleOffset(1.7);
    h_punzisig1->GetYaxis()->SetTitle("punzi significance");
    h_punzisig1->GetYaxis()->SetTitleSize(0.04);
    h_punzisig1->GetYaxis()->SetLabelSize(0.04);
    h_punzisig1->GetXaxis()->SetNdivisions(6, 5, 0);
    h_punzisig1->GetXaxis()->SetTitle("nStep");
    h_punzisig1->GetXaxis()->SetTitleSize(0.04);
    h_punzisig1->GetXaxis()->SetLabelSize(0.04);

    h_Sig50_alpha->GetYaxis()->SetNdivisions(6, 5, 0);
    h_Sig50_alpha->GetYaxis()->SetTitleOffset(1.5);
    h_Sig50_alpha->GetYaxis()->SetTitle("nJet/Normalized");
    h_Sig50_alpha->GetYaxis()->SetTitleSize(0.04);
    h_Sig50_alpha->GetYaxis()->SetLabelSize(0.04);
    h_Sig50_alpha->GetXaxis()->SetNdivisions(6, 5, 0);
    h_Sig50_alpha->GetXaxis()->SetTitle("#alpha");
    h_Sig50_alpha->GetXaxis()->SetTitleSize(0.04);
    h_Sig50_alpha->GetXaxis()->SetLabelSize(0.04);

    // h_punzisig50->Draw();
    h_punzisig50->Draw("same");
    h_punzisig150->Draw("same");
    h_punzisig1->Draw("same");
    // h_punzisig150->Draw("same");
    // h_Sig50_alpha->DrawNormalized("h ");
    // h_bgall_alpha->DrawNormalized("h same");
    // h_Sig1_alpha->DrawNormalized("h same");
    // h_Sig150_alpha->DrawNormalized("h same");
    ROC_MX1->SetLineColor(kRed);
    ROC_MX1->SetMarkerColor(kRed);
    ROC_MX1->SetMarkerStyle(21);
    ROC_MX50->SetLineColor(kGray + 2);
    ROC_MX50->SetMarkerColor(kGray + 2);
    ROC_MX150->SetLineColor(kBlue);
    ROC_MX50->SetMarkerColor(kBlue);
    ROC_MX1->SetLineWidth(2);
    ROC_MX50->SetLineWidth(2);
    ROC_MX150->SetLineWidth(2);

   
    ROC_MX50->GetYaxis()->SetTitle("bkg rejection");
    ROC_MX50->GetXaxis()->SetTitle("sigeff");

    /*
    TAxis *axis = ROC_MX50->GetXaxis();
    axis->SetLimits(0.,1.);       

    ROC_MX50->Draw("AP same");
    ROC_MX1->Draw("P same");
    
    ROC_MX150->Draw("P same");

    gStyle->SetOptStat(0);
    TLegend *l0 = new TLegend(0.4, 0.6, 0.90, 0.80);
    l0->SetBorderSize(0);
    l0->SetTextSize(0.03);
    l0->AddEntry(ROC_MX1, "m_{#chi_{2}} = 1 GeV, ctau = 1 mm", "P");
    l0->AddEntry(ROC_MX50, "m_{#chi_{2}} = 50 GeV, ctau = 10 mm", "P");
    l0->AddEntry(ROC_MX150, "m_{#chi_{2}} = 150 GeV, ctau = 1 mm", "P");
    // l0->AddEntry(h_bgall_alpha, "2016 MC background", "l");
    l0->Draw();
    */
    
    TLegend *l0 = new TLegend(0.4, 0.6, 0.90, 0.80);
    l0->SetBorderSize(0);
    l0->SetTextSize(0.03);
    l0->AddEntry(h_punzisig1, "m_{#chi_{2}} = 1 GeV, ctau = 1 mm", "l");
    l0->AddEntry(h_punzisig50, "m_{#chi_{2}} = 50 GeV, ctau = 10 mm", "l");
    l0->AddEntry(h_punzisig150, "m_{#chi_{2}} = 150 GeV, ctau = 1 mm", "l");
    // l0->AddEntry(h_bgall_alpha, "2016 MC background", "l");
    l0->Draw();

    int iPeriod = 0;
    int iPos = 33;
    CMS_lumi(c1, iPeriod, iPos);
    c1->Update();
    
    // c1->SaveAs("ee_Mx21_alpha_punzi.pdf");
}