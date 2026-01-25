#ifndef COMPOSITION_HPP
#define COMPOSITION_HPP

#include <map>
#include <vector>
#include <string>
#include "Participant.hpp"

class Species;
class ReactionChannel;

class Composition {
private:
    std::map<Species*, int> m_data;

public:
    Composition() = default;
    Composition(const Species& s);
    Composition(const Participant& p);
    Composition(const std::vector<Participant>& participants);

    void addParticipant(const Participant& p);
    void printComposition() const;
    const std::map<Species*, int> getData() const { return m_data; }

    template <typename T>
    Composition operator+(const T& other);

    template <typename T>
    ReactionChannel operator>>(const T& other);
};

#endif