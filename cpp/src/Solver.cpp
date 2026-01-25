#include "Solver.hpp"
#include <numeric>
#include <cmath>
#include <set>

Gillespie::Gillespie(const std::vector<ReactionChannel>& channels) 
    : channels(channels), currentTime(0.0), dist(0.0, 1.0) {
    std::random_device rd;
    rng.seed(rd());

    discoverSpecies();
    recordHistory();
}

void Gillespie::discoverSpecies() {
    std::set<Species*> speciesSet;
    for (const auto& channel : channels) {
        for (auto const& [s_ptr, stoichiometry] : channel.getReactants().getData()) {
            speciesSet.insert(s_ptr);
        }
        for (auto const& [s_ptr, stoichiometry] : channel.getProducts().getData()) {
            speciesSet.insert(s_ptr);
        }
    }
    for (Species* s : speciesSet) trackedSpecies.push_back(s);
}

void Gillespie::recordHistory() {
    TrajectoryPoint point;
    point.time = currentTime;
    for (Species* s : trackedSpecies) {
        point.speciesCounts[s->getName()] = s->getQuantity();
    }
    history.push_back(point);
}

double Gillespie::step() {
    double a0 = 0.0;
    std::vector<double> propensities;

    // 1. Calculate individual propensities and total a0
    for (auto& channel : channels) {
        channel.calculateH();
        double a = channel.getPropensity();

        propensities.push_back(a);
        a0 += a;
    }

    if (a0 <= 0) return 0.0;

    // 2. Generate random numbers
    double r1 = dist(rng);
    double r2 = dist(rng);

    // 3. Compute Tau (time to next reaction)
    double tau = -std::log(r1) / a0;
    currentTime += tau;

    // 4. Select reaction using r2
    double threshold = r2 * a0;
    double cumulative = 0.0;
    for (size_t i = 0; i < propensities.size(); ++i) {
        cumulative += propensities[i];
        if (cumulative >= threshold) {
            // 5. Update populations
            channels[i].executeUpdate(); 
            break;
        }
    }

    recordHistory();

    return a0;
}