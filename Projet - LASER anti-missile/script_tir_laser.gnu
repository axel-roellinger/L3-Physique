set term x11 persist
set xrange[0:ARG1+100]
set yrange[0:ARG2+100]
set y2tics autofreq norangelimit 
set xlabel "Distance parcourue (m)"
set ylabel "Altitude (m)"
set output "Intersection_LASER.png"
plot "laser_track.txt" using 1:2 with linespoints t "Missile (trace extrapolee)" lt rgb "blue", "laser_track.txt" using 3:4 with linespoints t "Missile (trace reelle)" lt rgb "green", "laser_track.txt" using 5:6 with lines t "LASER" lt rgb "red"
