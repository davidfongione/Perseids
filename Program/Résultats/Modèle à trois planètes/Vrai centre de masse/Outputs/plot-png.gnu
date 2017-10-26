reset
set terminal png enhanced size 1000, 1000
set output '/Users/antoinehugounet/Documents/Scolarité/UiO/FYS3150 - Computational physics/Project 3/Perseids/Program/Résultats/Modèle à trois planètes/Vrai centre de masse/Outputs/plot.png'
set size ratio -1
set title 'Time-step: 100.000000 years'
set xlabel 'distance (AU)'
set ylabel 'distance (AU)'

plot '/Users/antoinehugounet/Documents/Scolarité/UiO/FYS3150 - Computational physics/Project 3/Perseids/Program/Résultats/Modèle à trois planètes/Vrai centre de masse/Outputs/sun' using 1:2 w l lt rgb "black" title 'sun'