//
// Created by student on 11/24/23.
//

#include "Loadable.h"

bool Loadable::canTake() const {
    return getSize() < getCapacity();
}

bool Loadable::canGive() const {
    return getSize() > 0;
}