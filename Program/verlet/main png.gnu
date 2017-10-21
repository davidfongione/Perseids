earth = '/Users/antoinehugounet/Documents/Scolarité/UiO/FYS3150 - Computational physics/Project 3/Perseids/Program/verlet/earth'

jupiter = '/Users/antoinehugounet/Documents/Scolarité/UiO/FYS3150 - Computational physics/Project 3/Perseids/Program/verlet/jupiter'

mars = '/Users/antoinehugounet/Documents/Scolarité/UiO/FYS3150 - Computational physics/Project 3/Perseids/Program/verlet/mars'

neptune = '/Users/antoinehugounet/Documents/Scolarité/UiO/FYS3150 - Computational physics/Project 3/Perseids/Program/verlet/neptune'

saturn = '/Users/antoinehugounet/Documents/Scolarité/UiO/FYS3150 - Computational physics/Project 3/Perseids/Program/verlet/saturn'

sun = '/Users/antoinehugounet/Documents/Scolarité/UiO/FYS3150 - Computational physics/Project 3/Perseids/Program/verlet/sun'

mercury = '/Users/antoinehugounet/Documents/Scolarité/UiO/FYS3150 - Computational physics/Project 3/Perseids/Program/verlet/sun'

uranus = '/Users/antoinehugounet/Documents/Scolarité/UiO/FYS3150 - Computational physics/Project 3/Perseids/Program/verlet/uranus'

venus = '/Users/antoinehugounet/Documents/Scolarité/UiO/FYS3150 - Computational physics/Project 3/Perseids/Program/verlet/venus'

path = '/Users/antoinehugounet/Documents/Scolarité/UiO/FYS3150 - Computational physics/Project 3/Perseids/Program/plot.png'


set terminal png size 1000, 1000
set size ratio -1
set output path


plot earth using 1:2 w l lt rgb "blue" title 'Earth', jupiter using 1:2 lt rgb "goldenrod" w l title 'Jupiter', mars using 1:2 w l lt rgb "brown" title 'Mars', neptune using 1:2 w l lt rgb "cyan" title 'Neptune', saturn using 1:2 w l lt rgb "red" title 'Saturn', uranus using 1:2 w l lt rgb "aquamarine" title 'Uranus', venus using 1:2 w l lt rgb "orange" title 'Venus', mercury using 1:2 w l lt rgb "brown" title 'Mercury', sun using 1:2 w l lt rgb "yellow" title 'Sun'
