# Crane simulator

This project provides a C++ implementation for managing containers in a storage system, simulating operations such as loading, unloading, stacking, and transporting containers using cranes and trucks.

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Technologies Used](#technologies-used)
- [How to Use](#how-to-use)

## Introduction

The Container Management System is designed to facilitate the handling of containers within a storage environment. It includes classes for managing individual containers, stacks of containers, trucks for transportation, and cranes for loading and unloading.

## Features

- Creation and management of individual containers with specified properties such as weight, number, and cargo capacity.
- Stacking containers in a container stack with a predefined maximum height.
- Loading and unloading containers onto trucks using cranes, considering weight limitations and available space.
- Implementation of different loading strategies for optimized container placement.

## Technologies Used

- **C++**: The project is written in C++ to ensure efficiency and performance.
- **Boost.Test**: Unit testing is conducted using the Boost.Test framework to ensure code reliability.
- **CMake**: The project includes a CMakeLists.txt file for building the project using CMake.

## How to Use
1. **Clone the Repository**: Clone this repository to your local machine using the following command:

git clone [https://github.com/wmcqueensky/crane-simulator.git](https://github.com/wmcqueensky/crane-simulator.git)

2. **Compile the Code**: Compile the code using your preferred C++ compiler. Ensure that Boost.Test is properly installed and configured for running tests.

3. **Include Headers**: Ensure that the necessary header files (`Container.h`, `ContainerStack.h`, `Crane.h`, `Truck.h`, `Loadable.h`, `LoadStrategy.h`) are included in your project.

4. **Use Classes**: Utilize the provided classes (`Container`, `ContainerStack`, `Crane`, `Truck`, `Loadable`, `LoadStrategy`) in your application to manage containers and simulate container handling operations.
