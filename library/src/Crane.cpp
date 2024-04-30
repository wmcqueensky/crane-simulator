//
// Created by Wojciech Mokwiński on 14/11/2023.
//

#include <iostream>
#include "Crane.h"
#include "Truck.h"

Crane::Crane(LoadStrategy* strategy)
        : position(PARKED), container(std::make_unique<Container>(0)), loadStrategy(strategy) {
    for (std::unique_ptr<ContainerStack>& containerIndex : storage) {
        containerIndex = std::make_unique<ContainerStack>();
    }
}

Crane::~Crane() {
    delete loadStrategy; // Free memory
}

bool Crane::isParked() const {
    return position == PARKED;
}

bool Crane::isLoaded() const {
    return position <= OVER_TRAILER && container->getNumber() != 0;
}

bool Crane::isUnloaded() const {
    return position <= OVER_TRAILER && container->getNumber() == 0;
}

bool Crane::isWaitingEmpty() const {
    return position >= 0 && position <= MAX_STACKS && container->getNumber() == 0;
}

bool Crane::isWaitingFull() const {
    return position >= 0 && position <= MAX_STACKS && container->getNumber() != 0;
}

void Crane::park() {
    if (isParked() || isLoaded() || isWaitingFull()) {
        throw std::logic_error("Cannot park when Crane is loaded or waiting full or already parked.");
    } else {
        position = PARKED;
    }
}

void Crane::loadFrom(Loadable& truck) {
    if ((isUnloaded()) && truck.canGive()) {
        container = std::make_unique<Container>(truck.give());
    } else {
        throw std::logic_error("Crane not over loadable object or not unloaded");
    }
}

void Crane::unloadOnto(Loadable& loadableElement) {
    if (isLoaded() && loadableElement.canTake() && (position == OVER_TRAILER || position > PARKED)) {
        loadableElement.take(*container);
        container = std::make_unique<Container>(0);
    } else {
        throw std::logic_error("Crane not over loadable object or not loaded");
    }
}

void Crane::forward(int numSteps) {
    if (position + numSteps < MAX_STACKS) {
        position += numSteps;
    } else {
        throw std::out_of_range("It is not possible to move further than the MAX_STACKS");
    }
}

void Crane::backward(int numSteps) {
    if (position - numSteps >= OVER_TRAILER) {
        position -= numSteps;
    } else {
        throw std::out_of_range("It is not possible to move behind the trailer");
    }
}

void Crane::pickUp() {
    if (isWaitingEmpty() && storage[position]->getSize() !=0) {
        container = std::make_unique<Container>(storage[position]->give());
    } else {
        throw std::logic_error("Crane is not waiting empty or ContainerStack is empty");
    }
}

void Crane::putDown() {
    if (isWaitingFull() && storage[position]->getSize() < ContainerStack::MAX_HEIGHT) {
        storage[position]->take(*container);
        container = std::make_unique<Container>(0);
    } else {
        throw std::logic_error("Crane is not waiting full or ContainerStack is underneath is full");
    }
}

int Crane::getPosition() const {
    return position;
}

const Container& Crane::getContainer() const {
    if (container->getNumber() != 0) {
        return *container;
    } else {
        throw std::logic_error("There is no container right now");
    }
}

ContainerStack& Crane::stackAt(int stackPosition) const {
    if (stackPosition >= 0 && stackPosition < MAX_STACKS) {
//        if (storage[stackPosition] != nullptr) {
            return *storage[stackPosition];
//        } else {
//            throw std::logic_error("There is no stack at the given position");
//        }
    } else {
        throw std::out_of_range("You can only check stacks at positions 0-9");
    }
}

//bool Crane::canPutDown() const {
//    if (isWaitingFull()) {
//        const ContainerStack& currentStack = stackAt(position);
//        return currentStack.getSize() <= ContainerStack::MAX_HEIGHT;
//    }
//    return false;
//}

bool Crane::canPutDown() const {
    if (loadStrategy && isWaitingFull()) {
        const ContainerStack& currentStack = stackAt(position);
        return loadStrategy->canPutDown(*this->container, (Loadable &) currentStack);
    }
    return false;
}

void Crane::changeStrategy(LoadStrategy* strategy) {
    if (loadStrategy) {
        delete loadStrategy;
    }
    loadStrategy = strategy;
}