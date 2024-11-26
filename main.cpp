#include <iostream>
#include <cstring>

using std::cout;
using std::endl;

void parse_arguments(int& days, double& lat, double& inclination, double& azimuth, int argc, char** argv) {
    for (int i = 1; i < argc; ++i) {
        if ((strcmp(argv[i], "--days") == 0 || (strcmp(argv[i], "--t") == 0)) && (i + 1 < argc)) {
            days = std::stoi(argv[++i]);
        } else if (strcmp(argv[i], "--latitude") == 0 && i + 1 < argc) {
            lat = std::stod(argv[++i]);
        } else if ((strcmp(argv[i], "--inclination") == 0 || (strcmp(argv[i], "--i") == 0)) && (i + 1 < argc)) { 
            inclination = std::stod(argv[++i]);
        } else if (strcmp(argv[i], "--azimuth") == 0 && i + 1 < argc) {
            azimuth = std::stod(argv[++i]);
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc < 7) {
        cout << "Insufficient arguments!" << endl;
        return 1;
    }

    int days = 0;
    double latitude = 0.0;
    double inclination = 0.0; // Renamed from slope to inclination
    double azimuth = 0.0;
    parse_arguments(days, latitude, inclination, azimuth, argc, argv);

    #ifdef DEBUG
    cout << "Days from January 1st: " << days << endl;
    cout << "Latitude: " << latitude << endl;
    cout << "Collector inclination: " << inclination << " degrees" << endl; // Updated output
    cout << "Azimuth angle: " << azimuth << " degrees" << endl;
    #endif

    return 0;
}
