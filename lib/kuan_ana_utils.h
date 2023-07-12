#ifndef KUAN_ANA_UTIL_H
#define KUAN_ANA_UTIL_H

/*declare function*/
double punzi(double sigeff, double bg);

class MergeBFiles
{
public:
    TFile *ee_DYincli,
        *ee_DYHT100,
        *ee_DYHT200,
        *ee_DYHT400,
        *ee_DYHT600,
        *ee_DYHT800,
        *ee_DYHT1200,
        *ee_DYHT2500;

    TFile *uu_DYincli,
        *uu_DYHT100,
        *uu_DYHT200,
        *uu_DYHT400,
        *uu_DYHT600,
        *uu_DYHT800,
        *uu_DYHT1200,
        *uu_DYHT2500;

    TFile *ee_TTTo2L2Nufile,
        *ee_Top_TTWJetsToLNufile,
        *ee_Top_TTWJetsToQQfile,
        *ee_Top_TTZToQQfile,
        *ee_Top_TTZToLLNuNufile,
        *ee_Top_tW_antitopfile,
        *ee_Top_tW_topfile;

    TFile *emu_TTTo2L2Nufile,
        *emu_Top_TTWJetsToLNufile,
        *emu_Top_TTWJetsToQQfile,
        *emu_Top_TTZToQQfile,
        *emu_Top_TTZToLLNuNufile,
        *emu_Top_tW_antitopfile,
        *emu_Top_tW_topfile;

    TFile *uu_TTTo2L2Nufile,
        *uu_Top_TTWJetsToLNufile,
        *uu_Top_TTWJetsToQQfile,
        *uu_Top_TTZToQQfile,
        *uu_Top_TTZToLLNuNufile,
        *uu_Top_tW_antitopfile,
        *uu_Top_tW_topfile;

    TFile *ee_diboson_gg_ZZ_2e2mu,
        *ee_diboson_gg_ZZ_2e2nu,
        *ee_diboson_gg_ZZ_2e2tau,
        *ee_diboson_gg_ZZ_2mu2nu,
        *ee_diboson_gg_ZZ_2mu2tau,
        *ee_diboson_gg_ZZ_4e,
        *ee_diboson_gg_ZZ_4mu,
        *ee_diboson_gg_ZZ_4tau,
        *ee_diboson_gg_WW_2L2Nu,
        *ee_diboson_qq_WW_2L2Nu,
        *ee_diboson_qq_WZ_2L2Q,
        *ee_diboson_qq_WZ_3LNu,
        *ee_diboson_qq_ZZ_2L2Nu,
        *ee_diboson_qq_ZZ_2L2Q,
        *ee_diboson_qq_ZZ_4L;

    TFile *uu_diboson_gg_ZZ_2e2mu,
        *uu_diboson_gg_ZZ_2e2nu,
        *uu_diboson_gg_ZZ_2e2tau,
        *uu_diboson_gg_ZZ_2mu2nu,
        *uu_diboson_gg_ZZ_2mu2tau,
        *uu_diboson_gg_ZZ_4e,
        *uu_diboson_gg_ZZ_4mu,
        *uu_diboson_gg_ZZ_4tau,
        *uu_diboson_gg_WW_2L2Nu,
        *uu_diboson_qq_WW_2L2Nu,
        *uu_diboson_qq_WZ_2L2Q,
        *uu_diboson_qq_WZ_3LNu,
        *uu_diboson_qq_ZZ_2L2Nu,
        *uu_diboson_qq_ZZ_2L2Q,
        *uu_diboson_qq_ZZ_4L;

    /*For Tri-boson process*/
    TFile *ee_triboson_WWZfile,
        *ee_triboson_WZZfile,
        *ee_triboson_ZZZfile;

    TFile *uu_triboson_WWZfile,
        *uu_triboson_WZZfile,
        *uu_triboson_ZZZfile;

    MergeBFiles(const char *dirMerge = "/home/kuanyu/Documents/root_file");
    ~MergeBFiles();
};

class MergeWeight
{
public:
    MergeWeight(MergeBFiles *files);

    /*For  Drell-yan*/
    double ee_HT0Weight, ee_HT70Weight, ee_HT100Weight, ee_HT200Weight, ee_HT400Weight,
        ee_HT600Weight, ee_HT800Weight, ee_HT1200Weight, ee_HT2500Weight;

    double uu_HT0Weight, uu_HT70Weight, uu_HT100Weight, uu_HT200Weight, uu_HT400Weight,
        uu_HT600Weight, uu_HT800Weight, uu_HT1200Weight, uu_HT2500Weight;

    /*For Top process*/
    double ee_TTTo2L2NuWeight, ee_ST_tW_topWeight, ee_ST_tW_antitopWeight, ee_TTWJetsToLNuWeight,
        ee_TTWJetsToQQWeight, ee_TTZToQQWeight, ee_TTZToLLNuNuWeight;

    double uu_TTTo2L2NuWeight, uu_ST_tW_topWeight, uu_ST_tW_antitopWeight, uu_TTWJetsToLNuWeight,
        uu_TTWJetsToQQWeight, uu_TTZToQQWeight, uu_TTZToLLNuNuWeight;

    /*For Top emu process*/
    double emu_TTTo2L2NuWeight, emu_ST_tW_topWeight, emu_ST_tW_antitopWeight, emu_TTWJetsToLNuWeight,
        emu_TTWJetsToQQWeight, emu_TTZToQQWeight, emu_TTZToLLNuNuWeight;

    /*For Di-boson*/
    double ee_diboson_gg_ZZ_2e2mu_Weight, ee_diboson_gg_ZZ_2e2nu_Weight, ee_diboson_gg_ZZ_2e2tau_Weight,
        ee_diboson_gg_ZZ_2mu2nu_Weight, ee_diboson_gg_ZZ_2mu2tau_Weight, ee_diboson_gg_ZZ_4e_Weight, ee_diboson_gg_ZZ_4mu_Weight,
        ee_diboson_gg_ZZ_4tau_Weight, ee_diboson_gg_WW_2L2Nu_Weight, ee_diboson_qq_WW_2L2Nu_Weight, ee_diboson_qq_WZ_2L2Q_Weight,
        ee_diboson_qq_WZ_3LNu_Weight, ee_diboson_qq_ZZ_2L2Nu_Weight, ee_diboson_qq_ZZ_2L2Q_Weight, ee_diboson_qq_ZZ_4L_Weight;

    double uu_diboson_gg_ZZ_2e2mu_Weight, uu_diboson_gg_ZZ_2e2nu_Weight, uu_diboson_gg_ZZ_2e2tau_Weight,
        uu_diboson_gg_ZZ_2mu2nu_Weight, uu_diboson_gg_ZZ_2mu2tau_Weight, uu_diboson_gg_ZZ_4e_Weight, uu_diboson_gg_ZZ_4mu_Weight,
        uu_diboson_gg_ZZ_4tau_Weight, uu_diboson_gg_WW_2L2Nu_Weight, uu_diboson_qq_WW_2L2Nu_Weight, uu_diboson_qq_WZ_2L2Q_Weight,
        uu_diboson_qq_WZ_3LNu_Weight, uu_diboson_qq_ZZ_2L2Nu_Weight, uu_diboson_qq_ZZ_2L2Q_Weight, uu_diboson_qq_ZZ_4L_Weight;

    /*For Tri-boson*/
    double ee_WWZWeight, ee_WZZWeight, ee_ZZZWeight;

    double uu_WWZWeight, uu_WZZWeight, uu_ZZZWeight;
};

void ee_for_inclusive_sample(double HT, double i_tmp, MergeWeight merge_weight, double eventWeight, TH1D *h_tmp);

void uu_for_inclusive_sample(double HT, double i_tmp, MergeWeight merge_weight, double eventWeight, TH1D *h_tmp);

/*Implenentation*/
#ifndef KUAN_ANA_UTIL_NOIMPL
#include <TMath.h>
#include <TString.h>
#include "Cross_section.h"

double punzi(double sigeff, double bg)
{
    return sigeff / (1 + TMath::Power(abs(bg), 0.5));
}
MergeBFiles::MergeBFiles(const char *dirMerge)
{
    /*For Drell-Yan process*/
    this->ee_DYincli = TFile::Open(Form("%s/%s", dirMerge, "Ztoee/2016BKGMC/DY/ee_DYincli_nocut.root"));
    this->ee_DYHT100 = TFile::Open(Form("%s/%s", dirMerge, "Ztoee/2016BKGMC/DY/ee_ht100.root"));
    this->ee_DYHT200 = TFile::Open(Form("%s/%s", dirMerge, "Ztoee/2016BKGMC/DY/ee_ht200.root"));
    this->ee_DYHT400 = TFile::Open(Form("%s/%s", dirMerge, "Ztoee/2016BKGMC/DY/ee_ht400.root"));
    this->ee_DYHT600 = TFile::Open(Form("%s/%s", dirMerge, "Ztoee/2016BKGMC/DY/ee_ht600.root"));
    this->ee_DYHT800 = TFile::Open(Form("%s/%s", dirMerge, "Ztoee/2016BKGMC/DY/ee_ht800.root"));
    this->ee_DYHT1200 = TFile::Open(Form("%s/%s", dirMerge, "Ztoee/2016BKGMC/DY/ee_ht1200.root"));
    this->ee_DYHT2500 = TFile::Open(Form("%s/%s", dirMerge, "Ztoee/2016BKGMC/DY/ee_ht2500.root"));

    this->uu_DYincli = TFile::Open(Form("%s/%s", dirMerge, "Ztouu/2016BKGMC/DY/uu_DYincli.root"));
    this->uu_DYHT100 = TFile::Open(Form("%s/%s", dirMerge, "Ztouu/2016BKGMC/DY/uu_ht100.root"));
    this->uu_DYHT200 = TFile::Open(Form("%s/%s", dirMerge, "Ztouu/2016BKGMC/DY/uu_ht200.root"));
    this->uu_DYHT400 = TFile::Open(Form("%s/%s", dirMerge, "Ztouu/2016BKGMC/DY/uu_ht400.root"));
    this->uu_DYHT600 = TFile::Open(Form("%s/%s", dirMerge, "Ztouu/2016BKGMC/DY/uu_ht600.root"));
    this->uu_DYHT800 = TFile::Open(Form("%s/%s", dirMerge, "Ztouu/2016BKGMC/DY/uu_ht800.root"));
    this->uu_DYHT1200 = TFile::Open(Form("%s/%s", dirMerge, "Ztouu/2016BKGMC/DY/uu_ht1200.root"));
    this->uu_DYHT2500 = TFile::Open(Form("%s/%s", dirMerge, "Ztouu/2016BKGMC/DY/uu_ht2500.root"));

    /*For Top process*/
    this->ee_TTTo2L2Nufile = TFile::Open(Form("%s/%s", dirMerge, "Ztoee/2016BKGMC/top/ee_top_TTTo2L2Nu.root"));
    this->ee_Top_TTWJetsToLNufile = TFile::Open(Form("%s/%s", dirMerge, "Ztoee/2016BKGMC/top/ee_top_TTWJetsToLNu.root"));
    this->ee_Top_TTWJetsToQQfile = TFile::Open(Form("%s/%s", dirMerge, "Ztoee/2016BKGMC/top/ee_top_TTWJetsToQQ.root"));
    this->ee_Top_TTZToQQfile = TFile::Open(Form("%s/%s", dirMerge, "Ztoee/2016BKGMC/top/ee_top_TTZToQQ.root"));
    this->ee_Top_TTZToLLNuNufile = TFile::Open(Form("%s/%s", dirMerge, "Ztoee/2016BKGMC/top/ee_top_TTZToLLNuNu.root"));
    this->ee_Top_tW_antitopfile = TFile::Open(Form("%s/%s", dirMerge, "Ztoee/2016BKGMC/top/ee_top_tW_antitop.root"));
    this->ee_Top_tW_topfile = TFile::Open(Form("%s/%s", dirMerge, "Ztoee/2016BKGMC/top/ee_top_tW_top.root"));

    this->uu_TTTo2L2Nufile = TFile::Open(Form("%s/%s", dirMerge, "Ztouu/2016BKGMC/top/uu_top_TTTo2L2Nu.root"));
    this->uu_Top_TTWJetsToLNufile = TFile::Open(Form("%s/%s", dirMerge, "Ztouu/2016BKGMC/top/uu_top_TTWJetsToLNu.root"));
    this->uu_Top_TTWJetsToQQfile = TFile::Open(Form("%s/%s", dirMerge, "Ztouu/2016BKGMC/top/uu_top_TTWJetsToQQ.root"));
    this->uu_Top_TTZToQQfile = TFile::Open(Form("%s/%s", dirMerge, "Ztouu/2016BKGMC/top/uu_top_TTZToQQ.root"));
    this->uu_Top_TTZToLLNuNufile = TFile::Open(Form("%s/%s", dirMerge, "Ztouu/2016BKGMC/top/uu_top_TTZToLLNuNu.root"));
    this->uu_Top_tW_antitopfile = TFile::Open(Form("%s/%s", dirMerge, "Ztouu/2016BKGMC/top/uu_top_tW_antitop.root"));
    this->uu_Top_tW_topfile = TFile::Open(Form("%s/%s", dirMerge, "Ztouu/2016BKGMC/top/uu_top_tW_top.root"));

    this->emu_TTTo2L2Nufile = TFile::Open(Form("%s/%s", dirMerge, "Ztoemu/2016BKGMC/top/eu_top_emu_TTTo2L2Nu.root"));
    this->emu_Top_TTWJetsToLNufile = TFile::Open(Form("%s/%s", dirMerge, "Ztoemu/2016BKGMC/top/eu_top_emu_TTWJetsToLNu.root"));
    this->emu_Top_TTWJetsToQQfile = TFile::Open(Form("%s/%s", dirMerge, "Ztoemu/2016BKGMC/top/eu_top_emu_TTWJetsToQQ.root"));
    this->emu_Top_TTZToQQfile = TFile::Open(Form("%s/%s", dirMerge, "Ztoemu/2016BKGMC/top/eu_top_emu_TTZToQQ.root"));
    this->emu_Top_TTZToLLNuNufile = TFile::Open(Form("%s/%s", dirMerge, "Ztoemu/2016BKGMC/top/eu_top_emu_TTZToLLNuNu.root"));
    this->emu_Top_tW_antitopfile = TFile::Open(Form("%s/%s", dirMerge, "Ztoemu/2016BKGMC/top/eu_top_emu_tW_antitop.root"));
    this->emu_Top_tW_topfile = TFile::Open(Form("%s/%s", dirMerge, "Ztoemu/2016BKGMC/top/eu_top_emu_tW_top.root"));

    /*For Di-boson process*/
    this->ee_diboson_gg_ZZ_2e2mu = TFile::Open(Form("%s/%s", dirMerge, "Ztoee/2016BKGMC/diboson/ee_diboson_gg_ZZ_2e2mu.root"));
    this->ee_diboson_gg_ZZ_2e2nu = TFile::Open(Form("%s/%s", dirMerge, "Ztoee/2016BKGMC/diboson/ee_diboson_gg_ZZ_2e2nu.root"));
    this->ee_diboson_gg_ZZ_2e2tau = TFile::Open(Form("%s/%s", dirMerge, "Ztoee/2016BKGMC/diboson/ee_diboson_gg_ZZ_2e2tau.root"));
    this->ee_diboson_gg_ZZ_2mu2nu = TFile::Open(Form("%s/%s", dirMerge, "Ztoee/2016BKGMC/diboson/ee_diboson_gg_ZZ_2mu2nu.root"));
    this->ee_diboson_gg_ZZ_2mu2tau = TFile::Open(Form("%s/%s", dirMerge, "Ztoee/2016BKGMC/diboson/ee_diboson_gg_ZZ_2mu2tau.root"));
    this->ee_diboson_gg_ZZ_4e = TFile::Open(Form("%s/%s", dirMerge, "Ztoee/2016BKGMC/diboson/ee_diboson_gg_ZZ_4e.root"));
    this->ee_diboson_gg_ZZ_4mu = TFile::Open(Form("%s/%s", dirMerge, "Ztoee/2016BKGMC/diboson/ee_diboson_gg_ZZ_4mu.root"));
    this->ee_diboson_gg_ZZ_4tau = TFile::Open(Form("%s/%s", dirMerge, "Ztoee/2016BKGMC/diboson/ee_diboson_gg_ZZ_4tau.root"));
    this->ee_diboson_gg_WW_2L2Nu = TFile::Open(Form("%s/%s", dirMerge, "Ztoee/2016BKGMC/diboson/ee_diboson_gg_WW_2L2Nu.root"));
    this->ee_diboson_qq_WW_2L2Nu = TFile::Open(Form("%s/%s", dirMerge, "Ztoee/2016BKGMC/diboson/ee_diboson_qq_WW_2L2Nu.root"));
    this->ee_diboson_qq_WZ_2L2Q = TFile::Open(Form("%s/%s", dirMerge, "Ztoee/2016BKGMC/diboson/ee_diboson_qq_WZ_2L2Q.root"));
    this->ee_diboson_qq_WZ_3LNu = TFile::Open(Form("%s/%s", dirMerge, "Ztoee/2016BKGMC/diboson/ee_diboson_qq_WZ_3LNu.root"));
    this->ee_diboson_qq_ZZ_2L2Nu = TFile::Open(Form("%s/%s", dirMerge, "Ztoee/2016BKGMC/diboson/ee_diboson_qq_ZZ_2L2Nu.root"));
    this->ee_diboson_qq_ZZ_2L2Q = TFile::Open(Form("%s/%s", dirMerge, "Ztoee/2016BKGMC/diboson/ee_diboson_qq_ZZ_2L2Q.root"));
    this->ee_diboson_qq_ZZ_4L = TFile::Open(Form("%s/%s", dirMerge, "Ztoee/2016BKGMC/diboson/ee_diboson_qq_ZZ_4L.root"));

    this->uu_diboson_gg_ZZ_2e2mu = TFile::Open(Form("%s/%s", dirMerge, "Ztouu/2016BKGMC/diboson/uu_diboson_gg_ZZ_2e2mu.root"));
    this->uu_diboson_gg_ZZ_2e2nu = TFile::Open(Form("%s/%s", dirMerge, "Ztouu/2016BKGMC/diboson/uu_diboson_gg_ZZ_2e2nu.root"));
    this->uu_diboson_gg_ZZ_2e2tau = TFile::Open(Form("%s/%s", dirMerge, "Ztouu/2016BKGMC/diboson/uu_diboson_gg_ZZ_2e2tau.root"));
    this->uu_diboson_gg_ZZ_2mu2nu = TFile::Open(Form("%s/%s", dirMerge, "Ztouu/2016BKGMC/diboson/uu_diboson_gg_ZZ_2mu2nu.root"));
    this->uu_diboson_gg_ZZ_2mu2tau = TFile::Open(Form("%s/%s", dirMerge, "Ztouu/2016BKGMC/diboson/uu_diboson_gg_ZZ_2mu2tau.root"));
    this->uu_diboson_gg_ZZ_4e = TFile::Open(Form("%s/%s", dirMerge, "Ztouu/2016BKGMC/diboson/uu_diboson_gg_ZZ_4e.root"));
    this->uu_diboson_gg_ZZ_4mu = TFile::Open(Form("%s/%s", dirMerge, "Ztouu/2016BKGMC/diboson/uu_diboson_gg_ZZ_4mu.root"));
    this->uu_diboson_gg_ZZ_4tau = TFile::Open(Form("%s/%s", dirMerge, "Ztouu/2016BKGMC/diboson/uu_diboson_gg_ZZ_4tau.root"));
    this->uu_diboson_gg_WW_2L2Nu = TFile::Open(Form("%s/%s", dirMerge, "Ztouu/2016BKGMC/diboson/uu_diboson_gg_WW_2L2Nu.root"));
    this->uu_diboson_qq_WW_2L2Nu = TFile::Open(Form("%s/%s", dirMerge, "Ztouu/2016BKGMC/diboson/uu_diboson_qq_WW_2L2Nu.root"));
    this->uu_diboson_qq_WZ_2L2Q = TFile::Open(Form("%s/%s", dirMerge, "Ztouu/2016BKGMC/diboson/uu_diboson_qq_WZ_2L2Q.root"));
    this->uu_diboson_qq_WZ_3LNu = TFile::Open(Form("%s/%s", dirMerge, "Ztouu/2016BKGMC/diboson/uu_diboson_qq_WZ_3LNu.root"));
    this->uu_diboson_qq_ZZ_2L2Nu = TFile::Open(Form("%s/%s", dirMerge, "Ztouu/2016BKGMC/diboson/uu_diboson_qq_ZZ_2L2Nu.root"));
    this->uu_diboson_qq_ZZ_2L2Q = TFile::Open(Form("%s/%s", dirMerge, "Ztouu/2016BKGMC/diboson/uu_diboson_qq_ZZ_2L2Q.root"));
    this->uu_diboson_qq_ZZ_4L = TFile::Open(Form("%s/%s", dirMerge, "Ztouu/2016BKGMC/diboson/uu_diboson_qq_ZZ_4L.root"));

    /*For Tri-boson process*/
    this->ee_triboson_WWZfile = TFile::Open(Form("%s/%s", dirMerge, "Ztoee/2016BKGMC/triboson/ee_triboson_WWZ.root"));
    this->ee_triboson_WZZfile = TFile::Open(Form("%s/%s", dirMerge, "Ztoee/2016BKGMC/triboson/ee_triboson_WZZ.root"));
    this->ee_triboson_ZZZfile = TFile::Open(Form("%s/%s", dirMerge, "Ztoee/2016BKGMC/triboson/ee_triboson_ZZZ.root"));

    this->uu_triboson_WWZfile = TFile::Open(Form("%s/%s", dirMerge, "Ztouu/2016BKGMC/triboson/uu_triboson_WWZ.root"));
    this->uu_triboson_WZZfile = TFile::Open(Form("%s/%s", dirMerge, "Ztouu/2016BKGMC/triboson/uu_triboson_WZZ.root"));
    this->uu_triboson_ZZZfile = TFile::Open(Form("%s/%s", dirMerge, "Ztouu/2016BKGMC/triboson/uu_triboson_ZZZ.root"));
}

MergeBFiles::~MergeBFiles()
{
    this->ee_DYincli->Close();
    this->ee_DYHT100->Close();
    this->ee_DYHT200->Close();
    this->ee_DYHT400->Close();
    this->ee_DYHT600->Close();
    this->ee_DYHT800->Close();
    this->ee_DYHT1200->Close();
    this->ee_DYHT2500->Close();

    this->uu_DYincli->Close();
    this->uu_DYHT100->Close();
    this->uu_DYHT200->Close();
    this->uu_DYHT400->Close();
    this->uu_DYHT600->Close();
    this->uu_DYHT800->Close();
    this->uu_DYHT1200->Close();
    this->uu_DYHT2500->Close();

    this->ee_TTTo2L2Nufile->Close();
    this->ee_Top_TTWJetsToLNufile->Close();
    this->ee_Top_TTWJetsToQQfile->Close();
    this->ee_Top_TTZToQQfile->Close();
    this->ee_Top_TTZToLLNuNufile->Close();
    this->ee_Top_tW_antitopfile->Close();
    this->ee_Top_tW_topfile->Close();

    this->emu_TTTo2L2Nufile->Close();
    this->emu_Top_TTWJetsToLNufile->Close();
    this->emu_Top_TTWJetsToQQfile->Close();
    this->emu_Top_TTZToQQfile->Close();
    this->emu_Top_TTZToLLNuNufile->Close();
    this->emu_Top_tW_antitopfile->Close();
    this->emu_Top_tW_topfile->Close();

    this->uu_TTTo2L2Nufile->Close();
    this->uu_Top_TTWJetsToLNufile->Close();
    this->uu_Top_TTWJetsToQQfile->Close();
    this->uu_Top_TTZToQQfile->Close();
    this->uu_Top_TTZToLLNuNufile->Close();
    this->uu_Top_tW_antitopfile->Close();
    this->uu_Top_tW_topfile->Close();

    this->ee_diboson_gg_ZZ_2e2mu->Close();
    this->ee_diboson_gg_ZZ_2e2nu->Close();
    this->ee_diboson_gg_ZZ_2e2tau->Close();
    this->ee_diboson_gg_ZZ_2mu2nu->Close();
    this->ee_diboson_gg_ZZ_2mu2tau->Close();
    this->ee_diboson_gg_ZZ_4e->Close();
    this->ee_diboson_gg_ZZ_4mu->Close();
    this->ee_diboson_gg_ZZ_4tau->Close();
    this->ee_diboson_gg_WW_2L2Nu->Close();
    this->ee_diboson_qq_WW_2L2Nu->Close();
    this->ee_diboson_qq_WZ_2L2Q->Close();
    this->ee_diboson_qq_WZ_3LNu->Close();
    this->ee_diboson_qq_ZZ_2L2Nu->Close();
    this->ee_diboson_qq_ZZ_2L2Q->Close();
    this->ee_diboson_qq_ZZ_4L->Close();

    this->uu_diboson_gg_ZZ_2e2mu->Close();
    this->uu_diboson_gg_ZZ_2e2nu->Close();
    this->uu_diboson_gg_ZZ_2e2tau->Close();
    this->uu_diboson_gg_ZZ_2mu2nu->Close();
    this->uu_diboson_gg_ZZ_2mu2tau->Close();
    this->uu_diboson_gg_ZZ_4e->Close();
    this->uu_diboson_gg_ZZ_4mu->Close();
    this->uu_diboson_gg_ZZ_4tau->Close();
    this->uu_diboson_gg_WW_2L2Nu->Close();
    this->uu_diboson_qq_WW_2L2Nu->Close();
    this->uu_diboson_qq_WZ_2L2Q->Close();
    this->uu_diboson_qq_WZ_3LNu->Close();
    this->uu_diboson_qq_ZZ_2L2Nu->Close();
    this->uu_diboson_qq_ZZ_2L2Q->Close();
    this->uu_diboson_qq_ZZ_4L->Close();

    this->ee_triboson_WWZfile->Close();
    this->ee_triboson_WZZfile->Close();
    this->ee_triboson_ZZZfile->Close();

    this->uu_triboson_WWZfile->Close();
    this->uu_triboson_WZZfile->Close();
    this->uu_triboson_ZZZfile->Close();
}

/*Calculate Weight*/
MergeWeight::MergeWeight(MergeBFiles *files)
{
    TH1F *ee_h_HT_eventCout = files->ee_DYincli->Get<TH1F>("Event_Variable/h_HT_eventCout");
    TH1D *ee_DYHT100_sumevt = files->ee_DYHT100->Get<TH1D>("Event_Variable/h_totevent");
    TH1D *ee_DYHT200_sumevt = files->ee_DYHT200->Get<TH1D>("Event_Variable/h_totevent");
    TH1D *ee_DYHT400_sumevt = files->ee_DYHT400->Get<TH1D>("Event_Variable/h_totevent");
    TH1D *ee_DYHT600_sumevt = files->ee_DYHT600->Get<TH1D>("Event_Variable/h_totevent");
    TH1D *ee_DYHT800_sumevt = files->ee_DYHT800->Get<TH1D>("Event_Variable/h_totevent");
    TH1D *ee_DYHT1200_sumevt = files->ee_DYHT1200->Get<TH1D>("Event_Variable/h_totevent");
    TH1D *ee_DYHT2500_sumevt = files->ee_DYHT2500->Get<TH1D>("Event_Variable/h_totevent");

    TH1F *uu_h_HT_eventCout = files->uu_DYincli->Get<TH1F>("Event_Variable/h_HT_eventCout");
    TH1D *uu_DYHT100_sumevt = files->uu_DYHT100->Get<TH1D>("Event_Variable/h_totevent");
    TH1D *uu_DYHT200_sumevt = files->uu_DYHT200->Get<TH1D>("Event_Variable/h_totevent");
    TH1D *uu_DYHT400_sumevt = files->uu_DYHT400->Get<TH1D>("Event_Variable/h_totevent");
    TH1D *uu_DYHT600_sumevt = files->uu_DYHT600->Get<TH1D>("Event_Variable/h_totevent");
    TH1D *uu_DYHT800_sumevt = files->uu_DYHT800->Get<TH1D>("Event_Variable/h_totevent");
    TH1D *uu_DYHT1200_sumevt = files->uu_DYHT1200->Get<TH1D>("Event_Variable/h_totevent");
    TH1D *uu_DYHT2500_sumevt = files->uu_DYHT2500->Get<TH1D>("Event_Variable/h_totevent");

    TH1D *ee_TTTo2L2Nu_sumevt = files->ee_TTTo2L2Nufile->Get<TH1D>("Event_Variable/h_totevent");
    TH1D *ee_TTWJetsToLNu_sumevt = files->ee_Top_TTWJetsToLNufile->Get<TH1D>("Event_Variable/h_totevent");
    TH1D *ee_TTWJetsToQQ_sumevt = files->ee_Top_TTWJetsToQQfile->Get<TH1D>("Event_Variable/h_totevent");
    TH1D *ee_TTZToQQ_sumevt = files->ee_Top_TTZToQQfile->Get<TH1D>("Event_Variable/h_totevent");
    TH1D *ee_TTZToLLNuNu_sumevt = files->ee_Top_TTZToLLNuNufile->Get<TH1D>("Event_Variable/h_totevent");
    TH1D *ee_tW_antitop_sumevt = files->ee_Top_tW_antitopfile->Get<TH1D>("Event_Variable/h_totevent");
    TH1D *ee_tW_top_sumevt = files->ee_Top_tW_topfile->Get<TH1D>("Event_Variable/h_totevent");

    TH1D *uu_TTTo2L2Nu_sumevt = files->uu_TTTo2L2Nufile->Get<TH1D>("Event_Variable/h_totevent");
    TH1D *uu_TTWJetsToLNu_sumevt = files->uu_Top_TTWJetsToLNufile->Get<TH1D>("Event_Variable/h_totevent");
    TH1D *uu_TTWJetsToQQ_sumevt = files->uu_Top_TTWJetsToQQfile->Get<TH1D>("Event_Variable/h_totevent");
    TH1D *uu_TTZToQQ_sumevt = files->uu_Top_TTZToQQfile->Get<TH1D>("Event_Variable/h_totevent");
    TH1D *uu_TTZToLLNuNu_sumevt = files->uu_Top_TTZToLLNuNufile->Get<TH1D>("Event_Variable/h_totevent");
    TH1D *uu_tW_antitop_sumevt = files->uu_Top_tW_antitopfile->Get<TH1D>("Event_Variable/h_totevent");
    TH1D *uu_tW_top_sumevt = files->uu_Top_tW_topfile->Get<TH1D>("Event_Variable/h_totevent");

    TH1D *emu_TTTo2L2Nu_sumevt = files->emu_TTTo2L2Nufile->Get<TH1D>("Event_Variable/h_totevent");
    TH1D *emu_TTWJetsToLNu_sumevt = files->emu_Top_TTWJetsToLNufile->Get<TH1D>("Event_Variable/h_totevent");
    TH1D *emu_TTWJetsToQQ_sumevt = files->emu_Top_TTWJetsToQQfile->Get<TH1D>("Event_Variable/h_totevent");
    TH1D *emu_TTZToQQ_sumevt = files->emu_Top_TTZToQQfile->Get<TH1D>("Event_Variable/h_totevent");
    TH1D *emu_TTZToLLNuNu_sumevt = files->emu_Top_TTZToLLNuNufile->Get<TH1D>("Event_Variable/h_totevent");
    TH1D *emu_tW_antitop_sumevt = files->emu_Top_tW_antitopfile->Get<TH1D>("Event_Variable/h_totevent");
    TH1D *emu_tW_top_sumevt = files->emu_Top_tW_topfile->Get<TH1D>("Event_Variable/h_totevent");

    TH1D *ee_gg_ZZ_2e2mu_sumevt = files->ee_diboson_gg_ZZ_2e2mu->Get<TH1D>("Event_Variable/h_totevent");
    TH1D *ee_gg_ZZ_2e2nu_sumevt = files->ee_diboson_gg_ZZ_2e2nu->Get<TH1D>("Event_Variable/h_totevent");
    TH1D *ee_gg_ZZ_2e2tau_sumevt = files->ee_diboson_gg_ZZ_2e2tau->Get<TH1D>("Event_Variable/h_totevent");
    TH1D *ee_gg_ZZ_2mu2nu_sumevt = files->ee_diboson_gg_ZZ_2mu2nu->Get<TH1D>("Event_Variable/h_totevent");
    TH1D *ee_gg_ZZ_2mu2tau_sumevt = files->ee_diboson_gg_ZZ_2mu2tau->Get<TH1D>("Event_Variable/h_totevent");
    TH1D *ee_gg_ZZ_4e_sumevt = files->ee_diboson_gg_ZZ_4e->Get<TH1D>("Event_Variable/h_totevent");
    TH1D *ee_gg_ZZ_4mu_sumevt = files->ee_diboson_gg_ZZ_4mu->Get<TH1D>("Event_Variable/h_totevent");
    TH1D *ee_gg_ZZ_4tau_sumevt = files->ee_diboson_gg_ZZ_4tau->Get<TH1D>("Event_Variable/h_totevent");
    TH1D *ee_gg_WW_2L2Nu_sumevt = files->ee_diboson_gg_WW_2L2Nu->Get<TH1D>("Event_Variable/h_totevent");
    TH1D *ee_qq_WW_2L2Nu_sumevt = files->ee_diboson_qq_WW_2L2Nu->Get<TH1D>("Event_Variable/h_totevent");
    TH1D *ee_qq_WZ_2L2Q_sumevt = files->ee_diboson_qq_WZ_2L2Q->Get<TH1D>("Event_Variable/h_totevent");
    TH1D *ee_qq_WZ_3LNu_sumevt = files->ee_diboson_qq_WZ_3LNu->Get<TH1D>("Event_Variable/h_totevent");
    TH1D *ee_qq_ZZ_2L2Nu_sumevt = files->ee_diboson_qq_ZZ_2L2Nu->Get<TH1D>("Event_Variable/h_totevent");
    TH1D *ee_qq_ZZ_2L2Q_sumevt = files->ee_diboson_qq_ZZ_2L2Q->Get<TH1D>("Event_Variable/h_totevent");
    TH1D *ee_qq_ZZ_4L_sumevt = files->ee_diboson_qq_ZZ_4L->Get<TH1D>("Event_Variable/h_totevent");

    TH1D *uu_gg_ZZ_2e2mu_sumevt = files->uu_diboson_gg_ZZ_2e2mu->Get<TH1D>("Event_Variable/h_totevent");
    TH1D *uu_gg_ZZ_2e2nu_sumevt = files->uu_diboson_gg_ZZ_2e2nu->Get<TH1D>("Event_Variable/h_totevent");
    TH1D *uu_gg_ZZ_2e2tau_sumevt = files->uu_diboson_gg_ZZ_2e2tau->Get<TH1D>("Event_Variable/h_totevent");
    TH1D *uu_gg_ZZ_2mu2nu_sumevt = files->uu_diboson_gg_ZZ_2mu2nu->Get<TH1D>("Event_Variable/h_totevent");
    TH1D *uu_gg_ZZ_2mu2tau_sumevt = files->uu_diboson_gg_ZZ_2mu2tau->Get<TH1D>("Event_Variable/h_totevent");
    TH1D *uu_gg_ZZ_4e_sumevt = files->uu_diboson_gg_ZZ_4e->Get<TH1D>("Event_Variable/h_totevent");
    TH1D *uu_gg_ZZ_4mu_sumevt = files->uu_diboson_gg_ZZ_4mu->Get<TH1D>("Event_Variable/h_totevent");
    TH1D *uu_gg_ZZ_4tau_sumevt = files->uu_diboson_gg_ZZ_4tau->Get<TH1D>("Event_Variable/h_totevent");
    TH1D *uu_gg_WW_2L2Nu_sumevt = files->uu_diboson_gg_WW_2L2Nu->Get<TH1D>("Event_Variable/h_totevent");
    TH1D *uu_qq_WW_2L2Nu_sumevt = files->uu_diboson_qq_WW_2L2Nu->Get<TH1D>("Event_Variable/h_totevent");
    TH1D *uu_qq_WZ_2L2Q_sumevt = files->uu_diboson_qq_WZ_2L2Q->Get<TH1D>("Event_Variable/h_totevent");
    TH1D *uu_qq_WZ_3LNu_sumevt = files->uu_diboson_qq_WZ_3LNu->Get<TH1D>("Event_Variable/h_totevent");
    TH1D *uu_qq_ZZ_2L2Nu_sumevt = files->uu_diboson_qq_ZZ_2L2Nu->Get<TH1D>("Event_Variable/h_totevent");
    TH1D *uu_qq_ZZ_2L2Q_sumevt = files->uu_diboson_qq_ZZ_2L2Q->Get<TH1D>("Event_Variable/h_totevent");
    TH1D *uu_qq_ZZ_4L_sumevt = files->uu_diboson_qq_ZZ_4L->Get<TH1D>("Event_Variable/h_totevent");

    TH1D *ee_WWZ_sumevt = files->ee_triboson_WWZfile->Get<TH1D>("Event_Variable/h_totevent");
    TH1D *ee_WZZ_sumevt = files->ee_triboson_WZZfile->Get<TH1D>("Event_Variable/h_totevent");
    TH1D *ee_ZZZ_sumevt = files->ee_triboson_ZZZfile->Get<TH1D>("Event_Variable/h_totevent");

    TH1D *uu_WWZ_sumevt = files->uu_triboson_WWZfile->Get<TH1D>("Event_Variable/h_totevent");
    TH1D *uu_WZZ_sumevt = files->uu_triboson_WZZfile->Get<TH1D>("Event_Variable/h_totevent");
    TH1D *uu_ZZZ_sumevt = files->uu_triboson_ZZZfile->Get<TH1D>("Event_Variable/h_totevent");

    int ee_DYHT100_totevt = ee_DYHT100_sumevt->Integral();
    int ee_DYHT200_totevt = ee_DYHT200_sumevt->Integral();
    int ee_DYHT400_totevt = ee_DYHT400_sumevt->Integral();
    int ee_DYHT600_totevt = ee_DYHT600_sumevt->Integral();
    int ee_DYHT800_totevt = ee_DYHT800_sumevt->Integral();
    int ee_DYHT1200_totevt = ee_DYHT1200_sumevt->Integral();
    int ee_DYHT2500_totevt = ee_DYHT2500_sumevt->Integral();

    int uu_DYHT100_totevt = uu_DYHT100_sumevt->Integral();
    int uu_DYHT200_totevt = uu_DYHT200_sumevt->Integral();
    int uu_DYHT400_totevt = uu_DYHT400_sumevt->Integral();
    int uu_DYHT600_totevt = uu_DYHT600_sumevt->Integral();
    int uu_DYHT800_totevt = uu_DYHT800_sumevt->Integral();
    int uu_DYHT1200_totevt = uu_DYHT1200_sumevt->Integral();
    int uu_DYHT2500_totevt = uu_DYHT2500_sumevt->Integral();

    int ee_HT0_70_event = ee_h_HT_eventCout->GetBinContent(2);
    int ee_HT70_100_event = ee_h_HT_eventCout->GetBinContent(3);
    int ee_HT100_200_event = ee_h_HT_eventCout->GetBinContent(4);
    int ee_HT200_400_event = ee_h_HT_eventCout->GetBinContent(5);
    int ee_HT400_600_event = ee_h_HT_eventCout->GetBinContent(6);
    int ee_HT600_800_event = ee_h_HT_eventCout->GetBinContent(7);
    int ee_HT800_1200_event = ee_h_HT_eventCout->GetBinContent(8);
    int ee_HT1200_2500_event = ee_h_HT_eventCout->GetBinContent(9);
    int ee_HT2500_Inf_event = ee_h_HT_eventCout->GetBinContent(10);

    int uu_HT0_70_event = uu_h_HT_eventCout->GetBinContent(2);
    int uu_HT70_100_event = uu_h_HT_eventCout->GetBinContent(3);
    int uu_HT100_200_event = uu_h_HT_eventCout->GetBinContent(4);
    int uu_HT200_400_event = uu_h_HT_eventCout->GetBinContent(5);
    int uu_HT400_600_event = uu_h_HT_eventCout->GetBinContent(6);
    int uu_HT600_800_event = uu_h_HT_eventCout->GetBinContent(7);
    int uu_HT800_1200_event = uu_h_HT_eventCout->GetBinContent(8);
    int uu_HT1200_2500_event = uu_h_HT_eventCout->GetBinContent(9);
    int uu_HT2500_Inf_event = uu_h_HT_eventCout->GetBinContent(10);

    double ee_TTTo2L2Nu_totevt = ee_TTTo2L2Nu_sumevt->Integral();
    double ee_TTWJetsToLNu_totevt = ee_TTWJetsToLNu_sumevt->Integral();
    double ee_TTWJetsToQQ_totevt = ee_TTWJetsToQQ_sumevt->Integral();
    double ee_TTZToQQ_totevt = ee_TTZToQQ_sumevt->Integral();
    double ee_TTZToLLNuNu_totevt = ee_TTZToLLNuNu_sumevt->Integral();
    double ee_tW_antitop_totevt = ee_tW_antitop_sumevt->Integral();
    double ee_tW_top_totevt = ee_tW_top_sumevt->Integral();

    double uu_TTTo2L2Nu_totevt = uu_TTTo2L2Nu_sumevt->Integral();
    double uu_TTWJetsToLNu_totevt = uu_TTWJetsToLNu_sumevt->Integral();
    double uu_TTWJetsToQQ_totevt = uu_TTWJetsToQQ_sumevt->Integral();
    double uu_TTZToQQ_totevt = uu_TTZToQQ_sumevt->Integral();
    double uu_TTZToLLNuNu_totevt = uu_TTZToLLNuNu_sumevt->Integral();
    double uu_tW_antitop_totevt = uu_tW_antitop_sumevt->Integral();
    double uu_tW_top_totevt = uu_tW_top_sumevt->Integral();

    double emu_TTTo2L2Nu_totevt = emu_TTTo2L2Nu_sumevt->Integral();
    double emu_TTWJetsToLNu_totevt = emu_TTWJetsToLNu_sumevt->Integral();
    double emu_TTWJetsToQQ_totevt = emu_TTWJetsToQQ_sumevt->Integral();
    double emu_TTZToQQ_totevt = emu_TTZToQQ_sumevt->Integral();
    double emu_TTZToLLNuNu_totevt = emu_TTZToLLNuNu_sumevt->Integral();
    double emu_tW_antitop_totevt = emu_tW_antitop_sumevt->Integral();
    double emu_tW_top_totevt = emu_tW_top_sumevt->Integral();

    double ee_gg_ZZ_2e2mu_totevt = ee_gg_ZZ_2e2mu_sumevt->Integral();
    double ee_gg_ZZ_2e2nu_totevt = ee_gg_ZZ_2e2nu_sumevt->Integral();
    double ee_gg_ZZ_2e2tau_totevt = ee_gg_ZZ_2e2tau_sumevt->Integral();
    double ee_gg_ZZ_2mu2nu_totevt = ee_gg_ZZ_2mu2nu_sumevt->Integral();
    double ee_gg_ZZ_2mu2tau_totevt = ee_gg_ZZ_2mu2tau_sumevt->Integral();
    double ee_gg_ZZ_4e_totevt = ee_gg_ZZ_4e_sumevt->Integral();
    double ee_gg_ZZ_4mu_totevt = ee_gg_ZZ_4mu_sumevt->Integral();
    double ee_gg_ZZ_4tau_totevt = ee_gg_ZZ_4tau_sumevt->Integral();
    double ee_gg_WW_2L2Nu_totevt = ee_gg_WW_2L2Nu_sumevt->Integral();
    double ee_qq_WW_2L2Nu_totevt = ee_qq_WW_2L2Nu_sumevt->Integral();
    double ee_qq_WZ_2L2Q_totevt = ee_qq_WZ_2L2Q_sumevt->Integral();
    double ee_qq_WZ_3LNu_totevt = ee_qq_WZ_3LNu_sumevt->Integral();
    double ee_qq_ZZ_2L2Nu_totevt = ee_qq_ZZ_2L2Nu_sumevt->Integral();
    double ee_qq_ZZ_2L2Q_totevt = ee_qq_ZZ_2L2Q_sumevt->Integral();
    double ee_qq_ZZ_4L_totevt = ee_qq_ZZ_4L_sumevt->Integral();

    double uu_gg_ZZ_2e2mu_totevt = uu_gg_ZZ_2e2mu_sumevt->Integral();
    double uu_gg_ZZ_2e2nu_totevt = uu_gg_ZZ_2e2nu_sumevt->Integral();
    double uu_gg_ZZ_2e2tau_totevt = uu_gg_ZZ_2e2tau_sumevt->Integral();
    double uu_gg_ZZ_2mu2nu_totevt = uu_gg_ZZ_2mu2nu_sumevt->Integral();
    double uu_gg_ZZ_2mu2tau_totevt = uu_gg_ZZ_2mu2tau_sumevt->Integral();
    double uu_gg_ZZ_4e_totevt = uu_gg_ZZ_4e_sumevt->Integral();
    double uu_gg_ZZ_4mu_totevt = uu_gg_ZZ_4mu_sumevt->Integral();
    double uu_gg_ZZ_4tau_totevt = uu_gg_ZZ_4tau_sumevt->Integral();
    double uu_gg_WW_2L2Nu_totevt = uu_gg_WW_2L2Nu_sumevt->Integral();
    double uu_qq_WW_2L2Nu_totevt = uu_qq_WW_2L2Nu_sumevt->Integral();
    double uu_qq_WZ_2L2Q_totevt = uu_qq_WZ_2L2Q_sumevt->Integral();
    double uu_qq_WZ_3LNu_totevt = uu_qq_WZ_3LNu_sumevt->Integral();
    double uu_qq_ZZ_2L2Nu_totevt = uu_qq_ZZ_2L2Nu_sumevt->Integral();
    double uu_qq_ZZ_2L2Q_totevt = uu_qq_ZZ_2L2Q_sumevt->Integral();
    double uu_qq_ZZ_4L_totevt = uu_qq_ZZ_4L_sumevt->Integral();

    double ee_WWZ_totevt = ee_WWZ_sumevt->Integral();
    double ee_WZZ_totevt = ee_WZZ_sumevt->Integral();
    double ee_ZZZ_totevt = ee_ZZZ_sumevt->Integral();

    double uu_WWZ_totevt = uu_WWZ_sumevt->Integral();
    double uu_WZZ_totevt = uu_WZZ_sumevt->Integral();
    double uu_ZZZ_totevt = uu_ZZZ_sumevt->Integral();
    /*
        this->ee_HT0Weight = (GlobalConstants::Lumi2016) * ((GlobalConstants::HT0CS) / (ee_HT0_70_event)) * 1000;
        this->ee_HT70Weight = (GlobalConstants::Lumi2016) * ((GlobalConstants::HT70CS) / (ee_HT70_100_event)) * 1000;
        this->ee_HT100Weight = (GlobalConstants::Lumi2016) * (GlobalConstants::HT100CS / (ee_DYHT100_totevt + ee_HT100_200_event)) * 1000;
        this->ee_HT200Weight = (GlobalConstants::Lumi2016) * (GlobalConstants::HT200CS / (ee_DYHT200_totevt + ee_HT200_400_event)) * 1000;
        this->ee_HT400Weight = (GlobalConstants::Lumi2016) * (GlobalConstants::HT400CS / (ee_DYHT400_totevt + ee_HT400_600_event)) * 1000;
        this->ee_HT600Weight = (GlobalConstants::Lumi2016) * (GlobalConstants::HT600CS / (ee_DYHT600_totevt + ee_HT600_800_event)) * 1000;
        this->ee_HT800Weight = (GlobalConstants::Lumi2016) * (GlobalConstants::HT800CS / (ee_DYHT800_totevt + ee_HT800_1200_event)) * 1000;
        this->ee_HT1200Weight = (GlobalConstants::Lumi2016) * (GlobalConstants::HT1200CS / (ee_DYHT1200_totevt + ee_HT1200_2500_event)) * 1000;
        this->ee_HT2500Weight = (GlobalConstants::Lumi2016) * (GlobalConstants::HT2500CS / (ee_DYHT2500_totevt + ee_HT2500_Inf_event)) * 1000;
    */
    this->ee_HT0Weight = (GlobalConstants::Lumi2016) * ((GlobalConstants::HT0CS) / (ee_HT0_70_event)) * 1000;
    this->ee_HT70Weight = (GlobalConstants::Lumi2016) * ((GlobalConstants::HT70CS) / (ee_HT70_100_event)) * 1000;
    this->ee_HT100Weight = (GlobalConstants::Lumi2016) * (GlobalConstants::HT100CS / (ee_DYHT100_totevt)) * 1000;
    this->ee_HT200Weight = (GlobalConstants::Lumi2016) * (GlobalConstants::HT200CS / (ee_DYHT200_totevt)) * 1000;
    this->ee_HT400Weight = (GlobalConstants::Lumi2016) * (GlobalConstants::HT400CS / (ee_DYHT400_totevt)) * 1000;
    this->ee_HT600Weight = (GlobalConstants::Lumi2016) * (GlobalConstants::HT600CS / (ee_DYHT600_totevt)) * 1000;
    this->ee_HT800Weight = (GlobalConstants::Lumi2016) * (GlobalConstants::HT800CS / (ee_DYHT800_totevt)) * 1000;
    this->ee_HT1200Weight = (GlobalConstants::Lumi2016) * (GlobalConstants::HT1200CS / (ee_DYHT1200_totevt)) * 1000;
    this->ee_HT2500Weight = (GlobalConstants::Lumi2016) * (GlobalConstants::HT2500CS / (ee_DYHT2500_totevt)) * 1000;

    this->uu_HT0Weight = (GlobalConstants::Lumi2016) * ((GlobalConstants::HT0CS) / (uu_HT0_70_event)) * 1000;
    this->uu_HT70Weight = (GlobalConstants::Lumi2016) * ((GlobalConstants::HT70CS) / (uu_HT70_100_event)) * 1000;
    this->uu_HT100Weight = (GlobalConstants::Lumi2016) * (GlobalConstants::HT100CS / (uu_DYHT100_totevt + uu_HT100_200_event)) * 1000;
    this->uu_HT200Weight = (GlobalConstants::Lumi2016) * (GlobalConstants::HT200CS / (uu_DYHT200_totevt + uu_HT200_400_event)) * 1000;
    this->uu_HT400Weight = (GlobalConstants::Lumi2016) * (GlobalConstants::HT400CS / (uu_DYHT400_totevt + uu_HT400_600_event)) * 1000;
    this->uu_HT600Weight = (GlobalConstants::Lumi2016) * (GlobalConstants::HT600CS / (uu_DYHT600_totevt + uu_HT600_800_event)) * 1000;
    this->uu_HT800Weight = (GlobalConstants::Lumi2016) * (GlobalConstants::HT800CS / (uu_DYHT800_totevt + uu_HT800_1200_event)) * 1000;
    this->uu_HT1200Weight = (GlobalConstants::Lumi2016) * (GlobalConstants::HT1200CS / (uu_DYHT1200_totevt + uu_HT1200_2500_event)) * 1000;
    this->uu_HT2500Weight = (GlobalConstants::Lumi2016) * (GlobalConstants::HT2500CS / (uu_DYHT2500_totevt + uu_HT2500_Inf_event)) * 1000;

    this->ee_TTTo2L2NuWeight = (GlobalConstants::Lumi2016) * ((GlobalConstants::TTTo2L2Nu) / (ee_TTTo2L2Nu_totevt)) * 1000;
    this->ee_ST_tW_topWeight = (GlobalConstants::Lumi2016) * (GlobalConstants::ST_tW_top_5fCS / (ee_tW_top_totevt)) * 1000;
    this->ee_ST_tW_antitopWeight = (GlobalConstants::Lumi2016) * (GlobalConstants::ST_tW_antitop_5fCS / (ee_tW_antitop_totevt)) * 1000;
    this->ee_TTWJetsToLNuWeight = (GlobalConstants::Lumi2016) * (GlobalConstants::TTWJetsToLNu / (ee_TTWJetsToLNu_totevt)) * 1000;
    this->ee_TTWJetsToQQWeight = (GlobalConstants::Lumi2016) * (GlobalConstants::TTWJetsToQQ / (ee_TTWJetsToQQ_totevt)) * 1000;
    this->ee_TTZToQQWeight = (GlobalConstants::Lumi2016) * (GlobalConstants::TTZToQQ / (ee_TTZToQQ_totevt)) * 1000;
    this->ee_TTZToLLNuNuWeight = (GlobalConstants::Lumi2016) * (GlobalConstants::TTZToLLNuNu / (ee_TTZToLLNuNu_totevt)) * 1000;

    this->uu_TTTo2L2NuWeight = (GlobalConstants::Lumi2016) * ((GlobalConstants::TTTo2L2Nu) / (uu_TTTo2L2Nu_totevt)) * 1000;
    this->uu_ST_tW_topWeight = (GlobalConstants::Lumi2016) * (GlobalConstants::ST_tW_top_5fCS / (uu_tW_top_totevt)) * 1000;
    this->uu_ST_tW_antitopWeight = (GlobalConstants::Lumi2016) * (GlobalConstants::ST_tW_antitop_5fCS / (uu_tW_antitop_totevt)) * 1000;
    this->uu_TTWJetsToLNuWeight = (GlobalConstants::Lumi2016) * (GlobalConstants::TTWJetsToLNu / (uu_TTWJetsToLNu_totevt)) * 1000;
    this->uu_TTWJetsToQQWeight = (GlobalConstants::Lumi2016) * (GlobalConstants::TTWJetsToQQ / (uu_TTWJetsToQQ_totevt)) * 1000;
    this->uu_TTZToQQWeight = (GlobalConstants::Lumi2016) * (GlobalConstants::TTZToQQ / (uu_TTZToQQ_totevt)) * 1000;
    this->uu_TTZToLLNuNuWeight = (GlobalConstants::Lumi2016) * (GlobalConstants::TTZToLLNuNu / (uu_TTZToLLNuNu_totevt)) * 1000;

    this->emu_TTTo2L2NuWeight = (GlobalConstants::Lumi2016) * ((GlobalConstants::TTTo2L2Nu) / (emu_TTTo2L2Nu_totevt)) * 1000;
    this->emu_ST_tW_topWeight = (GlobalConstants::Lumi2016) * (GlobalConstants::ST_tW_top_5fCS / (emu_tW_top_totevt)) * 1000;
    this->emu_ST_tW_antitopWeight = (GlobalConstants::Lumi2016) * (GlobalConstants::ST_tW_antitop_5fCS / (emu_tW_antitop_totevt)) * 1000;
    this->emu_TTWJetsToLNuWeight = (GlobalConstants::Lumi2016) * (GlobalConstants::TTWJetsToLNu / (emu_TTWJetsToLNu_totevt)) * 1000;
    this->emu_TTWJetsToQQWeight = (GlobalConstants::Lumi2016) * (GlobalConstants::TTWJetsToQQ / (emu_TTWJetsToQQ_totevt)) * 1000;
    this->emu_TTZToQQWeight = (GlobalConstants::Lumi2016) * (GlobalConstants::TTZToQQ / (emu_TTZToQQ_totevt)) * 1000;
    this->emu_TTZToLLNuNuWeight = (GlobalConstants::Lumi2016) * (GlobalConstants::TTZToLLNuNu / (emu_TTZToLLNuNu_totevt)) * 1000;

    this->ee_diboson_gg_ZZ_2e2mu_Weight = (GlobalConstants::Lumi2016) * (GlobalConstants::gg_ZZ_2e2mu / (ee_gg_ZZ_2e2mu_totevt)) * 1000;
    this->ee_diboson_gg_ZZ_2e2nu_Weight = (GlobalConstants::Lumi2016) * (GlobalConstants::gg_ZZ_2e2nu / (ee_gg_ZZ_2e2nu_totevt)) * 1000;
    this->ee_diboson_gg_ZZ_2e2tau_Weight = (GlobalConstants::Lumi2016) * (GlobalConstants::gg_ZZ_2e2tau / (ee_gg_ZZ_2e2tau_totevt)) * 1000;
    this->ee_diboson_gg_ZZ_2mu2nu_Weight = (GlobalConstants::Lumi2016) * (GlobalConstants::gg_ZZ_2mu2nu / (ee_gg_ZZ_2mu2nu_totevt)) * 1000;
    this->ee_diboson_gg_ZZ_2mu2tau_Weight = (GlobalConstants::Lumi2016) * (GlobalConstants::gg_ZZ_2mu2tau / (ee_gg_ZZ_2mu2tau_totevt)) * 1000;
    this->ee_diboson_gg_ZZ_4e_Weight = (GlobalConstants::Lumi2016) * (GlobalConstants::gg_ZZ_4e / (ee_gg_ZZ_4e_totevt)) * 1000;
    this->ee_diboson_gg_ZZ_4mu_Weight = (GlobalConstants::Lumi2016) * (GlobalConstants::gg_ZZ_4mu / (ee_gg_ZZ_4mu_totevt)) * 1000;
    this->ee_diboson_gg_ZZ_4tau_Weight = (GlobalConstants::Lumi2016) * (GlobalConstants::gg_ZZ_4tau / (ee_gg_ZZ_4tau_totevt)) * 1000;
    this->ee_diboson_gg_WW_2L2Nu_Weight = (GlobalConstants::Lumi2016) * (GlobalConstants::gg_WW_2L2Nu / (ee_gg_WW_2L2Nu_totevt)) * 1000;
    this->ee_diboson_qq_WW_2L2Nu_Weight = (GlobalConstants::Lumi2016) * (GlobalConstants::qq_WW_2L2Nu / (ee_qq_WW_2L2Nu_totevt)) * 1000;
    this->ee_diboson_qq_WZ_2L2Q_Weight = (GlobalConstants::Lumi2016) * (GlobalConstants::qq_WZ_2L2Q / (ee_qq_WZ_2L2Q_totevt)) * 1000;
    this->ee_diboson_qq_WZ_3LNu_Weight = (GlobalConstants::Lumi2016) * (GlobalConstants::qq_WZ_3LNu / (ee_qq_WZ_3LNu_totevt)) * 1000;
    this->ee_diboson_qq_ZZ_2L2Nu_Weight = (GlobalConstants::Lumi2016) * (GlobalConstants::qq_ZZ_2L2Nu / (ee_qq_ZZ_2L2Nu_totevt)) * 1000;
    this->ee_diboson_qq_ZZ_2L2Q_Weight = (GlobalConstants::Lumi2016) * (GlobalConstants::qq_ZZ_2L2Q / (ee_qq_ZZ_2L2Q_totevt)) * 1000;
    this->ee_diboson_qq_ZZ_4L_Weight = (GlobalConstants::Lumi2016) * (GlobalConstants::qq_ZZ_4L / (ee_qq_ZZ_4L_totevt)) * 1000;

    this->uu_diboson_gg_ZZ_2e2mu_Weight = (GlobalConstants::Lumi2016) * (GlobalConstants::gg_ZZ_2e2mu / (uu_gg_ZZ_2e2mu_totevt)) * 1000;
    this->uu_diboson_gg_ZZ_2e2nu_Weight = (GlobalConstants::Lumi2016) * (GlobalConstants::gg_ZZ_2e2nu / (uu_gg_ZZ_2e2nu_totevt)) * 1000;
    this->uu_diboson_gg_ZZ_2e2tau_Weight = (GlobalConstants::Lumi2016) * (GlobalConstants::gg_ZZ_2e2tau / (uu_gg_ZZ_2e2tau_totevt)) * 1000;
    this->uu_diboson_gg_ZZ_2mu2nu_Weight = (GlobalConstants::Lumi2016) * (GlobalConstants::gg_ZZ_2mu2nu / (uu_gg_ZZ_2mu2nu_totevt)) * 1000;
    this->uu_diboson_gg_ZZ_2mu2tau_Weight = (GlobalConstants::Lumi2016) * (GlobalConstants::gg_ZZ_2mu2tau / (uu_gg_ZZ_2mu2tau_totevt)) * 1000;
    this->uu_diboson_gg_ZZ_4e_Weight = (GlobalConstants::Lumi2016) * (GlobalConstants::gg_ZZ_4e / (uu_gg_ZZ_4e_totevt)) * 1000;
    this->uu_diboson_gg_ZZ_4mu_Weight = (GlobalConstants::Lumi2016) * (GlobalConstants::gg_ZZ_4mu / (uu_gg_ZZ_4mu_totevt)) * 1000;
    this->uu_diboson_gg_ZZ_4tau_Weight = (GlobalConstants::Lumi2016) * (GlobalConstants::gg_ZZ_4tau / (uu_gg_ZZ_4tau_totevt)) * 1000;
    this->uu_diboson_gg_WW_2L2Nu_Weight = (GlobalConstants::Lumi2016) * (GlobalConstants::gg_WW_2L2Nu / (uu_gg_WW_2L2Nu_totevt)) * 1000;
    this->uu_diboson_qq_WW_2L2Nu_Weight = (GlobalConstants::Lumi2016) * (GlobalConstants::qq_WW_2L2Nu / (uu_qq_WW_2L2Nu_totevt)) * 1000;
    this->uu_diboson_qq_WZ_2L2Q_Weight = (GlobalConstants::Lumi2016) * (GlobalConstants::qq_WZ_2L2Q / (uu_qq_WZ_2L2Q_totevt)) * 1000;
    this->uu_diboson_qq_WZ_3LNu_Weight = (GlobalConstants::Lumi2016) * (GlobalConstants::qq_WZ_3LNu / (uu_qq_WZ_3LNu_totevt)) * 1000;
    this->uu_diboson_qq_ZZ_2L2Nu_Weight = (GlobalConstants::Lumi2016) * (GlobalConstants::qq_ZZ_2L2Nu / (uu_qq_ZZ_2L2Nu_totevt)) * 1000;
    this->uu_diboson_qq_ZZ_2L2Q_Weight = (GlobalConstants::Lumi2016) * (GlobalConstants::qq_ZZ_2L2Q / (uu_qq_ZZ_2L2Q_totevt)) * 1000;
    this->uu_diboson_qq_ZZ_4L_Weight = (GlobalConstants::Lumi2016) * (GlobalConstants::qq_ZZ_4L / (uu_qq_ZZ_4L_totevt)) * 1000;

    this->ee_WWZWeight = (GlobalConstants::Lumi2016) * (GlobalConstants::WWZ_TuneCUETP8M1 / (ee_WWZ_totevt)) * 1000;
    this->ee_WZZWeight = (GlobalConstants::Lumi2016) * (GlobalConstants::WZZ_TuneCUETP8M1 / (ee_WZZ_totevt)) * 1000;
    this->ee_ZZZWeight = (GlobalConstants::Lumi2016) * (GlobalConstants::ZZZ_TuneCUETP8M1 / (ee_ZZZ_totevt)) * 1000;

    this->uu_WWZWeight = (GlobalConstants::Lumi2016) * (GlobalConstants::WWZ_TuneCUETP8M1 / (uu_WWZ_totevt)) * 1000;
    this->uu_WZZWeight = (GlobalConstants::Lumi2016) * (GlobalConstants::WZZ_TuneCUETP8M1 / (uu_WZZ_totevt)) * 1000;
    this->uu_ZZZWeight = (GlobalConstants::Lumi2016) * (GlobalConstants::ZZZ_TuneCUETP8M1 / (uu_ZZZ_totevt)) * 1000;

    /*Hist Delete*/
    ee_h_HT_eventCout->Delete();
    ee_DYHT100_sumevt->Delete();
    ee_DYHT200_sumevt->Delete();
    ee_DYHT400_sumevt->Delete();
    ee_DYHT600_sumevt->Delete();
    ee_DYHT800_sumevt->Delete();
    ee_DYHT1200_sumevt->Delete();
    ee_DYHT2500_sumevt->Delete();

    uu_h_HT_eventCout->Delete();
    uu_DYHT100_sumevt->Delete();
    uu_DYHT200_sumevt->Delete();
    uu_DYHT400_sumevt->Delete();
    uu_DYHT600_sumevt->Delete();
    uu_DYHT800_sumevt->Delete();
    uu_DYHT1200_sumevt->Delete();
    uu_DYHT2500_sumevt->Delete();

    ee_TTTo2L2Nu_sumevt->Delete();
    ee_TTWJetsToLNu_sumevt->Delete();
    ee_TTWJetsToQQ_sumevt->Delete();
    ee_TTZToQQ_sumevt->Delete();
    ee_TTZToLLNuNu_sumevt->Delete();
    ee_tW_antitop_sumevt->Delete();
    ee_tW_top_sumevt->Delete();

    uu_TTTo2L2Nu_sumevt->Delete();
    uu_TTWJetsToLNu_sumevt->Delete();
    uu_TTWJetsToQQ_sumevt->Delete();
    uu_TTZToQQ_sumevt->Delete();
    uu_TTZToLLNuNu_sumevt->Delete();
    uu_tW_antitop_sumevt->Delete();
    uu_tW_top_sumevt->Delete();

    ee_gg_ZZ_2e2mu_sumevt->Delete();
    ee_gg_ZZ_2e2nu_sumevt->Delete();
    ee_gg_ZZ_2e2tau_sumevt->Delete();
    ee_gg_ZZ_2mu2nu_sumevt->Delete();
    ee_gg_ZZ_2mu2tau_sumevt->Delete();
    ee_gg_ZZ_4e_sumevt->Delete();
    ee_gg_ZZ_4mu_sumevt->Delete();
    ee_gg_ZZ_4tau_sumevt->Delete();
    ee_gg_WW_2L2Nu_sumevt->Delete();
    ee_qq_WW_2L2Nu_sumevt->Delete();
    ee_qq_WZ_2L2Q_sumevt->Delete();
    ee_qq_WZ_3LNu_sumevt->Delete();
    ee_qq_ZZ_2L2Nu_sumevt->Delete();
    ee_qq_ZZ_2L2Q_sumevt->Delete();
    ee_qq_ZZ_4L_sumevt->Delete();

    uu_gg_ZZ_2e2mu_sumevt->Delete();
    uu_gg_ZZ_2e2nu_sumevt->Delete();
    uu_gg_ZZ_2e2tau_sumevt->Delete();
    uu_gg_ZZ_2mu2nu_sumevt->Delete();
    uu_gg_ZZ_2mu2tau_sumevt->Delete();
    uu_gg_ZZ_4e_sumevt->Delete();
    uu_gg_ZZ_4mu_sumevt->Delete();
    uu_gg_ZZ_4tau_sumevt->Delete();
    uu_gg_WW_2L2Nu_sumevt->Delete();
    uu_qq_WW_2L2Nu_sumevt->Delete();
    uu_qq_WZ_2L2Q_sumevt->Delete();
    uu_qq_WZ_3LNu_sumevt->Delete();
    uu_qq_ZZ_2L2Nu_sumevt->Delete();
    uu_qq_ZZ_2L2Q_sumevt->Delete();
    uu_qq_ZZ_4L_sumevt->Delete();

    ee_WWZ_sumevt->Delete();
    ee_WZZ_sumevt->Delete();
    ee_ZZZ_sumevt->Delete();

    uu_WWZ_sumevt->Delete();
    uu_WZZ_sumevt->Delete();
    uu_ZZZ_sumevt->Delete();
}

void ee_for_inclusive_sample(double HT, double i_tmp, MergeWeight merge_weight, double eventWeight, TH1D *h_tmp)
{
    if (HT < 70)
    {
        h_tmp->Fill(i_tmp, merge_weight.ee_HT0Weight * eventWeight);
    }
    else if (HT >= 70 && HT < 100)
    {
        h_tmp->Fill(i_tmp, merge_weight.ee_HT70Weight * eventWeight);
    }
    else if (HT >= 100 && HT < 200)
    {
        h_tmp->Fill(i_tmp, merge_weight.ee_HT100Weight * eventWeight);
    }
    else if (HT >= 200 && HT < 400)
    {
        h_tmp->Fill(i_tmp, merge_weight.ee_HT200Weight * eventWeight);
    }
    else if (HT >= 400 && HT < 600)
    {
        h_tmp->Fill(i_tmp, merge_weight.ee_HT400Weight * eventWeight);
    }
    else if (HT >= 600 && HT < 800)
    {
        h_tmp->Fill(i_tmp, merge_weight.ee_HT600Weight * eventWeight);
    }
    else if (HT >= 800 && HT < 1200)
    {
        h_tmp->Fill(i_tmp, merge_weight.ee_HT800Weight * eventWeight);
    }
    else if (HT >= 1200 && HT < 2500)
    {
        h_tmp->Fill(i_tmp, merge_weight.ee_HT1200Weight * eventWeight);
    }
    else if (HT >= 2500)
    {
        h_tmp->Fill(i_tmp, merge_weight.ee_HT2500Weight * eventWeight);
    }
}

void uu_for_inclusive_sample(double HT, double i_tmp, MergeWeight merge_weight, double eventWeight, TH1D *h_tmp)
{
    if (HT < 70)
    {
        h_tmp->Fill(i_tmp, merge_weight.uu_HT0Weight * eventWeight);
    }
    else if (HT >= 70 && HT < 100)
    {
        h_tmp->Fill(i_tmp, merge_weight.uu_HT70Weight * eventWeight);
    }
    else if (HT >= 100 && HT < 200)
    {
        h_tmp->Fill(i_tmp, merge_weight.uu_HT100Weight * eventWeight);
    }
    else if (HT >= 200 && HT < 400)
    {
        h_tmp->Fill(i_tmp, merge_weight.uu_HT200Weight * eventWeight);
    }
    else if (HT >= 400 && HT < 600)
    {
        h_tmp->Fill(i_tmp, merge_weight.uu_HT400Weight * eventWeight);
    }
    else if (HT >= 600 && HT < 800)
    {
        h_tmp->Fill(i_tmp, merge_weight.uu_HT600Weight * eventWeight);
    }
    else if (HT >= 800 && HT < 1200)
    {
        h_tmp->Fill(i_tmp, merge_weight.uu_HT800Weight * eventWeight);
    }
    else if (HT >= 1200 && HT < 2500)
    {
        h_tmp->Fill(i_tmp, merge_weight.uu_HT1200Weight * eventWeight);
    }
    else if (HT >= 2500)
    {
        h_tmp->Fill(i_tmp, merge_weight.uu_HT2500Weight * eventWeight);
    }
}

#endif /*KUAN_ANA_UTIL_NOIMPL*/

#endif /*KUAN_ANA_UTIL_H*/