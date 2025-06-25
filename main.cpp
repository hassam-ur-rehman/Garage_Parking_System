#include "ParkingSystem.h"
#include <iostream>
using namespace std;

int main() {
    ParkingSystem ps(3, 5); // Initialize with 3 levels, 5 spots per level

    int choice;
    string number;
    do {
        cout << "\n--- Parking System ---\n";
        cout << "1. Park Vehicle\n";
        cout << "2. Free Spot\n";
        cout << "3. Display Parking Lot\n";
        cout << "4. Display Available Spots\n";
        cout << "5. Empty All Parking Spots\n"; 
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            cout << "Enter vehicle number: ";
            cin >> number;
            int typeChoice;
            cout << "Enter vehicle type (1 = Car, 2 = Bike, 3 = Bus): ";
            cin >> typeChoice;

            VehicleType type;
            switch (typeChoice) {
            case 1: type = CAR; break;
            case 2: type = BIKE; break;
            case 3: type = BUS; break;
            default:
                cout << "Invalid type. Defaulting to Car.\n";
                type = CAR;
            }

            ps.allocateSpot(number, type);
            break;
        }
        case 2:
            cout << "Enter vehicle number: ";
            cin >> number;
            ps.freeSpot(number);
            break;
        case 3:
            ps.displayParkingLot();
            break;
        case 4:
            ps.displayAvailableSpots();
            break;
        case 6:
            cout << "Exiting...\n";
            break;
        case 5:
            ps.emptyAllParkingSpots();
            break;

        default:
            cout << "Invalid choice.\n";
        }
    } while (choice != 6);

    return 0;
}
