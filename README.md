# Anemometre

Les abeilles sont sensibles au vent. C’est pour cela que les apiculteurs disposent leurs ruchers à l’abri des vents dominants 
et des courants d’air.  
Quand la vitesse du vent dépasse 30km/h, les abeilles hésitent à sortir. Elles ne pourront pas aller récolter pollen et nectar.

L'anémomètre est composé de 3 coupoles fixées à un mât mobile sur un axe. 
Ces éléments ont été dessinés en 3D sur tinkercad, et imprimés au FabLab des Bains douches numériques de Flers.

Pour compter le nombre de tours, nous allons placer un interrupteur Reed à la base de l’anémomètre 
et un aimant sur l'axe de l’anémomètre. Nous programmons le compteur grâce à l'arduino.
A chaque passage de l’aimant, l’interrupteur Reed laisse passer un courant électrique, 
ce qui sera détecté et comptabilisé par Arduino.  (voir vidéo anemometre)
Présentation du programme Arduino :
Sur l'Arduino, nous avons branché un interrupteur à aimant (reed) ainsi qu'une diode et une résistance. 
La diode sert juste à vérifier si le courant passe. Chaque fois que l'aimant passe au dessus du reed, la led s'allume,
signifiant que le courant passe. A chaque fois que la diode s'allume, le compteur intègre 1 tour de plus. 
De plus, nous avons ajouté un timer(millis) pour savoir combien de temps s'est écoulé entre chaque tour.


Nous avons revu notre programme, nous comptons maintenant le nombre de tour en un temps donné (10 secondes par exemple) e
t pour calculer la vitesse du vent, nous ajoutons une ligne de calcul au programme.

