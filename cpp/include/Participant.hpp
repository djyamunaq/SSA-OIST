#ifndef PARTICIPANT_HPP
#define PARTICIPANT_HPP

class Species;
class Composition;
class ReactionChannel;

class Participant {
private:
    Species* species;
    int stoichiometry;

public:
    Participant(Species& species, int stoichiometry);

    Species* getSpecies() const { return species; }
    int getStoichiometry() const { return stoichiometry; }

    template <typename T>
    Composition operator+(const T& other);

    template <typename T>
    ReactionChannel operator>>(const T& other);
};

#endif