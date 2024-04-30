//
// Created by Wojciech Mokwiński on 12/11/2023.
//

#ifndef CRANEPROJECT_CONTAINERSTACK_H
#define CRANEPROJECT_CONTAINERSTACK_H

#include <iostream>
#include <vector>
#include "Container.h"
#include "Loadable.h"

class ContainerStack : Loadable {
public:
    static const unsigned MAX_HEIGHT;

    ContainerStack();
    [[nodiscard]] unsigned getCapacity() const override;
    [[nodiscard]] unsigned getSize() const override;
    [[nodiscard]] Container& at(int height) override;
    void take(Container Container) override;
    Container give() override;

private:
    std::vector<Container> containers;
};

#endif //CRANEPROJECT_CONTAINERSTACK_H
