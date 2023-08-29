// @author zhaoyuan.cui@cern.ch
// @file generator/Track.hh
// @date Aug.28, 2023

#ifndef GENERATOR_TRACK_HH
#define GENERATOR_TRACK_HH

#include <vector>

struct Hit
{
    Hit(double x, double y)
    {
        m_x = x;
        m_y = y;
    }
    double m_x;
    double m_y;
};

class Track
{
public:
    Track();
    Track(double k, double b);
    ~Track();

    void getHits();
    double getX(double y, bool var) const;
    void print() const;

private:
    std::vector<Hit> m_hits; // truth hits
    std::vector<Hit> m_var_hits; // variation hits: to mimic inefficiency
    std::vector<double> m_layers {1.0, 1.5, 2.3, 3.0, 3.5, 4.2, 5.5, 7.0};

    double m_truth_k;
    double m_truth_b;
};

#endif // GENERATOR_TRACK_HH