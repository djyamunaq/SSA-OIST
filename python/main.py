import numpy as np
import matplotlib.pyplot as plt
import math
    
class ReactionChannel:
    def __init__(self, reactants, products):
        self.reactants = reactants
        self.products = products
        self.c = 0.0  # rate constant
        self.h = 1  # combinatory factor

        self.calculate_h()

    def calculate_h(self):
        self.h = 1  

        for participant in self.reactants.participants:
            species_quantity = participant.species.quantity
            stoichiometry = participant.stoichiometry

            self.h *= math.comb(species_quantity, stoichiometry)

    def update(self):
        for participant in self.reactants.participants:
            stoichiometry = participant.stoichiometry
            participant.species.update_quantity(-stoichiometry)

        for participant in self.products.participants:
            stoichiometry = participant.stoichiometry
            participant.species.update_quantity(stoichiometry)


class Composition:
    def __init__(self, participants):
        participant_map = {}

        for participant in participants:
            if participant.species.name in participant_map:
                participant_map[participant.species.name][1] += participant.stoichiometry
            else:
                participant_map[participant.species.name] = [participant.species, participant.stoichiometry]

        self.participants = [
            Participant(species, stoichiometry)
            for species, stoichiometry in participant_map.values()
        ]

    def __add__(self, other):
        if other.__class__ == Species:
            other = Participant(other, 1)
            return Composition([other, *self.participants])

        if other.__class__ == Participant:
            return Composition([other, *self.participants])

        if other.__class__ == Composition:
            return Composition([*self.participants, *other.participants])

    def __rshift__(self, other):
        print('shift called - Composition')

        if other.__class__ == Species:
            reactants = self
            products = Composition([Participant(other, 1)])

            return ReactionChannel(reactants, products)

        if other.__class__ == Participant:
            reactants = self
            products = Composition([other])

            return ReactionChannel(reactants, products)
        
        if other.__class__ == Composition:
            reactants = self
            products = other

            return ReactionChannel(reactants, products)


class Participant:
    def __init__(self, species, stoichiometry):
        self.species = species
        self.stoichiometry = stoichiometry

    def __add__(self, other):
        if other.__class__ == Species:
            other = Participant(other, 1)
            return Composition([other, self])

        if other.__class__ == Participant:
            return Composition([other, self])

        if other.__class__ == Composition:
            return Composition([self, *other.participants])
    
    def __rshift__(self, other):
        print('shift called - Participant')

        if other.__class__ == Species:
            reactants = Composition([self])
            products = Composition([Participant(other, 1)])

            return ReactionChannel(reactants, products)

        if other.__class__ == Participant:
            reactants = Composition([self])
            products = Composition([other])

            return ReactionChannel(reactants, products)
        
        if other.__class__ == Composition:
            reactants = Composition([self])
            products = other

            return ReactionChannel(reactants, products)


class Species:
    def __init__(self, name, quantity):
        self.name = name
        self.quantity = quantity

    def update_quantity(self, change):
        self.quantity += change

    def __mul__(self, stoichiometry):
        return Participant(self, stoichiometry)
    
    def __rmul__(self, stoichiometry):
        return Participant(self, stoichiometry)
    
    def __add__(self, other):
        if other.__class__ == Species:
            other = Participant(other, 1)
            return Composition([other, Participant(self, 1)])

        if other.__class__ == Participant:
            return Composition([other, Participant(self, 1)])
        
        if other.__class__ == Composition:
            return Composition([Participant(self, 1), *other.participants])

    def __rshift__(self, other):
        print('shift called - Species')

        if other.__class__ == Species:
            reactants = Composition([Participant(self, 1)])
            products = Composition([Participant(other, 1)])

            return ReactionChannel(reactants, products)

        if other.__class__ == Participant:
            reactants = Composition([Participant(self, 1)])
            products = Composition([other])

            return ReactionChannel(reactants, products)
        
        if other.__class__ == Composition:
            reactants = Composition([Participant(self, 1)])
            products = other

            return ReactionChannel(reactants, products)
    

class SpeciesLog:
    def __init__(self, species):
        self.species = species
        self.history = {s.name: [(s.quantity, 0)] for s in species}

    def update(self, t):
        for s in self.species:
            self.history[s.name].append((s.quantity, t))


class Gillespie:
    def __init__(self, reaction_channel_ls):
        self.reaction_channel_ls = reaction_channel_ls
        self.log = SpeciesLog(self.get_all_species())
        self.t_ls = [0.0]

    def get_all_species(self):
        species_set = set()

        for reaction_channel in self.reaction_channel_ls:
            for participant in reaction_channel.reactants.participants:
                species_set.add(participant.species)
            for participant in reaction_channel.products.participants:
                species_set.add(participant.species)

        return list(species_set)
    
    def step(self):
        '''
        Compute total reaction probability, a0=sum(ai) => ai=hi*ci => higher probability means time to next raction is smaller
        '''
        a0 = 0.0
        a_ls = []

        for reaction_channel in self.reaction_channel_ls:
            h = reaction_channel.h
            c = reaction_channel.c
            a = h * c
            a_ls.append(a)
            a0 += a

        if a0 <= 0:
            return a0

        '''
        3. Select two random numbers, p1 and p2, from a uniform distribution on the interval (0, 1)
        '''
        r1 = np.random.uniform(0, 1)
        r2 = np.random.uniform(0, 1)

        '''
        4. Compute the time to next reaction tau=-ln(r1)/a0
        '''
        tau = -np.log(r1)/a0

        '''
        5. Select the reaction that takes place at this time => partition interval (0,1) by relative sizes of individual reaction provbabilities, then select the reaction that occurs using randomly generated number r2
        '''
        a_cummulative = 0.0
        for i in range(0, len(a_ls)):
            a_cummulative += a_ls[i]

            if a_cummulative > r2*a0:
                reaction_index = i
                break

        '''
        6. Update reaction time t=t+tau => adjust number of molecules xi for each species
        '''
        t = self.t_ls[-1] + tau
        self.t_ls.append(t)

        self.reaction_channel_ls[reaction_index].update()
        
        self.log.update(t)

        for reaction_channel in self.reaction_channel_ls:
            reaction_channel.calculate_h()

        return a0

def main():
    A = Species("A", 1000)
    B = Species("B", 250)
    C = Species("C", 0)
    D = Species("D", 0)

    reaction_1 = A + B >> C 
    reaction_2 = B + C >> D

    reaction_1.c = 0.5
    reaction_2.c = 1.0

    for participant in reaction_1.reactants.participants:
        print(f"R1 Reactant - Species: {participant.species.name}, Stoichiometry: {participant.stoichiometry}")

    for participant in reaction_1.products.participants:
        print(f"R1 Product - Species: {participant.species.name}, Stoichiometry: {participant.stoichiometry}")

    for participant in reaction_2.reactants.participants:
        print(f"R2 Reactant - Species: {participant.species.name}, Stoichiometry: {participant.stoichiometry}")

    for participant in reaction_2.products.participants:
        print(f"R2 Product - Species: {participant.species.name}, Stoichiometry: {participant.stoichiometry}")

    gillespie = Gillespie([reaction_1, reaction_2])

    count = 0
    while True:
        # print(f'Step: {count}')
        count += 1

        a0 = gillespie.step()

        # print(f"a0: {a0}, A: {A.quantity}, B: {B.quantity}, C: {C.quantity}")
        
        # xa.append(A.quantity)
        # xb.append(B.quantity)
        # xc.append(C.quantity)

        if a0 <= 0:
            break

    log_A = gillespie.log.history[A.name]
    xa = [a for a, _ in log_A]
    ts = [t for _, t in log_A]

    log_B = gillespie.log.history[B.name]
    xb = [b for b, _ in log_B]

    log_C = gillespie.log.history[C.name]
    xc = [c for c, _ in log_C]

    log_D = gillespie.log.history[D.name]
    xd = [d for d, _ in log_D]
    
    plt.step(ts, xa, where='post', label='A')
    plt.step(ts, xb, where='post', label='B')
    plt.step(ts, xc, where='post', label='C')
    plt.step(ts, xd, where='post', label='D')

    plt.xlabel('Time')
    plt.ylabel('Molecule Count')
    plt.legend()
    plt.show()

if __name__ == "__main__":
    main()