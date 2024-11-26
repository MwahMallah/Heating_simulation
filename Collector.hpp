#ifndef __COLLECTOR_HPP
#define __COLLECTOR_HPP


class Collector {
    double _area, _incl;
public:
    Collector(double area, double inclination) 
        : _area(area), _incl(inclination) 
    {}

    double SolarIncidenceCos(double lat, double declination, double hourAngle);

    void SetIncl(double new_incl) {
        _incl = new_incl;
    }
};

#endif