//
// Created by Wojciech Mokwiński on 22/12/2023.
//
#include "LoadStrategy.h"

bool CheckFreePlaceStrategy::canPutDown(Container& container, Loadable& loadable) {
    return loadable.getSize() < loadable.getCapacity() && container.getNumber() != 0;
}

bool CheckPlaceAndWeightStrategy::canPutDown(Container& container, Loadable& loadable) {
    const unsigned containerWeight = container.getGrossWeight();
    const unsigned loadableCapacity = loadable.getCapacity();

    const unsigned MAX_WEIGHT_ALLOWED = 100;

    return (loadable.getSize() < loadableCapacity) && (containerWeight <= MAX_WEIGHT_ALLOWED);
}