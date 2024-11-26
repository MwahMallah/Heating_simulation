#include "Environment.hpp"

#include "Utils.hpp"

double Environment::SolarDeclination(int day) {
    if (day < 1 || day > 365) {
        throw std::invalid_argument("Day must be between 1 and 365");
    }
    // Formula for solar declination:
    double radians = DegreesToRadians((360 / 365.0) * (284 + day));
    return 23.45 * std::sin(radians);
}    

double Environment::SolarHourAngle(double hour) {
    int coef = 15; //earth rotates 15 degrees by hour
    
    return (hour - 12) * coef;
}

double Environment::DirectSolarIncidenceCos(double sunDeclination, double hourAngle) {
    double sunDeclinationRad = DegreesToRadians(sunDeclination);
    double hourAngleRad = DegreesToRadians(hourAngle);
    double latitudeRad = DegreesToRadians(_lat);

    //parts of the equation:
    //cos(theta z) = cos(latitude) * cos(sun declination) * cos(hour angle) + sin(latitude) * sin(sun declination)
    double leftPart = std::cos(latitudeRad) * std::cos(sunDeclinationRad) * std::cos(hourAngleRad);
    double rightPart = std::sin(latitudeRad) * std::sin(sunDeclinationRad);

    return leftPart + rightPart;
} 