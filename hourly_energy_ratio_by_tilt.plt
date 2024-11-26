# Gnuplot script for plotting energy ratios by hour

reset

set terminal pdf
set output "hourly_energy_ratio_by_tilt.pdf"

set title "Energy Ratios by Hour"
set xlabel "Time (hours)"
set ylabel "Energy Ratio"
set grid

# Define the range for the x-axis (from 6 to 18 hours)
set xrange [6:18]
set yrange [-1:1.5]  # Adjust the y-axis range if needed

# Plot each column of data
plot "hourly_energy_ratio_by_tilt.dat" using 1:2 title "10° Tilt" with lines, \
     "hourly_energy_ratio_by_tilt.dat" using 1:3 title "30° Tilt" with lines, \
     "hourly_energy_ratio_by_tilt.dat" using 1:4 title "90° Tilt" with lines, \
