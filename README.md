# EEE101-Assessment-2
## Introduction
    This project is the Assessment 2 for EEE101.
    Goal: Design a Rock, Scissors and Paper game for user to against with computer.
    IDE: Visual Studio
## Update Log:
### Basic information
    version:    3.0.0
    Author:     Ziqi Yang
    Date:       Nov 2, 2018
    Time:       13:09 pm.
### Update details
    1. Add functions:
        Notice user that can exit game immediately with Ctrl + C in info input and rounds UI.

    2. Improve:
        1) Change the print method of most of elements which has illegal input check to print at certain
        position.

        2) Change the background colour to blue and fix the size of windows.

        3) Optimize text layout.
    
    3. Repair bugs:
        Repair some bugs of re-input in original position.
### Introduction:
    This the new version, which improve the vision of user in this game. The pictures of rock, scissors 
    and paper is added in the welcome UI and rounds UI.
### Functions:
    1. Choose Start or Exit in the welcome UI.
        1) Illegal check
            a. Only 'a' and 'b' are allowed to input.
            b. If the input is illegal, ask user to input again until the input is correct.
    
    2. Input the name of player and rounds the player want to play.
        1) Illegal check
            a. Name check: All input is allowed but all space name.
            b. Rounds check: Only positive integer is allowed to input.
            c. If the input is illegal, ask user to input again until the input is correct. 
    
    3. Show the rest attemptes of game and source list, ask user to input rock, scissors or paper.
        1) Illegal check
            a. Only 'r', 's' and 'p' are allowed to input.
            b. If the input is illegal, ask user to input again until the input is correct.
    
    4. Show the picture of the character that user and computer chosen, give the result of the current game.

    5. Give the result in the final UI, and ask user to play again.
        1) Illegal check
            a. Only 'y' and 'n' are allowed to input.
            b. If the input is illegal, ask user to input again until the input is correct.