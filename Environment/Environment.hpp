#ifndef __ENVIRONMENT_HPP
#define __ENVIRONMENT_HPP

#include <math.h>
#include <iostream>

//class that represents current environment
class Environment {
    double _lat, _azimuth, _height, _avgTmp, _tmpDiff;
    double AtmosphericTransparency(double directSolarIncidenceCos); 
public:
    Environment(double lat, double azimuth, double height, double avgTemp, double tempDiff) 
        : _lat(lat), _azimuth(azimuth), _height(height), _avgTmp(avgTemp), _tmpDiff(tempDiff / 2) {}
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

    // 
    double SolarIrradianceOnHorizontalSurface(int day, double hour, double collector_incl, double collectorSolarIncidenceCos);

    double OutsideTemp(double hour);
};

#endif