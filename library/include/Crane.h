//
// Created by Wojciech Mokwiński on 14/11/2023.
//

#ifndef CRANEPROJECT_CRANE_H
#define CRANEPROJECT_CRANE_H

#include "Container.h"
#include "ContainerStack.h"
#include "LoadStrategy.h"

class Crane {
public:
    static const int MAX_STACKS = 5;

    Crane(LoadStrategy* strategy);
    ~Crane();

    [[nodiscard]] bool isParked() const;
    [[nodiscard]] bool isLoaded() const;
    [[nodiscard]] bool isUnloaded() const;
    [[nodiscard]] bool isWaitingEmpty() const;
    [[nodiscard]] bool isWaitingFull() const;

    void park();
    void loadFrom(Loadable& truck);
    void unloadOnto(Loadable& loadableElement);

    void forward(int numSteps);
    void backward(int numSteps);
    void pickUp();
    void putDown();

    [[nodiscard]] int getPosition() const;
    [[nodiscard]] const Container& getContainer() const;
    [[nodiscard]] ContainerStack& stackAt(int stackPosition) const;
    [[nodiscard]] bool canPutDown() const;

    void changeStrategy(LoadStrategy* strategy);

private:
    int position;
    std::unique_ptr<ContainerStack> storage[MAX_STACKS];
    std::unique_ptr<Container> container;
    LoadStrategy* loadStrategy;

    static const int OVER_TRAILER = -2;
    static const int PARKED = -1;
};

#endif //CRANEPROJECT_CRANE_H
