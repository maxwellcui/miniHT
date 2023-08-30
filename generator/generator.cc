// @author zhaoyuan.cui@cern.ch
// @file generator/generator.cc
// @date Aug.28, 2023

#include "Track.hh"
#include <iostream>
#include <random>
#include <fstream>

int main()
{
    // Randomly generate k and b fro a track: y=kx+b

    // Seed the random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    // For central region of the detecotr,
    // k shouldn't be too small
    // b shouldn't be too large (awasy from beam)
    std::uniform_real_distribution<double> k_dist(1, 10);
    std::uniform_real_distribution<double> b_dist(-0.5, 0.5);
    std::uniform_real_distribution<double> sign_dist(-1.0, 1.0);

    std::ofstream outputFile("hits.txt");
    for (int i = 0; i < 100; i++)
    {
        double factor = 0.0;
        sign_dist(gen) >= 0 ? factor = 1.0 : factor = -1.0;
        Track t(factor * k_dist(gen), b_dist(gen));
        t.print();
        auto hits = t.getVarHits();
        for (int i = 0; i < hits.size(); i++)
        {
            outputFile << hits.at(i).m_x << " " << hits.at(i).m_y << std::endl;
        }
    }

    // Track t1(1.0, 0.0);
    // t1.print();
    // auto hits = t1.getVarHits();

    outputFile.close();

    return 0;
}