Design choises:
* To spawn in players/enemies I use a gamemode class(which is an observer).
* Levels are loaded at the start, even though they are only used later on.
* Gameobjects are expected to have at least a transformcomponent.
* If you want to delete gameobjects, you can just call Destroy on it.



https://github.com/wountu/Programming04