#include "Species.hpp"
#include "Participant.hpp"
#include "Composition.hpp"
#include "ReactionChannel.hpp"
#include "Volume.hpp"
#include "Solver.hpp"
#include "matplotlibcpp.h"
#include <typeinfo>
#include <cstdio>

namespace plt = matplotlibcpp;

int main() {
    // Create volumes
    Volume vol1;

    // Create species
    Species A("A", 10000), B("B", 0), C("C", 0);

    // Define reaction channels r1 and r2
    auto r1 = A >> B;
    auto r2 = B >> C;  

    // Set rate constants
    r1.setC(0.5);
    r2.setC(1.0);

    // Add reaction channels to volume
    vol1.addReactionChannel(r1);
    vol1.addReactionChannel(r2);

    // Define solver
    Gillespie solver(vol1);
    solver.setSimulationTime(20.0);

    // Iterate through simulation
    auto done = solver.step();
    while (!done) {
        done = solver.step();
    }

    // Print history (species' quantities over time)
    // for (const auto& point : solver.getHistory()) {
    //     printf("Time: %.4f | A: %d, B: %d C: %d\n", 
    //            point.time, 
    //            point.speciesCounts.at("A"), 
    //            point.speciesCounts.at("B"),
    //            point.speciesCounts.at("C"));
    // }

    // Prepare data vectors for plotting
    std::vector<double> ts;
    std::vector<int> xa, xb, xc;

    // Get species' quantities and timestamps from history
    for (const auto& point : solver.getHistory()) {
        ts.push_back(point.time);
        xa.push_back(point.speciesCounts.at("A"));
        xb.push_back(point.speciesCounts.at("B"));
        xc.push_back(point.speciesCounts.at("C"));
    }

    // Plot quantities x time for each species
    plt::named_plot("A", ts, xa);
    plt::named_plot("B", ts, xb);
    plt::named_plot("C", ts, xc);

    // Set labels
    plt::xlabel("Time");
    plt::ylabel("Molecule Count");
    plt::legend();

    // Show
    plt::show();

    return 0;
}