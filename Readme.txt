ASCII roguelike

1. Load the levels from files like level1.txt, level2.txt etc.

2. W S A D can be used to move the player.
	For this, we'll use getch() or _getch() which is in conio.h
	It grabs the character typed without us having to press enter.

3. We can refresh our screen by printing a lot of newlines,
	so that older part of the output moves up.
	We can do this by creating a string of 100 newlines and printing it.
	Hence, cout << string(100, '\n'); will do our job.

4. Have some enemies that randomly move around and allow the player to attack them.

5. Make sure the player can't walk through walls.

(Optional ahead - )

6. Can save the game and load it again.

7. Add items and money and an item shop.

8. Allow the player to level up when he gets experience.

9. Have multiple levels.




# for walls
  for air
@ for plater
letters for monsters




We'll store our level as a vector of strings.
vector<string> leveldata
Now, leveldata[i][j] will give us the char at i,j position.

We'll use ifstream to load our level from a txt file.
getline one at a time, store it in a string, push back the string to a vector.
Do that until the file is empty.

To move a player/monster,
we check what char is there where he wants to move.
If it's air, let him move.
If it's wall, don't.
If it's monster/player, start combat.

Surround your level with walls to avoid player walking off the edge.
This will stop access violation, such as -1 in an array/string.

Create a Monster class and store the monsters in a vector<Monster>.
Give them some AI to move around and to attack the player if he's nearby.