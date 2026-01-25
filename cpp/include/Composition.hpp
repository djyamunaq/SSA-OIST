#ifndef COMPOSITION_HPP
#define COMPOSITION_HPP

#include <map>
#include <vector>
#include <string>
#include "Participant.hpp"

/**
 * Forward Declarations
 */
class Species;
class ReactionChannel;

/**
 * \brief Composition Class
 */
class Composition
{
private:
    std::map<Species *, int> m_data; /**< Map of Species pointers to their stoichiometry coefficients */

public:
    /**
     * \brief Constructor for Composition class (default)
     */
    Composition() = default;

    /**
     * \brief Constructor for Composition class with a Species
     * \param s Reference to the Species object
     */
    Composition(const Species &s);

    /**
     * \brief Constructor for Composition class with a Participant
     * \param p Reference to the Participant object
     */
    Composition(const Participant &p);

    /**
     * \brief Constructor for Composition class with a vector of Participants
     * \param participants Reference to the vector
     */
    Composition(const std::vector<Participant> &participants);

    /**
     * \brief Add a participant to the composition map
     * \param p Reference to the Participant object
     */
    void addParticipant(const Participant &p);

    /**
     * \brief Print composition details: Species name and stoichiometry of each participant
     */
    void printComposition() const;

    /**
     * \brief Get the map of species<>stoichiometry in the composition
     * \return m_data 
     */
    const std::map<Species *, int> getData() const { return m_data; }

    /**
     * \brief Overload of sum: Composition + ...
     * \param other The other Species/Participant/Composition
     */
    template <typename T>
    Composition operator+(const T &other);

    /**
     * \brief Overload of shift: Composition >> ...
     * \param other The other Species/Participant/Composition
     */
    template <typename T>
    ReactionChannel operator>>(const T &other);
};

#endif