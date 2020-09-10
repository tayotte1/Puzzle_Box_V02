/*

Puzzle Box For Emily Mak
LNL/TA
V01
07/19/2020

Puzzle Comments ---------------------------------------------------------------------
Puzzle 00:
Clue: Let's play our favorite original game! Do you remember how to serve pizza?
Electronics:
    - Reed switch activated by magnet, detect HIGH on PIN_PIZZA_SWITCH, send PIN_PUZ0 HIGH



Puzzle 01:
Clue: Different than a Rubik's Cube, but it reminded me of you nonetheless. Push any button to start.
Electronics:
    - 9 neopixels that display a pattern for the user to follow
    - 9 switches with LEDs that light up when pressed, read on PIN_GAME_0-PIN_GAME_8
    - Play 3 times, if win, send PIN_PUZ1 HIGH



Puzzle 02:
Clue: Hold onto the last Key to this puzzle box and where you might find it.
Electronics:
    - Two touch sensors, read on PIN_TOUCH0 and PIN_TOUCH1, send PIN_PUZ2 HIGH







 Software Comments ---------------------------------------------------------------

 
 */
