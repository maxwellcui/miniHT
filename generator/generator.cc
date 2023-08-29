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
    std::uniform_real_distribution<double> k_dist(1, 100);
    std::uniform_real_distribution<double> b_dist(0, 0.1);

    // Track t1(k_dist(gen), b_dist(gen));
    Track t1(1.0, 0.0);
    t1.print();

    auto hits = t1.getVarHits();

    std::ofstream outputFile ("hits.txt");
    for(int i=0; i<hits.size();i++)
    {
        outputFile<<hits.at(i).m_x<<" "<<hits.at(i).m_y<<std::endl;
    }

    outputFile.close();

    return 0;
}