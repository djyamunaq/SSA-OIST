#ifndef SPECIES_HPP
#define SPECIES_HPP

#include <string>

/**
 * Forward Declarations
 */
class Participant;
class Composition;
class ReactionChannel;

/**
 * \brief Species Class
 */
class Species
{
private:
    std::string name; /**< Species name */ 
    int quantity; /**< Quantity in number of molecules */

public:
    /**
     * Constructor for Species class
     * \param name The name of the species
     * \param quantity The initial quantity of the species in number of molecules
     */
    Species(std::string name, int quantity);

    /**
     * Getter for species name
     * \return The name of the species
     */
    std::string getName() const;

    /**
     * Getter for species quantity
     * \return The current quantity of the species
     */
    int getQuantity() const;

    /**
     * Update quantity by a certain amount
     * \param change The amount to change the quantity by (number of molecules to change/can be negative)
     */
    void updateQuantity(int change);

    /**
     * Overload for multiplication: S * 2
     * \param stoichiometry The stoichiometry coefficient
     */
    Participant operator*(int stoichiometry);

    /**
     * Overload for multiplication: 2 * S
     * \param stoichiometry The stoichiometry coefficient
     */
    friend Participant operator*(int stoichiometry, Species &s);

    /**
     * Overload for sum: S + ...
     * \param other The other Species/Participant/Composition
     * \return The resulting Composition
     */
    template <typename T>
    Composition operator+(const T &other);

    /**
     * Overload for shift: S >> ...
     * \param other The other Species/Participant/Composition
     * \return The resulting ReactionChannel
     */
    template <typename T>
    ReactionChannel operator>>(const T &other);
};

#endif