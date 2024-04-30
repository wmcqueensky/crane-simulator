//
// Created by Wojciech Mokwiński on 10/12/2023.
//

#include <boost/test/unit_test.hpp>
#include "../include/Truck.h"

BOOST_AUTO_TEST_SUITE(TruckTestSuite)

    BOOST_AUTO_TEST_CASE(testTruckConstructor) {
        Truck truck;
        BOOST_CHECK_EQUAL(truck.getCapacity(), 2);
        BOOST_CHECK_EQUAL(truck.getSize(), 0);
    }

    BOOST_AUTO_TEST_CASE(testTruckAt) {
        Truck truck;

        BOOST_CHECK_THROW(truck.at(-1), std::out_of_range);
        BOOST_CHECK_THROW(truck.at(2), std::out_of_range);
        BOOST_CHECK_THROW(truck.at(0), std::out_of_range);
        BOOST_CHECK_THROW(truck.at(1), std::out_of_range);

        Container newContainer(1);
        truck.take(newContainer);
        BOOST_CHECK_NO_THROW(truck.at(0));

        truck.give();
        BOOST_CHECK_THROW(truck.at(0), std::out_of_range);
    }

    BOOST_AUTO_TEST_CASE(testTruckTake) {
        Truck truck;
        Container container(123);
        truck.take(container);
        BOOST_CHECK_EQUAL(truck.getSize(), 1);
        BOOST_CHECK_EQUAL(truck.at(0).getNumber(), 123);

        Container container2(456);
        BOOST_CHECK_NO_THROW(truck.take(container2));
        Container container3(789);
        BOOST_CHECK_THROW(truck.take(container3), std::logic_error);
    }

    BOOST_AUTO_TEST_CASE(testTruckGive) {
        Truck truck;
        Container container(123);
        truck.take(container);
        BOOST_CHECK_EQUAL(truck.getSize(), 1);

        Container givenContainer = truck.give();
        BOOST_CHECK_EQUAL(givenContainer.getNumber(), 123);
        BOOST_CHECK_EQUAL(truck.getSize(), 0);

        BOOST_CHECK_THROW(truck.give(), std::logic_error);
    }

BOOST_AUTO_TEST_SUITE_END()