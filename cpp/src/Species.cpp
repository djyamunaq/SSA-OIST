#include "Species.hpp"
#include "Participant.hpp"
#include "Composition.hpp"
#include "ReactionChannel.hpp"

Species::Species(std::string name, int quantity) 
    : name(name), quantity(quantity) {}

std::string Species::getName() const { return name; }
int Species::getQuantity() const { return quantity; }

void Species::updateQuantity(int change) {
    quantity += change;
}

// Multiplication Logic
Participant Species::operator*(int stoichiometry) {
    return Participant(*this, stoichiometry);
}

Participant operator*(int stoichiometry, Species& s) {
    return Participant(s, stoichiometry);
}