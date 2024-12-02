# Name of the output executable
TARGET = main

# Compiler to use
CXX = g++

# Compiler flags: enable warnings and set the C++ standard to C++17
CXXFLAGS = -Wall -Wextra -std=c++17

DEBUGFLAGS = -DDEBUG

# Source files
SRC = Utils/Utils.cpp Environment/Environment.cpp Collector/Collector.cpp Room/Room.cpp RoomFactory/RoomFactory.cpp House/House.cpp main.cpp 

# Rule to build the executable
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

debug: $(SRC)
	$(CXX) $(CXXFLAGS) $(DEBUGFLAGS) -o $(TARGET) $(SRC)

# Rule to generate graphs using gnuplot
graphs: power_balance_by_hour.pdf hourly_energy_ratio_by_tilt.pdf seasonal_energy_ratio_by_tilt.pdf

# Rule to run the program with default parameters
run: $(TARGET)
	./$(TARGET) --col_i 60 --dStart 1 --latitude 49 --start_hour 12 --h 0.237 --env_avg_tmp -1 --env_diff_tmp 4 --area 10.8 --trans_eff 0.9
	$(MAKE) graphs

# Rule to generate power_balance_by_hour.pdf
power_balance_by_hour.pdf: Plots/power_balance_by_hour.plt PlotData/power_balance_by_hour.dat
	gnuplot Plots/power_balance_by_hour.plt

# Rule to generate hourly_energy_ratio_by_tilt.pdf
hourly_energy_ratio_by_tilt.pdf: Plots/hourly_energy_ratio_by_tilt.plt PlotData/hourly_energy_ratio_by_tilt.dat
	gnuplot Plots/hourly_energy_ratio_by_tilt.plt

# Rule to generate seasonal_energy_ratio_by_tilt.pdf
seasonal_energy_ratio_by_tilt.pdf: Plots/seasonal_energy_ratio_by_tilt.plt PlotData/seasonal_energy_ratio_by_tilt.dat
	gnuplot Plots/seasonal_energy_ratio_by_tilt.plt

# Rule to clean up build artifacts
clean:
	rm -f $(TARGET)
