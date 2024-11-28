#include "Environment.hpp"

#include "../Utils/Utils.hpp"

const int SOLAR_CONST = 1367;

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

double Environment::AtmosphericTransparency(double directSolarIncidenceCos) {
    //from table
    const double r0 = 0.985;  
    const double r1 = 0.9925; 
    const double rk = 1.0125; 
    
    double a0 = r0 * (0.4237 - 0.00821 * std::pow((6 - _height), 2));
    double a1 = r1 * (0.5055 - 0.00595 * std::pow((6.5 - _height), 2));
    double k  = rk * (0.2711 - 0.01858 * std::pow((2.5 - _height), 2));

    double expArg = -k / directSolarIncidenceCos;

    return a0 + a1 * std::exp(expArg);
}

double DiffusionCoef(double transparencyCoef) {
    return 0.271 - 0.294 * transparencyCoef;
}

double ReflectionCoef(double transparencyCoef) {
    return 0.271 + 0.706 * transparencyCoef;
}

double Environment::SolarIrradianceOnHorizontalSurface(int day, double hour, double collector_incl, double collectorSolarIncidenceCos) {
    const double rho = 0.3;

    double daysRad = DegreesToRadians((360 * day) / 365);
    double extraterRadiation = SOLAR_CONST * (1 + 0.033 * std::cos(daysRad));
    double sunDeclination = Environment::SolarDeclination(day);
    double hourAngle = Environment::SolarHourAngle(hour);

    double directSolarIncidenceCos = Environment::DirectSolarIncidenceCos(sunDeclination, hourAngle);
    double transparencyCoef = AtmosphericTransparency(directSolarIncidenceCos);
    double difCoef = DiffusionCoef(transparencyCoef);
    double reflCoef = ReflectionCoef(transparencyCoef);
    double halfCos = (1 + std::cos(DegreesToRadians(collector_incl))) / 2;

    double directIrradiance = extraterRadiation * transparencyCoef * collectorSolarIncidenceCos; 
    double diffuseIrradiance = extraterRadiation * directSolarIncidenceCos * difCoef * halfCos;
    double reflectionIrradiance = rho * extraterRadiation * directSolarIncidenceCos * reflCoef * halfCos;

    return std::max(0.0, directIrradiance + diffuseIrradiance + reflectionIrradiance);
}

double Environment::OutsideTemp(double hour) {
    // Normalize hour (0–24 -> 0–2pi)
    double normalizedHour = (hour / 24.0) * 2.0 * M_PI;

    // Temperature based on hour
    return _avgTmp + _tmpDiff * std::sin(normalizedHour - M_PI / 2.0);
}