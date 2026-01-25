// cpp/include/Solver.hpp
#ifndef SOLVER_HPP
#define SOLVER_HPP

#include <vector>
#include <random>
#include <map>
#include <string>
#include "ReactionChannel.hpp"

// Replaces Python's history dictionary
struct TrajectoryPoint {
    double time;
    std::map<std::string, int> speciesCounts;
};

class Gillespie {
private:
    std::vector<ReactionChannel> channels;
    std::vector<Species*> trackedSpecies; 
    double currentTime;
    std::vector<TrajectoryPoint> history; // The log
    
    std::mt19937 rng;
    std::uniform_real_distribution<double> dist;

    // Helper to extract all unique species from the channels
    void discoverSpecies();

public:
    Gillespie(const std::vector<ReactionChannel>& channels);
    
    double step();
    void recordHistory(); // Equivalent to SpeciesLog.update(t)
    
    const std::vector<TrajectoryPoint>& getHistory() const { return history; }
    double getCurrentTime() const { return currentTime; }
};

#include "Templates.tpp"
#endif