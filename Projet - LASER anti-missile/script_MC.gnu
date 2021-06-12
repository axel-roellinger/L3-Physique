set term x11 persist
set output "Monte_Carlo.png"
set xlabel "Distance parcourue (m)"
set ylabel "Occurences"
plot "y_0_laser.txt" lt rgb "blue" with linespoints t "Occurences d'une position de crash"

