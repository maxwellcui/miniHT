// @author zhaoyuan.cui@cern.ch
// @file generator/generator.cc
// @date Aug.28, 2023

#include "Track.hh"
#include <iostream>
#include <random>
#include <fstream>
#include "TTree.h"
#include "TFile.h"
#include "TH2D.h"

int main(int argc, char **argv)
{
    int numTrk = 1;
    if (argc > 1)
    {
        numTrk = atoi(argv[1]);
        if (numTrk < 1)
        {
            std::cout << "Number of track can't be smaller than 1\n";
            exit(1);
        }
    }

    // Randomly generate k and b fro a track: y=kx+b

    // Seed the random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    // For central region of the detecotr,
    // k shouldn't be too small
    // b shouldn't be too large (awasy from beam)
    std::uniform_real_distribution<double> k_dist(1, 100);
    std::uniform_real_distribution<double> b_dist(-0.5, 0.5);
    std::uniform_real_distribution<double> sign_dist(-1.0, 1.0);

    std::ofstream outputFile("hits.txt");
    TTree AnalysisTree("AnalysisTree", "AnalysisTree");
    double truth_k = 0.0;
    double truth_b = 0.0;
    // double truth_x = 0.0;
    // double truth_y = 0.0;
    std::vector<double> var_x;
    std::vector<double> var_y;

    AnalysisTree.Branch("truth_k", &truth_k);
    AnalysisTree.Branch("truth_b", &truth_b);
    // AnalysisTree.Branch("truth_x", &truth_x);
    // AnalysisTree.Branch("truth_y", &truth_y);
    AnalysisTree.Branch("var_x", &var_x);
    AnalysisTree.Branch("var_y", &var_y);

    TH2D var_dist("h_var_dist", "h_var_dist;x;y", 220, -11, 11, 220, -11, 11);

    for (int i = 0; i < numTrk; i++)
    {
        double factor = 0.0;
        sign_dist(gen) >= 0 ? factor = 1.0 : factor = -1.0;
        Track t(factor * k_dist(gen), b_dist(gen));
        t.print();

        // Set branches
        truth_k = t.getK();
        truth_b = t.getB();
        auto hits = t.getVarHits();
        for (long unsigned int i = 0; i < hits.size(); i++)
        {
            outputFile << hits.at(i).m_x << " " << hits.at(i).m_y << std::endl;
            var_x.push_back(hits.at(i).m_x);
            var_y.push_back(hits.at(i).m_y);
            var_dist.Fill(hits.at(i).m_x, hits.at(i).m_y);
        }
        AnalysisTree.Fill();
    }

    TFile outputROOT("simHits.root", "RECREATE");
    AnalysisTree.Write();

    var_dist.Write();
    outputROOT.Close();

    outputFile.close();

    return 0;
}