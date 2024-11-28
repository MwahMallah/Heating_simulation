#include <iostream>
#include <cstring>
#include <vector>
#include <fstream>

#include "Environment/Environment.hpp"
#include "Collector/Collector.hpp"
#include "RoomFactory/RoomFactory.hpp"
#include "House/House.hpp"

using std::cout;
using std::endl;

void parse_arguments(int& start_day, int& timespan, double& start_hour, double& lat, double& envAvgTemp, double& envTempDifference,
    double& azimuth, double& altitude, double& c_incl, double& c_area, double& c_heatTransfer, double& c_AbsorpTransm,
    int argc, char** argv) {
    for (int i = 1; i < argc; ++i) {
        if ((strcmp(argv[i], "--timespan") == 0 || (strcmp(argv[i], "--t") == 0)) && (i + 1 < argc)) {
            timespan = std::stoi(argv[++i]);
        } else if (strcmp(argv[i], "--latitude") == 0 && i + 1 < argc) {
            lat = std::stod(argv[++i]);
        } else if ((strcmp(argv[i], "--env_avg_tmp") == 0 || (strcmp(argv[i], "--out_tmp") == 0)) && (i + 1 < argc)) { 
            envAvgTemp = std::stod(argv[++i]);
        } else if ((strcmp(argv[i], "--env_diff_tmp") == 0 || (strcmp(argv[i], "--out_tmp_diff") == 0)) && (i + 1 < argc)) { 
            envTempDifference = std::stod(argv[++i]);
        } else if ((strcmp(argv[i], "--start_day") == 0 || (strcmp(argv[i], "--dStart") == 0)) && (i + 1 < argc)) { 
            start_day = std::stod(argv[++i]);
        } else if ((strcmp(argv[i], "--start_hour") == 0 || (strcmp(argv[i], "--hStart") == 0)) && (i + 1 < argc)) { 
            start_hour = std::stod(argv[++i]);
        } else if ((strcmp(argv[i], "--altitude") == 0 || (strcmp(argv[i], "--a") == 0) || (strcmp(argv[i], "--h") == 0)) && (i + 1 < argc)) { 
            altitude = std::stod(argv[++i]);
        } else if ((strcmp(argv[i], "--collector_inclination") == 0 || (strcmp(argv[i], "--col_i") == 0)) && (i + 1 < argc)) { 
            c_incl = std::stod(argv[++i]);
        } else if ((strcmp(argv[i], "--heat_transfer") == 0 || (strcmp(argv[i], "--ht") == 0)) && (i + 1 < argc)) { 
            c_heatTransfer = std::stod(argv[++i]);
        } else if ((strcmp(argv[i], "--collector_absorptance") == 0 || (strcmp(argv[i], "--absorp") == 0)) && (i + 1 < argc)) { 
            c_AbsorpTransm = std::stod(argv[++i]);
        } else if ((strcmp(argv[i], "--area") == 0 || (strcmp(argv[i], "--a") == 0)) && (i + 1 < argc)) { 
            c_area = std::stod(argv[++i]);
        } else if (strcmp(argv[i], "--azimuth") == 0 && i + 1 < argc) {
            azimuth = std::stod(argv[++i]);
        }
    }
}

void plot_seasonal_energy_ratio_by_tilt(int latitude, Environment& env, Collector& collector) 
{
    std::vector<int> inclination_angles = {10, 20, 30, 40, 50, 60, 70, 80, 90};

    std::ofstream seasonal_energy_ratio_by_tilt("PlotData/seasonal_energy_ratio_by_tilt.dat");
    int hour = 12;
    double hourAngle = Environment::SolarHourAngle(hour);
    int start_day = 1; 
    int timespan = 365;

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

    std::ofstream hourly_energy_ratio_by_tilt("PlotData/hourly_energy_ratio_by_tilt.dat");
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

double get_useful_collector_energy(Collector& collector, Environment& env, int day, double latitude, double hour) {
    double collectorInclination = collector.GetIncl();
    double declination = Environment::SolarDeclination(day);
    double hourAngle = Environment::SolarHourAngle(hour);

    double collectorSolarIncidenceCos = collector.SolarIncidenceCos(latitude, declination, hourAngle);

    double solarIrradiance = env.SolarIrradianceOnHorizontalSurface(day, hour, 
                                    collectorInclination, collectorSolarIncidenceCos);

    double usefulEnergy = collector.UsefulEnergy(solarIrradiance, env.OutsideTemp(hour));
    return usefulEnergy;
}

void simulate_power_balance_by_hour
    (Collector& collector, Environment& env, House& house, int day, double latitude) {

    std::ofstream power_balance_by_hour("PlotData/power_balance_by_hour.dat");
    
    for (double hour = 0; hour <= 24; hour += 0.5) {
        double collectorEnergy = get_useful_collector_energy(collector, env, day, latitude, hour);
        double houseLossEnergy = house.GetHeatLoss(env.OutsideTemp(hour));

        cout << "At time: " << hour << " hours" << endl;
        cout << "Collector's energy: " << collectorEnergy  << " W" << endl;
        cout << "House loss: " << houseLossEnergy << " W" << endl;
        cout << endl;

        //add new graph data
        power_balance_by_hour << hour << " " << collectorEnergy << " " << houseLossEnergy << endl;
    }
}

int main(int argc, char* argv[]) {
    int timespan = 365;

    // default day is 1st of January
    int start_day = 1;
    double start_hour = 12.0;
    double azimuth = 0.0;

    double collectorInclination = 0.0; 
    // default data for
    // TitanPowerPlus-ALDH29 V3 Solar Flat Plate Collector
    double collectorArea = 2.74;
    double collectorHeatTransferFactor = 0.8;
    double collectorAbsorptanceTransmittance = 0.8645;
    double collectorHeatLossCoefficient = 3.4;
    double collectorTemp = 40;

    //default for Brno
    double latitude = 49.11;
    double locationHeight = 0.237; 
    //default temperature and temperature difference of the day for 1st of january for Brno
    double envAvgTemp = -1; 
    double envTempDiff = 4;

    //parse command line arguments
    parse_arguments(start_day, timespan, start_hour, latitude, envAvgTemp, envTempDiff, azimuth, locationHeight, 
    collectorInclination, collectorArea, collectorHeatTransferFactor, collectorAbsorptanceTransmittance, argc, argv);

    //create objects for environment, collector and house
    Environment env(latitude, azimuth, locationHeight, envAvgTemp, envTempDiff);
    Collector collector(collectorArea, collectorInclination, collectorHeatTransferFactor, 
        collectorAbsorptanceTransmittance, collectorHeatLossCoefficient, collectorTemp);
    House house;
    house.SetDefaultRooms();

    //plot energy consume ratios by tilt
    plot_seasonal_energy_ratio_by_tilt(latitude, env, collector);
    plot_hourly_energy_ratio_by_tilt(latitude, env, collector);

    //set collector's inclination back to command line value
    collector.SetIncl(collectorInclination);

    simulate_power_balance_by_hour(collector, env, house, start_day, latitude);

    return 0;
}
