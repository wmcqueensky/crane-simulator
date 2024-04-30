//
// Created by Wojciech Mokwiński on 28/11/2023.
//

#include <boost/test/unit_test.hpp>
#include "../include/Crane.h"
#include "../include/Truck.h"

BOOST_AUTO_TEST_SUITE(CraneTestSuite)

    BOOST_AUTO_TEST_CASE(testCraneConstructor) {
        Crane crane(new CheckFreePlaceStrategy());
        BOOST_CHECK_EQUAL(crane.isParked(), true);
        BOOST_CHECK_THROW(crane.getContainer(), std::logic_error);
    }

    BOOST_AUTO_TEST_CASE(testCraneMovement) {
        Crane crane(new CheckFreePlaceStrategy());
        BOOST_CHECK_EQUAL(crane.getPosition(), -1);

        crane.forward(2);
        BOOST_CHECK_EQUAL(crane.getPosition(), 1);

        crane.backward(1);
        BOOST_CHECK_EQUAL(crane.getPosition(), 0);
        BOOST_CHECK_THROW(crane.forward(11), std::out_of_range);
        BOOST_CHECK_THROW(crane.backward(5), std::out_of_range);
    }

    BOOST_AUTO_TEST_CASE(testParking) {
        Crane crane(new CheckFreePlaceStrategy());
        Truck truck;
        BOOST_CHECK_EQUAL(crane.isParked(), true);

        truck.take(Container(123));
        crane.backward(1);
        crane.loadFrom(truck);
        BOOST_CHECK_EQUAL(crane.isLoaded(), true);
        BOOST_CHECK_THROW(crane.park(), std::logic_error);
        BOOST_CHECK_EQUAL(crane.isParked(), false);

        crane.unloadOnto(truck);
        BOOST_CHECK_EQUAL(crane.isLoaded(), false);

        crane.forward(2);
        BOOST_CHECK_NO_THROW(crane.park());
        BOOST_CHECK_EQUAL(crane.isParked(), true);
    }

    BOOST_AUTO_TEST_CASE(testLoadingContainer) {
        Crane crane(new CheckFreePlaceStrategy());
        Truck truck;

        BOOST_CHECK_EQUAL(crane.isLoaded(), false);
        BOOST_CHECK_THROW(crane.loadFrom(truck), std::logic_error);
        BOOST_CHECK_THROW(crane.loadFrom((Loadable &) crane.stackAt(1)), std::logic_error);

        crane.forward(1);
        BOOST_CHECK_EQUAL(crane.isWaitingEmpty(), true);
        BOOST_CHECK_THROW(crane.loadFrom((Loadable &) crane.stackAt(0)), std::logic_error);
        BOOST_CHECK_EQUAL(crane.isWaitingFull(), false);

        crane.pickUp();
        crane.backward(2);
        crane.unloadOnto(truck);
        BOOST_CHECK_NO_THROW(crane.loadFrom(truck));
        BOOST_CHECK_EQUAL(crane.isLoaded(), true);
    }

    BOOST_AUTO_TEST_CASE(testUnloadingContainer) {
        Crane crane(new CheckFreePlaceStrategy());
        Truck truck;
        BOOST_CHECK_EQUAL(crane.isUnloaded(), false);
        BOOST_CHECK_THROW(crane.unloadOnto(truck), std::logic_error);

        crane.forward(1);
        BOOST_CHECK_THROW(crane.unloadOnto(truck), std::logic_error);
        BOOST_CHECK_EQUAL(crane.isUnloaded(), false);

        crane.pickUp();
        crane.backward(2);
        BOOST_CHECK_EQUAL(crane.isUnloaded(), false);
        BOOST_CHECK_NO_THROW(crane.unloadOnto(truck));
        BOOST_CHECK_EQUAL(crane.isUnloaded(), true);
    }

    BOOST_AUTO_TEST_CASE(testPickUp) {
        Crane crane(new CheckFreePlaceStrategy());
        BOOST_CHECK_EQUAL(crane.isWaitingEmpty(), false);
        BOOST_CHECK_THROW(crane.pickUp(), std::logic_error);

        crane.forward(2);
        BOOST_CHECK_EQUAL(crane.isWaitingEmpty(), true);

        BOOST_CHECK_NO_THROW(crane.pickUp());
        BOOST_CHECK_EQUAL(crane.isWaitingEmpty(), false);
        BOOST_CHECK_EQUAL(crane.isWaitingFull(), true);

        crane.forward(1);
        BOOST_CHECK_THROW(crane.pickUp(), std::logic_error);

        crane.backward(3);
        BOOST_CHECK_THROW(crane.pickUp(), std::logic_error);

        crane.backward(1);
        BOOST_CHECK_THROW(crane.pickUp(), std::logic_error);
    }

    BOOST_AUTO_TEST_CASE(testPutDown) {
        Crane crane(new CheckFreePlaceStrategy());
        BOOST_CHECK_EQUAL(crane.isWaitingFull(), false);
        BOOST_CHECK_EQUAL(crane.canPutDown(), false);
        BOOST_CHECK_THROW(crane.putDown(), std::logic_error);

        crane.forward(2);
        BOOST_CHECK_EQUAL(crane.isWaitingEmpty(), true);

        BOOST_CHECK_NO_THROW(crane.pickUp());
        BOOST_CHECK_EQUAL(crane.isWaitingFull(), true);
        BOOST_CHECK_EQUAL(crane.canPutDown(), true);

        BOOST_CHECK_NO_THROW(crane.putDown());
        BOOST_CHECK_EQUAL(crane.isWaitingEmpty(), true);
        BOOST_CHECK_EQUAL(crane.isWaitingFull(), false);
        BOOST_CHECK_THROW(crane.putDown(), std::logic_error);

        crane.forward(1);
        BOOST_CHECK_NO_THROW(crane.pickUp());
        BOOST_CHECK_EQUAL(crane.isWaitingFull(), true);
        BOOST_CHECK_EQUAL(crane.canPutDown(), true);

        crane.backward(3);
        BOOST_CHECK_THROW(crane.putDown(), std::logic_error);

        crane.backward(1);
        BOOST_CHECK_THROW(crane.putDown(), std::logic_error);
    }

    BOOST_AUTO_TEST_CASE(testGetContainerStackAt) {
        Crane crane(new CheckFreePlaceStrategy());
        BOOST_CHECK_THROW(crane.getContainer().getNumber(), std::logic_error);

        BOOST_CHECK_THROW(crane.stackAt(-2), std::out_of_range);
        BOOST_CHECK_THROW(crane.stackAt(11), std::out_of_range);
        BOOST_CHECK_THROW(crane.stackAt(-1), std::out_of_range);
        BOOST_CHECK_NO_THROW(crane.stackAt(1));
        BOOST_CHECK_NO_THROW(crane.stackAt(3));
        BOOST_CHECK_NO_THROW(crane.stackAt(4));


        crane.forward(3);

        const ContainerStack& initialStack = crane.stackAt(0);
        BOOST_CHECK_EQUAL(initialStack.getSize(), 9);

        const ContainerStack& newStack = crane.stackAt(3);
        BOOST_CHECK_EQUAL(newStack.getSize(), 9);
    }

    BOOST_AUTO_TEST_CASE(testCanPutDownWithStrategy) {
        Crane crane(new CheckFreePlaceStrategy());
        Truck truck;

        BOOST_CHECK_EQUAL(crane.canPutDown(), false);

        truck.take(Container(1));
        crane.backward(1);
        crane.loadFrom(truck);

        BOOST_CHECK_EQUAL(crane.canPutDown(), false);

        crane.forward(2);
        BOOST_CHECK_EQUAL(crane.canPutDown(), true);
    }

    BOOST_AUTO_TEST_CASE(testChangeStrategy) {
        Crane crane(new CheckFreePlaceStrategy());

        Truck truck;
        truck.take(Container(1));

        crane.backward(1);
        crane.loadFrom(truck);

        BOOST_CHECK_EQUAL(crane.canPutDown(), false);

        crane.changeStrategy(new CheckPlaceAndWeightStrategy());

        BOOST_CHECK_EQUAL(crane.canPutDown(), false);
    }

    BOOST_AUTO_TEST_CASE(testCraneWithNoStrategy) {
        Crane crane(nullptr);
        Truck truck;

        BOOST_CHECK_EQUAL(crane.canPutDown(), false);

        truck.take(Container(1));
        crane.backward(1);
        crane.loadFrom(truck);

        BOOST_CHECK_EQUAL(crane.canPutDown(), false); // Without a strategy, canPutDown() should return false
    }


BOOST_AUTO_TEST_SUITE_END()