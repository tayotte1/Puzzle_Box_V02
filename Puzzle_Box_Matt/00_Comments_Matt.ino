/*

Puzzle Box For Matt Capozza
LNL/TA
V01
07/13/2020


Puzzle Comments ---------------------------------------------------------------------
Puzzle 00:
Clue: Touch the three players with the home runs for the Red Sox?
    - Ted Williams: 521
    - David Ortiz:​ 483
    - Carl Yastrzemski: 452
Electronics:
    - Touch 3 capacitive touch sensors hidden behind Red Sox players, light PIN_PUZ0


Puzzle 01:
Clue: The keys to success are hidden in plain sight. 
    - Find the tool hidden in the box
Electronics:
    - Micro switch releases when tool is removed, light PIN_PUZ1


Puzzle 02:
Clue: You'll See.
  -Use tool to turn rotary encoder and enter proper numbers
    - How many championships have the Bruins, Red Sox, and Celtics won combined? 6+9+17=32
    - What number did Vince Wilfork wear? 75
    - What number did Dave Roberts wear? 31
Electronics:
    - LCD screen
    - Rotary encoder with push button to enter values
    - Light PIN_PUZ2 when button is pressed after correctly answering questions


Puzzle 03:
Clue: You'll See.
  - Use push buttons to enter correct answers
    - 3 more questions
Electronics:
    - LCD screen
    - Rotary encoder with push button to enter Lindsay's birthday
    - Light PIN_PUZ3 when button is pressed after entering the year







 Software Comments ---------------------------------------------------------------
Rotary Encoder:
    - encoderValue increases or decreases by 4 every notch on the encoder
    - encoderValue only increases or decreases by 2 on the first notch turn

 
 */
