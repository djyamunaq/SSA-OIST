#include "Participant.hpp"
#include "Species.hpp"

Participant::Participant(Species& species, int stoichiometry) 
    : species(&species), stoichiometry(stoichiometry) {}