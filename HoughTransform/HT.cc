#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <generator/Track.hh>
#include "TH2D.h"
#include "TCanvas.h"

int main()
{
    std::ifstream inputFile("../generator/hits.txt");
    if (!inputFile.is_open())
    {
        std::cout << "Couldn't open file.\n";
        exit(1);
    }

    std::vector<double> xValues;
    std::vector<double> yValues;

    std::string line;
    while (std::getline(inputFile, line))
    {
        std::istringstream iss(line);
        double x, y;
        if (iss >> x >> y)
        {
            xValues.push_back(x);
            yValues.push_back(y);
        }
        else
        {
            std::cerr << "Error parsing line: " << line << std::endl;
        }
    }

    inputFile.close();

    // Print the extracted values
    for (size_t i = 0; i < xValues.size(); ++i)
    {
        std::cout << "x: " << xValues[i] << ", y: " << yValues[i] << std::endl;
    }

    // Create 2-D histo for accumulator
    double x_low = -100.0;
    double x_high = 100.0;
    double x_step = 2000;
    double x_size = (x_high - x_low) / x_step;
    double y_low = -10.0;
    double y_high = 10.0;
    double y_step = 200;

    TH2D accumulator("HTaccumulator", "HTaccumulator; k; b", x_step, x_low, x_high, y_step, y_low, y_high);
    for (long unsigned int i = 0; i < xValues.size(); i++)
    {
        for (double j = x_low; j < x_high; j = j + x_size)
            accumulator.Fill(j, yValues.at(i) - j * xValues.at(i));
    }

    TCanvas c1("c1", "c1", 1900, 1900);
    accumulator.SetStats(0);
    accumulator.Draw("colz0");
    c1.Print("./accumulator.png");
    accumulator.Draw("lego");
    c1.Print("./accumulator_lego.png");

    return 0;
}