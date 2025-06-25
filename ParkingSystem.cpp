#include "ParkingSystem.h"
#include <iostream>
#include <fstream>
using namespace std;

// SpotNode constructor to initialize a parking spot
SpotNode::SpotNode(int l, int s)
    : level(l), spot(s), reserved(false), vehicle(NULL), left(NULL), right(NULL) {}

// ParkingSystem constructor to initialize levels and spots
ParkingSystem::ParkingSystem(int l, int s)
    : levels(l), spotsPerLevel(s), totalRevenue(0), availableSpots(NULL) {
    // Initialize the parking lot as a 2D array
    for (int i = 0; i < levels; ++i) {
        vector<SpotNode*> levelSpots;
        for (int j = 0; j < spotsPerLevel; ++j) {
            SpotNode* spot = new SpotNode(i, j);
            availableSpots = insertSpot(availableSpots, i, j); // Add spot to BST
            levelSpots.push_back(spot);
        }
        parkingLot.push_back(levelSpots);
    }
    loadDataFromFile(); // Load previous parking data if available
}

// Destructor to clean up resources
ParkingSystem::~ParkingSystem() {
    saveDataToFile(); // Save parking data before shutting down
    for (auto& level : parkingLot) {
        for (auto& spot : level) {
            delete spot; // Free memory for each parking spot
        }
    }
}

// Insert a parking spot into the BST
SpotNode* ParkingSystem::insertSpot(SpotNode* root, int level, int spot) {
    if (!root) return new SpotNode(level, spot); // Create a new node if BST is empty
    if (level < root->level || (level == root->level && spot < root->spot)) {
        root->left = insertSpot(root->left, level, spot);
    }
    else {
        root->right = insertSpot(root->right, level, spot);
    }
    return root;
}

// Find and remove the nearest available spot from the BST
SpotNode* ParkingSystem::findAndRemoveSpot(SpotNode* root, SpotNode*& found) {
    if (!root) return NULL; // Return NULL if BST is empty
    if (!root->left) {      // If no left child, this is the smallest node
        found = root;
        return root->right; // Replace with right subtree
    }
    root->left = findAndRemoveSpot(root->left, found);
    return root;
}
void ParkingSystem::allocateSpot(string vehicleNumber, VehicleType type) {
    if (!availableSpots) {
        cout << "No available spots.\n";
        return;
    }
    SpotNode* found = NULL;
    availableSpots = findAndRemoveSpot(availableSpots, found);

    Vehicle* vehicle = new Vehicle(vehicleNumber, type);
    found->vehicle = vehicle;
    found->reserved = true;

    // Update the parking lot grid to reflect the reserved spot
    parkingLot[found->level][found->spot]->reserved = true;
    parkingLot[found->level][found->spot]->vehicle = vehicle;

    activeVehicles[vehicleNumber] = found; // Add to active vehicles map
    cout << "Allocated Spot - Level: " << found->level << ", Spot: " << found->spot
        << " for a " << (type == CAR ? "Car" : (type == BIKE ? "Bike" : "Bus")) << "\n";
}
void ParkingSystem::freeSpot(string vehicleNumber) {
    if (activeVehicles.find(vehicleNumber) == activeVehicles.end()) {
        cout << "Vehicle not found.\n";
        return;
    }

    SpotNode* spot = activeVehicles[vehicleNumber];
    double fee = spot->vehicle->calculateFee();
    totalRevenue += fee;
    cout << "Freed Spot - Level: " << spot->level << ", Spot: " << spot->spot << ", Fee: $" << fee << "\n";

    // Free the spot and update the grid
    delete spot->vehicle;
    spot->vehicle = NULL;
    spot->reserved = false;

    parkingLot[spot->level][spot->spot]->reserved = false;
    parkingLot[spot->level][spot->spot]->vehicle = NULL;

    activeVehicles.erase(vehicleNumber);
    availableSpots = insertSpot(availableSpots, spot->level, spot->spot);
}


void ParkingSystem::displayParkingLot() {
    cout << "\n--- Parking Lot ---\n";

    // Loop through each level
    for (int i = 0; i < levels; ++i) {
        cout << "Level " << i + 1 << ": ";

        // Loop through each spot on the level
        for (int j = 0; j < spotsPerLevel; ++j) {
            // Check if the spot is reserved
            if (parkingLot[i][j]->reserved) {
                cout << "[1] "; // Occupied spot
            }
            else {
                cout << "[0] "; // Free spot
            }
        }
        cout << "\n";
    }
    cout << endl;
}


// Display available spots
void ParkingSystem::displayAvailableSpots() {
    cout << "Available Spots:\n";
    displayBST(availableSpots);
}

// In-order traversal of the BST to display available spots
void ParkingSystem::displayBST(SpotNode* root) {
    if (!root) return;
    displayBST(root->left);
    cout << "Level " << root->level << ", Spot " << root->spot << endl;
    displayBST(root->right);
}

// Save parking data to a file
void ParkingSystem::saveDataToFile() {
    ofstream file("parking_data.txt");
    for (const auto& entry : activeVehicles) {
        file << entry.first << " " << entry.second->level << " " << entry.second->spot << endl;
    }
    file.close();
}

// Load parking data from a file
void ParkingSystem::loadDataFromFile() {
    ifstream file("parking_data.txt");
    string vehicleNumber;
    int level, spot;
    while (file >> vehicleNumber >> level >> spot) {
        allocateSpot(vehicleNumber, CAR); // Assuming all loaded vehicles are cars
    }
    file.close();
}

void ParkingSystem::emptyAllParkingSpots() {
    // Loop through all active vehicles
    for (auto it = activeVehicles.begin(); it != activeVehicles.end(); ) {
        SpotNode* spot = it->second; // Get the parking spot associated with the vehicle
        double fee = spot->vehicle->calculateFee(); // Calculate the parking fee
        totalRevenue += fee; // Add the fee to the total revenue
        cout << "Freed Spot - Level: " << spot->level << ", Spot: " << spot->spot
            << ", Fee: $" << fee << " (Vehicle: " << it->first << ")\n";

        delete spot->vehicle; // Free the vehicle memory
        spot->vehicle = NULL;
        spot->reserved = false;

        // Add the spot back to the available BST
        availableSpots = insertSpot(availableSpots, spot->level, spot->spot);

        // Erase the vehicle from the active vehicles map
        it = activeVehicles.erase(it);
    }
    cout << "All parking spots have been emptied.\n";
}
