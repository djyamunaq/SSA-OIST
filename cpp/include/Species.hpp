#ifndef SPECIES_HPP
#define SPECIES_HPP

#include <string>

class Participant;
class Composition;
class ReactionChannel;

class Species {
private:
    std::string name;
    int quantity;

public:
    Species(std::string name, int quantity);

    // Getters and Setters
    std::string getName() const;
    int getQuantity() const;
    void updateQuantity(int change);

    // Multiplication: S * 2
    Participant operator*(int stoichiometry);

    // Mirrored multiplication: 2 * S
    friend Participant operator*(int stoichiometry, Species& s);

    // Addition Overloads
    template <typename T>
    Composition operator+(const T& other);

    // Shift Overloads
    template <typename T>
    ReactionChannel operator>>(const T& other);
};


#endif