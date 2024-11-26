#ifndef __ENVIRONMENT_HPP
#define __ENVIRONMENT_HPP

#include <math.h>
#include <iostream>

class Environment {
    double _lat, _azimuth;
public:
    Environment(double lat, double azimuth) : _lat(lat), _azimuth(azimuth) {}
    // Static method to calculate solar declination based on the day of the year
    // Returns the value in degrees
    static double SolarDeclination(int day);

    // Static method to calculate solar hour angle based on the hour of the day
    // Returns the value in degrees
    static double SolarHourAngle(double hour);

    // Method to calculate the cosine of the direct solar incidence angle 
    // on a horizontal surface at given sun declination, hour angle and latitude 
    // all taken in degrees
    double DirectSolarIncidenceCos(double sunDeclination, double hourAngle);
};

#endif