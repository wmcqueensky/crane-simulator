//
// Created by student on 11/24/23.
//

#ifndef CRANEPROJECT_TRUCK_H
#define CRANEPROJECT_TRUCK_H

#include "Loadable.h"
#include "Container.h"

class Truck : public Loadable {
private:
    static const int MAX_CONTAINERS_ON_TRUCK = 2;
    Container trailer[MAX_CONTAINERS_ON_TRUCK];

public:
    Truck();

    [[nodiscard]] unsigned getCapacity() const override;
    [[nodiscard]] unsigned getSize() const override;
    Container& at(int index) override;
    void take(Container container) override;
    Container give() override;
};

#endif //CRANEPROJECT_TRUCK_H
