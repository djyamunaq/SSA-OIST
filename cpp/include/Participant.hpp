#ifndef PARTICIPANT_HPP
#define PARTICIPANT_HPP

/**
 * Forward Declarations
 */
class Species;
class Composition;
class ReactionChannel;

/**
 * \brief Participant Class
 */
class Participant
{
private:
    Species *species; /**< Reference to species object */
    int stoichiometry;  /**< Stoichiometry coefficient */

public:
    /**
     * \brief Constructor for Participant class
     * \param species Reference to the Species object
     * \param stoichiometry The stoichiometry coefficient
     */
    Participant(Species &species, int stoichiometry);

    /**
     * \brief Getter for species reference
     * \return Pointer to the Species object
     */
    Species *getSpecies() const { return species; }

    /**
     * \brief Getter for stoichiometry coefficient
     * \return The stoichiometry coefficient
     */
    int getStoichiometry() const { return stoichiometry; }

    /**
     * Overload for sum: Participant + ...
     * \param other The other Species/Participant/Composition
     */
    template <typename T>
    Composition operator+(const T &other);

    /**
     * Overload for shift: Participant >> ...
     * \param other The other Species/Participant/Composition
     */
    template <typename T>
    ReactionChannel operator>>(const T &other);
};

#endif