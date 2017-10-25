source = '/Users/antoinehugounet/Documents/Scolarité/UiO/FYS3150 - Computational physics/Project 3/Perseids/Program/Models/fs_rmc_verlet/system-total-energy'

set xrange [0:1]
set xlabel 'time (years)'
set ylabel 'total energy'

plot source using 1:2
