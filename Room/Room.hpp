#ifndef __ROOM_HPP
#define __ROOM_HPP

class Room {
    // Height of the room in meters (default value is 3)
    double _height = 3;
    // Total length of the wall exposed to the outside in meters
    // This value represents the cumulative length of all external walls
    double _outWallLength;
    // Thermal conductivity of the wall material (W/m·C)
    // default aerated concrete
    const double _wallThermalConductivity = 0.3;
    // Thermal conductivity of the roof material (W/m·C)
    // default for bituminous shingles roofing
    const double _roofThermalConductivity = 0.5;
    // Thermal resistance of the window ((m^2·C/W))
    const double _windowThermalResistance = 0.7;
    // Thickness of the external wall in meters
    double _outWallThickness;
    // Total length of the wall facing the interior in meters
    // This value represents the cumulative length of all internal walls
    double _inWallLength;
    // Total length of all windows in meters
    // This value represents the cumulative length of all windows in the room
    double _windowLength;
    // Height windows in meters
    double _windowHeight;
    // Length of the room in meters
    double _roomLength;
    // Width of the room in meters
    double _roomWidth;
    // Thickness of the walls and roof (in meters)
    // This includes the wall thickness and the roof thickness for heat loss calculations
    double _roofThickness;
    // Internal temperature of the room (°C)
    double _tmp;
    // Method for calculating heat loss through the external walls
    double GetHeatLossWalls(double outsideTemp);
    // Method for calculating heat loss through the roof
    double GetHeatLossRoof(double outsideTemp);
    // Method for calculating heat loss through the windows
    double GetHeatLossWindows(double outsideTemp);
public:
    Room(double outWallLength, double outWallThickness, double inWallLength, double windowLength, 
         double windowHeight, double roomLength, double roomWidth, double roofThickness, double tmp)
         : _outWallLength(outWallLength), _outWallThickness(outWallThickness), _inWallLength(inWallLength),
           _windowLength(windowLength), _windowHeight(windowHeight), _roomLength(roomLength), 
           _roomWidth(roomWidth), _roofThickness(roofThickness), _tmp(tmp) 
    {}

    // Method for calculating total heat loss (in watts) based on outside and inside temperatures
    double GetHeatLoss(double outsideTemp);
};

#endif
