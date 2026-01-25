#ifndef PARTICIPANT_TPP
#define PARTICIPANT_TPP

#include "Species.hpp"      
#include "Participant.hpp"
#include "Composition.hpp"
#include "ReactionChannel.hpp"

template <typename T>
Composition Composition::operator+(const T& other) {
    Composition next = *this;
    Composition other_comp = Composition(other);

    for (auto const& [species, stoichiometry] : other_comp.getData()) {

        next.addParticipant(Participant(*species, stoichiometry));
    }

    return next;
}

template <typename T>
Composition Participant::operator+(const T& other) {
    return Composition(*this) + other;
}

template <typename T>
Composition Species::operator+(const T& other) {
    return Participant(*this, 1) + other;
}

template <typename T>
ReactionChannel Composition::operator>>(const T& other) {
    Composition reactant = *this;
    Composition product = Composition(other);

    return ReactionChannel(reactant, product);
}

template <typename T>
ReactionChannel Participant::operator>>(const T& other) {
    return Composition(*this) >> other;
}

template <typename T>
ReactionChannel Species::operator>>(const T& other) {
    return Participant(*this, 1) >> other;
}

#endif