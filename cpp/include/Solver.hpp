// cpp/include/Solver.hpp
#ifndef SOLVER_HPP
#define SOLVER_HPP

#include <vector>
#include <random>
#include <map>
#include <string>
#include "Volume.hpp"

// /**
//  * Forward Declarations
//  */
// class Volume;
// class Volume;

/**
 * \brief Object to store a point in the reaction trajectory
 */
struct TrajectoryPoint
{
    double time;
    std::map<std::string, int> speciesCounts;
};

/**
 * \brief Gillespie Stochastic Simulation Algorithm Solver
 */
class Gillespie
{
private:
    Volume volume;                               /**< Volume in the system */
    std::vector<Species *> trackedSpecies;       /**< Vector of species being tracked */
    double currentTime;                          /**< Current simulation time  */
    double simTime{-1};                          /**< Total simulation time  */
    std::vector<TrajectoryPoint> history;        /**< Trajectory history => log of species counts over time */
    std::mt19937 rng;                            /**< Random number generator */
    std::uniform_real_distribution<double> dist; /**< Uniform distribution (0, 1) */

    /**
     * \brief Helper to extract all unique species from the channels
     */
    void discoverSpecies();

public:
    /**
     * Constructor for Gillespie class
     * \param volume Volume object
     * \param simTime Simulation time
     */
    Gillespie(const Volume &volume, double simTime);

    /**
     * Constructor for Gillespie class
     * \param volume Volume object
     */
    Gillespie(const Volume &volume);

    /**
     * Step in simulation
     * \return boolean: is simulation done
     */
    bool step();

    /**
     * \brief Record a point in reaction trajectory to history
     */
    void recordHistory();

    /**
     * \brief Get history vector with all the points in the reaction trajectory (history of species quantities over time)
     * \return history vector
     */
    const std::vector<TrajectoryPoint> &getHistory() const { return history; }

    /**
     * \brief Get current simulation time
     * \return Current time
     */
    double getCurrentTime() const { return currentTime; }

    /**
     * \brief Get total simulation time
     * \return Current time
     */
    double getSimulationTime();

    /**
     * \brief Set total simulation time
     * \return Current time
     */
    void setSimulationTime(double simTime);
};

#include "Templates.tpp"
#endif