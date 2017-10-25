reset
set size ratio -1
set title 'Time-step: 5.000000 years'
set xlabel 'distance (AU)'
set ylabel 'distance (AU)'

plot '/Users/antoinehugounet/Documents/Scolarité/UiO/FYS3150 - Computational physics/Project 3/Perseids/Program/Models/fs-rmc-verlet/earth' using 1:2 w l lt rgb "blue" title 'earth'

replot '/Users/antoinehugounet/Documents/Scolarité/UiO/FYS3150 - Computational physics/Project 3/Perseids/Program/Models/fs-rmc-verlet/jupiter' using 1:2 w l lt rgb "light-goldenrod" title 'jupiter'

replot '/Users/antoinehugounet/Documents/Scolarité/UiO/FYS3150 - Computational physics/Project 3/Perseids/Program/Models/fs-rmc-verlet/mars' using 1:2 w l lt rgb "brown" title 'mars'

replot '/Users/antoinehugounet/Documents/Scolarité/UiO/FYS3150 - Computational physics/Project 3/Perseids/Program/Models/fs-rmc-verlet/mercury' using 1:2 w l lt rgb "orange-red" title 'mercury'

replot '/Users/antoinehugounet/Documents/Scolarité/UiO/FYS3150 - Computational physics/Project 3/Perseids/Program/Models/fs-rmc-verlet/neptune' using 1:2 w l lt rgb "royalblue" title 'neptune'

replot '/Users/antoinehugounet/Documents/Scolarité/UiO/FYS3150 - Computational physics/Project 3/Perseids/Program/Models/fs-rmc-verlet/saturn' using 1:2 w l lt rgb "goldenrod" title 'saturn'

replot '/Users/antoinehugounet/Documents/Scolarité/UiO/FYS3150 - Computational physics/Project 3/Perseids/Program/Models/fs-rmc-verlet/sun' using 1:2 w l lt rgb "black" title 'sun'

replot '/Users/antoinehugounet/Documents/Scolarité/UiO/FYS3150 - Computational physics/Project 3/Perseids/Program/Models/fs-rmc-verlet/venus' using 1:2 w l lt rgb "dark-goldenrod" title 'venus'

replot '/Users/antoinehugounet/Documents/Scolarité/UiO/FYS3150 - Computational physics/Project 3/Perseids/Program/Models/fs-rmc-verlet/uranus' using 1:2 w l lt rgb "light-blue" title 'uranus'

