reset
set size ratio -1
set title 'Time-step: 100.000000 years'
set xlabel 'distance (AU)'
set ylabel 'distance (AU)'

plot '/Users/antoinehugounet/Documents/Scolarité/UiO/FYS3150 - Computational physics/Project 3/Perseids/Program/Résultats/Modèle à trois planètes/Vrai centre de masse/Outputs/earth' using 1:2 w l lt rgb "blue" title 'earth'

replot '/Users/antoinehugounet/Documents/Scolarité/UiO/FYS3150 - Computational physics/Project 3/Perseids/Program/Résultats/Modèle à trois planètes/Vrai centre de masse/Outputs/jupiter' using 1:2 w l lt rgb "light-goldenrod" title 'jupiter'

replot '/Users/antoinehugounet/Documents/Scolarité/UiO/FYS3150 - Computational physics/Project 3/Perseids/Program/Résultats/Modèle à trois planètes/Vrai centre de masse/Outputs/sun' using 1:2 w l lt rgb "black" title 'sun'

