# GuitarHero
GuitarHero is my rendition of the game Guitar Hero on a breadboard with simple electrical components.
This a brief video that will go over all the rules, game mechanics, and components used. 
I suggest you watch the video first, and then refer back here to the written text, for an easier understanding.
https://www.youtube.com/watch?v=i45QvAkXZts

##Components:
1) Breadboard

2) Wires

3) 8x8 LED Matrix
4) Basic Keypad
5) ATmega1284 Microcontroller
6) Seven Segment Display
7) LCD Screen
8) Potentionmeter
9) 128 Ohm Resistors

##How-To/Rules:
1) Press `*` to begin game
2) Press `#` to reset game at any time
3) LED Matrix row number that lights up represents the "note" to hit, corresponding to the number on the keypad.
Watch video for example of this feature.
4) +10 points for every note that is correctly hit
5) -10 points for every note that is incorrectly hit
6) You start off with 9 lives
7) -1 life for every note incorrectly hit/missed
8) 9 total level, start off at level 1
9) As levels increase, the amount of notes will increase, along with their speed, i.e., the higher the level, the more notes you have to hit, and the faster they will appear on the LED Matrix
10) You lose the game if the LED Matrix completely fills up
11) To pass the level you must have at least 1 life remaining
12) LCD Screen displayes `Lives`, `Level`, `Score`, and other messages to the user
13) Notes are randomized every time
14) The Seven Segment Display shows your current grade.
Your grade is based upon your standing to the highest score, i.e., it compares your current score to the max score achievable at that level.
15) Grade scales from `A`, `B`, `C`, and `D`

##Bugs
1) LCD Screen will begin to grow dim if LED Matrix is drawing too much power by having too many LED Matrix rows lit up at the same time. 
Mostly occurs when more than 5 rows are lit simultaneously.
Can be fixed by reducing the number of rows that are lit, or changing the potentionmeter to your visibility preference.
2) Althouh very rare, stickey keys can happen where it counts your single input twice, and proceeds to losing 10 points and 1 life, or more, depending on how long the incorrect note is held down.
