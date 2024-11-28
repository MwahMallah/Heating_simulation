#include "Room.hpp"

#include <iostream>

double fourierEquation(double tmpDiff, double thermalResistance, double area);

double Room::GetHeatLossWalls(double outTmp) {
    double tmpDiff = _tmp - outTmp;
    double area = _outWallLength * _height;
    double thermalResistance = _outWallThickness / _wallThermalConductivity;

    return fourierEquation(tmpDiff, thermalResistance, area);
}

double Room::GetHeatLossRoof(double outTmp) {
    double tmpDiff = _tmp - outTmp;
    double area = _roomWidth * _roomLength;
    double thermalResistance = _roofThickness / _roofThermalConductivity;

    return fourierEquation(tmpDiff, thermalResistance, area);
}

double Room::GetHeatLossWindows(double outTmp) {
    double tmpDiff = _tmp - outTmp;
    double area = _windowLength * _windowHeight;
    double thermalResistance = _windowThermalResistance;

    return fourierEquation(tmpDiff, thermalResistance, area);    
}

double Room::GetHeatLoss(double outTmp) {
    double outWalls = GetHeatLossWalls(outTmp);
    double roof = GetHeatLossRoof(outTmp);
    double windows = GetHeatLossWindows(outTmp);

    return outWalls + roof + windows;
}

double fourierEquation(double tmpDiff, double thermalResistance, double area) {
    return (tmpDiff * area) / thermalResistance;
}