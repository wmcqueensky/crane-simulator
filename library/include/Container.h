//
// Created by Wojciech Mokwiński on 24/10/2023.
//

#ifndef CRANEPROJECT_CONTAINER_H
#define CRANEPROJECT_CONTAINER_H

class Container {
private:
    unsigned int number;
    double tareWeight;
    double maxWeight;
    double strength;
    double cargo;

public:
    // Constructors
    Container();
    Container(int containerNumber);

    // Getters
    int getNumber() const;
    double getTareWeight() const;
    double getMaxWeight() const;
    double getStrength() const;
    double getGrossWeight() const;
    double getNetWeight() const;
    double getMaxCargo() const;

    // Setters
    void setTareWeight(double tareWeight);
    void setMaxWeight(double maxWeight);
    void setStrength(double strength);

    // Load and unloadOnto cargo
    void loadCargo(double amount);
    void unloadCargo(double amount);
};

#endif //CRANEPROJECT_CONTAINER_H
