#include "ReactionChannel.hpp"
#include "Composition.hpp"
#include "Species.hpp"
#include "Utils.hpp"
#include <cmath>

ReactionChannel::ReactionChannel(const Composition& reactants, const Composition& products)
    : reactants(reactants), products(products), c(0.0), h(0.0) {
    // Initialize state change vector
    calculateStateChangeVector();
    // Calculate initial factorial coefficient h
    calculateH();
}

void ReactionChannel::calculateStateChangeVector() {
    // Get changes for reactants
    for (auto const& [species, stoichiometry] : reactants.getData()) {
        stateChangeVector[species] -= stoichiometry;
    }
    // Get changes for products
    for (auto const& [species, stoichiometry] : products.getData()) {
        stateChangeVector[species] += stoichiometry;
    }
}

void ReactionChannel::calculateH() {
    // Get utils instance
    auto& utils = Utils::getInstance();
    
    // Initialize h to 1
    h = 1.0;
    // Multiply contributions from each reactant species (combinatorial of choosing stoichiometry from quantity)
    for (auto const& [species, stoichiometry] : reactants.getData()) {
        h *= utils.nCr(species->getQuantity(), stoichiometry);
    }
}

Composition ReactionChannel::getReactants() const {
    return this->reactants;
}

Composition ReactionChannel::getProducts() const {
    return this->products;
}

void ReactionChannel::executeUpdate() {
    for (auto const& [species, delta] : stateChangeVector) {
        // printf("Updating Species: %s by %d\n", species->getName().c_str(), delta);
        species->updateQuantity(delta);
    }
}

void ReactionChannel::printReactionChannel() const {
    printf("[REACTANTS]\n");
    this->reactants.printComposition();
    printf("[PRODUCTS]\n");
    this->products.printComposition();
}