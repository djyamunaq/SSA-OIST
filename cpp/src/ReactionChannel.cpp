#include "ReactionChannel.hpp"
#include "Composition.hpp"
#include "Species.hpp"
#include <cmath>

long long ReactionChannel::nCr(int n, int r) {
    // Heuristic to avoid large multiplications (Avoid overflow)
    // TODO: Look for a BigInteger analogous in cpp 
    if (r < 0 || r > n) return 0;
    if (r == 0 || r == n) return 1;
    if (r > n / 2) r = n - r;
    long long res = 1;
    for (int i = 1; i <= r; ++i) {
        res = res * (n - i + 1) / i;
    }
    return res;
}

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
    // Initialize h to 1
    h = 1.0;
    // Multiply contributions from each reactant species (combinatorial of choosing stoichiometry from quantity)
    for (auto const& [species, stoichiometry] : reactants.getData()) {
        h *= nCr(species->getQuantity(), stoichiometry);
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