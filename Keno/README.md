## Keno ##

### What is it? ###

Keno is a game where the player make a bet with a wage that him wish to bet, a number of rounds and at last the numbers of your bet (15 numbers max) that should be between 1 and 80. Then 20 random numbers will be drawn and compared to  the numbers in his bet, the player got a point every time a number in his bet matches with a drawn number, this points will give him a multiplier for his wage in this round (the multiplier will depend on your points and how much numbers you have gave on your bet).

### How does it work? ###

The program will read a file with your bet containing the wage, number of rounds and numbers of the bet, respectively.

**Exemple:**
```
"2000.0        //Wage"
"4             //Rounds"
"4 5 24 64 13  //Number(s) to bet"
```

Then, if the bet is valid (do not have a null or negative wage or less than 1 round) the progam will filter the numbers of the bet (removing any number out of the range between 1 and 80 or if the number was already readed, and ignoring any number after the 15º valid number). 

After read a valid bet the program will give a table with the hits and the respective payout for a number of hits(the table depends in how much numbers the bet have) then 20 random numbers in the interval from 1 to 80 will drawn and the bet numbers will be compared to the drawn ones, each number that matches will be add to a vector, this vector will show the player hits and it's size represents how much points the player made in this round. 

For each round the program will take the hits and the respective payout, multiplie the payout by the wage for the round and sum to the total wage. After finishing all the rounds the final balance is done, showing how much the player had in the initial bet, how much he won and the total cash he have at the end of the game.

### Compiling ###

To compile the program use the following code:

`g++ -std=c++11 ./src/keno.cpp ./include/keno.h -o ./bin/keno`

### Setting the bet ###

To set your bet you must edit the `bet.txt` file in the `data/` folder

The first line is your wage, the second is the number of rounds and the last is the numbers to be wagered (always separeting them with whitespace)

**Exemple:**
```
"3000.0        //Wage"
"5             //Rounds"
"23 48 4 12 13 59 71 //Number(s) to bet"
```

### Running ###

To run the program use the following code:

`./bin/keno ./data/bet.txt`

This program was made by ANDERSON CAIO and RAYAN AVELINO. ⒸAll rights reserved.