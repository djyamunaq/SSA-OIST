#ifndef REACTION_CHANNEL_HPP
#define REACTION_CHANNEL_HPP

#include <map>
#include "Composition.hpp" 

class Species;

class ReactionChannel {
private:
    Composition reactants; 
    Composition products; 
    
    double c;
    double h;
    
    std::map<Species*, int> stateChangeVector;
    void calculateStateChangeVector();

public:
    ReactionChannel(const Composition& reactants, const Composition& products);
    double getPropensity() const { return h * c; }
    double getH() const {return h;}
    void calculateH();
    double getC() const { return c; }
    void setC(double c) { this->c = c; }
    Composition getReactants() const;
    Composition getProducts() const;
    void executeUpdate();
    void printReactionChannel() const;
};

#endif