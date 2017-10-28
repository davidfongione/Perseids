reset
set size ratio -1
set title 'Time-step: 17.000000 years'
set xlabel 'distance (AU)'
set ylabel 'distance (AU)'

plot '/Users/antoinehugounet/Documents/Scolarité/UiO/FYS3150 - Computational physics/Project 3/Perseids/Program/Results/Peri/earth' using 1:2 w l lt rgb "blue" title 'earth'

replot '/Users/antoinehugounet/Documents/Scolarité/UiO/FYS3150 - Computational physics/Project 3/Perseids/Program/Results/Peri/mars' using 1:2 w l lt rgb "brown" title 'mars'

replot '/Users/antoinehugounet/Documents/Scolarité/UiO/FYS3150 - Computational physics/Project 3/Perseids/Program/Results/Peri/sun' using 1:2 w l lt rgb "black" title 'sun'

replot '/Users/antoinehugounet/Documents/Scolarité/UiO/FYS3150 - Computational physics/Project 3/Perseids/Program/Results/Peri/jupiter' using 1:2 w l lt rgb "light-goldenrod" title 'jupiter'

replot '/Users/antoinehugounet/Documents/Scolarité/UiO/FYS3150 - Computational physics/Project 3/Perseids/Program/Results/Peri/saturn' using 1:2 w l lt rgb "goldenrod" title 'saturn'

