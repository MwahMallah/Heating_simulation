#ifndef __COLLECTOR_HPP
#define __COLLECTOR_HPP

class Collector {
    double _area, _incl, _heatTransferFactor;
    double _absorptanceTransmittance, _heatLossCoef, _temp;
public:
    Collector(double area, double inclination, 
        double heatTransferFactor, double absorptanceTransmittance, double heatLossCoef,
        double temp) 
        : _area(area), _incl(inclination), _heatTransferFactor(heatTransferFactor),
          _absorptanceTransmittance(absorptanceTransmittance), _heatLossCoef(heatLossCoef), 
          _temp(temp)
    {}

    double SolarIncidenceCos(double lat, double declination, double hourAngle);

    void SetIncl(double new_incl) {
        _incl = new_incl;
    }

    double GetIncl() {
        return _incl;
    }

    double UsefulEnergy(double solarIrradiance, double envTemp);
};

#endif