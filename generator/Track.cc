// @author zhaoyuan.cui@cern.ch
// @file generator/Track.cc
// @date Aug.28, 2023

#include "Track.hh"
#include <iostream>
#include <chrono>
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
    getHits();
}

void Track::getHits()
{
    // y = kx + b
    // For a certain y, x is
    // x = (y-b)/k
    for (double &layer : m_layers)
    {
        m_hits.push_back(Hit(getX(layer, false), layer));
        m_var_hits.push_back(Hit(getX(layer, true), layer));
    }
}

double Track::getX(double y, bool var) const
{
    if (var)
    {
        // get a variation X
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::default_random_engine generator(seed);
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
              << "Truth b is " << m_truth_b << std::endl;
    for (const Hit &hit : m_hits)
    {
        std::cout << "Truth (x,y) = (" << hit.m_x << "," << hit.m_y << ")\n";
    }
    for (const Hit &hit : m_var_hits)
    {
        std::cout << "Variation (x,y) = (" << hit.m_x << "," << hit.m_y << ")\n";
    }
}
