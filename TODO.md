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

- [x] basic game (ghost direction aléatoire)
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
  - [x] death time pour les ghosts
  - [x] si pleusieurs ghosts eatten in the same super -> more points
  - [x] move super_mode in ghost struct (if eaten, not scared anymore)
- [x] rotation player + anim bouche 
- [x] ghosts rotation selon direction + scared ghosts
- [x] ghosts clignotte quand reste plus que 3sec
- [x] pacman death animation
- [x] ghosts blink more fluently
- [ ] Free Board mem :)
- [x] (create function Free Board mem)
- [x] count level
- [x] increase difficulty over level
- [ ] remake collision
- [ ] remake pacman move
- [x] gestionGraphics -> a refaire
- [x] CLEAN CODE
- [ ] ^^^ objectif ^^^
- [ ] vvv  bonus   vvv 
- [ ] ghost respawn to the closest point
- [ ] wall attach texture
- [ ] (animation gums)
- [ ] Paques Man (tete ile de Paques -> mange oeufs en chocolat)
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

- [x] Pacman direction after reloading a level
- [ ] crash at the end on freeing SDL memory