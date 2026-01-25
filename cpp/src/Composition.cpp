#include "Composition.hpp"
#include "Participant.hpp"
#include "Species.hpp"

Composition::Composition(const Species& s) {
    addParticipant(Participant(const_cast<Species&>(s), 1));
}

Composition::Composition(const Participant& p) {
    addParticipant(p);
}

Composition::Composition(const std::vector<Participant>& participants) {
    for (const auto& p : participants) {
        addParticipant(p);
    }
}

void Composition::printComposition() const {
    for (auto const& [species, stoichiometry] : this->m_data) {
        printf("Species: %s, Stoichiometry: %d\n", species->getName().c_str(), stoichiometry);
    }
}

void Composition::addParticipant(const Participant& p) {
    this->m_data[p.getSpecies()] += p.getStoichiometry();
}