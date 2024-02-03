# TODO

## Stockage externe

- niveaux (plateau)
- sprites
Later :
- (score)

### Stockage des niveaux : levels.txt
Chaque ligne est un niveau
Chaque ligne est composée de plusieurs nombres :
|nombre|objet|
|---|---|
|0|vide|
|1|mur|
|2|pacman|
|3|fantome|
|4|gum|
|5|big Gum|
|6|téléporteur|


## Structure

- main
- board
- physic
- graphics
- wall
- player
- ghost
- warp
- gum

## TODO

- basic game (ghost direction aléatoire)
	- [X] import level
	- [X] init every objects of the level
	- [ ] move player
	- [ ] collision with walls
	- [ ] ghost
	- [ ] gum and biggum
( [ ] (warp)
- ajouter du son
- menu / end screen
- best score
- ghost avec différents algos (random, pathfinding, chemin le plus long..;) et fuir si super pacman
- Unit test
- faire un éditeur de maps (terminal)
- ajouter différentes maps
- faire un editeur graphique à la souris

