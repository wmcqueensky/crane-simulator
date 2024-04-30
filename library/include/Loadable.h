//
// Created by student on 11/24/23.
//

#ifndef CRANEPROJECT_LOADABLE_H
#define CRANEPROJECT_LOADABLE_H

#include "Container.h"

class Loadable {
public:
    [[nodiscard]] virtual unsigned getCapacity() const = 0;
    [[nodiscard]] virtual unsigned getSize() const = 0;
    virtual Container& at(int index) = 0;
    virtual void take(Container container) = 0;
    virtual Container give() = 0;

    [[nodiscard]] bool canTake() const;
    [[nodiscard]] bool canGive() const;

    virtual ~Loadable() = default;
};

#endif //CRANEPROJECT_LOADABLE_H
