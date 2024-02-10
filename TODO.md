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
|6|gate|
|7|ghost respawn point|


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
	- [X] gum
	- [X] print score
	- [x] win condition
	- [x] biggum + eat ghost
	- [x] add gate (ghost can go through but not the player)
	- [x] respawn point for ghosts
	- [x] heal time pour les ghosts
	- [ ] *code improvement :* move super_mode in player struct
	- [ ] si pleusieurs ghosts eatten in the same super -> more points
- [ ] rotation player et ghosts selon direction + scared ghosts(clignotte quand reste plus que 2sec)
- [ ] pacman death animation
- [ ] Free Board mem :)
- [ ] remake collision
- [ ] remake pacman move
- [ ] gestionGraphics -> a refaire
- [ ] ghost respawn to the closest point
- [ ] ^^^ objectif ^^^
- [ ] vvv  bonus   vvv 
- [ ] wall attach texture
- [ ] (animation gums)
- [ ] Paques Man (tete ile de Paques -> mange oeufs en chhocolat)
- [ ] warp texture in one file
- [ ] menu / end / win screen
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

### Bugs to fix

- [X] Pacman direction after reloading a level