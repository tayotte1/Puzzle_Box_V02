/*

Puzzle Box For Ryan Mak
LNL/TA
V01

05/22/2020
Confirmed working on test setup

Puzzle Comments ---------------------------------------------------------------------
Puzzle 00:
Clue: Touch the three players with the Most Grand Slam tournament singles titles?
    - Margaret Smith Court: 24
    - Serena Williams:​ 23
    - Steffi Graf: 22
Electronics:
    - Touch 3 capacitive touch sensors hidden behind tennis players, light PIN_PUZ0



Puzzle 01:
Clue: The keys to success are always hidden in plain sight.
    - Hidden tool within the box
Electronics:
    - Momentary micro rocker switch is unclicked when the tool is found, light PIN_PUZ1



Puzzle 02:
Clue: You'll See.
    - LCD screen asks for Lindsay's Birthday
Electronics:
    - LCD screen
    - Rotary encoder with push button to enter Lindsay's birthday
    - Light PIN_PUZ2 when button is pressed after entering the year







 Software Comments ---------------------------------------------------------------
Rotary Encoder:
    - encoderValue increases or decreases by 4 every notch on the encoder
    - encoderValue only increases or decreases by 2 on the first notch turn

 
 */
