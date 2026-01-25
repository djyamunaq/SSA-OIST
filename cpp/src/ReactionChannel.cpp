#include "ReactionChannel.hpp"
#include "Composition.hpp"
#include "Species.hpp"
#include <cmath>

long long nCr(int n, int r) {
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
    calculateStateChangeVector();
    calculateH();
}

void ReactionChannel::calculateStateChangeVector() {
    for (auto const& [species, stoichiometry] : reactants.getData()) {
        stateChangeVector[species] -= stoichiometry;
    }
    for (auto const& [species, stoichiometry] : products.getData()) {
        stateChangeVector[species] += stoichiometry;
    }
}

void ReactionChannel::calculateH() {
    h = 1.0;
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
        species->updateQuantity(delta);
    }
}

void ReactionChannel::printReactionChannel() const {
    printf("[REACTANTS]\n");
    this->reactants.printComposition();
    printf("[PRODUCTS]\n");
    this->products.printComposition();
}