#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>
#include <ctime>
using namespace std;

// Enum to represent different types of vehicles
enum VehicleType { CAR, BIKE, BUS };

// Vehicle class to store vehicle-related information
class Vehicle {
public:
    string numberPlate;  // Unique identifier for the vehicle
    VehicleType type;    // Type of the vehicle (CAR, BIKE, BUS)
    time_t entryTime;    // Entry time for calculating parking duration

    // Constructor to initialize the vehicle
    Vehicle(string number, VehicleType t);

    // Method to calculate parking fee based on duration
    double calculateFee();
};

#endif
