#include "RoomFactory.hpp"

// Function to create a default Kitchen
Room createDefaultKitchen() {
    // Default parameters for a kitchen
    double outWallLength = 7.81;  // Length of the external wall (m)
    double outWallThickness = 0.5;  // Thickness of the external wall (m)
    double inWallLength = 7.41;   // Length of the internal wall (m)
    double windowLength = 0.6;    // Length of windows (m)
    double windowHeight = 1.5;    // Height of windows (m)
    double roomLength = 5.76;     // Length of the room (m)
    double roomWidth = 2.65;      // Width of the room (m)
    double roofThickness = 0.25;  // Thickness of the roof (m)
    double internalTemp = 21.0;   // Internal temperature of the room (°C)

    // Create and return the room object
    return Room(outWallLength, outWallThickness, inWallLength, windowLength, windowHeight, roomLength, roomWidth, roofThickness, internalTemp);
}

// Function to create a default Bedroom
Room createDefaultBedroom() {
    // Default parameters for a bedroom
    double outWallLength = 5.85;  // Length of the external wall (m)
    double outWallThickness = 0.5;  // Thickness of the external wall (m)
    double inWallLength = 6.35;   // Length of the internal wall (m)
    double windowLength = 1;    // Length of windows (m)
    double windowHeight = 1.5;    // Height of windows (m)
    double roomLength = 4.6;      // Length of the room (m)
    double roomWidth = 2;       // Width of the room (m)
    double roofThickness = 0.25;  // Thickness of the roof (m)
    double internalTemp = 21.0;   // Internal temperature of the room (°C)

    // Create and return the room object
    return Room(outWallLength, outWallThickness, inWallLength, windowLength, windowHeight, roomLength, roomWidth, roofThickness, internalTemp);
}

// Function to create a default Living Room
Room createDefaultLivingRoom() {
    // Default parameters for a living room
    double outWallLength = 8.865;  // Length of the external wall (m)
    double outWallThickness = 0.5;  // Thickness of the external wall (m)
    double inWallLength = 4.6 + 1.5;   // Length of the internal wall (m)
    double windowLength = 2;   // Length of windows (m)
    double windowHeight = 2;    // Height of windows (m)
    double roomLength = 5.6;     // Length of the room (m)
    double roomWidth = 4.765;       // Width of the room (m)
    double roofThickness = 0.25;   // Thickness of the roof (m)
    double internalTemp = 21.0;   // Internal temperature of the room (°C)

    // Create and return the room object
    return Room(outWallLength, outWallThickness, inWallLength, windowLength, windowHeight, roomLength, roomWidth, roofThickness, internalTemp);
}

// Function to create a default Bathroom
Room createDefaultBathroom() {
    // Default parameters for a bathroom
    double outWallLength = 1.5;  // Length of the external wall (m)
    double outWallThickness = 0.5;  // Thickness of the external wall (m)
    double inWallLength = 4.35 + 1.5;   // Length of the internal wall (m)
    double windowLength = 0;    // Length of windows (m)
    double windowHeight = 0;    // Height of windows (m)
    double roomLength = 4.35;      // Length of the room (m)
    double roomWidth = 1.5;       // Width of the room (m)
    double roofThickness = 0.3;   // Thickness of the roof (m)
    double internalTemp = 21.0;   // Internal temperature of the room (°C)

    // Create and return the room object
    return Room(outWallLength, outWallThickness, inWallLength, windowLength, windowHeight, roomLength, roomWidth, roofThickness, internalTemp);
}

// Function to create a default Hallway
Room createDefaultHallway() {
    // Default parameters for a hallway
    double outWallLength = 5.03;  // Length of the external wall (m)
    double outWallThickness = 0.5;  // Thickness of the external wall (m)
    double inWallLength = 5.03;   // Length of the internal wall (m)
    double windowLength = 1.2;    // Length of windows (m)
    double windowHeight = 2.0;    // Height of windows (m)
    double roomLength = 5.03;      // Length of the room (m)
    double roomWidth = 1.2;       // Width of the room (m)
    double roofThickness = 0.3;   // Thickness of the roof (m)
    double internalTemp = 21.0;   // Internal temperature of the room (°C)

    // Create and return the room object
    return Room(outWallLength, outWallThickness, inWallLength, windowLength, windowHeight, roomLength, roomWidth, roofThickness, internalTemp);
}
