// SmartParkingSystem.cpp

#include "SmartParkingSystem.h"
#include <algorithm>
#include <cstdlib>

using namespace std;

SmartParkingSystem::SmartParkingSystem() : totalParkingSpots(0) {}

void SmartParkingSystem::run() {
    while (true) {
        displayMenu();
        int choice;
        cout << "Enter your choice: ";
        cin >> choice;

        MenuChoice selectedChoice = static_cast<MenuChoice>(choice);
        if (selectedChoice >= CHECK_AVAILABILITY && selectedChoice <= EXIT) {
            handleMenuChoice(selectedChoice);
        } else {
            cout << "Invalid choice. Please enter a valid option.\n";
        }
    }
}

void SmartParkingSystem::displayMenu() {
    cout << "Smart Parking System Menu:\n";
    cout << CHECK_AVAILABILITY << ". Check Availability\n"
         << OCCUPY_PARKING_SPOT << ". Occupy Parking Spot\n"
         << VACATE_PARKING_SPOT << ". Vacate Parking Spot\n"
         << AUTOMATED_VEHICLE_STORAGE << ". Automated Vehicle Storage\n"
         << AUTOMATIC_VEHICLE_WITHDRAWAL << ". Automatic Vehicle Withdrawal\n"
         << RESERVATION << ". Reservation\n"
         << DISPLAY_PARKING_STATUS << ". Display Parking Status\n"
         << EXIT << ". Exit\n";
}

void SmartParkingSystem::handleMenuChoice(MenuChoice choice) {
    switch (choice) {
    case CHECK_AVAILABILITY:
        checkParkingAvailability();
        break;
    case OCCUPY_PARKING_SPOT:
        occupyParkingSpot();
        break;
    case VACATE_PARKING_SPOT:
        vacateParkingSpot();
        break;
    case AUTOMATED_VEHICLE_STORAGE:
        automatedVehicleStorage();
        break;
    case AUTOMATIC_VEHICLE_WITHDRAWAL:
        automaticVehicleWithdrawal();
        break;
    case RESERVATION:
        reservation();
        break;
    case DISPLAY_PARKING_STATUS:
        displayParkingStatus();
        break;
    case EXIT:
        cout << "Exiting Smart Parking System. Goodbye!\n";
        exit(0);
    default:
        cout << "Invalid choice. Please enter a valid option.\n";
    }
}

void SmartParkingSystem::checkParkingAvailability() {
    string designated;
    cout << "Is the area designated for parking? (yes/no): ";
    cin >> designated;

    if (designated == "yes") {
        cout << "Enter the number of parking spots: ";
        cin >> totalParkingSpots;

        // Initialize the parking spots vector with the specified number of spots
        parkingSpots.resize(totalParkingSpots, false);
        reservedSpots.resize(totalParkingSpots);
        passwords.resize(totalParkingSpots);
        vehicleNumbers.resize(totalParkingSpots);

        cout << "Number of available parking spots: " << getAvailableParkingSpots() << "\n";
    } else {
        cout << "This area is not designated for parking.\n";
    }
}

int SmartParkingSystem::getAvailableParkingSpots() {
    return count(parkingSpots.begin(), parkingSpots.end(), false);
}

void SmartParkingSystem::occupyParkingSpot() {
    if (getAvailableParkingSpots() > 0) {
        string hasReservedSpot;
        cout << "Do you have a reserved spot? (yes/no): ";
        cin >> hasReservedSpot;

        if (hasReservedSpot == "no") {
            displayAvailableParkingSpots();
            int spotNumber;
            cout << "Choose a spot to park: ";
            cin >> spotNumber;

            if (spotNumber >= 0 && spotNumber < totalParkingSpots && !parkingSpots[spotNumber] && reservedSpots[spotNumber].empty()) {
                string vehicleNumber;
                cout << "Enter your vehicle number: ";
                cin >> vehicleNumber;

                cout << "Vehicle parked successfully in spot " << spotNumber << "\n";
                parkingSpots[spotNumber] = true;
                vehicleNumbers[spotNumber] = vehicleNumber;
            } else {
                cout << "Invalid spot. Please choose a valid and unoccupied spot.\n";
            }
        } else if (hasReservedSpot == "yes") {
            displayReservedParkingSpots();
            string mobileNumber, password;
            cout << "Enter your mobile number: ";
            cin >> mobileNumber;
            cout << "Enter your password: ";
            cin >> password;

            int reservedSpotIndex = findReservedSpotIndex(mobileNumber, password);
            if (reservedSpotIndex != -1 && !parkingSpots[reservedSpotIndex]) {
                cout << "Vehicle parked successfully in reserved spot " << reservedSpotIndex << "\n";
                parkingSpots[reservedSpotIndex] = true;
                vehicleNumbers[reservedSpotIndex] = mobileNumber;
            } else if (reservedSpotIndex == -1) {
                cout << "Invalid mobile number or password. Parking failed.\n";
            } else {
                cout << "Reserved spot " << reservedSpotIndex << " is already occupied or invalid credentials. Parking failed.\n";
            }
        } else {
            cout << "Invalid choice. Please enter 'yes' or 'no' for reserved spot.\n";
        }
    } else {
        cout << "No available parking spots. Parking is full.\n";
    }
}

void SmartParkingSystem::displayReservedParkingSpots() {
    cout << "Reserved Parking Spots:\n";
    for (int i = 0; i < totalParkingSpots; i++) {
        if (!reservedSpots[i].empty()) {
            cout << "Spot " << i << " - Reserved for " << reservedSpots[i] << "\n";
        }
    }
}

void SmartParkingSystem::displayAvailableParkingSpots() {
    cout << "Available Parking Spots:\n";
    for (int i = 0; i < totalParkingSpots; i++) {
        if (!parkingSpots[i] && reservedSpots[i].empty()) {
            cout << "Spot " << i << " - Vacant\n";
        }
    }
}

void SmartParkingSystem::vacateParkingSpot() {
    string vehicleNumber;
    cout << "Enter your vehicle number: ";
    cin >> vehicleNumber;

    int spotIndex = findVehicleInParkingSpots(vehicleNumber);
    if (spotIndex != -1) {
        parkingSpots[spotIndex] = false;
        cout << "Vehicle vacated from spot " << spotIndex << "\n";
    } else {
        cout << "Vehicle not found in the parking spots.\n";
    }
}

void SmartParkingSystem::automatedVehicleStorage() {
    string hasReservedSpot;
    cout << "Do you have a reserved parking spot? (yes/no): ";
    cin >> hasReservedSpot;

    if (hasReservedSpot == "yes") {
        string mobileNumber, password;
        cout << "Enter your mobile number: ";
        cin >> mobileNumber;
        cout << "Enter your password: ";
        cin >> password;

        int reservedSpotIndex = findReservedSpotIndex(mobileNumber, password);
        if (reservedSpotIndex != -1) {
            cout << "Vehicle stored in reserved spot " << reservedSpotIndex << "\n";
        } else {
            cout << "Invalid mobile number or password. Storage failed.\n";
        }
    } else {
        string password;
        int emptyStorageSpot = findEmptyStorageSpot();
        if (emptyStorageSpot != -1) {
            cout << "Enter a password for vehicle storage: ";
            cin >> password;

            string vehicleNumber;
            cout << "Enter your vehicle number: ";
            cin >> vehicleNumber;

            cout << "Vehicle stored in storage spot " << emptyStorageSpot << "\n";
            reservedSpots[emptyStorageSpot] = vehicleNumber;
            passwords[emptyStorageSpot] = password;
        } else {
            cout << "No available storage spots. Storage is full.\n";
        }
    }
}

void SmartParkingSystem::automaticVehicleWithdrawal() {
    string password;
    cout << "Enter the password used for storing the vehicle: ";
    cin >> password;

    int storedSpotIndex = findStoredSpotIndex(password);
    if (storedSpotIndex != -1) {
        cout << "Vehicle withdrawn from storage spot " << storedSpotIndex << "\n";
        reservedSpots[storedSpotIndex] = "";
        passwords[storedSpotIndex] = "";  // Clear the password after withdrawal
    } else {
        cout << "Invalid password. Vehicle withdrawal failed.\n";
    }
}

void SmartParkingSystem::reservation() {
    string mobileNumber, password;
    int spotNumber;
    cout << "Enter your mobile number: ";
    cin >> mobileNumber;
    cout << "Enter your password: ";
    cin >> password;
    cout << "Which spot do you want to reserve? ";
    cin >> spotNumber;

    if (spotNumber >= 0 && spotNumber < totalParkingSpots && !parkingSpots[spotNumber]) {
        cout << "Spot " << spotNumber << " reserved successfully.\n";
        reservedSpots[spotNumber] = mobileNumber;
        passwords[spotNumber] = password;
    } else {
        cout << "Invalid spot. Reservation failed.\n";
    }
}

void SmartParkingSystem::displayParkingStatus() {
    std::cout << "Parking Status:\n";
    for (int i = 0; i < totalParkingSpots; i++) {
        if (!reservedSpots[i].empty()) {
            std::cout << "Spot " << i << " - Reserved for " << reservedSpots[i] << "\n";
        } else if (parkingSpots[i]) {
            std::cout << "Spot " << i << " - Occupied by Vehicle " << vehicleNumbers[i] << "\n";
        } else {
            std::cout << "Spot " << i;
            if (i == getReservedSpotIndex()) {
                std::cout << " - Occupied by Vehicle (VIP)\n";
            } else {
                std::cout << " - Vacant\n";
            }
        }
    }
}


int SmartParkingSystem::getReservedSpotIndex() {
    for (int i = 0; i < totalParkingSpots; i++) {
        if (!reservedSpots[i].empty() && reservedSpots[i] == "VIP") {
            return i;
        }
    }
    return -1;
}

int SmartParkingSystem::findReservedSpotIndex(const string& mobileNumber, const string& password) {
    for (int i = 0; i < totalParkingSpots; i++) {
        if (!reservedSpots[i].empty() && reservedSpots[i] == mobileNumber && passwords[i] == password) {
            return i;
        }
    }
    return -1;
}

int SmartParkingSystem::findVehicleInParkingSpots(const string& vehicleNumber) {
    for (int i = 0; i < totalParkingSpots; i++) {
        if (parkingSpots[i] && vehicleNumbers[i] == vehicleNumber) {
            return i;
        }
    }
    return -1;
}

int SmartParkingSystem::findEmptyStorageSpot() {
    for (int i = 0; i < totalParkingSpots; i++) {
        if (reservedSpots[i].empty()) {
            return i;
        }
    }
    return -1;
}

int SmartParkingSystem::findStoredSpotIndex(const string& password) {
    for (int i = 0; i < totalParkingSpots; i++) {
        if (!passwords[i].empty() && passwords[i] == password) {
            return i;
        }
    }
    return -1;
}
