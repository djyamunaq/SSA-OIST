#include "Species.hpp"
#include "Participant.hpp"
#include "Composition.hpp"
#include "ReactionChannel.hpp"
#include "Solver.hpp"
#include "matplotlibcpp.h"
#include <typeinfo>
#include <cstdio>

namespace plt = matplotlibcpp;

int main() {
    Species A("A", 1000), B("B", 0), C("C", 0);

    auto r1 = A >> B;
    r1.setC(0.5);
    auto r2 = B >> C;  
    r2.setC(1.0);

    Gillespie solver({r1, r2});

    while (true) {
        auto a0 = solver.step();

        if(a0 <= 0) break;
    }

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

    for (const auto& point : solver.getHistory()) {
        ts.push_back(point.time);
        xa.push_back(point.speciesCounts.at("A"));
        xb.push_back(point.speciesCounts.at("B"));
        xc.push_back(point.speciesCounts.at("C"));
    }

    plt::named_plot("A", ts, xa);
    plt::named_plot("B", ts, xb);
    plt::named_plot("C", ts, xc);

    plt::xlabel("Time");
    plt::ylabel("Molecule Count");
    plt::legend();
    plt::show();

    return 0;
}