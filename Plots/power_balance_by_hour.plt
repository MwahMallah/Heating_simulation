# Gnuplot script for plotting energy and heat loss by hour

reset

set terminal pdf
set output "power_balance_by_hour.pdf"

set title "Energy vs. Time"
set xlabel "Time (hours)"
set ylabel "Energy (Watts)"
set grid

# Define the range for the x-axis and y-axis if necessary
set xrange [0:24]

# Plot energy data (time vs energy)
plot "PlotData/power_balance_by_hour.dat" using 1:2 title "Collector's Energy" with lines, \
     "PlotData/power_balance_by_hour.dat" using 1:3 title "House Heat Loss" with lines
