reset
set size ratio -1
set title 'Time-step: 5.000000 years'
set xlabel 'distance (AU)'
set ylabel 'distance (AU)'

plot '/Users/antoinehugounet/Documents/Scolarité/UiO/FYS3150 - Computational physics/Project 3/Perseids/Program/Test/Peri/sun' using 1:2 w l lt rgb "black" title 'sun'

replot '/Users/antoinehugounet/Documents/Scolarité/UiO/FYS3150 - Computational physics/Project 3/Perseids/Program/Test/Peri/mercury' using 1:2 w l lt rgb "orange-red" title 'mercury'

replot '/Users/antoinehugounet/Documents/Scolarité/UiO/FYS3150 - Computational physics/Project 3/Perseids/Program/Test/Peri/earth' using 1:2 w l lt rgb "blue" title 'earth'

