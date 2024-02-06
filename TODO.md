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

- [ ] basic game (ghost direction aléatoire)
	- [X] import level
	- [X] init every objects of the level
	- [X] Setup SDL
	- [X] move player
	- [X] collision with walls (% si sort de l'écran)
	- [X] ghost (random path)
	- [X] add ghost collision
	- [ ] gum and biggum + print score
	- [ ] add gate (ghost can go through but not the player)
- [ ] rotation player et ghosts selon direction
- [ ] pacman death animation
- [ ] (animation gums)
- [ ] Free Board mem :)
- [ ] menu / end screen
- [ ] Credits
- [ ] ajouter du son
- [ ] best score
- [ ] !taille_de_niveau : x!=19, y!=21
- [ ] ghost avec différents algos (random, pathfinding, chemin le plus long..;) et fuir si super pacman
- [ ] Unit test
- [ ] faire un éditeur de maps (terminal)
- [ ] ajouter différentes maps
- [ ] faire un editeur graphique à la souris
- [ ] (warp)
