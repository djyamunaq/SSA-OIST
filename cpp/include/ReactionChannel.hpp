#ifndef REACTION_CHANNEL_HPP
#define REACTION_CHANNEL_HPP

#include <map>
#include "Composition.hpp"

/**
 * Forward Declarations
 */
class Species;

/**
 * \brief ReactionChannel Class
 */
class ReactionChannel
{
private:
    Composition reactants;                      /**< Reactant Compositions */
    Composition products;                       /**< Product Compositions */
    double c;                                   /**< Rate Constant */
    double h;                                   /**< Combinatorial Factor => Accounts for the number of distinct reactant combinations */
    std::map<Species *, int> stateChangeVector; /**< State Change Vector => Maps Species to their net change in quantity when the reaction occurs */

    /**
     * \brief Helper to compute the state change vector (the amount each participant quantity varies after a single reaction)
     */
    void calculateStateChangeVector();

public:
    /**
     * \brief Constructor for ReactionChannel class
     * \param reactants Composition of reactant participants
     * \param products Composition of produtc participants
     */
    ReactionChannel(const Composition &reactants, const Composition &products);

    /**
     * \brief Compute nCr (combinations of n items
     * @param n Total number of items
     * @param r Number of items to choose
     * @return The number of combinations (n choose r)
     */
    long long nCr(int n, int r);

    /**
     * \brief Get the propensity to a reaction (Based on factorial factor and rate coefficient)
     * \return Propensity to reaction
     */
    double getPropensity() const
    {
        return h * c;
    }

    /**
     * \brief Get the factorial coefficient h
     * \return Factorial coefficient h
     */
    double getH() const { return h; }

    /**
     * \brief Get the rate constant c
     * \return Rate constant c
     */
    double getC() const { return c; }

    /**
     * \brief Set the rate constant c
     * \param c Rate constant
     */
    void setC(double c) { this->c = c; }

    /**
     * \brief Get the reactant composition in reaction channel
     * \return Reactant Composition object
     */
    Composition getReactants() const;

    /**
     * \brief Get the product composition in reaction channel
     * \return Product Composition object
     */
    Composition getProducts() const;

    /**
     * \brief Calculate the factorial factor h
     */
    void calculateH();

    /**
     * \brief Execute update on species' quantities after reaction
     */
    void executeUpdate();

    /** 
     * \brief Print the reaction channel details: Species names and stoichiometries for reactants and products
     */
    void printReactionChannel() const;
};

#endif