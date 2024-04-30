//
// Created by Wojciech Mokwiński on 12/11/2023.
//

#include <boost/test/unit_test.hpp>
#include "../include/Container.h"
#include "../include/ContainerStack.h"

BOOST_AUTO_TEST_SUITE(ContainerStackTestSuite)

    BOOST_AUTO_TEST_CASE(testInitialEmptyStack) {
        ContainerStack stack;
        BOOST_CHECK_EQUAL(stack.getSize(), 9);
    }

    BOOST_AUTO_TEST_CASE(testLoadOneContainer) {
        ContainerStack stack;
        Container container(1);
        stack.take(container);

        BOOST_CHECK_EQUAL(stack.getSize(), 10);
        BOOST_CHECK_EQUAL(stack.at(1).getNumber(), 1);
    }

    BOOST_AUTO_TEST_CASE(testLoadMultipleContainersWithinCapacity) {
        ContainerStack stack;

        stack.take(Container(123));

        BOOST_CHECK_EQUAL(stack.getSize(), ContainerStack::MAX_HEIGHT);
    }

    BOOST_AUTO_TEST_CASE(testLoadTooManyContainers) {
        ContainerStack stack;

        stack.take(Container(123));

        BOOST_CHECK_THROW(stack.take(Container(ContainerStack::MAX_HEIGHT + 1)), std::overflow_error);
    }

    BOOST_AUTO_TEST_CASE(testRemoveContainerFromOneItemStack) {
        ContainerStack stack;
        Container container(1);
        stack.take(container);
        stack.give();

        BOOST_CHECK_EQUAL(stack.getSize(), 9);
    }

    BOOST_AUTO_TEST_CASE(testRemoveContainerFromThreeItemStack) {
        ContainerStack stack;

        stack.take(Container(123));

        stack.give();

        BOOST_CHECK_EQUAL(stack.getSize(), 9);
        BOOST_CHECK_EQUAL(stack.at(1).getNumber(), 1);
        BOOST_CHECK_EQUAL(stack.at(2).getNumber(), 2);
    }

    BOOST_AUTO_TEST_CASE(testAccessContainersInOrder) {
        ContainerStack stack;

        stack.take(Container(10));

        for (int i = 1; i <= ContainerStack::MAX_HEIGHT; i++) {
            BOOST_CHECK_EQUAL(stack.at(i).getNumber(), i);
        }
    }

    BOOST_AUTO_TEST_CASE(testLoadUnloadContainers) {
        ContainerStack stack;

        for (int i = 1; i <= 5; i++) {
            stack.give();
        }

        for (int i = 1; i <= 5; i++) {
            Container container(4 + i);
            stack.take(container);
            BOOST_CHECK_EQUAL(stack.getSize(), 4 + i);
            BOOST_CHECK_EQUAL(stack.at(i).getNumber(), i);
        }

        for (int i = 5; i >= 1; i--) {
            stack.give();
            BOOST_CHECK_EQUAL(stack.getSize(), 3 + i);
        }
    }

    BOOST_AUTO_TEST_CASE(testUnloadFromEmptyStack) {
        ContainerStack stack;

        for (int i = 9; i >= 1; i--) {
            stack.give();
        }

        BOOST_CHECK_THROW(stack.give(), std::underflow_error);
    }

    BOOST_AUTO_TEST_CASE(testLoadBeyondCapacity) {
        ContainerStack stack;

        stack.take(Container(10));

        BOOST_CHECK_THROW(stack.take(Container(ContainerStack::MAX_HEIGHT + 1)), std::overflow_error);
    }

    BOOST_AUTO_TEST_CASE(testAccessInvalidHeight) {
        ContainerStack stack;

        BOOST_CHECK_THROW(stack.at(10), std::out_of_range);
        BOOST_CHECK_THROW(stack.at(-1), std::out_of_range);

        stack.give();

        BOOST_CHECK_THROW(stack.at(9), std::out_of_range);
    }

BOOST_AUTO_TEST_SUITE_END()
