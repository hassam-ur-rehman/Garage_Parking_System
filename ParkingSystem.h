#ifndef PARKING_SYSTEM_H
#define PARKING_SYSTEM_H

#include "Vehicle.h"
#include <vector>
#include <map>
using namespace std;

// Node structure for managing parking spots in a Binary Search Tree (BST)
struct SpotNode {
    int level;               // Level of the parking spot
    int spot;                // Spot number on the level
    bool reserved;           // Indicates if the spot is reserved
    Vehicle* vehicle;        // Pointer to the vehicle parked in this spot
    SpotNode* left;          // Left child in the BST
    SpotNode* right;         // Right child in the BST

    // Constructor to initialize a parking spot node
    SpotNode(int l, int s);
};

// ParkingSystem class to manage the entire parking lot
class ParkingSystem {
private:
    int levels;                            // Total number of levels in the parking lot
    int spotsPerLevel;                     // Number of spots per level
    int totalRevenue;                      // Total revenue collected
    SpotNode* availableSpots;              // Root of the BST for managing available spots
    vector<vector<SpotNode*>> parkingLot;  // 2D array representation of the parking lot
    map<string, SpotNode*> activeVehicles; // Map of active vehicles and their corresponding spots

    // Helper methods
    SpotNode* insertSpot(SpotNode* root, int level, int spot);      // Insert a spot into the BST
    SpotNode* findAndRemoveSpot(SpotNode* root, SpotNode*& found); // Find and remove a spot from the BST
    void displayBST(SpotNode* root);                               // Display available spots using in-order traversal
    void saveDataToFile();                                         // Save parking data to a file
    void loadDataFromFile();                                       // Load parking data from a file

public:
    // Constructor and destructor
    ParkingSystem(int levels, int spotsPerLevel);
    ~ParkingSystem();

    // Core functionalities
    void allocateSpot(string vehicleNumber, VehicleType type); // Allocate a parking spot
    void freeSpot(string vehicleNumber);                      // Free an occupied parking spot
    void displayParkingLot();                                 // Display the current parking lot status
    void displayAvailableSpots();                            // Display all available spots
    void emptyAllParkingSpots();
    // Generate a report with revenue and occupancy details
};

#endif
