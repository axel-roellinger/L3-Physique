 # LASER anti-missile
 
 Ce programme a été réalisé dans le cadre du projet "LASER Anti-missile"
 
 L'objectif était de concevoir un LASER capable d'intercepter un missile, en mesurant sa trajectoire avec des incertitudes,
 qui sont des propriétés intrinsèques du détecteur de missile. Le détecteur se charge de mesurer quelques dizaines de points formant le début de la trajectoire du missile. Ce jeu de points permet alors d'extrapoler une trajectoire complète,
 qui se révèle être toujours fausse, en raison des incertitudes, mais qui peut néanmoins être utilisable pour intercepter le missile.
 
Concernant l'espace considéré, on s'imagine un monde en 2D, où le missile a une simple trajectoire parabolique, et où le 
détecteur se déplace sur un rail le long de l'axe des abscisses.
 
Pour plus de réalisme, un "délai" est implémenté, qui correspond simplement à un tir de LASER sur une certaine coordonnée de la fausse trajectoire, qui est le point atteignable le plus "rapidement", les autres points ne l'étant pas car on simule 
un temps de calcul.

Ce projet s'articule autour de la programmation orientée objet, où deux classes sont utilisées : une pour le missile, et une pour le LASER.

La classe Missile est simple : un calculateur de trajectoire, qui utilise la vitesse et l'angle initial de tir, et de 
nombreux accesseurs et modificateurs de variables privées, telles que la taille du missile et sa position.

La classe LASER quant à elle est plus complexe : il faut inclure une méthode pour mesurer les coordonnées du missile, le 
calculateur de trajectoire extrapolée, et une méthode de détection d'impact.

Pour constituer le tableau de mesures du missile du point de vue LASER, j'ai employé des distributions uniformes, me générant des valeurs aléatoires positives ou négatives que j'ajoute aux coordonnées réelles.

Exemple : 
- couple réel de mesures  : (25, 37)
- erreur générée sur x : -2
- erreur générée sur y : +3
- couple stocké dans le tableau de valeurs côté LASER : (22, 40)

Concernant l'extrapolation, j'ai dû résoudre un système me permettant de reconstituer les coefficients de la parabole représentant la trajectoire de la forme ax^2 + bx + c = 0. Il a donc fallu recréer a, b et c.

Enfin, afin de positionner le LASER, j'ai choisi de positionner sa base au niveau de l'apex de la trajectoire mesurée, ce qui est purement arbitraire, et expliqué par le fait que mon LASER peut tirer avec un angle. Il aurait été envisageable de concevoir un LASER tirant uniquement à la verticale.

Afin de calculer l'angle de tir, j'ai utilisé de la trigonométrie, en mesurant les différentes longueurs nécessaires pour calculer la tangente de l'angle, à savoir l'écart du socle du LASER par rapport au point selon l'axe des abscisses, que nous appellerons delta_X, et la hauteur du point, qui est simplement sa coordonnée en y.

Nous avons alors : tan(angle de tir) = y/delta_X.

Une fois ces informations recueillies, le tir peut être effectué. Il faut maintenant vérifier que l'impact a eu lieu.

J'utilise un tableau pour stocker les points constituant la trajectoire du LASER, et j'étudie le point le plus proche de la trajectoire initiale du missile, qui n'est pas faussée. En utilisant les dimensions du missile, j'étudie alors où le LASER est passé relativement au missile, et je calcule l'écart au centre du missile. Si ce dernier est inférieur à la moitié de la hauteur du missile, on considère que l'impact est réalisé, et que le missile est détruit.

Pour le lancer, il suffira de taper "./projet.exe" depuis le Terminal.
 
Il y aura alors plusieurs options disponibles :

    - La 1ère correspond à une méthode Monte-Carlo sur le site de crash des missiles du point de vue des personnes cherchant à arrêter le missile. Les options sont pré-définies, et la courbe du nombre d'occurences en fonction de l'abscisse de crash sera affichée automatiquement
    
    - La 2nde correspond également à une méthode Monte-Carlo, mais avec des entrées utlisateurs possibles. La courbe s'affichera également seule.
    
    - La 3ème correspond à un tir de missile et une tentative d'interruption de sa trajectoire par un LASER. La courbe résultante affichera la trace réelle du missile, la trace extrapolée et le trajet du LASER
    
    - La 4ème correspond également à un tir de missile mais les variables d'entrée sont définies par l'utilisateur. A nouveau la courbe s'affichera seule
    
BUGS CONNUS :

    - La 2è option peut causer l'affichage d'une courbe peu exploitable en fonction de la vitesse initiale choisie notamment. Cela vient du fait que le parseur employé pour arrondir les vitesses ne soit pas assez efficace. 
    
     - La 3è option cause parfois une "segmentation fault". Le seul moyen pour la corriger est d'arrêter le programme par un Ctrl+Z, de le relancer et de sélectionner à nouveau l'option 3. Cette erreur peut survenir plusieurs fois d'affilée, dans ce cas, répéter la procédure.
    
    - La 4è option peut induire des bugs d'affichage en fonction de des incertitudes choisies.
    
    - Lorsqu'une des optiosn eprsonnalisables est choisie, il se peut qu'une vitesse entre 250 et 400 m/s cause des plantages, le programme s'arrêtant au milieu de ses calculs. Ce bug se manifeste rarement cependant pour une vitesse supérieure, comme 1000 m/s.
    
    - Il se peut que quelques autres bugs s'immiscent durant les phases de calcul, occasionnant des artefacts sur les courbes à afficher, comme des points de trajectoire hors propos. Ceux-ci peuvent être corrigés en relançant le programme avec les mêmes variables d'entrée.
