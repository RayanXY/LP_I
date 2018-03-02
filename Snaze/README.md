## Snaze ##

### What is it? ###

This project is a simulation of the classic Snake game. But in this case the snake has a AI and it is trapped in a maze. It's challenge is to find the food on its own.

### How does it work? ###

The program receive a file that contains the level. The level is composed by this set of characters:

```
"# - Walls"
"* - Start Point of the Snake"
". - Invisible Walls"
"White spaces is where the Snake can pass"
```

After reading the file, the program will genarate the food, so the Snake can find and eat it. It has 5 lives to try to eat 10 foods in a roll, if it dies the amount of food is restarted. Unfortunately, we couldn't get the program to read more than one maze per file.

### Compiling ###

To compile the program use the following code:

`make`

### Running ###

To run the program use the following code:

`./bin/snaze ./data/'NAME_OF_THE_MAZE'`

Notice that `NAME_OF_THE_MAZE` is the name of the file where the maze is stored.

This program was made by ANDERSON CAIO and RAYAN AVELINO. ⒸAll rights reserved.