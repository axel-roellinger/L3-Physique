 Ce programme a été réalisé dans le cadre du projet "LASER Anti-missile"
 
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
