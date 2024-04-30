//
// Created by Wojciech Mokwiński on 24/10/2023.
//

#include "../include/Container.h"
#include <iostream>

// Constructors
Container::Container() : number(0), tareWeight(0.0), maxWeight(0.0), strength(0.0), cargo(0.0) {}

Container::Container(int containerNumber) : number(containerNumber), tareWeight(0.0), maxWeight(0.0), strength(0.0), cargo(0.0) {}

// Getters
int Container::getNumber() const { return number; }

double Container::getTareWeight() const { return tareWeight; }

double Container::getMaxWeight() const { return maxWeight; }

double Container::getStrength() const { return strength; }

double Container::getGrossWeight() const { return tareWeight + cargo; }

double Container::getNetWeight() const { return cargo; }

double Container::getMaxCargo() const { return maxWeight - tareWeight; }

// Setters
void Container::setTareWeight(double tareWeight) {
    if (cargo == 0) {
        this->tareWeight = tareWeight;
    } else {
        throw std::logic_error("Cannot change tare weight with cargo in the container.");
    }
}

void Container::setMaxWeight(double maxWeight) { this->maxWeight = maxWeight; }

void Container::setStrength(double strength) { this->strength= strength; }

// Load and unloadOnto cargo
void Container::loadCargo(double amount) {
    if (amount <= maxWeight - tareWeight - cargo) {
        cargo += amount;
    } else {
        throw std::overflow_error("Container is full");
    }
}

void Container::unloadCargo(double amount) {
    if (amount <= cargo) {
        cargo -= amount;
    } else {
        throw std::underflow_error("Cannot unloadOnto more cargo than what's currently in the container.");
    }
}
