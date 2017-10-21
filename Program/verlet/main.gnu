earth = '/Users/antoinehugounet/Documents/Scolarité/UiO/FYS3150 - Computational physics/Project 3/Perseids/Program/verlet/earth'

jupiter = '/Users/antoinehugounet/Documents/Scolarité/UiO/FYS3150 - Computational physics/Project 3/Perseids/Program/verlet/jupiter'

mars = '/Users/antoinehugounet/Documents/Scolarité/UiO/FYS3150 - Computational physics/Project 3/Perseids/Program/verlet/mars'

path = '/Users/antoinehugounet/Documents/Scolarité/UiO/FYS3150 - Computational physics/Project 3/Perseids/Program/plot.png'

set terminal png
set output path

plot earth using 1:2 w l lt rgb "blue" title 'Earth', jupiter using 1:2 lt rgb "goldenrod" w l title 'Jupiter', mars using 1:2 w l lt rgb "brown" title 'Mars'