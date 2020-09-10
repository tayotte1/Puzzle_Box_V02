/*

Puzzle Box For Paige Scrofani
LNL/TA
V01 
05/05/2020

Puzzle Comments ---------------------------------------------------------------------
Puzzle 00:
Clue: Something about skydiving
Electronics:
    - Accelerometer detects the box having been dropped, send PIN_PUZ0 HIGH



Puzzle 01:
Clue: What an exhausting but exhilerating day of skydiving.  Now we're overtired and can't sleep.  I wonder what's on TV.
Electronics:
    - IR sensor detects button press from a tv remote, send PIN_PUZ1 HIGH



Puzzle 02:
Clue: Eh I guess we're not sleeping.  All we can do now is listen to the fan!
Electronics:
    - Hall effect sensor detects fan blowing spinning magnet, send PIN_PUZ2 HIGH







 Software Comments ---------------------------------------------------------------
Speed Sensor:
    - Speed sensor moved from pin 4 to pin 2 for interrupt, using the hall effect sensor

 
 */
