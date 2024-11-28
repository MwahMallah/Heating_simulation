#include "Collector.hpp"

#include "math.h"
#include "../Utils/Utils.hpp"

double Collector::SolarIncidenceCos(double lat, double declination, double hourAngle) {
    double latMinusInclRad = DegreesToRadians(lat - _incl); 
    double declinationRad = DegreesToRadians(declination);
    double hourAngleRad = DegreesToRadians(hourAngle);

    // parts of the equation:
    // cos(lat minus inclination) * cos(declination) * cos(hour angle) + sin(lat minus inclination) * sin(declination)
    double leftPart  = std::cos(latMinusInclRad) * std::cos(declinationRad) * std::cos(hourAngleRad);
    double rightPart = std::sin(latMinusInclRad) * std::sin(declinationRad);

    return leftPart + rightPart; 
}

double Collector::UsefulEnergy(double solarIrradiance, double envTemp) {
    //equation:
    //energy = heat transfer factor * Area * [irradiance * transmittance - heat loss coef * (T col - T env)] 
    double leftPart = _heatTransferFactor * _area;
    double rightPart = solarIrradiance * _absorptanceTransmittance - _heatLossCoef * (_temp - envTemp);

    return std::max(0.0, leftPart * rightPart);
}