#include <vector>
#include <iostream>
#include <fstream>
#include <queue>
#include <algorithm>
#include <TH1D.h>
#include <TFile.h>
#include "untuplizer.h"
#include <TClonesArray.h>
#include <TLorentzVector.h>
#include <TAxis.h>
#include <math.h>
#include <string>
using namespace std;

//-------------------------------
// Useful function
//-------------------------------
void efferr(float nsig, float ntotal, float factor = 1)
{
    float eff = nsig / ntotal;
    float err = sqrt((1 - eff) * eff / ntotal);
    cout << "efficiency = " << eff * factor << " +- " << err * factor << endl;
}

bool pt_greater(const TLorentzVector a, const TLorentzVector b)
{
    double A = a.Pt();
    double B = b.Pt();
    return (A > B);
}

double median_value(vector<double> tmpvector)
{
    float med_value = 0.0;
    sort(tmpvector.begin(), tmpvector.end());

    if (tmpvector.size() % 2 == 0) // even
    {
        med_value = (tmpvector[tmpvector.size() / 2 - 1] + tmpvector[tmpvector.size() / 2]) / 2;
    }
    else // odd
    {
        med_value = tmpvector[tmpvector.size() / 2];
    }
    return (med_value);
}

double mean_value(const vector<double> &ttmpvector)
{
    float sum_value = 0.0;
    for (float x : ttmpvector)
    {
        sum_value += x;
    }
    return (sum_value / ttmpvector.size());
}

float cal_dphi(float phi1, float phi2)
{
    float dphi = phi1 - phi2;
    while (dphi >= TMath::Pi())
        dphi -= 2 * TMath::Pi();
    while (dphi < -TMath::Pi())
        dphi += 2 * TMath::Pi();
    return TMath::Abs(dphi);
}

int countLinesInFile(string filename)
{
    ifstream file(filename);
    string line;
    int lines = 0;
    while (getline(file, line))
        ++lines;
    return lines;
}

void printProgressBar(int percent)
{
    cout << "\r" << setw(3) << percent << "% ";
    int numBars = percent / 2;
    for (int i = 0; i < numBars; ++i)
        cout << "|";
    cout << flush;
}
/// afs/cern.ch/user/k/kuanyu/test/tmp150.txt
void xAna_ztoee_2016(string inputtxtFilename = "/afs/cern.ch/user/k/kuanyu/test/tmp150.txt", string outputfile = "./output/ee_Mx2_150_old_remove_0alpha.root")
{
    // string inputFile(inputtxtFilename.data());
    cout << "inputtxtFilename = " << inputtxtFilename << endl;
    ifstream flist(inputtxtFilename.data());
    string inputFile;

    fstream fin(inputtxtFilename, ios::in);
    if (!fin)
    {
        std::cout << "Failed to open file.\n";
    }

    //------------------
    // Create histrogram
    //------------------
    TH1D *h_genee_event = new TH1D("h_genee_event", "gen events", 5, 0, 5);
    h_genee_event->Sumw2();

    TH1D *h_recoee_event = new TH1D("h_recoee_event", "reco events", 5, 0, 5);
    h_recoee_event->Sumw2();

    TH1D *h_totevent = new TH1D("h_totevent", "total events", 5, 0, 5);
    h_totevent->Sumw2();

    TH1F *h_HT_eventCout = new TH1F("h_HT_eventCout", "", 10, 0, 10);
    h_HT_eventCout->SetYTitle("N event");
    h_HT_eventCout->Sumw2();

    TH1F *h_ee_npass = new TH1F("h_ee_npass", "", 10, 0, 10);
    h_ee_npass->SetXTitle("npass");
    h_ee_npass->Sumw2();

    TH1D *gen_chi2numb = new TH1D("gen_chi2numb", "Chi2", 5, 0, 5);
    TH1D *gen_dquarknumb = new TH1D("gen_dquarknumb", "d quark", 10, 0, 10);
    TH1D *gen_eenumber = new TH1D("gen_eenumber", "e", 10, 0, 10);
    TH1D *match_dquarknumb = new TH1D("match_dquarknumb", "d quark", 10, 0, 10);

    TH1D *h_ele_n = new TH1D("h_ele_n", "Nr of electron", 10, 0, 10);
    h_ele_n->GetXaxis()->SetTitle("Number of electron");
    h_ele_n->GetYaxis()->SetTitle("Number of Events");
    h_ele_n->Sumw2();

    TH1D *h_tau_n = new TH1D("h_tau_n", "Nr of tau", 10, 0, 10);
    h_tau_n->GetXaxis()->SetTitle("Number of tau");
    h_tau_n->GetYaxis()->SetTitle("Number of Events");
    h_tau_n->Sumw2();

    TH1D *h_mu_n = new TH1D("h_mu_n", "Nr of Muon", 10, 0, 10);
    h_mu_n->GetXaxis()->SetTitle("Number of muon");
    h_mu_n->GetYaxis()->SetTitle("Number of Events");
    h_mu_n->Sumw2();

    TH1D *Z_eemass = new TH1D("Z_eemass", "Z->ee", 150, 0, 150);
    Z_eemass->GetXaxis()->SetTitle("Z mass");
    Z_eemass->GetYaxis()->SetTitle("Number of Events");
    Z_eemass->Sumw2();

    TH1D *dilepton_pT = new TH1D("dilepton_pT", "dilepton_pT", 100, 0, 1000);
    dilepton_pT->GetXaxis()->SetTitle("dilepton pT");
    dilepton_pT->GetYaxis()->SetTitle("Number of Events");
    dilepton_pT->Sumw2();

    TH1D *dilepton_pT_after_ledptcut = new TH1D("dilepton_pT_after_ledptcut", "dilepton_pT_after_ledptcut", 100, 0, 1000);
    dilepton_pT_after_ledptcut->GetXaxis()->SetTitle("dilepton pT");
    dilepton_pT_after_ledptcut->GetYaxis()->SetTitle("Number of Events");
    dilepton_pT_after_ledptcut->Sumw2();

    TH1D *dilepton_pT_after_dilepmasscut = new TH1D("dilepton_pT_after_dilepmasscut", "dilepton_pT_after_dilepmasscut", 100, 0, 1000);
    dilepton_pT_after_dilepmasscut->GetXaxis()->SetTitle("dilepton pT");
    dilepton_pT_after_dilepmasscut->GetYaxis()->SetTitle("Number of Events");
    dilepton_pT_after_dilepmasscut->Sumw2();

    TH1D *dilepton_pT_after_extralepcut = new TH1D("dilepton_pT_after_extralepcut", "dilepton_pT_after_extralepcut", 100, 0, 1000);
    dilepton_pT_after_extralepcut->GetXaxis()->SetTitle("dilepton pT");
    dilepton_pT_after_extralepcut->GetYaxis()->SetTitle("Number of Events");
    dilepton_pT_after_extralepcut->Sumw2();

    TH1D *dilepton_pT_after_vetotaucut = new TH1D("dilepton_pT_after_vetotaucut", "dilepton_pT_after_extralepcut", 100, 0, 1000);
    dilepton_pT_after_vetotaucut->GetXaxis()->SetTitle("dilepton pT");
    dilepton_pT_after_vetotaucut->GetYaxis()->SetTitle("Number of Events");
    dilepton_pT_after_vetotaucut->Sumw2();

    TH1D *dilepton_pT_after_nJetcut = new TH1D("dilepton_pT_after_nJetcut", "dilepton_pT_after_nJetcut", 100, 0, 1000);
    dilepton_pT_after_nJetcut->GetXaxis()->SetTitle("dilepton pT");
    dilepton_pT_after_nJetcut->GetYaxis()->SetTitle("Number of Events");
    dilepton_pT_after_nJetcut->Sumw2();

    TH1D *h_njet = new TH1D("h_njet", "Nr of jets pass jet preselection", 15, 0, 15);
    h_njet->GetXaxis()->SetTitle("Number of Jets");
    h_njet->GetYaxis()->SetTitle("Number of Events");
    h_njet->Sumw2();

    TH1D *h_njet_pass_trks = new TH1D("h_njet_pass_trks", "Nr of jets pass jet preselection + track selection", 15, 0, 15);
    h_njet_pass_trks->GetXaxis()->SetTitle("Number of Jets");
    h_njet_pass_trks->GetYaxis()->SetTitle("Number of Events");
    h_njet_pass_trks->Sumw2();

    TH1D *h_jet_csv = new TH1D("h_jet_csv", "", 120, 11, 1.);
    h_jet_csv->GetXaxis()->SetTitle("JetCSV");
    h_jet_csv->GetYaxis()->SetTitle("nJet");
    h_jet_csv->Sumw2();

    TH1D *h_jet_rank = new TH1D("h_jet_rank", "Nr of rank Matched jets", 15, 0, 15);
    h_jet_rank->GetXaxis()->SetTitle("Jet_rank");
    h_jet_rank->GetYaxis()->SetTitle("Number of Events");
    h_jet_rank->Sumw2();

    TH1D *h_trk_npass = new TH1D("h_trk_npass", "", 10, 0, 10);
    h_trk_npass->Sumw2();

    TH1D *h_trkpt = new TH1D("h_trkpt", "", 1000, 0, 1000);
    h_trkpt->Sumw2();

    //----------------------
    // Volid Tree variable
    //----------------------
    Int_t I_event;
    Int_t I_weight;
    ULong64_t I_eventID;
    Int_t I_tot_Recoevt;
    Int_t I_tot_gencoevt;
    Int_t I_Sumeventweight;
    Float_t f_HT;
    Float_t f_Met;
    Double_t d_Met_leptons_ratio;
    Float_t f_dileptonmass;
    Float_t f_dileptonPT;

    vector<float> v_MetdeltaPhi;
    //-----------------
    // Jets variable
    //-----------------
    Int_t I_nthinJet;
    vector<float> f_thinJetPT;
    vector<float> f_thinJetEta;
    vector<float> f_thinjetCSVv2;
    Float_t f_leadJeteta;
    Float_t f_leadJetpt;
    Float_t f_leadJetCSVv2;
    Float_t f_minalphaJeteta;
    Float_t f_minalphaJetpt;
    Int_t I_nPassthinJets;
    Double_t v_nPassthinJet_alphamin;
    vector<int> v_nTrk_cut3Dsig;
    vector<int> v_Jetpipeup;
    vector<float> v_nPassthinJetEta;
    vector<float> v_nPassthinJetPT;
    vector<float> v_nPassthinJetM;
    vector<float> v_nPassthinJetCSVv2;
    vector<float> v_nPassthinJetalpha;
    vector<float> v_nPassthinJetalpha2;
    vector<float> v_nPassthinJetalpha3;
    vector<float> v_nPassthinJetalpha4;
    vector<float> v_nPassthinJethadflavor;
    vector<float> v_nPassthinJetpartonflavor;
    vector<float> v_nPassthinJetledLepdr;
    vector<float> v_nPassthinJetsubLepdr;

    //-----------------
    // Tracks variable
    //-----------------
    vector<int> v_Trkindex;
    vector<int> v_nTrk;
    vector<float> v_Trk_dz;
    vector<float> v_Trk_dzerror;
    vector<float> v_Trk_dxy;
    vector<float> v_Trk_dxyerror;
    vector<float> v_TrkPT;
    vector<double> v_TrkIP3D;
    vector<float> v_TrkIP2DxTrkPT;
    vector<float> v_TrkEta;
    vector<float> v_Trkdr;
    vector<double> v_TrkChi3D_Paper;
    vector<double> v_TrkChi3D;
    vector<double> v_TrkChi2D;
    vector<double> v_TrkXYresolu;

    vector<double> v_chi2_P;

    vector<float> v_bTrkIP2D;
    vector<float> v_bTrkChi3D;
    vector<float> v_cTrkIP2D;
    vector<float> v_cTrkChi3D;
    vector<float> v_lTrkIP2D;
    vector<float> v_lTrkChi3D;

    TTree *T_tree = new TTree("T_tree", "Tree");
    T_tree->Branch("I_event", &I_event);
    T_tree->Branch("I_weight", &I_weight);
    T_tree->Branch("I_eventID", &I_eventID);
    T_tree->Branch("v_chi2_P", &v_chi2_P);
    T_tree->Branch("I_tot_gencoevt", &I_tot_gencoevt);
    T_tree->Branch("I_tot_Recoevt", &I_tot_Recoevt);
    T_tree->Branch("I_Sumeventweight", &I_Sumeventweight);
    T_tree->Branch("f_Met", &f_Met);
    T_tree->Branch("d_Met_leptons_ratio", &d_Met_leptons_ratio);
    T_tree->Branch("f_HT", &f_HT);
    T_tree->Branch("f_dileptonmass", &f_dileptonmass);
    T_tree->Branch("f_dileptonPT", &f_dileptonPT);
    T_tree->Branch("v_MetdeltaPhi", &v_MetdeltaPhi);
    T_tree->Branch("I_nthinJet", &I_nthinJet);
    T_tree->Branch("f_thinJetPT", &f_thinJetPT);
    T_tree->Branch("f_thinJetEta", &f_thinJetEta);
    T_tree->Branch("f_thinjetCSVv2", &f_thinjetCSVv2);
    T_tree->Branch("f_leadJetpt", &f_leadJetpt);
    T_tree->Branch("f_leadJeteta", &f_leadJeteta);
    T_tree->Branch("f_leadJetCSVv2", &f_leadJetCSVv2);
    T_tree->Branch("f_minalphaJetpt", &f_minalphaJetpt);
    T_tree->Branch("f_minalphaJeteta", &f_minalphaJeteta);
    T_tree->Branch("I_nPassthinJets", &I_nPassthinJets);
    T_tree->Branch("v_nTrk", &v_nTrk);
    T_tree->Branch("v_Trkindex", &v_Trkindex);
    T_tree->Branch("v_TrkPT", &v_TrkPT);
    T_tree->Branch("v_TrkIP2DxTrkPT", &v_TrkIP2DxTrkPT);
    T_tree->Branch("v_TrkEta", &v_TrkEta);
    T_tree->Branch("v_Trkdr", &v_Trkdr);
    T_tree->Branch("v_Trk_dz", &v_Trk_dz);
    T_tree->Branch("v_Trk_dzerror", &v_Trk_dzerror);
    T_tree->Branch("v_Trk_dxy", &v_Trk_dxy);
    T_tree->Branch("v_Trk_dxyerror", &v_Trk_dxyerror);
    T_tree->Branch("v_TrkIP3D", &v_TrkIP3D);
    T_tree->Branch("v_TrkChi2D", &v_TrkChi2D);
    T_tree->Branch("v_TrkXYresolu", &v_TrkXYresolu);
    T_tree->Branch("v_TrkChi3D", &v_TrkChi3D);
    T_tree->Branch("v_TrkChi3D_Paper", &v_TrkChi3D_Paper);
    T_tree->Branch("v_nTrk_cut3Dsig", &v_nTrk_cut3Dsig);
    T_tree->Branch("v_Jetpipeup", &v_Jetpipeup);
    T_tree->Branch("v_nPassthinJetPT", &v_nPassthinJetPT);
    T_tree->Branch("v_nPassthinJetEta", &v_nPassthinJetEta);
    T_tree->Branch("v_nPassthinJetM", &v_nPassthinJetM);
    T_tree->Branch("v_nPassthinJetCSVv2", &v_nPassthinJetCSVv2);
    T_tree->Branch("v_nPassthinJetalpha", &v_nPassthinJetalpha);
    T_tree->Branch("v_nPassthinJetalpha2", &v_nPassthinJetalpha2);
    T_tree->Branch("v_nPassthinJetalpha3", &v_nPassthinJetalpha3);
    T_tree->Branch("v_nPassthinJetalpha4", &v_nPassthinJetalpha4);
    T_tree->Branch("v_nPassthinJethadflavor", &v_nPassthinJethadflavor);
    T_tree->Branch("v_nPassthinJetpartonflavor", &v_nPassthinJetpartonflavor);
    T_tree->Branch("v_nPassthinJetledLepdr", &v_nPassthinJetledLepdr);
    T_tree->Branch("v_nPassthinJetsubLepdr", &v_nPassthinJetsubLepdr);
    T_tree->Branch("v_nPassthinJet_alphamin", &v_nPassthinJet_alphamin);
    T_tree->Branch("v_bTrkIP2D", &v_bTrkIP2D);
    T_tree->Branch("v_bTrkChi3D", &v_bTrkChi3D);
    T_tree->Branch("v_cTrkIP2D", &v_cTrkIP2D);
    T_tree->Branch("v_cTrkChi3D", &v_cTrkChi3D);
    T_tree->Branch("v_lTrkIP2D", &v_lTrkIP2D);
    T_tree->Branch("v_lTrkChi3D", &v_lTrkChi3D);

    int totalLines = countLinesInFile(inputtxtFilename);
    int linesProcessed = 0;

    while (getline(flist, inputFile))
    {

        ++linesProcessed;
        int percent = (100 * linesProcessed) / totalLines;
        printProgressBar(percent);

        bool BKG2016MC = true;
        //  Identify input file type
        if (((inputFile).find("DYJetsToLL") != std::string::npos) ||
            ((inputFile).find("ZZTo") != std::string::npos) ||
            ((inputFile).find("WWTo") != std::string::npos) ||
            ((inputFile).find("WZTo") != std::string::npos) ||
            ((inputFile).find("top_5f") != std::string::npos) ||
            ((inputFile).find("TTTo") != std::string::npos) ||
            ((inputFile).find("TTWJetsTo") != std::string::npos) ||
            ((inputFile).find("TTZTo") != std::string::npos) ||
            ((inputFile).find("WWZ_") != std::string::npos) ||
            ((inputFile).find("WZZ_") != std::string::npos) ||
            ((inputFile).find("ZZZ_") != std::string::npos))
        {
            BKG2016MC = true;
        }
        TreeReader data(inputFile.data());
        for (Long64_t jEntry = 0; jEntry < data.GetEntriesFast(); jEntry++)
        {
            //-------------------
            //  void some variable
            //-------------------
            Int_t neeRecoTotal = 0;
            Int_t neeGenevt = 0;
            Int_t SumeventWeight = 0;
            //  clear Tree vector for each event
            v_chi2_P.clear();
            f_thinJetPT.clear();
            f_thinJetEta.clear();
            f_thinjetCSVv2.clear();
            v_TrkChi3D.clear();
            v_TrkChi2D.clear();
            v_TrkXYresolu.clear();
            v_TrkChi3D_Paper.clear();
            v_TrkIP3D.clear();
            v_Trkindex.clear();
            v_nTrk.clear();
            v_nTrk_cut3Dsig.clear();
            v_TrkPT.clear();
            v_TrkIP2DxTrkPT.clear();
            v_TrkEta.clear();
            v_Trkdr.clear();
            v_Trk_dz.clear();
            v_Trk_dzerror.clear();
            v_Trk_dxy.clear();
            v_Trk_dxyerror.clear();
            v_MetdeltaPhi.clear();
            v_bTrkIP2D.clear();
            v_bTrkChi3D.clear();
            v_cTrkIP2D.clear();
            v_cTrkChi3D.clear();
            v_lTrkIP2D.clear();
            v_lTrkChi3D.clear();
            v_Jetpipeup.clear();
            v_nPassthinJetPT.clear();
            v_nPassthinJetEta.clear();
            v_nPassthinJetM.clear();
            v_nPassthinJetCSVv2.clear();
            v_nPassthinJetalpha.clear();
            v_nPassthinJetalpha2.clear();
            v_nPassthinJetalpha3.clear();
            v_nPassthinJetalpha4.clear();
            v_nPassthinJethadflavor.clear();
            v_nPassthinJetpartonflavor.clear();
            v_nPassthinJetledLepdr.clear();
            v_nPassthinJetsubLepdr.clear();
            data.GetEntry(jEntry);
            /*For Mc weight*/
            Float_t mcWeight = data.GetFloat("mcWeight");
            Double_t eventWeight = mcWeight;
            if (eventWeight > 0)
            {
                eventWeight = 1;
            }
            else if (eventWeight < 0)
            {
                eventWeight = -1;
            }
            else
            {
                eventWeight = 1;
            }
            SumeventWeight += eventWeight;
            //-----------------------------------
            // For inclusive sample event counter
            //-----------------------------------
            Float_t HT = data.GetFloat("HT");
            if (HT < 70)
            {
                h_HT_eventCout->Fill(1, eventWeight);
            }
            else if (HT >= 70 && HT < 100)
            {
                h_HT_eventCout->Fill(2, eventWeight);
            }
            else if (HT >= 100 && HT < 200)
            {
                h_HT_eventCout->Fill(3, eventWeight);
            }
            else if (HT >= 200 && HT < 400)
            {
                h_HT_eventCout->Fill(4, eventWeight);
            }
            else if (HT >= 400 && HT < 600)
            {
                h_HT_eventCout->Fill(5, eventWeight);
            }
            else if (HT >= 600 && HT < 800)
            {
                h_HT_eventCout->Fill(6, eventWeight);
            }
            else if (HT >= 800 && HT < 1200)
            {
                h_HT_eventCout->Fill(7, eventWeight);
            }
            else if (HT >= 1200 && HT < 2500)
            {
                h_HT_eventCout->Fill(8, eventWeight);
            }
            else if (HT >= 2500)
            {
                h_HT_eventCout->Fill(9, eventWeight);
            }
            //---------------------------
            // Store Total event number
            //---------------------------
            h_totevent->Fill(1.0, eventWeight);

            bool matchee = false;
            vector<TLorentzVector> myEles;
            vector<TLorentzVector> dquark;
            vector<TLorentzVector> chi2s;
            dquark.clear();
            myEles.clear();
            chi2s.clear();
            // 0. check the generator-level information and make sure there is a Z->e+e-
            Int_t nGenPar = data.GetInt("nGenPar");
            TClonesArray *genParP4 = (TClonesArray *)data.GetPtrTObject("genParP4");
            Int_t *genParId = data.GetPtrInt("genParId");
            Int_t *genParSt = data.GetPtrInt("genParSt");
            Int_t *genMomParId = data.GetPtrInt("genMomParId");
            for (int ig = 0; ig < nGenPar; ig++)
            {
                TLorentzVector *thisGen = (TLorentzVector *)genParP4->At(ig);
                int pid = genParId[ig];
                int mompid = genMomParId[ig];
                int status = genParSt[ig];
                if (abs(pid) == 11 && mompid == 23)
                {
                    matchee = true;
                    myEles.push_back(*thisGen);
                }
                // chi2Id 18
                if (abs(pid) == 1 && abs(mompid) == 18)
                {
                    dquark.push_back(*thisGen);
                }
                if (abs(pid) == 18)
                {
                    chi2s.push_back(*thisGen);
                    v_chi2_P.push_back(thisGen->P());
                }
            }
            gen_dquarknumb->Fill(dquark.size(), eventWeight);
            gen_chi2numb->Fill(chi2s.size(), eventWeight);
            gen_eenumber->Fill(myEles.size(), eventWeight);

            if (BKG2016MC)
            {
                matchee = true;
            }
            if (matchee)
            {
                neeGenevt++;

                // 1. electron
                int nEle = data.GetInt("nEle");
                TClonesArray *eleP4 = (TClonesArray *)data.GetPtrTObject("eleP4");
                vector<bool> &eleIsPassLoose = *((vector<bool> *)data.GetPtr("eleIsPassLoose"));
                vector<bool> &eleIsPassMedium = *((vector<bool> *)data.GetPtr("eleIsPassMedium"));
                vector<bool> &eleIsPassVeto = *((vector<bool> *)data.GetPtr("eleIsPassVeto"));
                float *eleChHadIso = data.GetPtrFloat("eleChHadIso");
                float *eleNeHadIso = data.GetPtrFloat("eleNeHadIso");
                float *eleGamIso = data.GetPtrFloat("eleGamIso");
                float *elePUPt = data.GetPtrFloat("elePUPt");
                vector<TLorentzVector> goodElectrons;
                goodElectrons.clear();
                vector<int> vetoee;
                vetoee.clear();
                for (int ie = 0; ie < nEle; ie++)
                {
                    TLorentzVector *myEle = (TLorentzVector *)eleP4->At(ie);
                    double elepT = myEle->Pt();
                    if (myEle->Pt() <= 20)
                        continue;
                    if (fabs(myEle->Eta()) >= 2.4)
                        continue;
                    /*
                    if (eleIsPassVeto[ie])
                    {
                        vetoee.push_back(ie);
                    }
                    */
                    if (!eleIsPassMedium[ie])
                        continue;
                    /*
                    vector<int>::iterator p = find(vetoee.begin(), vetoee.end(), ie);
                    if (p != vetoee.end())
                    {
                        vetoee.erase(p);
                    }
                    */
                    goodElectrons.push_back(*myEle);
                } // End of loop nEle event
                /*if (goodElectrons.size() >= 2)
                {
                    if (vetoee.size() != 0)
                    {
                        continue;
                    }
                }
                */
                h_ele_n->Fill(goodElectrons.size(), eventWeight);
                // Sort electron by PT
                sort(goodElectrons.begin(), goodElectrons.end(), pt_greater);

                // 2. Muon
                int nMu = data.GetInt("nMu");
                TClonesArray *muP4 = (TClonesArray *)data.GetPtrTObject("muP4");
                vector<bool> &isTightMuon = *((vector<bool> *)data.GetPtr("isTightMuon"));
                vector<bool> &isSoftMuon = *((vector<bool> *)data.GetPtr("isSoftMuon"));
                float *muChHadIso = data.GetPtrFloat("muChHadIso");
                float *muNeHadIso = data.GetPtrFloat("muNeHadIso");
                float *muGamIso = data.GetPtrFloat("muGamIso");
                float *muPUPt = data.GetPtrFloat("muPUPt");
                int *muTrkLayers = data.GetPtrInt("muTrkLayers");
                vector<TLorentzVector> goodmuons;
                goodmuons.clear();
                for (int imu = 0; imu < nMu; imu++)
                {
                    TLorentzVector *myMu = (TLorentzVector *)muP4->At(imu);
                    double mupT = myMu->Pt();
                    if (myMu->Pt() <= 20)
                        continue;
                    if (fabs(myMu->Eta()) >= 2.4)
                        continue;
                    double myMuIso = (muChHadIso[imu] + max(0., muNeHadIso[imu] + muGamIso[imu] - 0.5 * muPUPt[imu])) / mupT;
                    if (myMuIso > 0.15) //~~~!!!!
                        continue;
                    if (muTrkLayers[imu] < 5)
                        continue;
                    if (!isSoftMuon[imu])
                        continue;
                    goodmuons.push_back(*myMu);
                } // End of Muon loop
                h_mu_n->Fill(goodmuons.size(), eventWeight);

                bool recoeeEvent = false;
                bool recouuEvent = false;
                if (goodmuons.size() == goodElectrons.size())
                {
                    continue;
                }
                if (goodElectrons.size() >= 2 && goodmuons.size() < 2)
                {
                    recoeeEvent = true;
                }
                if (goodmuons.size() >= 2 && goodElectrons.size() < 2)
                {
                    recouuEvent = true;
                }

                if (recoeeEvent)
                {
                    h_recoee_event->Fill(1, eventWeight);
                    h_ee_npass->Fill(1, eventWeight);
                    neeRecoTotal++;
                    // cout<<"neeRecoTotal = "<<neeRecoTotal<<endl;
                    //  3. has a good vertex
                    int nVtx = data.GetInt("nVtx");
                    if (nVtx < 1)
                        continue;
                    h_ee_npass->Fill(2, eventWeight);
                    // 4. veto tau
                    int nTau = data.GetInt("HPSTau_n");
                    TClonesArray *tauP4 = (TClonesArray *)data.GetPtrTObject("HPSTau_4Momentum");
                    vector<bool> &disc_decayModeFinding = *((vector<bool> *)data.GetPtr("disc_decayModeFinding")); // DecayModeFinding metho?
                    vector<bool> &disc_decayModeFindingNewDMs = *((vector<bool> *)data.GetPtr("disc_decayModeFindingNewDMs"));
                    vector<bool> &disc_byVVTightIsolationMVA3newDMwLT = *((vector<bool> *)data.GetPtr("disc_byVVTightIsolationMVA3newDMwLT"));
                    vector<bool> &disc_byVTightIsolationMVA3newDMwLT = *((vector<bool> *)data.GetPtr("disc_byVTightIsolationMVA3newDMwLT"));
                    vector<bool> &disc_byTightIsolationMVA3newDMwLT = *((vector<bool> *)data.GetPtr("disc_byTightIsolationMVA3newDMwLT"));
                    vector<TLorentzVector> goodtau;
                    goodtau.clear();
                    for (int it = 0; it < nTau; it++)
                    {
                        TLorentzVector *myTau = (TLorentzVector *)tauP4->At(it);
                        if (myTau->Pt() <= 20)
                            continue;
                        if (fabs(myTau->Eta()) >= 2.5)
                            continue;
                        if (!disc_decayModeFindingNewDMs[it])
                            continue;
                        if (!disc_byVTightIsolationMVA3newDMwLT[it])
                            continue;
                        goodtau.push_back(*myTau);
                    } // End of tau loop
                    h_tau_n->Fill(goodtau.size(), eventWeight);
                    // 5. For Met
                    Float_t met = data.GetFloat("pfMetCorrPt");
                    Float_t metphi = data.GetFloat("pfMetCorrPhi");
                    // TLorentzVector *thisJet = (TLorentzVector *)thinjetP4->At(j);
                    // float Thinjeteta = thisJet->Eta();
                    // float Thinjetphi = thisJet->Phi();
                    // float deta = Thinjeteta - Tracketa;
                    // float dphi = Thinjetphi - Trackphi;
                    for (auto i : goodElectrons)
                    {
                        float LepPhi = i.Phi();
                        v_MetdeltaPhi.push_back(cal_dphi(metphi, LepPhi));
                        // cout << cal_dphi(metphi, LepPhi) << endl;
                    }
                    // 6. Z boson
                    float PDGZmass = 91.1876;
                    float dilepPt = (goodElectrons[0] + goodElectrons[1]).Pt();
                    dilepton_pT->Fill(dilepPt, eventWeight);
                    d_Met_leptons_ratio = (abs(met - dilepPt) / dilepPt);
                    if (goodElectrons[0].Pt() < 25 && goodElectrons[1].Pt() < 20)
                    {
                        continue;
                    }
                    dilepton_pT_after_ledptcut->Fill(dilepPt, eventWeight);
                    h_ee_npass->Fill(3, eventWeight);
                    TLorentzVector Z_boson_ee;
                    Z_boson_ee = goodElectrons[0] + goodElectrons[1];
                    float deltaMass = abs(PDGZmass - Z_boson_ee.M());
                    if (deltaMass > 15)
                    {
                        continue;
                    }
                    dilepton_pT_after_dilepmasscut->Fill(dilepPt, eventWeight);
                    h_ee_npass->Fill(4, eventWeight);
                    //----------------------
                    // To reduce diboson case
                    //----------------------
                    if (goodElectrons.size() > 2 || goodmuons.size() > 0)
                        continue;
                    dilepton_pT_after_extralepcut->Fill(dilepPt, eventWeight);
                    h_ee_npass->Fill(5, eventWeight);

                    //-----------------
                    // Remove extra Tau
                    //-----------------
                    bool tauee = false;
                    if (goodtau.size() > 0)
                    {
                        for (int i = 0; i < goodtau.size(); i++)
                        {
                            float thisdr = goodtau[i].DeltaR(goodElectrons[0]);
                            float thatdr = goodtau[i].DeltaR(goodElectrons[1]);
                            // h_tau_dr->Fill(goodtau[i].DeltaR(goodElectrons[j]), eventWeight);
                            if (thisdr > 0.4 && thatdr > 0.4)
                            {
                                tauee = true;
                                break;
                            }
                        } // End of veto tau loop
                    }
                    if (tauee)
                        continue;
                    dilepton_pT_after_vetotaucut->Fill(dilepPt, eventWeight);
                    h_ee_npass->Fill(6, eventWeight);
                    // 7. Thin Jet
                    int nTHINJets = data.GetInt("THINnJet");
                    TClonesArray *thinjetP4 = (TClonesArray *)data.GetPtrTObject("THINjetP4");
                    Int_t *THINjetHadronFlavor = data.GetPtrInt("THINjetHadronFlavor");
                    Int_t *THINjetPartonFlavor = data.GetPtrInt("THINjetPartonFlavor");

                    // Int_t *THINjetNTracks = data.GetPtrInt("THINjetNTracks");
                    float *thinJetCSV = data.GetPtrFloat("THINjetCISVV2");
                    vector<int> indexForPassAK4;
                    indexForPassAK4.clear();
                    vector<TLorentzVector> goodJet;
                    goodJet.clear();
                    for (int i = 0; i < nTHINJets; i++)
                    {
                        TLorentzVector *thisJet = (TLorentzVector *)thinjetP4->At(i);
                        if (thisJet->Pt() <= 30)
                            continue;
                        if (fabs(thisJet->Eta()) >= 2.5)
                            continue;
                        float thisdr = thisJet->DeltaR(goodElectrons[0]);
                        float thatdr = thisJet->DeltaR(goodElectrons[1]);
                        if (thisdr < 0.4 || thatdr < 0.4)
                        {
                            continue;
                        }
                        //---------------------------------
                        // Match to down quark (for signal)
                        //---------------------------------
                        int match_q = 0;
                        if (!BKG2016MC)
                        {
                            bool jetdquark = false;
                            for (int j = 0; j < dquark.size(); j++)
                            {
                                if (thisJet->DeltaR(dquark[j]) < 0.4)
                                {
                                    match_q++;
                                    jetdquark = true;
                                }
                            }
                            if (!jetdquark)
                                continue;
                        }
                        /*Study piple up*/
                        bool jetnotpiple = false;
                        for (int ig = 0; ig < nGenPar; ig++)
                        {
                            TLorentzVector *thisGen = (TLorentzVector *)genParP4->At(ig);
                            int pid = genParId[ig];
                            int mompid = genMomParId[ig];
                            if (thisJet->DeltaR(*thisGen) < 0.2)
                            {
                                jetnotpiple = true;
                                /*if (abs(pid) == 11 && mompid == 23)
                                {
                                    cout << "check for ele "<< endl;
                                    cout << "ele size = " << goodElectrons.size() << endl;
                                    cout << "this dr = " << thisJet->DeltaR(goodElectrons[0]) << endl;
                                    cout << "that dr = " << thisJet->DeltaR(goodElectrons[1]) << endl;
                                    cout << "dr = " << thisJet->DeltaR(*thisGen) << endl;
                                    cout << "pid = " << pid << endl;
                                    cout << "mompid = " << mompid << endl;
                                }*/
                                break;
                            }
                            /*else
                            {
                                continue;
                            }*/
                        }

                        v_Jetpipeup.push_back(jetnotpiple);
                        f_thinJetPT.push_back(thisJet->Pt());
                        f_thinJetEta.push_back(thisJet->Eta());
                        f_thinjetCSVv2.push_back(thinJetCSV[i]);
                        h_jet_rank->Fill(i, eventWeight);
                        goodJet.push_back(*thisJet);
                        indexForPassAK4.push_back(i);
                    } // End of nThinJet loop
                    // Sort goodJet by PT
                    sort(goodJet.begin(), goodJet.end(), pt_greater);
                    /*Number of jet select*/
                    if (indexForPassAK4.size() < 2)
                        // if (indexForPassAK4.size() == 0)
                        continue;
                    dilepton_pT_after_nJetcut->Fill(dilepPt, eventWeight);
                    h_ee_npass->Fill(7, eventWeight);
                    h_njet->Fill(indexForPassAK4.size(), eventWeight);
                    //---------------------------
                    // Study match Jet's tracks
                    //---------------------------
                    Int_t *nTHINjetNTracks = data.GetPtrInt("THINjetNTracks");
                    vector<float> *THINjetTrackImpdz = data.GetPtrVectorFloat("THINjetTrackImpdz", nTHINJets);
                    vector<float> *THINjetTrackImpdzError = data.GetPtrVectorFloat("THINjetTrackImpdzError", nTHINJets);
                    vector<float> *THINjetTrackImpdxy = data.GetPtrVectorFloat("THINjetTrackImpdxy", nTHINJets);
                    vector<float> *THINjetTrackImpdxyError = data.GetPtrVectorFloat("THINjetTrackImpdxyError", nTHINJets);
                    vector<float> *THINjetTrackPt = data.GetPtrVectorFloat("THINjetTrackPt", nTHINJets);
                    vector<float> *THINjetTrackPhi = data.GetPtrVectorFloat("THINjetTrackPhi", nTHINJets);
                    vector<float> *THINjetTrackEta = data.GetPtrVectorFloat("THINjetTrackEta", nTHINJets);
                    int Jetmultiplicity = 0;
                    vector<int> Jetpass_index;
                    vector<float> v_aph;
                    vector<int> v_aph_index;
                    vector<vector<int>> v_indexPassJetTrack;
                    v_indexPassJetTrack.clear();
                    Jetpass_index.clear();
                    v_aph.clear();
                    v_aph_index.clear();
                    // cout << "part 1 " << endl;
                    for (int i = 0; i < indexForPassAK4.size(); i++)
                    {
                        int jetpass_index = indexForPassAK4[i];

                        vector<int> Track_index;
                        Track_index.clear();
                        // cout << "Jet_n  = " << indexForPassAK4[i] << endl;
                        for (int j = 0; j < nTHINjetNTracks[jetpass_index]; j++)
                        {
                            h_trk_npass->Fill(1, eventWeight);
                            h_trkpt->Fill(THINjetTrackPt[jetpass_index][j], eventWeight);
                            // cout << "Track_index = " << j << endl;
                            if (THINjetTrackPt[jetpass_index][j] <= 1.0)
                            {
                                continue;
                            }
                            h_trk_npass->Fill(2, eventWeight);
                            if (THINjetTrackImpdzError[jetpass_index][j] == 0 || THINjetTrackImpdxyError[jetpass_index][j] == 0 || isinf(THINjetTrackImpdzError[jetpass_index][j]) || isinf(THINjetTrackImpdxyError[jetpass_index][j]))
                            {
                                continue;
                            }
                            h_trk_npass->Fill(3, eventWeight);
                            Track_index.push_back(j);
                            // cout << "Pass Track_index = " << j << "\n"
                        } // End of Track loop
                        v_indexPassJetTrack.push_back(Track_index);
                    } // End Match Thin Jet index loop
                    if (indexForPassAK4.size() != v_indexPassJetTrack.size())
                    {
                        cout << "bug" << endl;
                    }
                    if (indexForPassAK4.size() < 2)
                    {
                        cout << "indexForPassAK4.size() = " << indexForPassAK4.size() << endl;
                    }

                    for (int i = 0; i < indexForPassAK4.size(); i++)
                    {
                        int correctjet_index = indexForPassAK4[i];
                        // cout<<"i = " << i << endl;
                        // cout<<"correctjet_index = " << indexForPassAK4[i] << endl;
                        //  nTHINjetNTracks[indexForPassAK4[i]]
                        //  cout << "Track_index = " << correcttrack_index << endl;
                        float SumOfTrackPt = 0;
                        float SumofTrackPT_cut = 0;
                        float SumOfTrackPt_cut2 = 0.;
                        float SumOfTrackPt_cut3 = 0.;
                        float SumOfTrackPt_cut4 = 0.;
                        float SumofTrackPT_Papercut = 0;
                        int Trackmultiplicity = 0;
                        int Trackmultiplicitycut = 0;

                        for (int j = 0; j < v_indexPassJetTrack[i].size(); j++)
                        {
                            int correcttrack_index = v_indexPassJetTrack[i][j];
                            // nTHINjetNTracks[indexForPassAK4[i]]
                            // cout << "Track_index = " << correcttrack_index << endl;
                            float dz = THINjetTrackImpdz[correctjet_index][correcttrack_index];
                            float dzerror = THINjetTrackImpdzError[correctjet_index][correcttrack_index];
                            float dxy = THINjetTrackImpdxy[correctjet_index][correcttrack_index];
                            float dxyerror = THINjetTrackImpdxyError[correctjet_index][correcttrack_index];
                            float dzsignificant = THINjetTrackImpdz[correctjet_index][correcttrack_index] / THINjetTrackImpdzError[correctjet_index][correcttrack_index];
                            float dxysignificant = THINjetTrackImpdxy[correctjet_index][correcttrack_index] / THINjetTrackImpdxyError[correctjet_index][correcttrack_index];
                            double chi3d = sqrt(dzsignificant * dzsignificant + dxysignificant * dxysignificant);
                            double chi2d = sqrt(dxysignificant * dxysignificant);
                            double IP2D = (THINjetTrackImpdxy[correctjet_index][correcttrack_index]);
                            double IP3D = sqrt(pow(THINjetTrackImpdz[correctjet_index][correcttrack_index], 2) + pow(THINjetTrackImpdxy[correctjet_index][correcttrack_index], 2));

                            //----------------------
                            //  Save Paper Variables
                            //----------------------
                            float dzpow = pow(THINjetTrackImpdz[correctjet_index][correcttrack_index] / 0.01, 2);
                            float chiP = sqrt(dzpow + dxysignificant * dxysignificant);
                            //----------------------
                            // Calculate DeltaR
                            //----------------------
                            float Tracketa = THINjetTrackEta[correctjet_index][correcttrack_index];
                            float Trackphi = THINjetTrackPhi[correctjet_index][correcttrack_index];
                            TLorentzVector *thisJet = (TLorentzVector *)thinjetP4->At(correctjet_index);
                            float Thinjeteta = thisJet->Eta();
                            float Thinjetphi = thisJet->Phi();
                            float deta = Thinjeteta - Tracketa;
                            float dphi = Thinjetphi - Trackphi;
                            while (dphi > TMath::Pi())
                                dphi -= 2 * TMath::Pi();
                            while (dphi <= -TMath::Pi())
                                dphi += 2 * TMath::Pi();
                            float dR = sqrt(deta * deta + dphi * dphi);
                            //------------------------------------
                            // Calculate denominator and numerator
                            //------------------------------------
                            SumOfTrackPt += abs(THINjetTrackPt[correctjet_index][correcttrack_index]);
                            if (THINjetTrackPt[correctjet_index][correcttrack_index] < 0)
                            {
                                cout << "hello" << endl;
                            }
                            if (log10(chi3d) < 1.0)
                            {
                                Trackmultiplicitycut++;
                                SumofTrackPT_cut += abs(THINjetTrackPt[correctjet_index][correcttrack_index]);
                            }
                            if (log10(chi3d) < 2.0)
                            {
                                SumOfTrackPt_cut2 += abs(THINjetTrackPt[correctjet_index][correcttrack_index]);
                            }
                            if (log10(chi3d) < 3.0)
                            {
                                SumOfTrackPt_cut3 += abs(THINjetTrackPt[correctjet_index][correcttrack_index]);
                            }
                            if (log10(chi3d) < 4.0)
                            {
                                SumOfTrackPt_cut4 += abs(THINjetTrackPt[correctjet_index][correcttrack_index]);
                            }
                            if (log10(chiP) < 1.0)
                            {
                                SumofTrackPT_Papercut += abs(THINjetTrackPt[correctjet_index][correcttrack_index]);
                            }
                            //----------------------
                            // Fill Tree variable
                            //----------------------
                            v_Trkindex.push_back(j);
                            v_Trkdr.push_back(dR);
                            v_Trk_dz.push_back(dz);
                            v_Trk_dzerror.push_back(dzerror);
                            v_Trk_dxy.push_back(dxy);
                            v_Trk_dxyerror.push_back(dxyerror);
                            v_TrkChi3D.push_back(chi3d);
                            v_TrkChi3D_Paper.push_back(chiP);
                            v_TrkChi2D.push_back(chi2d);

                            double trk_xy_resolu = (dxy) / dxyerror;

                            v_TrkXYresolu.push_back(sqrt(trk_xy_resolu * trk_xy_resolu));
                            v_TrkIP3D.push_back(IP3D);
                            v_TrkPT.push_back(THINjetTrackPt[correctjet_index][correcttrack_index]);
                            v_TrkIP2DxTrkPT.push_back(IP2D * THINjetTrackPt[correctjet_index][correcttrack_index]);
                            float TrackPt = thisJet->Pt();
                            if (TrackPt < THINjetTrackPt[correctjet_index][correcttrack_index])
                            {
                                cout << "--------- Jet and Track Information ---------\n"
                                     << endl;

                                cout << "Jet PT = " << TrackPt << "\n"
                                     << endl;
                                cout << "Track PT = " << THINjetTrackPt[correctjet_index][correcttrack_index] << endl;
                            }
                            v_TrkEta.push_back(THINjetTrackEta[correctjet_index][correcttrack_index]);
                            //-----------------------
                            // Calculate Track number
                            //-----------------------
                            Trackmultiplicity++;
                            //---------------------------
                            // Study Different flavor
                            //---------------------------
                            if (THINjetHadronFlavor[correctjet_index] == 5)
                            {
                                v_bTrkIP2D.push_back(IP2D);
                                v_bTrkChi3D.push_back(chi3d);
                            }
                            else if (THINjetHadronFlavor[correctjet_index] == 4)
                            {
                                v_cTrkIP2D.push_back(IP2D);
                                v_cTrkChi3D.push_back(chi3d);
                            }
                            else
                            {
                                v_lTrkIP2D.push_back(IP2D);
                                v_lTrkChi3D.push_back(chi3d);
                            }
                        } // End of Track loop
                        if (SumOfTrackPt == 0)
                        {
                            continue;
                        }
                        //-----------------
                        // Calculate alpha
                        //-----------------
                        // float alphapaper = SumofTrackPT_Papercut / SumOfTrackPt;
                        double alpha = SumofTrackPT_cut / SumOfTrackPt;
                        double alpha2 = SumOfTrackPt_cut2 / SumOfTrackPt;
                        double alpha3 = SumOfTrackPt_cut3 / SumOfTrackPt;
                        double alpha4 = SumOfTrackPt_cut4 / SumOfTrackPt;

                        v_nTrk_cut3Dsig.push_back(Trackmultiplicitycut);
                        v_nTrk.push_back(Trackmultiplicity);
                        v_aph.push_back(alpha);
                        //------------------
                        //     For Fake rate
                        //------------------
                        TLorentzVector *thisJet = (TLorentzVector *)thinjetP4->At(correctjet_index);
                        v_nPassthinJetPT.push_back(thisJet->Pt());
                        v_nPassthinJetEta.push_back(thisJet->Eta());
                        v_nPassthinJetM.push_back(thisJet->M());
                        v_nPassthinJetCSVv2.push_back(thinJetCSV[correctjet_index]);
                        v_nPassthinJethadflavor.push_back(THINjetHadronFlavor[correctjet_index]);
                        v_nPassthinJetpartonflavor.push_back(THINjetPartonFlavor[correctjet_index]);
                        h_jet_csv->Fill(thinJetCSV[correctjet_index], eventWeight);
                        //-------
                        // For dr
                        //-------
                        v_nPassthinJetledLepdr.push_back(thisJet->DeltaR(goodElectrons[0]));
                        v_nPassthinJetsubLepdr.push_back(thisJet->DeltaR(goodElectrons[1]));
                        v_nPassthinJetalpha.push_back(alpha);
                        v_nPassthinJetalpha2.push_back(alpha2);
                        v_nPassthinJetalpha3.push_back(alpha3);
                        v_nPassthinJetalpha4.push_back(alpha4);
                        //------------------
                        // Jetmultiplicity
                        //------------------
                        Jetmultiplicity++;
                        v_aph_index.push_back(i);
                        // if (v_N_Tracks.size() != v_nPassthinJetalpha.size())
                        //{
                        //     cout << "bug" << endl;
                        //}
                    } // End Match Thin Jet index loop
                    h_njet_pass_trks->Fill(v_nPassthinJetalpha.size(), eventWeight);
                    if (v_nPassthinJetalpha.size() == 0) // !!!!! Test
                    {
                        continue;
                    }
                    h_ee_npass->Fill(8, eventWeight);
                    // float maxaph = *max_element(v_aph.begin(), v_aph.end());
                    float minaph = *min_element(v_aph.begin(), v_aph.end());
                    // int minElementIndex = min_element(v_aph.begin(), v_aph.end()) - v_aph.begin();
                    //---------------------------
                    //   Fill Tree event variable
                    //---------------------------
                    I_event = jEntry;
                    I_weight = eventWeight;
                    f_HT = HT;
                    f_Met = met;
                    I_tot_Recoevt = neeRecoTotal;
                    I_tot_gencoevt = neeGenevt;
                    I_Sumeventweight = SumeventWeight;
                    f_dileptonPT = dilepPt;
                    I_nthinJet = indexForPassAK4.size();
                    I_nPassthinJets = Jetmultiplicity;
                    if (Jetmultiplicity > indexForPassAK4.size())
                    {
                        cout << "bug here" << endl;
                    }
                    f_leadJetpt = goodJet[0].Pt();
                    f_leadJeteta = goodJet[0].Eta();
                    v_nPassthinJet_alphamin = minaph;
                    f_dileptonmass = Z_boson_ee.M();
                    ULong64_t eventId = data.GetLong64("eventId");
                    I_eventID = eventId;
                    T_tree->Fill();
                } // recoEE
            }     // GenEE
        }         // End of loop over entries
    }             // End of loop all files
    //-----------------
    // Close input file
    //-----------------
    flist.close();

    // out Tree branches
    TFile *outFile = new TFile(outputfile.c_str(), "RECREATE");
    outFile->cd();
    T_tree->Write();
    outFile->mkdir("Event_Variable", "Event_Variable")->cd();
    h_totevent->Write();
    h_genee_event->Write();
    h_recoee_event->Write();
    h_ele_n->Write();
    h_mu_n->Write();
    h_tau_n->Write();
    Z_eemass->Write();
    dilepton_pT->Write();
    dilepton_pT_after_ledptcut->Write();
    dilepton_pT_after_dilepmasscut->Write();
    dilepton_pT_after_extralepcut->Write();
    dilepton_pT_after_vetotaucut->Write();
    dilepton_pT_after_nJetcut->Write();
    h_ee_npass->Write();
    gen_chi2numb->Write();
    gen_dquarknumb->Write();
    gen_eenumber->Write();
    match_dquarknumb->Write();
    h_HT_eventCout->Write();
    outFile->cd("/");
    outFile->mkdir("Jet_Variable", "Jet_Variable")->cd();
    h_jet_rank->Write();
    h_njet->Write();
    h_njet_pass_trks->Write();
    h_jet_csv->Write();
    outFile->cd("/");
    outFile->mkdir("Track_Variable", "Track_Variable")->cd();
    h_trk_npass->Write();
    h_trkpt->Write();
    outFile->cd("/");
    outFile->Close();
}
