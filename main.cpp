#include <iostream>
#include <cstring>
#include <vector>
#include <fstream>

#include "Environment.hpp"
#include "Collector.hpp"

using std::cout;
using std::endl;

void parse_arguments(int& start_day, int& timespan, double& lat, 
    double& azimuth, double& c_incl, double& c_area, int argc, char** argv) {
    for (int i = 1; i < argc; ++i) {
        if ((strcmp(argv[i], "--timespan") == 0 || (strcmp(argv[i], "--t") == 0)) && (i + 1 < argc)) {
            timespan = std::stoi(argv[++i]);
        } else if (strcmp(argv[i], "--latitude") == 0 && i + 1 < argc) {
            lat = std::stod(argv[++i]);
        } else if ((strcmp(argv[i], "--start_day") == 0 || (strcmp(argv[i], "--start") == 0)) && (i + 1 < argc)) { 
            start_day = std::stod(argv[++i]);
        } else if ((strcmp(argv[i], "--collector_inclination") == 0 || (strcmp(argv[i], "--col_i") == 0)) && (i + 1 < argc)) { 
            c_incl = std::stod(argv[++i]);
        } else if ((strcmp(argv[i], "--area") == 0 || (strcmp(argv[i], "--a") == 0)) && (i + 1 < argc)) { 
            c_area = std::stod(argv[++i]);
        } else if (strcmp(argv[i], "--azimuth") == 0 && i + 1 < argc) {
            azimuth = std::stod(argv[++i]);
        }
    }
}

void plot_seasonal_energy_ratio_by_tilt(int start_day, int timespan, int latitude, 
    Environment& env, Collector& collector) 
{
    std::vector<int> inclination_angles = {10, 20, 30, 40, 50, 60, 70, 80, 90};

    std::ofstream seasonal_energy_ratio_by_tilt("seasonal_energy_ratio_by_tilt.dat");
    int hour = 12;
    double hourAngle = Environment::SolarHourAngle(hour);

    for (int day = start_day; day < start_day + timespan; day++) {
        double declination = Environment::SolarDeclination(day);
        double directSolarIncidenceCos = env.DirectSolarIncidenceCos(declination, hourAngle);
        seasonal_energy_ratio_by_tilt << day << " ";

        for (int incl : inclination_angles) {
            collector.SetIncl(incl);
            double collectorSolarIncidenceCos = collector.SolarIncidenceCos(latitude, declination, hourAngle);
            double ratio = collectorSolarIncidenceCos / directSolarIncidenceCos;
            seasonal_energy_ratio_by_tilt << ratio << " ";
        }

        seasonal_energy_ratio_by_tilt << endl;
    }
}

void plot_hourly_energy_ratio_by_tilt(int latitude, Environment& env, Collector& collector) {
    std::vector<int> inclination_angles = {10, 30, 90};

    std::ofstream hourly_energy_ratio_by_tilt("hourly_energy_ratio_by_tilt.dat");
    int day = 182; //1st of June
    double declination = Environment::SolarDeclination(day);

    for (int hour = 6; hour <= 18; hour += 1) {
        double hourAngle = Environment::SolarHourAngle(hour);
        double directSolarIncidenceCos = env.DirectSolarIncidenceCos(declination, hourAngle);
        hourly_energy_ratio_by_tilt << hour << " ";

        for (int incl : inclination_angles) {
            collector.SetIncl(incl);
            double collectorSolarIncidenceCos = collector.SolarIncidenceCos(latitude, declination, hourAngle);
            double ratio = collectorSolarIncidenceCos / directSolarIncidenceCos;
            hourly_energy_ratio_by_tilt << ratio << " ";
        }

        hourly_energy_ratio_by_tilt << endl;
    }
}

int main(int argc, char* argv[]) {
    if (argc < 7) {
        cout << "Insufficient arguments!" << endl;
        return 1;
    }

    int timespan = 0;
    int start_day = 0;
    double latitude = 0.0;
    double azimuth = 0.0;
    double collector_inclination = 0.0; 
    double collector_area = 0.0;
    parse_arguments(start_day, timespan, latitude, azimuth, collector_inclination, collector_area, argc, argv);

    Environment env(latitude, azimuth);
    Collector collector(collector_area, collector_inclination);

    plot_seasonal_energy_ratio_by_tilt(start_day, timespan, latitude, env, collector);

    plot_hourly_energy_ratio_by_tilt(latitude, env, collector);

    return 0;
}
