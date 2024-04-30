#include <iostream>
//#include "/Container.h"
#include "../../library/include/Container.h"

void display(Container container) {
    std::cout << "Container Number: " << container.getNumber() << std::endl;
    std::cout << "Tare Weight: " << container.getTareWeight() << std::endl;
    std::cout << "Max Weight: " << container.getMaxWeight() << std::endl;
    std::cout << "Strength: " << container.getStrength() << std::endl;
    std::cout << "Gross Weight: " << container.getGrossWeight() << std::endl;
    std::cout << "Net Weight: " << container.getNetWeight() << std::endl;
    std::cout << "Max Cargo: " << container.getMaxCargo() << std::endl;
}

void testLocalObject() {
    Container localContainer(2);
    localContainer.setTareWeight(15.0);
    localContainer.setMaxWeight(120.0);
    localContainer.setStrength(95.0);

    display(localContainer);
}

void displayCargo(Container& container) {
    std::cout << "Current Cargo Weight: " << container.getNetWeight() << std::endl;
}

void loadAndSend(Container& container, double goods) {
    displayCargo(container);
    container.loadCargo(goods);
    displayCargo(container);
}

Container* prepare(int number, double goods) {
    Container* dynamicContainer = new Container(number);
    dynamicContainer->setTareWeight(5.0);
    dynamicContainer->setMaxWeight(80.0);
    dynamicContainer->setStrength(75.0);
    dynamicContainer->loadCargo(goods);

    return dynamicContainer;
}

void display(Container* containerPointer) {
    if (containerPointer) {
        std::cout << "Container Number: " << containerPointer->getNumber() << std::endl;
        std::cout << "Tare Weight: " << containerPointer->getTareWeight() << std::endl;
        std::cout << "Max Weight: " << containerPointer->getMaxWeight() << std::endl;
        std::cout << "Strength: " << containerPointer->getStrength() << std::endl;
        std::cout << "Gross Weight: " << containerPointer->getGrossWeight() << std::endl;
        std::cout << "Net Weight: " << containerPointer->getNetWeight() << std::endl;
        std::cout << "Max Cargo: " << containerPointer->getMaxCargo() << std::endl;
    }
}

void testDynamicObject() {
    Container* dynamicContainer = prepare(3, 25.0);
    display(dynamicContainer);

    delete dynamicContainer;
}

int main() {
    testLocalObject();
    std::cout << "---------------------" << std::endl;
    Container mainContainer(1);
    mainContainer.setTareWeight(10.0);
    mainContainer.setMaxWeight(100.0);
    mainContainer.setStrength(90.0);
    loadAndSend(mainContainer, 30.0);
    std::cout << "---------------------" << std::endl;
    testDynamicObject();

    return 0;
}