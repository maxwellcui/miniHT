// @author zhaoyuan.cui@cern.ch
// @file generator/Track.cc
// @date Aug.28, 2023

#include "Track.hh"
#include <iostream>
#include <random>

Track::Track()
{
    // Default constructor does nothing
}

Track::~Track()
{
    // Destructor does nothing
}

Track::Track(double k, double b)
    : m_truth_k(k),
      m_truth_b(b)
{
    // Constructor which creates a track with k and b
    // Get the hits
    detectHits();
}

void Track::detectHits()
{
    // Radomize the direction of the track, traveling up or down
    // Seed the random number generator
    std::random_device rd;
    std::mt19937 gen(rd());

    // Define the distribution for the range -1 to 1
    std::uniform_real_distribution<double> dist(-1.0, 1.0);
    double factor = 0.0;
    // if the randome value is greater than 0,
    // it's traveling upward otherwise downward
    dist(gen) >= 0 ? factor = 1.0 : factor = -1.0;
    for (double &layer : m_layers)
    {
        layer *= factor;
        m_truth_hits.push_back(Hit(calculateX(layer, false), layer));
        m_var_hits.push_back(Hit(calculateX(layer, true), layer));
    }
}

double Track::calculateX(double y, bool var) const
{
    if (var)
    {
        std::random_device rd;
        std::default_random_engine generator(rd());
        // Define random generator with Gaussian distribution
        const double mean = 0.0;
        const double stddev = 0.1;
        std::normal_distribution<double> dist(mean, stddev);
        return (y - m_truth_b) / m_truth_k + dist(generator);
    }
    else
    {
        // get a truth X
        return (y - m_truth_b) / m_truth_k;
    }
}

void Track::print() const
{
    std::cout << "Truth k is " << m_truth_k
              << " Truth b is " << m_truth_b << std::endl;
    for (const Hit &hit : m_truth_hits)
    {
        std::cout << "Truth (x,y) = (" << hit.m_x << "," << hit.m_y << ")\n";
    }
    for (const Hit &hit : m_var_hits)
    {
        std::cout << "Variation (x,y) = (" << hit.m_x << "," << hit.m_y << ")\n";
    }
}
