/**
 *  @file   src/Helper.cc
 * 
 *  @brief  Implementation of the helper class.
 * 
 *  $Log: $
 */

#include "Helper.h"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

#include "TChain.h"
#include "TGraphErrors.h"
#include "TH1F.h"
#include "TH2F.h"

using namespace analysis;

Helper::Helper()
{
}

//-----------------------------------------------------------------------------------------------------------------------------------------

Helper::~Helper()
{
}

//-----------------------------------------------------------------------------------------------------------------------------------------

float Helper::CalculateCosTheta2D(const float x1, const float y1, const float x2, const float y2)
{
    const float mag1(std::sqrt(x1*x1+y1*y1));
    const float mag2(std::sqrt(x2*x2+y2*y2));
    return (x1*x2 + y1*y2) / (mag1 * mag2);
}

//-----------------------------------------------------------------------------------------------------------------------------------------

float Helper::GetFullWidthAtHalfMaximum(TH1F *pTH1F)
{
    float maxBinContent(0.f);

    for (int xBin = 0; xBin < pTH1F->GetNbinsX(); xBin++)
    {
        const float binContent(pTH1F->GetBinContent(xBin));
        if (binContent > maxBinContent)
            maxBinContent = binContent;
    }

    float halfMaximum(maxBinContent * 0.5f);
    float lowHalfMaximum(0.f), highHalfMaximum(0.f);

    for (int xBin = 0; xBin < pTH1F->GetNbinsX(); xBin++)
    {
        const float binContent(pTH1F->GetBinContent(xBin));
        if (binContent > halfMaximum)
        {
            lowHalfMaximum = pTH1F->GetBinCenter(xBin);
            break;
        }
    }

    for (int xBin = pTH1F->GetNbinsX(); xBin > 0; xBin--)
    {
        const float binContent(pTH1F->GetBinContent(xBin));
        if (binContent > halfMaximum)
        {
            highHalfMaximum = pTH1F->GetBinCenter(xBin);
            break;
        }
    }
    return (highHalfMaximum - lowHalfMaximum);
}

//-----------------------------------------------------------------------------------------------------------------------------------------

Particle Helper::GetParticleType(int pdg)
{
    switch (pdg)
    {
        case 11: return ELECTRON;
        case -11: return POSITRON;
        case 22: return PHOTON;
        case 13: return MUON;
        case -13: return ANTIMUON;
        case 2212: return PROTON;
        case -2212: return ANTIPROTON;
        case 2112: return NEUTRON;
        case -2112: return ANTINEUTRON;
        case 12: return NEUTRINO;
        case -12: return NEUTRINO;
        case 14: return NEUTRINO;
        case -14: return NEUTRINO;
        case 16: return NEUTRINO;
        case -16: return NEUTRINO;
        case 211: return PIPLUS;
        case -211: return PIMINUS;
        case 111: return PIZERO;
        case 130: return KAON0L;
        case 310: return KAON0S;
        case 321: return KAONPLUS;
        case -321: return KAONMINUS;
        default : return OTHER;
    }
}

//-----------------------------------------------------------------------------------------------------------------------------------------

const char *Helper::GetParticleString(Particle part)
{
    switch (part)
    {
        case ELECTRON: return "e^{-}";
        case POSITRON: return "e^{+}";
        case PHOTON: return "#gamma";
        case MUON: return "#mu^{-}";
        case ANTIMUON: return "#mu^{+}";
        case PROTON: return "p";
        case ANTIPROTON: return "#bar{p}";
        case NEUTRON: return "n";
        case ANTINEUTRON: return "#bar{n}";
        case NEUTRINO: return "#nu";
        case PIPLUS: return "#pi^{+}";
        case PIMINUS: return "#pi^{-}";
        case PIZERO: return "#pi^{0}";
        case KAON0L: return "K^{0}_{L}";
        case KAON0S: return "K^{0}_{S}";
        case KAONPLUS: return "K^{+}";
        case KAONMINUS: return "K^{-}";
        case OTHER: return "Other";
        default : return "Unknown";
    }
}

//-----------------------------------------------------------------------------------------------------------------------------------------

const char *Helper::GetParticleName(Particle part)
{
    switch (part)
    {
        case ELECTRON: return "Electron";
        case POSITRON: return "Positron";
        case PHOTON: return "Photon";
        case MUON: return "Muon";
        case ANTIMUON: return "AntiMuon";
        case PROTON: return "Proton";
        case ANTIPROTON: return "AntiProton";
        case NEUTRON: return "Neutron";
        case ANTINEUTRON: return "AntiNeutron";
        case NEUTRINO: return "Neutrino";
        case PIPLUS: return "PiPlus";
        case PIMINUS: return "PiMinus";
        case PIZERO: return "PiZero";
        case KAON0L: return "KaonOL";
        case KAON0S: return "KaonOS";
        case KAONPLUS: return "KaonPlus";
        case KAONMINUS: return "KaonMinus";
        case OTHER: return "Other";
        default : return "Unknown";
    }
}

//-----------------------------------------------------------------------------------------------------------------------------------------

int Helper::ParticleToLineColor(Particle part)
{
    switch (part)
    {
        case ELECTRON: return 4;
        case POSITRON: return 4;
//        case PHOTON: return 5;
        case MUON: return 1;
        case ANTIMUON: return 1;
        case PROTON: return 2;
        case ANTIPROTON: return 2;
//        case NEUTRON: return 7;
//        case ANTINEUTRON: return 7;
//        case NEUTRINO: return 30;
        case PIPLUS: return 6;
        case PIMINUS: return 6;
//        case PIZERO: return 9;
//        case KAON0L: return 2;
//        case KAON0S: return 2;
        case KAONPLUS: return 8;
        case KAONMINUS: return 8;
        case OTHER: return 3;
        default : return 3;
    }
}

//-----------------------------------------------------------------------------------------------------------------------------------------

void Helper::Save(TCanvas *pTCanvas, std::string name, int momenta)
{
    std::string pdfName(""), dotCName("");
    if (momenta > 0.f)
    {
        pdfName = name + "_" + ToString(momenta) + "GeV_Beam" + ".pdf";
        dotCName = name + "_" + ToString(momenta) + "GeV_Beam" + ".C";
    }
    else
    {
        pdfName = name + ".pdf";
        dotCName = name + ".C";
    }
    pTCanvas->SaveAs(pdfName.c_str());
    pTCanvas->SaveAs(dotCName.c_str());
}

//-----------------------------------------------------------------------------------------------------------------------------------------

template<typename T>
void Helper::Format(T *&pT)
{
    pT->GetXaxis()->SetTitle("Entries");
    pT->GetXaxis()->SetLabelSize(0.05);
    pT->GetXaxis()->SetTitleSize(0.05);
    pT->GetYaxis()->SetTitle("Fraction Of Events");
    pT->GetYaxis()->SetLabelSize(0.05);
    pT->GetYaxis()->SetTitleSize(0.05);
}

//-----------------------------------------------------------------------------------------------------------------------------------------

void Helper::BinLogX(TH1F *pTH1F)
{
    TAxis *pTAxis = pTH1F->GetXaxis();
    int nBins = pTAxis->GetNbins();

    float from = pTAxis->GetXmin();
    float to = pTAxis->GetXmax();
    float width = (to - from) / nBins;
    float *new_bins = new float[nBins + 1];

    for (int bin = 0; bin <= nBins; bin++)
    {
        new_bins[bin] = std::pow(10, from + bin * width);
    }

    pTAxis->Set(nBins, new_bins);
    delete new_bins;
}

//-----------------------------------------------------------------------------------------------------------------------------------------

TGraphErrors *Helper::MakeEfficiency(TH1F *pTH1F_Total, TH1F *pTH1F_Matched, const std::string &label, const int cut)
{
    TGraphErrors *pTGraphErrors_Efficiency = new TGraphErrors();
    pTGraphErrors_Efficiency->SetName(label.c_str());

    for (unsigned int bin = 0; bin < (unsigned int)(pTH1F_Total->GetNbinsX()); bin++)
    {
        int binContentAll(pTH1F_Total->GetBinContent(bin));
        int binContentMatched(pTH1F_Matched->GetBinContent(bin));
        if (binContentAll > cut)
        {
            const float efficiency = (float)(binContentMatched)/(float)(binContentAll);
            // Binomial np(1-p)
            const float efficiencyError(std::sqrt(efficiency*(1-efficiency)/(float)(binContentAll)));
            const float binWidth(pTH1F_Total->GetBinWidth(bin));
            pTGraphErrors_Efficiency->SetPoint(pTGraphErrors_Efficiency->GetN(), pTH1F_Total->GetBinCenter(bin), efficiency);
            pTGraphErrors_Efficiency->SetPointError(pTGraphErrors_Efficiency->GetN()-1, binWidth/2.f, efficiencyError);
        }
    }

    pTGraphErrors_Efficiency->SetMarkerStyle(1);
    pTGraphErrors_Efficiency->GetXaxis()->SetTitleSize(0.05);
    pTGraphErrors_Efficiency->GetXaxis()->SetLabelSize(0.05);
    pTGraphErrors_Efficiency->GetYaxis()->SetTitleSize(0.05);
    pTGraphErrors_Efficiency->GetYaxis()->SetLabelSize(0.05);
    pTGraphErrors_Efficiency->GetXaxis()->SetDecimals();
    pTGraphErrors_Efficiency->GetYaxis()->SetDecimals();
    pTGraphErrors_Efficiency->GetYaxis()->SetTitle("Reconstruction Efficiency");
    pTGraphErrors_Efficiency->GetYaxis()->SetRangeUser(0,1);
    pTGraphErrors_Efficiency->GetYaxis()->SetNdivisions(5);

    return pTGraphErrors_Efficiency;
}

//-----------------------------------------------------------------------------------------------------------------------------------------

TH2F *Helper::MakeEfficiency2D(TH2F *pTH2F_Total, TH2F *pTH2F_Matched, std::string label, const int cut)
{
    TH2F *pTH2F = new TH2F(label.c_str(), "", pTH2F_Total->GetXaxis()->GetNbins(), pTH2F_Total->GetXaxis()->GetXmin(),
        pTH2F_Total->GetXaxis()->GetXmax(), pTH2F_Total->GetYaxis()->GetNbins(), pTH2F_Total->GetYaxis()->GetXmin(),
        pTH2F_Total->GetYaxis()->GetXmax());

    for (unsigned int xBin = 0; xBin < (unsigned int)(pTH2F_Total->GetNbinsX()); xBin++)
    {
        for (unsigned int yBin = 0; yBin < (unsigned int)(pTH2F_Total->GetNbinsY()); yBin++)
        {
            const float binContentAll(pTH2F_Total->GetBinContent(xBin, yBin));
            const float binContentMatched(pTH2F_Matched->GetBinContent(xBin, yBin));

            if (binContentAll > cut)
            {
                const float efficiency(binContentMatched/binContentAll);
                // Binomial np(1-p)
                //const float efficiencyError(std::sqrt(efficiency*(1-efficiency)/(float)(binContentAll)));
                pTH2F->SetBinContent(xBin, yBin, efficiency);
            }
        }
    }

    Helper::Format(pTH2F);
    pTH2F->GetZaxis()->SetTitle("Reconstruction Efficiency");
    return pTH2F;
}

//-----------------------------------------------------------------------------------------------------------------------------------------

Particle Helper::GetParticle(const int ckov0Status, const int ckov1Status, const float momentum, const float tof)
{
    if (momentum < 2.5)
    {
        if (ckov0Status == 1)
        {
            return POSITRON;
        }
        else if (ckov0Status == 0)
        {
            if ((momentum < 1.5 && tof > 170) || (momentum > 1.5 && tof > 160))
            {
                return PROTON;
            }
            else
            {
                return PIPLUS;
            }
        }
    }
    else if (momentum > 2.5 && momentum < 3.5)
    {
        if (ckov0Status == 1 && ckov1Status == 1)
        {
            return POSITRON;
        }
        else if (ckov0Status == 1 && ckov1Status == 0)
        {
            return PIPLUS;
        }
        else if (ckov0Status == 0 && ckov1Status == 0)
        {
            //  ATTN: This could be a proton or kaon
            return OTHER;
        }
    }
    else if (momentum > 4)
    {
        if (ckov0Status == 1 && ckov1Status == 1)
        {
            // ATTN: This could be an electron or a pion
            return OTHER;
        }
        else if (ckov0Status == 1 && ckov1Status == 0)
        {
            return KAONPLUS;
        }
        else if (ckov0Status == 0 && ckov1Status == 0)
        {
            return PROTON;
        }
    }
//    std::cout << "ckov0Status : ckov1Status : momentum : tof = " << ckov0Status << " : " << ckov1Status << " : " << momentum << " : " << tof << std::endl;
    return OTHER;
}

//-----------------------------------------------------------------------------------------------------------------------------------------

template<typename T>
std::string Helper::ToString(T t)
{
    std::stringstream ss;
    ss << t;
    return ss.str();
}

//-----------------------------------------------------------------------------------------------------------------------------------------

template <typename T>
std::string Helper::ToStringPrecision(const T a_value, const int n)
{
    std::ostringstream out;
    out << std::fixed;
    out << std::setprecision(n) << a_value;
    return out.str();
}

//-----------------------------------------------------------------------------------------------------------------------------------------

bool Helper::CompareFiles(const std::string &fileNameA, const std::string &fileNameB, const std::string &treeName,
    const StringVector &intStrings, const StringVector &floatStrings, const StringVector &intVectorStrings,
    const StringVector &floatVectorStrings, const StringMap &nameSwitch)
{
    TChain *pTChainA = new TChain(treeName.c_str());
    pTChainA->Add(fileNameA.c_str());

    TChain *pTChainB = new TChain(treeName.c_str());
    pTChainB->Add(fileNameB.c_str());

    const int nEntriesA(pTChainA->GetEntries()), nEntriesB(pTChainB->GetEntries());

    if (nEntriesA != nEntriesB)
    {
        std::cout << "TChains have different sizes.  Exiting." << std::endl;
        return false;
    }

    StringIntMap intFeatureMapA, intFeatureMapB;
    StringFloatMap floatFeatureMapA, floatFeatureMapB;
    StringIntVectorMap intVectorFeatureMapA, intVectorFeatureMapB;
    StringFloatVectorMap floatVectorFeatureMapA, floatVectorFeatureMapB;

    for (const std::string feature : intStrings)
    {
        intFeatureMapA.insert(StringIntMap::value_type(feature, std::numeric_limits<int>::max()));
        intFeatureMapB.insert(StringIntMap::value_type(feature, std::numeric_limits<int>::max()));

        pTChainA->SetBranchAddress(feature.c_str(), &intFeatureMapA.at(feature));

        const std::string featureNameB(nameSwitch.find(feature) != nameSwitch.end() ? nameSwitch.at(feature) : feature);
        pTChainB->SetBranchAddress(featureNameB.c_str(), &intFeatureMapB.at(feature));
    }

    for (const std::string feature : floatStrings)
    {
        floatFeatureMapA.insert(StringFloatMap::value_type(feature, std::numeric_limits<float>::max()));
        floatFeatureMapB.insert(StringFloatMap::value_type(feature, std::numeric_limits<float>::max()));

        pTChainA->SetBranchAddress(feature.c_str(), &floatFeatureMapA.at(feature));
        pTChainB->SetBranchAddress(feature.c_str(), &floatFeatureMapB.at(feature));
    }

    for (const std::string feature : intVectorStrings)
    {
        intVectorFeatureMapA.insert(StringIntVectorMap::value_type(feature, new IntVector()));
        intVectorFeatureMapB.insert(StringIntVectorMap::value_type(feature, new IntVector()));

        pTChainA->SetBranchAddress(feature.c_str(), &intVectorFeatureMapA.at(feature));
        pTChainB->SetBranchAddress(feature.c_str(), &intVectorFeatureMapB.at(feature));
    }

    for (const std::string feature : floatVectorStrings)
    {
        floatVectorFeatureMapA.insert(StringFloatVectorMap::value_type(feature, new FloatVector()));
        floatVectorFeatureMapB.insert(StringFloatVectorMap::value_type(feature, new FloatVector()));

        pTChainA->SetBranchAddress(feature.c_str(), &floatVectorFeatureMapA.at(feature));
        pTChainB->SetBranchAddress(feature.c_str(), &floatVectorFeatureMapB.at(feature));
    }

    for (int entry = 0; entry < nEntriesA; entry++)
    {
        pTChainA->GetEntry(entry);
        pTChainB->GetEntry(entry);

        for (const auto iter : intFeatureMapA)
        {
            if (iter.second != intFeatureMapB.at(iter.first))
            {
                std::cout << "In Entry " << entry << ", the int feature " << iter.first << " differs between the files (A, B) : (" <<
                    iter.second << ", " << intFeatureMapB.at(iter.first) << ")" << std::endl;
                return false;
            }
        }

        for (const auto iter : floatFeatureMapA)
        {
            if (iter.second != floatFeatureMapB.at(iter.first))
            {
                std::cout << "In Entry " << entry << ", the float feature " << iter.first << " differs between the files (A, B) : (" <<
                    iter.second << ", " << floatFeatureMapB.at(iter.first) << ")" << std::endl;
                return false;
            }
        }

        for (const auto iter : intVectorFeatureMapA)
        {
            if (*iter.second != *intVectorFeatureMapB.at(iter.first))
            {
                std::cout << "In Entry " << entry << ", the int vector feature " << iter.first << " differs between the files" << std::endl; 

                std::cout << "A) {";
                for (const auto iter1 : *iter.second)
                    std::cout << iter1 << ", ";
                std::cout << "}" << std::endl;

                std::cout << "B) {";
                for (const auto iter2 : *intVectorFeatureMapB.at(iter.first))
                    std::cout << iter2 << ", ";
                std::cout << "}" << std::endl;
                return false;
            }
        }

        for (const auto iter : floatVectorFeatureMapA)
        {
            if (!AreFloatVectorsIdentical(*iter.second, *floatVectorFeatureMapB.at(iter.first)))
            {
                std::cout << "In Entry " << entry << ", the float vector feature " << iter.first << " differs between the files"
                    << std::endl;

                std::cout << "A) {";
                for (const auto iter1 : *iter.second)
                    std::cout << iter1 << ", ";
                std::cout << "}" << std::endl;

                std::cout << "B) {";
                for (const auto iter2 : *floatVectorFeatureMapB.at(iter.first))
                    std::cout << iter2 << ", ";
                std::cout << "}" << std::endl;
                return false;
            }
        }
    }

    std::cout << "The files are identical." << std::endl;
    return true;
}

//-----------------------------------------------------------------------------------------------------------------------------------------

bool Helper::DoesFileExist(const std::string &fileName)
{
    std::ifstream infile(fileName.c_str());
    return infile.good();
}

//-----------------------------------------------------------------------------------------------------------------------------------------

bool Helper::AreFloatVectorsIdentical(const FloatVector &floatVectorA, const FloatVector &floatVectorB)
{
    if (floatVectorA.size() != floatVectorB.size())
    {
        std::cout << "FloatVectors have different sizes" << std::endl;
        return false;
    }

    for (unsigned int entry = 0; entry < floatVectorA.size(); entry++)
    {
        if (std::fabs(floatVectorA.at(entry) - floatVectorB.at(entry)) > std::numeric_limits<float>::epsilon())
        {
            std::cout << "Entry " << entry << " differs in the vectors (A, B) : (" << floatVectorA.at(entry) << ", " <<
                floatVectorB.at(entry) << ")" << std::endl;

            return false;
        }
    }
    return true;
}

//-----------------------------------------------------------------------------------------------------------------------------------------

template std::string Helper::ToString(int);
template std::string Helper::ToString(float);
template std::string Helper::ToString(double);

template std::string Helper::ToStringPrecision(int, const int);
template std::string Helper::ToStringPrecision(float, const int);
template std::string Helper::ToStringPrecision(double, const int);

template void Helper::Format(TGraphErrors *&pTGraphErrors);
template void Helper::Format(TH1F *&pTH1F);
template void Helper::Format(TH2F *&pTH2F);
