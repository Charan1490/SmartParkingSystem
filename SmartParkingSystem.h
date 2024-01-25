// SmartParkingSystem.h

#ifndef SMART_PARKING_SYSTEM_H
#define SMART_PARKING_SYSTEM_H

#include <iostream>
#include <vector>
#include <string>

class SmartParkingSystem {
private:
    int totalParkingSpots;
    std::vector<bool> parkingSpots;
    std::vector<std::string> reservedSpots;
    std::vector<std::string> passwords;
    std::vector<std::string> vehicleNumbers;

    enum MenuChoice {
        CHECK_AVAILABILITY = 1,
        OCCUPY_PARKING_SPOT,
        VACATE_PARKING_SPOT,
        AUTOMATED_VEHICLE_STORAGE,
        AUTOMATIC_VEHICLE_WITHDRAWAL,
        RESERVATION,
        DISPLAY_PARKING_STATUS,
        EXIT
    };

public:
    SmartParkingSystem();

    void run();

private:
    void displayMenu();
    void handleMenuChoice(MenuChoice choice);
    void checkParkingAvailability();
    int getAvailableParkingSpots();
    void occupyParkingSpot();
    void displayReservedParkingSpots();
    void displayAvailableParkingSpots();
    void vacateParkingSpot();
    void automatedVehicleStorage();
    void automaticVehicleWithdrawal();
    void reservation();
    void displayParkingStatus();
    int getReservedSpotIndex();
    int findReservedSpotIndex(const std::string& mobileNumber, const std::string& password);
    int findVehicleInParkingSpots(const std::string& vehicleNumber);
    int findEmptyStorageSpot();
    int findStoredSpotIndex(const std::string& password);
};

#endif // SMART_PARKING_SYSTEM_H
