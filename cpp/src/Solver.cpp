#include "Solver.hpp"
#include "ReactionChannel.hpp"
#include "Volume.hpp"
#include <numeric>
#include <cmath>
#include <set>

Gillespie::Gillespie(const Volume &volume, double simTime)
    : volume(volume), currentTime(0.0), dist(0.0, 1.0)
{
    std::random_device rd;
    rng.seed(rd());

    discoverSpecies();
    recordHistory();
}

Gillespie::Gillespie(const Volume &volume)
    : volume(volume), currentTime(0.0), dist(0.0, 1.0)
{
    std::random_device rd;
    rng.seed(rd());

    discoverSpecies();
    recordHistory();
}

void Gillespie::discoverSpecies()
{
    // Set to store unique species references
    std::set<Species *> speciesSet;

    // Get volume channels
    auto channels = volume.getChannels();

    // Iterate over reaction channels
    for (const auto &channel : channels)
    {
        // Reactants
        for (auto const &[s_ptr, stoichiometry] : channel.getReactants().getData())
        {
            speciesSet.insert(s_ptr);
        }
        // Products
        for (auto const &[s_ptr, stoichiometry] : channel.getProducts().getData())
        {
            speciesSet.insert(s_ptr);
        }
    }

    // Save unique species to vector
    for (Species *s : speciesSet)
    {
        trackedSpecies.push_back(s);
    }
}

void Gillespie::recordHistory()
{
    TrajectoryPoint point;
    point.time = currentTime;

    // Get species quantities in current state
    for (Species *s : trackedSpecies)
    {
        point.speciesCounts[s->getName()] = s->getQuantity();
    }

    history.push_back(point);
}

// int count = 0;
bool Gillespie::step()
{
    // Total propensity
    double a0 = 0.0;

    // Individual propensities (one per reaction channel)
    std::vector<double> propensities;

    // Get volume channels
    auto channels = volume.getChannels();

    // Calculate individual propensities and total a0
    for (auto &channel : channels)
    {
        channel.calculateH();
        double a = channel.getPropensity();

        propensities.push_back(a);
        a0 += a;
    }

    // Print volume details
    // if (count++ % 100)
    // {
    //     printf("%lf\n", a0);
    //     volume.printVolume();
    // }

    // Check if propensity is 0 => no reaction
    if (a0 <= 0)
    {
        return true;
    }

    // Generate random numbers
    double r1 = dist(rng);
    double r2 = dist(rng);

    // Compute Tau (time to next reaction)
    double tau = -std::log(r1) / a0;
    currentTime += tau;

    // Check if simulation time is up
    if (simTime > 0 && currentTime > simTime)
    {
        return true;
    }

    // Select reaction using r2
    double threshold = r2 * a0;
    double cumulative = 0.0;
    for (size_t i = 0; i < propensities.size(); ++i)
    {
        cumulative += propensities[i];
        if (cumulative >= threshold)
        {
            // 5. Update populations
            channels[i].executeUpdate();
            break;
        }
    }

    // Record current state
    recordHistory();

    return false;
}

double Gillespie::getSimulationTime()
{
    return simTime;
}

void Gillespie::setSimulationTime(double simTime)
{
    this->simTime = simTime;
}