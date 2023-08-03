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
void xAna_data_ztoee(string inputtxtFilename = "./tmpdata.txt", string outputfile = "./testdata.root")
{
    ifstream flist(inputtxtFilename.data());

    string inputFile;

    // Create histrogram
    TH1D *h_jet_n = new TH1D("h_jet_n", "Nr of Matched jets", 15, 0, 15);
    h_jet_n->GetXaxis()->SetTitle("Number of Jets");
    h_jet_n->GetYaxis()->SetTitle("Number of Events");
    h_jet_n->Sumw2();

    TH1D *h_jet_rank = new TH1D("h_jet_rank", "Nr of rank Matched jets", 15, 0, 15);
    h_jet_rank->GetXaxis()->SetTitle("Jet_rank");
    h_jet_rank->GetYaxis()->SetTitle("Number of Events");
    h_jet_rank->Sumw2();

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

    TH1D *Z_massee = new TH1D("Z_massee", "Z->ee", 150, 0, 150);
    Z_massee->GetXaxis()->SetTitle("Z mass");
    Z_massee->GetYaxis()->SetTitle("Number of Events");
    Z_massee->Sumw2();

    TH1D *dilepton_pT = new TH1D("dilepton_pT", "dilepton_pT", 50, 0, 500);
    dilepton_pT->GetXaxis()->SetTitle("dilepton pT");
    dilepton_pT->GetYaxis()->SetTitle("Number of Events");
    dilepton_pT->Sumw2();

    TH1D *Thinjet_pT = new TH1D("Thinjet_pT", "Thinjet pT", 50, 0, 500);
    Thinjet_pT->GetXaxis()->SetTitle("Thinjet pT");
    Thinjet_pT->GetYaxis()->SetTitle("Number of Jets");
    Thinjet_pT->Sumw2();

    TH1D *h_ee_event = new TH1D("h_ee_event", "events", 10, 0, 10);
    h_ee_event->Sumw2();

    TH1D *h_ee_stu_event = new TH1D("h_ee_stu_event", "events", 10, 0, 10);
    h_ee_stu_event->Sumw2();

    TH1D *h_event = new TH1D("h_event", "events", 10, 0, 10);
    h_event->Sumw2();

    TH1D *h_eventWeight = new TH1D("h_eventWeight", "eventWeight", 100, -1, 1);
    TH1D *h_SumWeight = new TH1D("h_SumWeight", "Sum Weigh", 1, 0, 1);

    TH1D *Chi3Dlog = new TH1D("Chi3Dlog", "Chi3D", 100, -10, 10);
    Chi3Dlog->GetXaxis()->SetTitle("Chi3D");
    Chi3Dlog->GetYaxis()->SetTitle("N Tracks");
    Chi3Dlog->Sumw2();

    TH1D *Chi3Dlogaf = new TH1D("Chi3Dlogaf", "Chi3D", 100, -10, 10);
    Chi3Dlogaf->GetXaxis()->SetTitle("Chi3D");
    Chi3Dlogaf->GetYaxis()->SetTitle("N Tracks");
    Chi3Dlogaf->Sumw2();

    TH1D *Chi3D = new TH1D("Chi3D", "Chi3D", 50, 0, 100);
    Chi3D->GetXaxis()->SetTitle("Chi3D");
    Chi3D->GetYaxis()->SetTitle("N Tracks");
    Chi3D->Sumw2();

    TH1D *Chi3DPaperlog = new TH1D("Chi3DPaperlog", "Chi3DPaperlog", 100, -10, 10);
    Chi3DPaperlog->GetXaxis()->SetTitle("Chi3D(0.01)");
    Chi3DPaperlog->GetYaxis()->SetTitle("N Tracks");
    Chi3DPaperlog->Sumw2();

    TH1D *Chi2Dlog = new TH1D("Chi2Dlog", "Chi2D", 100, -10, 10);
    Chi2Dlog->GetXaxis()->SetTitle("Chi2D");
    Chi2Dlog->GetYaxis()->SetTitle("N Tracks");
    Chi2Dlog->Sumw2();

    TH1F *hmet = new TH1F("hmet", "", 20, 0, 800);
    hmet->GetYaxis()->SetTitle("Number of Events");
    hmet->SetXTitle("#slash{E}_{T}");
    hmet->Sumw2();

    TH1F *h_nTracks = new TH1F("h_nTracks", "", 35, 0, 35);
    h_nTracks->SetXTitle("nTracks");
    h_nTracks->SetYTitle("N Jets");
    h_nTracks->Sumw2();

    TH1F *h_AK4mass = new TH1F("h_AK4mass", "", 100, 0, 100);
    h_AK4mass->SetYTitle("N Jets");
    h_AK4mass->SetXTitle("h_AK4mass");
    h_AK4mass->Sumw2();

    TH1F *h_aph = new TH1F("h_aph", "", 100, 0, 1);
    h_aph->SetXTitle("h_aph3D");
    h_aph->SetYTitle("N Jets");
    h_aph->Sumw2();

    TH1F *h_aphmax = new TH1F("h_aphmax", "", 24, 0, 1.2);
    h_aphmax->SetXTitle("h_aphmax");
    h_aphmax->SetYTitle("N events");
    h_aphmax->Sumw2();

    TH1F *h_aphmin = new TH1F("h_aphmin", "", 24, 0, 1.2);
    h_aphmin->SetXTitle("h_aphmin");
    h_aphmin->SetYTitle("N events");
    h_aphmin->Sumw2();

    TH1F *h_aph026 = new TH1F("h_aph026", "", 24, 0, 1.2);
    h_aph026->SetXTitle("h_aph3D");
    h_aph026->SetYTitle("N Jets");
    h_aph026->Sumw2();

    TH1D *h_jet_eta = new TH1D("h_jet_eta", "eta jets", 10, -5, 5);
    h_jet_eta->SetXTitle("#{eta}");
    h_jet_eta->SetYTitle("N Jets");
    h_jet_eta->Sumw2();

    TH1D *h_jet_pt = new TH1D("h_jet_pt", "pt jets", 100, 0, 1000);
    h_jet_pt->SetXTitle("pt");
    h_jet_pt->SetYTitle("N Jets");
    h_jet_pt->Sumw2();

    TH1F *PUdz = new TH1F("PUdz", "", 600, -30, 30);
    PUdz->SetXTitle("PUdz");
    PUdz->Sumw2();

    TH1F *h_dzError = new TH1F("h_dzError", "", 50, 0, 5);
    h_dzError->SetXTitle("dzError");
    h_dzError->Sumw2();

    TH1F *h_dxyError = new TH1F("h_dxyError", "", 50, 0, 5);
    h_dxyError->SetXTitle("dxyError");
    h_dxyError->Sumw2();

    TH1F *Teacketa = new TH1F("Teacketa", "", 20, -10, 10);
    Teacketa->SetXTitle("eta");
    Teacketa->SetYTitle("N Tracks");
    Teacketa->Sumw2();

    TH1D *gen_chi2numb = new TH1D("gen_chi2numb", "Chi2", 5, 0, 5);
    TH1D *gen_dquarknumb = new TH1D("gen_dquarknumb", "d quark", 10, 0, 10);
    TH1D *match_dquarknumb = new TH1D("match_dquarknumb", "d quark", 10, 0, 10);

    TH1D *ratioTrackPt = new TH1D("ratioTrackPt", "", 10, 0, 1);
    TH1D *h_track_phi = new TH1D("h_track_phi", "", 100, -10, 10);
    TH1D *h_track_dr = new TH1D("h_track_dr", "", 50, 0, 5);
    TH1D *h_track_draf = new TH1D("h_track_draf", "", 500, 0, 5);

    TH1F *h_jet_dr_d2 = new TH1F("h_jet_dr_d2", "", 50, 0, 5);
    h_jet_dr_d2->SetXTitle("dr");
    h_jet_dr_d2->SetYTitle("N Jets");
    h_jet_dr_d2->Sumw2();
    TH1F *h_jet_dr_d3 = new TH1F("h_jet_dr_d3", "", 50, 0, 5);
    h_jet_dr_d3->SetXTitle("dr");
    h_jet_dr_d3->SetYTitle("N Jets");
    h_jet_dr_d3->Sumw2();

    TH1F *h_jet_hadronbig0_2Flavour = new TH1F("h_jet_hadronbig0_2Flavour", "", 10, 0, 10);
    h_jet_hadronbig0_2Flavour->SetXTitle("hadronFlavour");
    h_jet_hadronbig0_2Flavour->SetYTitle("N Jets");
    h_jet_hadronbig0_2Flavour->Sumw2();

    TH1F *h_jet_hadronless_0_2Flavour = new TH1F("h_jet_hadronless_0_2Flavour", "", 10, 0, 10);
    h_jet_hadronless_0_2Flavour->SetXTitle("hadronFlavour");
    h_jet_hadronless_0_2Flavour->SetYTitle("N Jets");
    h_jet_hadronless_0_2Flavour->Sumw2();

    TH1F *h_mt2 = new TH1F("h_mt2", "", 100, 0, 1000);
    h_mt2->SetXTitle("transverse mass");
    h_mt2->SetYTitle("");
    h_mt2->Sumw2();

    TH1F *h_ee_npass = new TH1F("h_ee_npass", "", 10, 0, 10);
    h_ee_npass->SetXTitle("npass");
    h_ee_npass->Sumw2();

    TH1F *h_tau_thisdr = new TH1F("h_tau_thisdr", "", 50, 0, 5);
    h_tau_thisdr->SetXTitle("dr");
    h_tau_thisdr->SetYTitle("N event");
    h_tau_thisdr->Sumw2();
    TH1F *h_tau_thatdr = new TH1F("h_tau_thatdr", "", 50, 0, 5);
    h_tau_thatdr->SetXTitle("dr");
    h_tau_thatdr->SetYTitle("N event");
    h_tau_thatdr->Sumw2();

    //---------------------------
    //     Void TTree variable
    //---------------------------
    Int_t I_event;
    ULong64_t I_eventID;
    Int_t I_weight;
    Double_t f_alphamax;
    Double_t f_alphamin;
    float_t f_Met;
    float_t f_dileptonPT;
    Float_t f_HT;
    Float_t f_dileptonmass;

    // T_Track variable
    vector<int> v_N_Tracks;
    vector<float> v_TrackPT;
    vector<float> v_TrackEta;
    vector<float> v_Chi3Dlog;
    vector<float> v_Chi2Dlog;

    // Study match thin jet
    Int_t I_nThinJets;
    float_t f_leadJeteta;
    float_t f_leadJetpt;
    vector<int> I_matchnJet;
    vector<int> I_matchnJetflavor;
    vector<float> f_matchJet_PT;
    vector<float> f_matchJet_Eta;

    TTree *T_event = new TTree("T_event", "Tree");
    T_event->Branch("I_event", &I_event);
    T_event->Branch("I_eventID", &I_eventID);
    T_event->Branch("I_weight", &I_weight);
    T_event->Branch("f_dileptonPT", &f_dileptonPT);
    T_event->Branch("f_Met", &f_Met);
    T_event->Branch("f_HT", &f_HT);
    T_event->Branch("f_dileptonmass", &f_dileptonmass);
    T_event->Branch("I_nThinJets", &I_nThinJets);
    T_event->Branch("f_leadJetpt", &f_leadJetpt);
    T_event->Branch("f_leadJeteta", &f_leadJeteta);
    T_event->Branch("I_matchnJet", &I_matchnJet);
    T_event->Branch("I_matchnJetflavor", &I_matchnJetflavor);
    T_event->Branch("f_matchJet_PT", &f_matchJet_PT);
    T_event->Branch("f_matchJet_Eta", &f_matchJet_Eta);
    T_event->Branch("v_N_Tracks", &v_N_Tracks);
    T_event->Branch("v_TrackPT", &v_TrackPT);
    T_event->Branch("v_TrackEta", &v_TrackEta);

    T_event->Branch("f_alphamax", &f_alphamax);
    T_event->Branch("f_alphamin", &f_alphamin);
    T_event->Branch("v_Chi3Dlog", &v_Chi3Dlog);
    T_event->Branch("v_Chi2Dlog", &v_Chi2Dlog);

    // void some variable
    Long64_t neeTotal = 0;
    int SumeventWeight = 0;
    while (getline(flist, inputFile))
    {
        // Identify input file type
        bool CMSdata = false;
        bool DoubEe = false;
        bool MuonEG = false;
        bool DiMuon = false;
        bool SinglEe = false;
        bool SinglMu = false;
        // Identify input file type
        if ((inputFile).find("crab_MuonEG") != std::string::npos)
        {
            CMSdata = true;
            MuonEG = true;
        }
        if ((inputFile).find("crab_DoubleEG") != std::string::npos)
        {
            CMSdata = true;
            DoubEe = true;
        }
        if ((inputFile).find("crab_DoubleMuon") != std::string::npos)
        {
            CMSdata = true;
            DiMuon = true;
        }
        if ((inputFile).find("crab_SingleElectron") != std::string::npos)
        {
            CMSdata = true;
            SinglEe = true;
        }
        if ((inputFile).find("crab_SingleMuon") != std::string::npos)
        {
            CMSdata = true;
            SinglMu = true;
        }
        TreeReader data(inputFile.data());
        for (Long64_t jEntry = 0; jEntry < data.GetEntriesFast(); jEntry++)
        {
            if (jEntry % 2000 == 0)
            {
                fprintf(stderr, "Processing event %lli of %lli\n", jEntry + 1, data.GetEntriesFast());
            }
            // clear Tree vector for each event
            f_matchJet_PT.clear();
            f_matchJet_Eta.clear();
            I_matchnJet.clear();
            I_matchnJetflavor.clear();
            v_Chi3Dlog.clear();
            v_Chi2Dlog.clear();
            v_N_Tracks.clear();
            v_TrackPT.clear();
            v_TrackEta.clear();

            data.GetEntry(jEntry);
            Float_t mcWeight = data.GetFloat("mcWeight");
            Double_t eventWeight = mcWeight;
            if (eventWeight > 0)
            {
                eventWeight = 1;
            }
            else if (eventWeight < 0)
            {
                eventWeight = 1;
            }
            else
            {
                eventWeight = 1;
            }

            h_event->Fill(1.0, eventWeight);
            // Sum over event Weight
            h_eventWeight->Fill(0., eventWeight);

            SumeventWeight += eventWeight;
            // 1. Trigger
            if (CMSdata)
            {
                std::string *trigName = data.GetPtrString("hlt_trigName");
                vector<bool> &trigResult = *((vector<bool> *)data.GetPtr("hlt_trigResult"));

                bool passTrigger = false;
                for (unsigned int it = 0; it < trigResult.size(); it++)
                {
                    std::string thisTrig = trigName[it];
                    bool results = trigResult[it];
                    if (DiMuon)
                    {
                        if ((thisTrig.find("Mu17_TrkIsoVVL_Mu8_TrkIsoVVL") !=
                                 std::string::npos &&
                             results == 1) ||
                            (thisTrig.find("Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ") !=
                                 std::string::npos &&
                             results == 1) ||
                            (thisTrig.find("TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ") !=
                                 std::string::npos &&
                             results == 1))
                        {
                            //cout << thisTrig << endl;
                            passTrigger = true;
                            break;
                        }
                    }
                    if (SinglEe)
                    {
                        if ((thisTrig.find("Ele25_eta2p1_WPTight_Gsf") !=
                                 std::string::npos &&
                             results == 1) ||
                            (thisTrig.find("Ele27_eta2p1_WPLoose_Gsf") !=
                                 std::string::npos &&
                             results == 1) ||
                            (thisTrig.find("Ele27_WPTight_Gsf") !=
                                 std::string::npos &&
                             results == 1) ||
                            (thisTrig.find("Ele35_WPLoose_Gsf") !=
                                 std::string::npos &&
                             results == 1))
                        {
                            //cout << thisTrig << endl;
                            passTrigger = true;
                            break;
                        }
                    }
                    if (SinglMu)
                    {
                        if ((thisTrig.find("IsoMu22") !=
                                 std::string::npos &&
                             results == 1) ||
                            (thisTrig.find("IsoTkMu22") !=
                                 std::string::npos &&
                             results == 1) ||
                            (thisTrig.find("IsoMu24") !=
                                 std::string::npos &&
                             results == 1) ||
                            (thisTrig.find("IsoTkMu24") !=
                                 std::string::npos &&
                             results == 1))
                        {
                            //cout << thisTrig << endl;
                            passTrigger = true;
                            break;
                        }
                    }
                    if (MuonEG)
                    {
                        if ((thisTrig.find("Mu17_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL") !=
                                 std::string::npos &&
                             results == 1) ||
                            (thisTrig.find("Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL") !=
                                 std::string::npos &&
                             results == 1) ||
                            (thisTrig.find("Mu17_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL") !=
                                 std::string::npos &&
                             results == 1) ||
                            (thisTrig.find("Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL") !=
                                 std::string::npos &&
                             results == 1) ||
                            (thisTrig.find("Mu8_TrkIsoVVL_Ele17_CaloIdL_TrackIdL_IsoVL") !=
                                 std::string::npos &&
                             results == 1) ||
                            (thisTrig.find("Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL") !=
                                 std::string::npos &&
                             results == 1))
                        {
                            //cout << thisTrig << endl;
                            passTrigger = true;
                        }
                    }
                    if (DoubEe)
                    {
                        if ((thisTrig.find("Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ") !=
                                 std::string::npos &&
                             results == 1))
                        {
                            // cout << thisTrig << endl;
                            passTrigger = true;
                            break;
                        }
                    }
                    if (!passTrigger)
                        continue;
                }
            }
            // 2. electron
            int nEle = data.GetInt("nEle");
            TClonesArray *eleP4 = (TClonesArray *)data.GetPtrTObject("eleP4");
            vector<bool> &eleIsPassLoose = *((vector<bool> *)data.GetPtr("eleIsPassLoose"));
            vector<bool> &eleIsPassMedium = *((vector<bool> *)data.GetPtr("eleIsPassMedium"));
            vector<bool> &eleIsPassVeto = *((vector<bool> *)data.GetPtr("eleIsPassVeto"));
            vector<TLorentzVector> goodElectrons;
            goodElectrons.clear();
            vector<int> vetoee;
            vetoee.clear();
            for (int ie = 0; ie < nEle; ie++)
            {
                TLorentzVector *myEle = (TLorentzVector *)eleP4->At(ie);
                if (myEle->Pt() < 20)
                    continue;
                if (fabs(myEle->Eta()) > 2.4)
                    continue;
                if (!eleIsPassMedium[ie])
                    continue;
                goodElectrons.push_back(*myEle);
            } // End of loop nEle event

            h_ele_n->Fill(goodElectrons.size(), eventWeight);
            // Sort electron by PT
            sort(goodElectrons.begin(), goodElectrons.end(), pt_greater);
            // 2.1 Muon
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
                if (myMu->Pt() < 20)
                    continue;
                if (fabs(myMu->Eta()) > 2.4)
                    continue;
                double myMuIso = (muChHadIso[imu] + max(0., muNeHadIso[imu] + muGamIso[imu] - 0.5 * muPUPt[imu])) / mupT;
                if (myMuIso > 0.15)
                    continue;
                if (muTrkLayers[imu] < 5)
                    continue;
                if (!isSoftMuon[imu])
                    continue;
                goodmuons.push_back(*myMu);
            } // End of Muon loop
            // cout << goodmuons.size() << endl;
            h_mu_n->Fill(goodmuons.size(), eventWeight);
            bool recoeeEvent = false;
            bool recouuEvent = false;

            if (goodElectrons.size() >= 2 && goodmuons.size() < 2)
            {
                recoeeEvent = true;
            }
            else
            {
                h_ee_stu_event->Fill(goodElectrons.size(), eventWeight);
            }
            if (goodmuons.size() >= 2 && goodElectrons.size() < 2)
            {
                recouuEvent = true;
            }
            if (goodmuons.size() == goodElectrons.size())
            {
                continue;
            }
            if (recoeeEvent)
            {
                neeTotal++;

                h_ee_npass->Fill(1, eventWeight);

                // 1. has a good vertex
                int nVtx = data.GetInt("nVtx");
                if (nVtx < 1)
                    continue;

                h_ee_npass->Fill(2, eventWeight);

                // 3. veto tau
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
                    if (myTau->Pt() < 18)
                        continue;
                    if (fabs(myTau->Eta()) > 2.5)
                        continue;
                    if (!disc_decayModeFindingNewDMs[it])
                        continue;
                    if (!disc_byVTightIsolationMVA3newDMwLT[it])
                        continue;
                    goodtau.push_back(*myTau);
                } // end of tau loop

                h_tau_n->Fill(goodtau.size(), eventWeight);

                // 4. For Met
                Float_t met = data.GetFloat("pfMetCorrPt");
                hmet->Fill(met, eventWeight);

                Float_t metphi = data.GetFloat("pfMetCorrPhi");

                Float_t SumEt = data.GetFloat("pfMetCorrSumEt");

                TLorentzVector met_l4(0, 0, 0, 0);
                met_l4.SetPtEtaPhiE(met, 0, metphi, met);

                float X1_mass = 0.1;
                float Etmiss = sqrt(pow(met, 2) + pow(X1_mass, 2));
                for (int i = 0; i < goodElectrons.size(); i++)
                {
                    // float eledphi = fabs(met_l4.DeltaPhi(goodElectrons[i]));
                    // float mt2 = sqrt(2*met*goodElectrons[i].Pt()*(1- cos(eledphi)));
                    // h_mt2->Fill(mt2, eventWeight);
                    float m2t = pow(goodElectrons[i].M(), 2) + pow(X1_mass, 2) + 2 * (goodElectrons[i].Et() * Etmiss - goodElectrons[i].Pt() * met);
                    // cout << "m2t = " << m2t << endl;
                    // cout<<"test = "<< 2*(SumEt)<<endl;
                }

                // 5. Z boson
                double PDGZmass = 91.1876;
                double PT1 = goodElectrons[0].Pt();
                double PT2 = goodElectrons[1].Pt();
                float dilepPt = (goodElectrons[0] + goodElectrons[1]).Pt();
                dilepton_pT->Fill(dilepPt, eventWeight);
                if (PT1 < 25 && PT2 < 20)
                    continue;
                h_ee_npass->Fill(3, eventWeight);

                TLorentzVector Z_boson_ee;
                Z_boson_ee = goodElectrons[0] + goodElectrons[1];
                double deltaMass = abs(PDGZmass - Z_boson_ee.M());
                if (deltaMass > 15)
                    continue;

                h_ee_npass->Fill(4, eventWeight);
                Z_massee->Fill(Z_boson_ee.M(), eventWeight);

                if (goodElectrons.size() > 2 || goodmuons.size() > 2)
                    continue;
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
                            h_tau_thisdr->Fill(thisdr, eventWeight);
                            h_tau_thatdr->Fill(thatdr, eventWeight);
                            tauee = true;
                            break;
                        }
                    }
                } // End of veto tau
                if (tauee)
                    continue;
                h_ee_npass->Fill(6, eventWeight);

                // 6. Thin Jet
                int nTHINJets = data.GetInt("THINnJet");
                TClonesArray *thinjetP4 = (TClonesArray *)data.GetPtrTObject("THINjetP4");
                Int_t *THINjetNTracks = data.GetPtrInt("THINjetNTracks");
                float *thinJetCSV = data.GetPtrFloat("THINjetCISVV2");
                vector<float> *THINjetTrackImpdz = data.GetPtrVectorFloat("THINjetTrackImpdz", nTHINJets);
                vector<float> *THINjetTrackImpdzError = data.GetPtrVectorFloat("THINjetTrackImpdzError", nTHINJets);
                vector<float> *THINjetTrackImpdxy = data.GetPtrVectorFloat("THINjetTrackImpdxy", nTHINJets);
                vector<float> *THINjetTrackImpdxyError = data.GetPtrVectorFloat("THINjetTrackImpdxyError", nTHINJets);
                vector<float> *THINjetTrackPt = data.GetPtrVectorFloat("THINjetTrackPt", nTHINJets);
                vector<float> *THINjetTrackPhi = data.GetPtrVectorFloat("THINjetTrackPhi", nTHINJets);
                vector<float> *THINjetTrackEta = data.GetPtrVectorFloat("THINjetTrackEta", nTHINJets);
                vector<int> indexForPassAK4;
                indexForPassAK4.clear();
                vector<TLorentzVector> goodJet;
                goodJet.clear();
                for (int i = 0; i < nTHINJets; i++)
                {
                    TLorentzVector *thisJet = (TLorentzVector *)thinjetP4->At(i);
                    h_jet_pt->Fill(thisJet->Pt(), eventWeight);
                    // cout<<"Pt = "<< thisJet->Pt()<<endl;
                    if (thisJet->Pt() < 30)
                        continue;
                    h_jet_eta->Fill(thisJet->Eta(), eventWeight);
                    if (fabs(thisJet->Eta()) > 2.5)
                        continue;
                    bool Thinjetee = false;
                    for (int j = 0; j < goodElectrons.size(); j++)
                    {
                        if (thisJet->DeltaR(goodElectrons[j]) < 0.4)
                        {
                            Thinjetee = true;
                            break;
                        }
                    }
                    if (Thinjetee)
                        continue;

                    f_matchJet_PT.push_back(thisJet->Pt());
                    f_matchJet_Eta.push_back(thisJet->Eta());
                    indexForPassAK4.push_back(i);
                    h_jet_rank->Fill(i, eventWeight);
                    goodJet.push_back(*thisJet);
                } // End of nThinJet
                h_jet_n->Fill(indexForPassAK4.size(), eventWeight);
                sort(goodJet.begin(), goodJet.end(), pt_greater);

                if (indexForPassAK4.size() == 0)
                    continue;

                h_ee_npass->Fill(7, eventWeight);

                //----------------------------------------------------------------
                // Loop all match THINjet
                //----------------------------------------------------------------
                vector<float> v_aph;
                v_aph.clear();
                for (int j = 0; j < indexForPassAK4.size(); j++)
                {
                    int Tracknumber = 0;
                    double SSumTrackPt = 0;
                    double UPmaxSSumTrackPt = 0;
                    double UPSSumTrackPt = 0;
                    double UPSSumTrackPtpaper = 0;
                    int InfTrackPt = 0;
                    for (int k = 0; k < THINjetNTracks[indexForPassAK4[j]]; k++)
                    {
                        TLorentzVector *thisJet = (TLorentzVector *)thinjetP4->At(j);
                        // Jet PT
                        float ThinjetPt = thisJet->Pt();
                        Thinjet_pT->Fill(ThinjetPt, eventWeight);
                        // Track Pt > 1 GeV
                        if (THINjetTrackPt[indexForPassAK4[j]][k] < 1.0)
                            continue;
                        Tracknumber++;
                        // Fill dz
                        float PPUdz = THINjetTrackImpdz[indexForPassAK4[j]][k];
                        PUdz->Fill(PPUdz, eventWeight);
                        if (isinf(THINjetTrackImpdzError[indexForPassAK4[j]][k]) == 1)
                        {
                            InfTrackPt++;
                            continue;
                        }
                        if (isinf(THINjetTrackImpdxyError[indexForPassAK4[j]][k]) == 1)
                        {
                            InfTrackPt++;
                            continue;
                        }
                        // float ddz = pow(THINjetTrackImpdz[indexForPassAK4[j]][k]/THINjetTrackImpdzError[indexForPassAK4[j]][k],2);
                        float dzsignificant = THINjetTrackImpdz[indexForPassAK4[j]][k] / THINjetTrackImpdzError[indexForPassAK4[j]][k];
                        h_dzError->Fill(THINjetTrackImpdzError[indexForPassAK4[j]][k], eventWeight);
                        // float ddxy = pow(THINjetTrackImpdxy[indexForPassAK4[j]][k]/THINjetTrackImpdxyError[indexForPassAK4[j]][k],2);
                        float dxysignificant = THINjetTrackImpdxy[indexForPassAK4[j]][k] / THINjetTrackImpdxyError[indexForPassAK4[j]][k];
                        h_dxyError->Fill(THINjetTrackImpdxyError[indexForPassAK4[j]][k], eventWeight);
                        float chi3d = sqrt(dzsignificant * dzsignificant + dxysignificant * dxysignificant);
                        // float chi2d = sqrt(dxysignificant*dxysignificant);
                        float chi2d = dxysignificant;
                        // cout<<"chi2d = "<<dxysignificant<<endl;
                        Chi3Dlog->Fill(log10(chi3d), eventWeight);
                        Chi3D->Fill(chi3d, eventWeight);
                        Chi2Dlog->Fill(log10(chi2d), eventWeight);
                        // Save Paper Variables
                        float dz = pow(THINjetTrackImpdz[indexForPassAK4[j]][k] / 0.01, 2);
                        float chiP = sqrt(dz + dxysignificant * dxysignificant);
                        Chi3DPaperlog->Fill(log10(chiP), eventWeight);
                        // Fill Tree variable
                        v_Chi3Dlog.push_back(log10(chi3d));
                        v_Chi2Dlog.push_back(log10(chi2d));
                        // Sum over Track pt
                        SSumTrackPt += THINjetTrackPt[indexForPassAK4[j]][k];
                        float Tracketa = THINjetTrackEta[indexForPassAK4[j]][k];
                        float Trackphi = THINjetTrackPhi[indexForPassAK4[j]][k];
                        float Thinjeteta = thisJet->Eta();
                        float Thinjetphi = thisJet->Phi();
                        float deta = Thinjeteta - Tracketa;
                        float dphi = Thinjetphi - Trackphi;
                        while (dphi > TMath::Pi())
                            dphi -= 2 * TMath::Pi();
                        while (dphi <= -TMath::Pi())
                            dphi += 2 * TMath::Pi();
                        double dR = sqrt(deta * deta + dphi * dphi);
                        // cout<<"dr = "<<dR<<endl;
                        h_track_dr->Fill(dR, eventWeight);
                        if (dR < 0.4)
                        {
                            UPmaxSSumTrackPt += THINjetTrackPt[indexForPassAK4[j]][k];
                        }
                        if (log10(chi3d) < 1.0)
                        {
                            Chi3Dlogaf->Fill(log10(chi3d), eventWeight);
                            // cout<<"log10(chi3d) = "<<log10(chi3d)<<endl;
                            UPSSumTrackPt += THINjetTrackPt[indexForPassAK4[j]][k];
                        }
                        if (log10(chiP) < 1.0)
                        {
                            UPSSumTrackPtpaper += THINjetTrackPt[indexForPassAK4[j]][k];
                        }
                    } // End track
                    v_N_Tracks.push_back(Tracknumber);
                    h_nTracks->Fill(Tracknumber, eventWeight);
                    if (Tracknumber > 0)
                    {
                        double rateTrackPt = InfTrackPt / Tracknumber;
                        ratioTrackPt->Fill(rateTrackPt, eventWeight);
                    }
                    // This case is Track <1 GeV
                    if (SSumTrackPt > 0)
                    {
                        double alpha1 = UPSSumTrackPt / SSumTrackPt;
                        double alpha1paper = UPSSumTrackPtpaper / SSumTrackPt;
                        h_aph->Fill(alpha1, eventWeight);
                        v_aph.push_back(alpha1);
                        double alpha026 = UPmaxSSumTrackPt / SSumTrackPt;
                        h_aph026->Fill(alpha026, eventWeight);
                    }

                } // End Thin Jet index loop

                if (v_aph.size() == 0)
                    continue;

                double maxaph = *max_element(v_aph.begin(), v_aph.end());
                h_aphmax->Fill(maxaph, eventWeight);

                double minaph = *min_element(v_aph.begin(), v_aph.end());
                h_aphmin->Fill(minaph, eventWeight);

                //--------------
                //  T_eventTree
                //--------------
                f_Met = met;
                I_event = neeTotal;
                I_weight = eventWeight;
                f_dileptonPT = dilepPt;
                I_nThinJets = indexForPassAK4.size();
                f_leadJetpt = goodJet[0].Pt();
                f_leadJeteta = goodJet[0].Eta();
                f_alphamax = maxaph;
                f_alphamin = minaph;
                f_dileptonmass = Z_boson_ee.M();
                ULong64_t eventId = data.GetLong64("eventId");
                I_eventID = eventId;

                T_event->Fill();
            } // recoEE
        }     // End of loop over entries
    }         // End of loop all files

    // out Tree branches
    TFile *outFile = new TFile(outputfile.c_str(), "RECREATE");

    outFile->cd();
    T_event->Write();
    outFile->mkdir("Event_Variable", "Event_Variable")->cd();
    gen_chi2numb->Write();
    gen_dquarknumb->Write();
    match_dquarknumb->Write();
    PUdz->Write();
    h_dzError->Write();
    h_dxyError->Write();
    hmet->Write();
    h_ele_n->Write();
    h_mu_n->Write();
    h_tau_n->Write();
    h_jet_n->Write();
    h_aphmax->Write();
    h_aphmin->Write();
    Z_massee->Write();
    dilepton_pT->Write();
    h_ee_event->Write();
    h_eventWeight->Write();
    h_event->Write();
    h_ee_stu_event->Write();
    h_ee_npass->Write();
    h_SumWeight->Write();

    outFile->cd("/");
    outFile->mkdir("Jet_Variable", "Jet_Variable")->cd();
    h_jet_eta->Write();
    h_jet_pt->Write();
    h_jet_rank->Write();
    h_nTracks->Write();
    h_track_phi->Write();
    h_track_dr->Write();
    h_track_draf->Write();
    Thinjet_pT->Write();
    h_jet_dr_d2->Write();
    h_jet_dr_d3->Write();
    h_jet_hadronless_0_2Flavour->Write();
    h_jet_hadronbig0_2Flavour->Write();

    outFile->cd("/");
    outFile->mkdir("Track_Variable", "Track_Variable")->cd();
    Chi3Dlog->Write();
    Chi3Dlogaf->Write();
    Chi3D->Write();
    Chi3DPaperlog->Write();
    Chi2Dlog->Write();
    Teacketa->Write();
    ratioTrackPt->Write();

    h_aph026->Write();
    outFile->cd("/");

    h_tau_thisdr->Write();
    h_tau_thatdr->Write();
    h_mt2->Write();

    outFile->Close();
}
