earth = '/Users/antoinehugounet/Documents/Scolarité/UiO/FYS3150 - Computational physics/Project 3/Perseids/Program/verlet/earth'

jupiter = '/Users/antoinehugounet/Documents/Scolarité/UiO/FYS3150 - Computational physics/Project 3/Perseids/Program/verlet/jupiter'

mars = '/Users/antoinehugounet/Documents/Scolarité/UiO/FYS3150 - Computational physics/Project 3/Perseids/Program/verlet/mars'

neptune = '/Users/antoinehugounet/Documents/Scolarité/UiO/FYS3150 - Computational physics/Project 3/Perseids/Program/verlet/neptune'

saturn = '/Users/antoinehugounet/Documents/Scolarité/UiO/FYS3150 - Computational physics/Project 3/Perseids/Program/verlet/saturn'

sun = '/Users/antoinehugounet/Documents/Scolarité/UiO/FYS3150 - Computational physics/Project 3/Perseids/Program/verlet/sun'

mercury = '/Users/antoinehugounet/Documents/Scolarité/UiO/FYS3150 - Computational physics/Project 3/Perseids/Program/verlet/mercury'

uranus = '/Users/antoinehugounet/Documents/Scolarité/UiO/FYS3150 - Computational physics/Project 3/Perseids/Program/verlet/uranus'

venus = '/Users/antoinehugounet/Documents/Scolarité/UiO/FYS3150 - Computational physics/Project 3/Perseids/Program/verlet/venus'

moon = '/Users/antoinehugounet/Documents/Scolarité/UiO/FYS3150 - Computational physics/Project 3/Perseids/Program/verlet/moon'

path = '/Users/antoinehugounet/Documents/Scolarité/UiO/FYS3150 - Computational physics/Project 3/Perseids/Program/plot.png'

set size ratio -1

plot earth using 1:2 w l lt rgb "blue" title 'Earth' 
replot jupiter using 1:2 lt rgb "goldenrod" w l title 'Jupiter' 
replot mars using 1:2 w l lt rgb "brown" title 'Mars'
replot mercury using 1:2 w l lt rgb "brown" title 'Mercury'
replot neptune using 1:2 w l lt rgb "cyan" title 'Neptune'
replot saturn using 1:2 w l lt rgb "red" title 'Saturn'
replot sun using 1:2 w l lt rgb "black" title 'Sun'
replot uranus using 1:2 w l lt rgb "aquamarine" title 'Uranus'
replot venus using 1:2 w l lt rgb "orange" title 'Venus'

## replot moon using 1:2 w l lt rgb "gray" title 'Venus'