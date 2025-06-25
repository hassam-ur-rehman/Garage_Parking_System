#include "Vehicle.h"

// Constructor: Initialize the vehicle with its number plate and type
Vehicle::Vehicle(string number, VehicleType t) : numberPlate(number), type(t) {
    entryTime = time(0); // Record the current time as the entry time
}

// Method to calculate parking fees
double Vehicle::calculateFee() {
    time_t currentTime = time(0); // Get the current time
    double hoursParked = difftime(currentTime, entryTime) / 3600.0; // Calculate hours parked

    // Return fee based on vehicle type
    switch (type) {
    case CAR: return hoursParked * 5.0;  // $5 per hour for cars
    case BIKE: return hoursParked * 2.0; // $2 per hour for bikes
    case BUS: return hoursParked * 10.0; // $10 per hour for buses
    default: return 0.0; // Default to $0 for invalid types
    }
}
