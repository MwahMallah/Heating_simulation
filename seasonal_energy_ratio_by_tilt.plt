# GnuPlot script for seasonal energy ratio by collector tilt angle with averages
# This file is used to plot the seasonal energy ratio as a function of day
# Data format: Day Rb_10 Rb_30 Rb_40 Rb_50 Rb_90

reset
set terminal pdf size 6,4 enhanced
set output 'seasonal_energy_ratio_by_tilt_with_avg.pdf'

set title "Seasonal Energy Ratio by Collector Tilt with Averages"
set xlabel "Day of the Year"
set ylabel "Energy Ratio (Rb)"
set grid

# Set Y-axis range from 0 to 4.5
set yrange [0:4]

set xrange [0:366]

set key outside right

# Calculate the averages for each column (Rb_10, Rb_30, Rb_40, Rb_50, Rb_90)
stats "seasonal_energy_ratio_by_tilt.dat" using 2 nooutput
avg_10 = STATS_mean

stats "seasonal_energy_ratio_by_tilt.dat" using 3 nooutput
avg_20 = STATS_mean

stats "seasonal_energy_ratio_by_tilt.dat" using 4 nooutput
avg_30 = STATS_mean

stats "seasonal_energy_ratio_by_tilt.dat" using 5 nooutput
avg_40 = STATS_mean

stats "seasonal_energy_ratio_by_tilt.dat" using 6 nooutput
avg_50 = STATS_mean

stats "seasonal_energy_ratio_by_tilt.dat" using 7 nooutput
avg_60 = STATS_mean

stats "seasonal_energy_ratio_by_tilt.dat" using 8 nooutput
avg_70 = STATS_mean

stats "seasonal_energy_ratio_by_tilt.dat" using 9 nooutput
avg_80 = STATS_mean

stats "seasonal_energy_ratio_by_tilt.dat" using 10 nooutput
avg_90 = STATS_mean

# Plot data for different collector tilt angles and average lines with varied colors and styles
plot "seasonal_energy_ratio_by_tilt.dat" using 1:2 title "10° Tilt" with lines lc rgb "#0000FF" lw 2, \
     "seasonal_energy_ratio_by_tilt.dat" using 1:3 title "20° Tilt" with lines lc rgb "#FF8000" lw 2, \
     "seasonal_energy_ratio_by_tilt.dat" using 1:4 title "30° Tilt" with lines lc rgb "#FFFF00" lw 2, \
     "seasonal_energy_ratio_by_tilt.dat" using 1:5 title "40° Tilt" with lines lc rgb "#00FF00" lw 2, \
     "seasonal_energy_ratio_by_tilt.dat" using 1:6 title "50° Tilt" with lines lc rgb "#00FFFF" lw 2, \
     "seasonal_energy_ratio_by_tilt.dat" using 1:7 title "60° Tilt" with lines lc rgb "#007FFF" lw 2, \
     "seasonal_energy_ratio_by_tilt.dat" using 1:8 title "70° Tilt" with lines lc rgb "#FF0000" lw 2, \
     "seasonal_energy_ratio_by_tilt.dat" using 1:9 title "80° Tilt" with lines lc rgb "#7F00FF" lw 2, \
     "seasonal_energy_ratio_by_tilt.dat" using 1:10 title "90° Tilt" with lines lc rgb "#FF00FF" lw 2, \
     x*0 + avg_10 title "Avg 10° Tilt" with lines lc rgb "#0000FF" dt 2 lw 2, \
     x*0 + avg_20 title "Avg 20° Tilt" with lines lc rgb "#FF8000" dt 2 lw 2, \
     x*0 + avg_30 title "Avg 30° Tilt" with lines lc rgb "#FFF000" dt 2 lw 2, \
     x*0 + avg_40 title "Avg 40° Tilt" with lines lc rgb "#00FF00" dt 2 lw 2, \
     x*0 + avg_50 title "Avg 50° Tilt" with lines lc rgb "#00FFFF" dt 2 lw 2, \
     x*0 + avg_60 title "Avg 60° Tilt" with lines lc rgb "#007FFF" dt 2 lw 2, \
     x*0 + avg_70 title "Avg 70° Tilt" with lines lc rgb "#FF0000" dt 2 lw 2, \
     x*0 + avg_80 title "Avg 80° Tilt" with lines lc rgb "#7F00FF" dt 2 lw 2, \
     x*0 + avg_90 title "Avg 90° Tilt" with lines lc rgb "#FF00FF" dt 2 lw 2
