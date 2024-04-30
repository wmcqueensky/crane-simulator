//
// Created by student on 11/24/23.
//

#include <iostream>
#include "Truck.h"

Truck::Truck() {
    for (Container& container : trailer) {
        container = Container(0);
    }
}

unsigned Truck::getCapacity() const {
    return MAX_CONTAINERS_ON_TRUCK;
}

unsigned Truck::getSize() const {
    unsigned size = 0;
    for (const Container& container : trailer) {
        if (container.getNumber() != 0) {
            ++size;
        }
    }
    return size;
}

Container& Truck::at(int index) {
    if (index >= 0 && index < MAX_CONTAINERS_ON_TRUCK && trailer[index].getNumber() != 0) {
        return trailer[index];
    } else {
        throw std::out_of_range("Invalid index or the place at index is empty");
    }
}

void Truck::take(Container container) {
    for (Container& trailerContainer : trailer) {
        if (trailerContainer.getNumber() == 0) {
            trailerContainer = container;
            return;
        }
    }
    throw std::logic_error("Truck is full");
}

Container Truck::give() {
    for (Container& container : trailer) {
        if (container.getNumber() != 0) {
            Container givenContainer = container;
            container = Container(0);
            return givenContainer;
        }
    }
    throw std::logic_error("No containers in the truck");
}