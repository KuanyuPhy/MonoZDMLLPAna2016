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
void xAna_ztoee_2017(string inputtxtFilename = "/afs/cern.ch/user/k/kuanyu/test/tmp2017_MX21.txt", string outputfile = "/afs/cern.ch/user/k/kuanyu/ZtoLL/conder_script/2017_ee_Mx21_1p0.root")
{
    ifstream flist(inputtxtFilename.data());
    string inputFile;

    cout << "inputtxtFilename = " << inputtxtFilename << endl;

    fstream fin(inputtxtFilename, ios::in);
    if (!fin)
    {
        std::cout << "Failed to open file.\n";
    }
    string tmps;
    int line = 0;
    while (getline(fin, tmps))
    {
        line++;
    }
    fin.close();
    cout << "line" << line << endl;

    TH1D *h_totevent = new TH1D("h_totevent", "total events", 5, 0, 5);
    h_totevent->Sumw2();

    TH1F *h_total_mcweight = new TH1F("h_total_mcweight", "total MC events", 5, 0, 5);
    h_total_mcweight->Sumw2();

    TH1F *h_total_mcweight_new = new TH1F("h_total_mcweight_new", "total MC events of all files of certain process", 5, 0, 5);
    h_total_mcweight_new->Sumw2();

    TH1D *h_HT_eventCount = new TH1D("h_HT_eventCount", "", 10, 0, 10);
    h_HT_eventCount->SetYTitle("N event");
    h_HT_eventCount->Sumw2();

    TH1F *h_ee_npass = new TH1F("h_ee_npass", "", 10, 0, 10);
    h_ee_npass->SetXTitle("npass");
    h_ee_npass->Sumw2();

    TH1D *h_ee_npass_noweight = new TH1D("h_ee_npass_noweight", "", 10, 0, 10);
    h_ee_npass_noweight->SetXTitle("npass");
    h_ee_npass_noweight->Sumw2();

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

    //-----------------
    // Jets variable
    //-----------------

    vector<float> v_nPassthinJetCSVv2;
    vector<float> v_nPassthinJetDeepCsv;
    //-----------------
    // Tracks variable
    //-----------------
    vector<float> v_Trk_dz;
    vector<float> v_Trk_dzerror;
    vector<float> v_Trk_dxy;
    vector<float> v_Trk_dxyerror;
    vector<float> v_TrkPT;

    TFile *outFile = new TFile(outputfile.c_str(), "RECREATE");

    TTree *T_tree = new TTree("T_tree", "Tree");
    T_tree->Branch("I_event", &I_event);
    T_tree->Branch("I_weight", &I_weight);
    T_tree->Branch("I_eventID", &I_eventID);
    T_tree->Branch("I_tot_gencoevt", &I_tot_gencoevt);
    T_tree->Branch("I_tot_Recoevt", &I_tot_Recoevt);
    T_tree->Branch("I_Sumeventweight", &I_Sumeventweight);
    T_tree->Branch("f_Met", &f_Met);
    T_tree->Branch("d_Met_leptons_ratio", &d_Met_leptons_ratio);
    T_tree->Branch("f_HT", &f_HT);
    T_tree->Branch("f_dileptonmass", &f_dileptonmass);
    T_tree->Branch("f_dileptonPT", &f_dileptonPT);
    T_tree->Branch("v_TrkPT", &v_TrkPT);
    T_tree->Branch("v_Trk_dz", &v_Trk_dz);
    T_tree->Branch("v_Trk_dzerror", &v_Trk_dzerror);
    T_tree->Branch("v_Trk_dxy", &v_Trk_dxy);
    T_tree->Branch("v_Trk_dxyerror", &v_Trk_dxyerror);
    T_tree->Branch("v_nPassthinJetCSVv2", &v_nPassthinJetCSVv2);
    T_tree->Branch("v_nPassthinJetDeepCsv", &v_nPassthinJetDeepCsv);

    int totalLines = countLinesInFile(inputtxtFilename);
    int linesProcessed = 0;

    while (getline(flist, inputFile))
    {

        ++linesProcessed;
        int percent = (100 * linesProcessed) / totalLines;
        printProgressBar(percent);

        h_total_mcweight->Reset();

        TString file(inputFile);
        TFile *openfile = TFile::Open(file);

        h_total_mcweight = static_cast<TH1F *>(openfile->Get("h_total_mcweight"));
        h_total_mcweight_new->Add(h_total_mcweight);

        TreeReader data(inputFile.data(), "outTree");
        // Event Loop
        cout << "Total Event =" << data.GetEntriesFast() << endl;

        for (Long64_t jEntry = 0; jEntry < data.GetEntriesFast(); jEntry++)
        {

            //-------------------
            //  void some variable
            //-------------------
            Int_t neeRecoTotal = 0;
            Int_t neeGenevt = 0;
            Int_t SumeventWeight = 0;
            //  clear Tree vector for each event
            v_TrkPT.clear();
            v_Trk_dz.clear();
            v_Trk_dzerror.clear();
            v_Trk_dxy.clear();
            v_Trk_dxyerror.clear();
            v_nPassthinJetCSVv2.clear();
            v_nPassthinJetDeepCsv.clear();

            data.GetEntry(jEntry);

            Float_t mcWeight = data.GetFloat("mcweight");
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
            /* Get Total event number*/
            h_totevent->Fill(1, eventWeight);
            /*For inclusive sample event counter*/
            /*
            Float_t HT = data.GetFloat("st_HT");
            f_HT = HT;
            if (HT < 70)
            {
                h_HT_eventCount->Fill(1, eventWeight);
            }
            else if (HT >= 70 && HT < 100)
            {
                h_HT_eventCount->Fill(2, eventWeight);
            }
            else if (HT >= 100 && HT < 200)
            {
                h_HT_eventCount->Fill(3, eventWeight);
            }
            else if (HT >= 200 && HT < 400)
            {
                h_HT_eventCount->Fill(4, eventWeight);
            }
            else if (HT >= 400 && HT < 600)
            {
                h_HT_eventCount->Fill(5, eventWeight);
            }
            else if (HT >= 600 && HT < 800)
            {
                h_HT_eventCount->Fill(6, eventWeight);
            }
            else if (HT >= 800 && HT < 1200)
            {
                h_HT_eventCount->Fill(7, eventWeight);
            }
            else if (HT >= 1200 && HT < 2500)
            {
                h_HT_eventCount->Fill(8, eventWeight);
            }
            else if (HT >= 2500)
            {
                h_HT_eventCount->Fill(9, eventWeight);
            }*/

            /*1. Select electron*/
            Long64_t nEle = data.GetLong64("st_nEle");
            Float_t *elePx = data.GetPtrFloat("st_elePx");
            Float_t *elePy = data.GetPtrFloat("st_elePy");
            Float_t *elePz = data.GetPtrFloat("st_elePz");
            Float_t *eleEnergy = data.GetPtrFloat("st_eleEnergy");
            vector<bool> &eleIsPassMedium = *((vector<bool> *)data.GetPtr("st_eleIsPassMedium"));
            vector<TLorentzVector> goodElectrons;
            goodElectrons.clear();

            for (int ie = 0; ie < nEle; ie++)
            {
                // nEleBefore ++;
                TLorentzVector *myEle = new TLorentzVector(elePx[ie], elePy[ie], elePz[ie], eleEnergy[ie]);
                if (!eleIsPassMedium[ie])
                {
                    continue;
                }
                goodElectrons.push_back(*myEle);

            } // End of Ele Loop
            sort(goodElectrons.begin(), goodElectrons.end(), pt_greater);

            /*2. Select muon*/
            Long64_t nMu = data.GetLong64("st_nMu");
            Float_t *muPx = data.GetPtrFloat("st_muPx");
            Float_t *muPy = data.GetPtrFloat("st_muPy");
            Float_t *muPz = data.GetPtrFloat("st_muPz");
            Float_t *muEnergy = data.GetPtrFloat("st_muEnergy");
            vector<bool> &isSoftLooseIsoMuon = *((vector<bool> *)data.GetPtr("st_isSoftLooseIsoMuon"));
            vector<TLorentzVector> goodmuons;
            goodmuons.clear();

            for (int imu = 0; imu < nMu; imu++)
            {
                TLorentzVector *myMu = new TLorentzVector(muPx[imu], muPy[imu], muPz[imu], muEnergy[imu]);
                // if (muTrkLayers[imu] < 5) continue;
                if (!isSoftLooseIsoMuon[imu])
                {
                    continue;
                }

                goodmuons.push_back(*myMu);

            } // End of Muon Loop
            bool recoeeEvent = false;
            bool recouuEvent = false;
            if (goodmuons.size() == goodElectrons.size())
            {
                continue;
            }
            // if (goodElectrons.size() >= 2 && goodmuons.size() < 2)
            if (goodElectrons.size() >= 2 && goodmuons.size() == 0)
            {
                recoeeEvent = true;
            }
            // if (goodmuons.size() >= 2 && goodElectrons.size() < 2)
            if (goodmuons.size() == 2 && goodElectrons.size() == 0)
            {
                recouuEvent = true;
            }
            if (recoeeEvent)
            {
                h_ee_npass->Fill(1, eventWeight);

                Float_t met = data.GetFloat("st_pfMetCorrPt");

                TLorentzVector DilepAfterRecoee = goodElectrons[0] + goodElectrons[1];

                // 3. Good Vertex
                Long64_t nVtx = data.GetLong64("st_nVtx");
                if (nVtx < 1)
                    continue;
                h_ee_npass->Fill(2, eventWeight);

                // 4. Tau Veto
                Long64_t nTau_DRBased_EleVeto = data.GetLong64("st_nTau_DRBased_EleVeto");
                if (nTau_DRBased_EleVeto > 0)
                    continue;
                h_ee_npass->Fill(3, eventWeight);

                // 5. Z boson
                if (goodElectrons[0].Pt() <= 25 && goodElectrons[1].Pt() <= 20)
                {
                    continue;
                }
                h_ee_npass->Fill(4, eventWeight);

                float PDGZmass = 91.1876;
                float dilepMass = DilepAfterRecoee.M();
                float deltaMass = abs(PDGZmass - dilepMass);
                if (deltaMass > 15)
                {
                    continue;
                }
                h_ee_npass->Fill(5, eventWeight);
                //----------------------
                // To reduce diboson case
                //----------------------
                if (goodElectrons.size() > 2 || goodmuons.size() > 0)
                    continue;

                // 6. Thin Jet
                Long64_t nTHINjets = data.GetLong64("st_THINnJet");
                Float_t *THINjetPx = data.GetPtrFloat("st_THINjetPx");
                Float_t *THINjetPy = data.GetPtrFloat("st_THINjetPy");
                Float_t *THINjetPz = data.GetPtrFloat("st_THINjetPz");
                Float_t *THINjetEnergy = data.GetPtrFloat("st_THINjetEnergy");
                Int_t *THINjetHadronFlavor = data.GetPtrInt("st_THINjetHadronFlavor");
                vector<int> indexForPassAK4;
                indexForPassAK4.clear();

                /*Add d quark match*/

                if (nTHINjets < 2)
                    continue;

                /*
                for (int itj = 0; itj < nTHINjets; itj++)
                {
                    TLorentzVector *thisTHINjet = new TLorentzVector(THINjetPx[itj], THINjetPy[itj], THINjetPz[itj], THINjetEnergy[itj]);
                    goodTHINjets.push_back(*thisTHINjet);
                }*/
                h_ee_npass->Fill(7, eventWeight);

                //---------------------------
                // Study match Jet's tracks of Thin Jets
                //---------------------------
                Int_t *THINjetNTracks = data.GetPtrInt("st_THINjetNTracks");
                vector<float> *THINjetTrackPt = data.GetPtrVectorFloat("st_THINjetTrackPt");
                vector<float> *THINjetTrackEta = data.GetPtrVectorFloat("st_THINjetTrackEta");
                vector<float> *THINjetTrackPhi = data.GetPtrVectorFloat("st_THINjetTrackPhi");

                vector<float> *THINjetTrackdz = data.GetPtrVectorFloat("st_THINjetTrackdz");
                vector<float> *THINjetTrackdzError = data.GetPtrVectorFloat("st_THINjetTrackdzError");
                vector<float> *THINjetTrackdxy = data.GetPtrVectorFloat("st_THINjetTrackdxy");
                vector<float> *THINjetTrackdxyError = data.GetPtrVectorFloat("st_THINjetTrackdxyError");
                vector<int> *THINjetTrackStatus = data.GetPtrVectorInt("st_THINjetTrackStatus");

                vector<float> *THINjet3Dsignificance = data.GetPtrVectorFloat("THINjet3Dsignificance");

                vector<float> *THINjetLog10_of_3Dsignificance = data.GetPtrVectorFloat("THINjetLog10_of_3Dsignificance"); //, nTHINjets);
                Float_t *THINjetAlpha3D = data.GetPtrFloat("THINjetAlpha3D");
                Float_t *THINjetSumTrackPt = data.GetPtrFloat("THINjetSumTrackPt");
                Float_t *THINjetSumTrackPt_cutLog10_3Dsig = data.GetPtrFloat("THINjetSumTrackPt_cutLog10_3Dsig");
                Float_t *THINjetCISVv2 = data.GetPtrFloat("st_THINjetCISVV2");
                Float_t *THINjetDeepCSV = data.GetPtrFloat("st_THINjetDeepCSV");

                int emergTrackMultiplicity;

                vector<float> temp_passJetAlpha3D;
                vector<float> temp_passJetCISVv2;
                vector<float> temp_passJetDeepCSV;

                vector<float> temp_passTrack3Dsig;
                vector<float> temp_emergTrackPt;
                vector<float> temp_emergTrackEta;
                vector<float> temp_emergTrackPhi;
                vector<float> temp_emergTrackdR;

                vector<float> temp_emergTrackdz;
                vector<float> temp_emergTrackdzerror;
                vector<float> temp_emergTrackdxy;
                vector<float> temp_emergTrackdxyerror;

                temp_passJetAlpha3D.clear();

                for (int iak4j = 0; iak4j < nTHINjets; iak4j++)
                {
                    temp_passTrack3Dsig.clear();
                    temp_emergTrackPt.clear();
                    temp_emergTrackEta.clear();
                    temp_emergTrackPhi.clear();
                    temp_emergTrackdR.clear();

                    temp_emergTrackdz.clear();
                    temp_emergTrackdzerror.clear();
                    temp_emergTrackdxy.clear();
                    temp_emergTrackdxyerror.clear();

                    emergTrackMultiplicity = THINjetNTracks[iak4j];

                    temp_passJetAlpha3D.push_back(THINjetAlpha3D[iak4j]);
                    temp_passJetCISVv2.push_back(THINjetCISVv2[iak4j]);
                    temp_passJetDeepCSV.push_back(THINjetDeepCSV[iak4j]);

                    for (int it = 0; it < THINjetNTracks[iak4j]; it++)
                    {
                        float emergTrackPt = THINjetTrackPt[iak4j][it];
                        float emergTrackEta = THINjetTrackEta[iak4j][it];
                        float emergTrackPhi = THINjetTrackPhi[iak4j][it];
                        TLorentzVector *thisJet = new TLorentzVector(THINjetPx[iak4j], THINjetPy[iak4j], THINjetPz[iak4j], THINjetEnergy[iak4j]);
                        float ak4JetEta = thisJet->Eta();
                        float ak4JetPhi = thisJet->Phi();
                        float deta = ak4JetEta - emergTrackEta;
                        float dphi = ak4JetPhi - emergTrackPhi;
                        while (dphi > TMath::Pi())
                            dphi -= 2 * TMath::Pi();
                        while (dphi <= -TMath::Pi())
                            dphi += 2 * TMath::Pi();
                        float dR = sqrt(deta * deta + dphi * dphi);
                        // save dR in vector
                        temp_emergTrackPt.push_back(emergTrackPt);
                        temp_emergTrackEta.push_back(emergTrackEta);
                        temp_emergTrackPhi.push_back(emergTrackPhi);
                        temp_emergTrackdR.push_back(dR);

                        // Save trk impact paremeter
                        float Trk_dz = THINjetTrackdz[iak4j][it];
                        float Trk_dzerror = THINjetTrackdzError[iak4j][it];
                        float Trk_dxy = THINjetTrackdxy[iak4j][it];
                        float Trk_dxyerror = THINjetTrackdxyError[iak4j][it];

                        temp_emergTrackdz.push_back(Trk_dz);
                        temp_emergTrackdzerror.push_back(Trk_dzerror);
                        temp_emergTrackdxy.push_back(Trk_dxy);
                        temp_emergTrackdxyerror.push_back(Trk_dxyerror);

                        /*For alpha3D*/
                        float displacedTrack3Dsig = THINjet3Dsignificance[iak4j][it];
                        temp_passTrack3Dsig.push_back(displacedTrack3Dsig);
                    }
                    v_TrkPT.insert(v_TrkPT.end(), temp_emergTrackPt.begin(), temp_emergTrackPt.end());
                    v_Trk_dz.insert(v_Trk_dz.end(), temp_emergTrackdz.begin(), temp_emergTrackdz.end());
                    v_Trk_dzerror.insert(v_Trk_dzerror.end(), temp_emergTrackdzerror.begin(), temp_emergTrackdzerror.end());
                    v_Trk_dxy.insert(v_Trk_dxy.end(), temp_emergTrackdxy.begin(), temp_emergTrackdxy.end());
                    v_Trk_dxyerror.insert(v_Trk_dxyerror.end(), temp_emergTrackdxyerror.begin(), temp_emergTrackdxyerror.end());
                    /*For displaced var*/
                    //v_passJetAlpha3D.insert(v_passJetAlpha3D.end(), temp_passJetAlpha3D.begin(), temp_passJetAlpha3D.end());
                    v_nPassthinJetCSVv2.insert(v_nPassthinJetCSVv2.end(), temp_passJetCISVv2.begin(), temp_passJetCISVv2.end());
                    v_nPassthinJetDeepCsv.insert(v_nPassthinJetDeepCsv.end(), temp_passJetDeepCSV.begin(), temp_passJetDeepCSV.end());

                } // end of ak4jet loop for emerg track (emerg jet)

                I_event = jEntry;
                I_weight = eventWeight;

                f_Met = met;


                T_tree->Fill();
            } // End of rece EE
        }     // End of loop all files
    }         // End of all files loop

    outFile->cd();
    T_tree->Write();
    outFile->Close();
    cout << "output written to " << outputfile << endl;
} // Big Scope End
