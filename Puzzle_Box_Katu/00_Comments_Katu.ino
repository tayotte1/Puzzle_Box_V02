/*

Puzzle Box For Katie Ng Ross
LNL/TA
V01 
07/23/2020

Puzzle Comments ---------------------------------------------------------------------
Puzzle 00:
Clue: I have a list titled "Katie's Bae" on my phone from 2014. Hold onto 3 of those
      people to solve the first puzzle
Electronics:
    - Three touch sensors, send PIN_PUZ0 HIGH



Puzzle 01:
Clue: Should we keep up your tradition of skateboarding during weddings? Why don't you try it out now?
Electronics:
    - Hall effect sensor detects magnet spinning in wheel, send PIN_PUZ1 HIGH



Puzzle 02:
Clue: It's been a while since we've done gymnastics together - think you can pull off this routine?
      Don't forget to salute the judges and hold those handstands for 2 seconds!
Electronics:
    - Accelerometer senses orientation of box, send PIN_PUZ2 HIGH







 Software Comments ---------------------------------------------------------------
Speed Sensor:
    - Speed sensor moved from pin 4 to pin 3 for interrupt, using the hall effect sensor

 
 */
