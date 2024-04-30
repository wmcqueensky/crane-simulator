//
// Created by Wojciech Mokwiński on 01/11/2023.
//

#include <boost/test/unit_test.hpp>
#include "../include/Container.h"

BOOST_AUTO_TEST_SUITE(ContainerTestSuite)

    BOOST_AUTO_TEST_CASE(testInitialEmptyContainer) {
        Container container(234);

        BOOST_CHECK_EQUAL(container.getNumber(), 234);
        BOOST_CHECK_EQUAL(container.getTareWeight(), 0.0);
        BOOST_CHECK_EQUAL(container.getMaxWeight(), 0.0);
        BOOST_REQUIRE_EQUAL(container.getNetWeight(), 0.0);
//        BOOST_REQUIRE_CLOSE_FRACTION(container.getGrossWeight(), 0.0, 0.00001);
    }

    BOOST_AUTO_TEST_CASE(testInitialEmptyContainerWithNoId) {
        Container container;
        BOOST_CHECK_EQUAL(container.getNumber(), 0);
        BOOST_CHECK_EQUAL(container.getTareWeight(), 0.0);
        BOOST_CHECK_EQUAL(container.getMaxWeight(), 0.0);
        BOOST_REQUIRE_EQUAL(container.getNetWeight(), 0.0);
        BOOST_REQUIRE_CLOSE_FRACTION(container.getGrossWeight(), 0.0, 0.00001);
}

    BOOST_AUTO_TEST_CASE(testCargoBelowMaxWeight) {
        Container container(20);
        container.setTareWeight(4.0);
        container.setMaxWeight(22.5);
        container.setStrength(14.0);
        container.loadCargo(12.0);
        BOOST_CHECK_EQUAL(container.getNumber(), 20);
        BOOST_CHECK_EQUAL(container.getTareWeight(), 4.0);
        BOOST_CHECK_EQUAL(container.getMaxWeight(), 22.5);
        BOOST_REQUIRE_EQUAL(container.getStrength(), 14.0);
        BOOST_REQUIRE_EQUAL(container.getNetWeight(), 12.0);
        BOOST_REQUIRE_EQUAL(container.getGrossWeight(), 16.0);

    }

    BOOST_AUTO_TEST_CASE(testCargoAboveMaxWeight) {
        Container container(20);
        container.setTareWeight(3.0);
        container.setMaxWeight(12.5);

        BOOST_CHECK_EQUAL(container.getMaxWeight(), 12.5);
        BOOST_CHECK_THROW(container.loadCargo(12.0), std::overflow_error);
    }

    BOOST_AUTO_TEST_CASE(testUnloadMorThanItContains) {
        Container container(20);
        container.setTareWeight(3.0);
        container.setMaxWeight(12.5);

        BOOST_CHECK_EQUAL(container.getMaxWeight(), 12.5);
        BOOST_CHECK_THROW(container.unloadCargo(32.0), std::underflow_error);
    }



BOOST_AUTO_TEST_SUITE_END()
