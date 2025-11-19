```Text
.-.-.-..-.,-.
| | | || . <
`-----'`-'`-'
```

# Documentation Wilfuck 1.0

## Le concept de base
Le WilFuck est organisé sous forme d'un ***tableau de 32768 cellules***.

## Les instructions
Il existe seulement 12 signes disponibles en Wilfuck.
| Signe | Utilité																		|
|-------|-------------------------------------------------------------------------------|
|   <   | Aller à la cellule précédente (gauche)										|
|   >   | Aller à la cellule suivante (droite)											|
|   +   | Ajouter 1 à la cellule sélectionnée											|
|   -   | Enlever 1 à la cellule sélectionnée											|
|  []   | Executer ce qui est à l'intérieur si la cellule active est différente de 0	|
|  {}   | Créer une fonction															|
|   ^   | Executer la dernière fonction créée											|
|   @   | Appeler le syscall correspondant												|
|   .   | Afficher la valeur ASCII de la cellules										|
|   ,   | Demander une valeur à l'utilisateur											|

## Contributeurs
Tout contributeur est le bienvenue :)

Je ne maintiens plus ce projet.

*wilrak0v, btw*:w

