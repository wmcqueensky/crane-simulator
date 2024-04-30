//
// Created by Wojciech Mokwiński on 12/11/2023.
//
#include <iostream>
#include "../include/ContainerStack.h"

const unsigned ContainerStack::MAX_HEIGHT = 10;

ContainerStack::ContainerStack() {
    for (int i = 1; i < MAX_HEIGHT; i++) {
        take(Container(i));
    }
}

unsigned ContainerStack::getCapacity() const {
    return MAX_HEIGHT;
}

unsigned ContainerStack::getSize() const {
    return containers.size();
}

Container& ContainerStack::at(int height)  {
    if (height > 0 && height <= getSize()) {
        return containers[height - 1];
    } else {
        throw std::out_of_range("Invalid height");
    }
}

void ContainerStack::take(Container container) {
    if (getSize() < getCapacity()) {
        containers.push_back(container);
    } else {
        throw std::overflow_error("ContainerStack is full");
    }
}

Container ContainerStack::give() {
    if (!containers.empty()) {
        Container lastContainer = containers.back();
        containers.pop_back();
        return lastContainer;
    } else {
        throw std::underflow_error("ContainerStack is empty");
    }
}