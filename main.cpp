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
    double& azimuth, double& altitude, double& c_incl, double& c_area, double& c_transEff, double& c_heatTransfer, double& c_AbsorpTransm,
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
        } else if ((strcmp(argv[i], "--transfer_efficiency") == 0 || (strcmp(argv[i], "--trans_eff") == 0)) && (i + 1 < argc)) { 
            c_transEff = std::stod(argv[++i]);
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
    (Collector& collector, Environment& env, House& house, int day, double latitude, double transferEfficiency) {
    // Output file for storing power balance data (hour, collector energy, house energy loss)
    std::ofstream power_balance_by_hour("PlotData/power_balance_by_hour.dat");

    // Time slice for simulation (hours)
    double time_slice = 0.5;

    // Accumulators for total energy collected and energy lost
    double total_energy_loss = 0;
    double total_collected_energy = 0;

    // Simulate energy balance for each time slice throughout the day
    for (double hour = 0; hour <= 24; hour += time_slice) {
        // Calculate power collected by the solar collector at the current hour
        double current_collector_power = get_useful_collector_energy(collector, env, day, latitude, hour);

        // Calculate heat loss from the house at the current hour
        double current_house_loss_power = house.GetHeatLoss(env.OutsideTemp(hour));

        // Debug output for monitoring simulation progress
        cout << "At time: " << hour << " hours" << endl;
        cout << "Collector's power: " << current_collector_power  << " W" << endl;
        cout << "House loss: " << current_house_loss_power << " W" << endl;
        cout << endl;

        // Write the current hour's data to the file
        power_balance_by_hour << hour << " " 
                              << current_collector_power << " " 
                              << current_house_loss_power << endl;

        // Estimate average power values over the time slice for accurate integration
        double avg_collector_power = get_useful_collector_energy(collector, env, day, latitude, hour + time_slice / 2);
        double avg_house_loss_power = house.GetHeatLoss(env.OutsideTemp(hour + time_slice / 2));

        // Accumulate energy values for the entire day
        total_collected_energy += avg_collector_power * time_slice;
        total_energy_loss += avg_house_loss_power * time_slice;
    }

    // Calculate and display the ratio of collected energy to lost energy
    double energy_ratio = total_collected_energy * transferEfficiency / total_energy_loss;

    // Final results output
    cout << "Simulation results:" << endl;
    cout << "-------------------" << endl;
    cout << "Total energy collected by the solar collector through the day: " 
         << total_collected_energy << " J" << endl;
    cout << "Total energy received by the house through the day (transfer efficiency " 
         << transferEfficiency * 100 
         << "%): " 
         << total_collected_energy * transferEfficiency << " J" << endl;
    cout << "Total energy lost by the house through the day: " 
         << total_energy_loss << " J" << endl;
    cout << "Ratio of received to lost energy: " 
         << energy_ratio * 100 
         << "%"
         << endl;
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
    double collectorTransferEfficiency = 0.8;

    //default for Brno
    double latitude = 49.11;
    double locationHeight = 0.237; 
    //default temperature and temperature difference of the day for 1st of january for Brno
    double envAvgTemp = -1; 
    double envTempDiff = 4;

    //parse command line arguments
    parse_arguments(start_day, timespan, start_hour, latitude, envAvgTemp, envTempDiff, azimuth, locationHeight, 
    collectorInclination, collectorArea, collectorTransferEfficiency, collectorHeatTransferFactor, collectorAbsorptanceTransmittance, argc, argv);

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

    simulate_power_balance_by_hour(collector, env, house, start_day, latitude, collectorTransferEfficiency);

    return 0;
}
