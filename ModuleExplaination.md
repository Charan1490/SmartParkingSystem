# SmartParkingSystem
PBL Files 3rd sem
SmartParkingSystem.h
Explanation:
Class Definition (class SmartParkingSystem): This class encapsulates the functionality of a smart parking system.

Private Data Members:

totalParkingSpots: Total number of parking spots.
parkingSpots: Vector to represent the occupancy status of each parking spot.
reservedSpots: Vector to store information about reserved spots.
passwords: Vector to store passwords associated with reserved spots.
vehicleNumbers: Vector to store vehicle numbers associated with occupied spots.
Private Enum (enum MenuChoice): Enumeration to represent the menu choices.

Public Member Functions:

SmartParkingSystem(): Constructor for initializing the smart parking system.
run(): Main function to run the smart parking system.
Private Member Functions:

displayMenu(): Display the menu options.
handleMenuChoice(MenuChoice choice): Handle user input based on the selected menu choice.
Other functions to implement specific functionalities like checking availability, occupying spots, displaying status, etc.

SmartParkingSystem.cpp
Explanation:
Implementation of Constructor (SmartParkingSystem::SmartParkingSystem()): Initializes totalParkingSpots to 0.

Implementation of run() function: The main loop that displays the menu and handles user input.

Implementation of Other Member Functions: Further implementation of member functions for the smart parking system.

main.cpp
Explaination
main() Function: Entry point of the program. Creates an instance of SmartParkingSystem and calls its run() method.

Summary:
This modularized code separates the declaration (header file) from the implementation (source file) of the SmartParkingSystem class. The header file defines the class structure, member variables, and function prototypes, while the source file contains the actual implementation of the class methods. This separation enhances code organization, readability, and maintainability. The main.cpp file serves as the entry point for the program, creating an instance of the smart parking system and initiating its execution.
