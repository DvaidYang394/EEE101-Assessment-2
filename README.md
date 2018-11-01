# EEE101-Assessment-2
## Introduction
    This project is the Assessment 2 for EEE101.
    Goal: Design a Rock, Scissors and Paper game for user to against with computer.
    IDE: Visual Studio
## Update Log:
### Basic information
    version:    2.2.0
    Author:     Ziqi Yang
    Date:       Nov 2, 2018
    Time:       0:41 pm.
### Update details
    Repair bugs:
        Fix the position of elements in rounds UI.
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

    5. Give the result in the final UI.