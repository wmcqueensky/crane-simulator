//
// Created by Wojciech Mokwiński on 22/12/2023.
//

#ifndef CRANEPROJECT_LOADSTRATEGY_H
#define CRANEPROJECT_LOADSTRATEGY_H
#include "Loadable.h"

class LoadStrategy {
public:
    virtual bool canPutDown(Container& container, Loadable& loadable) = 0;
};

class CheckFreePlaceStrategy : public LoadStrategy {
public:
    bool canPutDown(Container& container, Loadable& loadable) override;
};

class CheckPlaceAndWeightStrategy : public LoadStrategy {
public:
    bool canPutDown(Container& container, Loadable& loadable) override;
};

#endif //CRANEPROJECT_LOADSTRATEGY_H
