/*************************************************************************************
 * Copyright (C) 2018
 * @File name: 1718112_2.c
 * @Author: Ziqi Yang
 * @Version: 4.0.0
 * @Date: 2018-11-3
 * @Description: EEE101-Assessment-2 Project
 *				 A game of rock, scissors and paper for user to against computer.
*************************************************************************************/

/**
 * @brief	libraries for the project.
 * @date	2018-11-2	
 */
#include <stdio.h>		/* For use of printf(), gets(), rewind(), sizeof(), getchar(). */
#include <string.h>		/* For use of strlen(). */
#include <Windows.h>	/* For use of Sleep(), GetStdHandle(), GetConsoleScreenBufferInfo(), SetConsoleCursorPosition(). */
#include <ctype.h>		/* For use of isdigit(). */
#include <stdlib.h>		/* For use of system(), srand(), rand(). */
#include <time.h>		/* For use of time(). */

/**
 * @brief	define for the project.
 * @date	2018-11-2						
 */
#define GET_ARRAY_LEN(array,len){len = (sizeof(array) / sizeof(array[0]));}		/* Get the length of array. */
#define rounds_X_text_pos 13				/* x-axis coordinates for character text in console in rounds UI. */
#define rounds_Y_text_pos 29				/* y-axis coordinates for character text in console in rounds UI. */
#define rounds_Y_character_pos 14			/* y-axis coordinates for character pictures in console in rounds UI. */
#define rounds_X_current_result_pos 35		/* x-axis coordinates for current result text in console in rounds UI. */
#define rounds_Y_current_result_pos 31		/* y-axis coordinates for current result text in console in rounds UI. */
#define rounds_user_X_pos 50				/* x-axis coordinates for user character picture in console in rounds UI. */
#define X_LENGTH 100						/* The width of console. */

/**
 * @enum	General_Select
 * @brief	a enum type to represent the selected character of computer or user.
 * @date	2018-11-2
 *
 * @var	rock		rock selected.
 * @var	scissors	scissors selected.
 * @var	paper		paper selected.
 */
typedef enum
{
	rock = 0,
	scissors,
	paper
} General_Select;

/**
 * @enum	Character_Size
 * @brief	a enum type to represent the size of the character picture needed to print.
 * @date	2018-11-2
 *
 * @var	mini	print mini size character picture.
 * @var normal	print normal size character picture.
 */
typedef enum
{
	mini = 0,
	normal
} Character_Size;

/**
 * @enum	Game_Player
 * @brief	a enum type to represent the winner of game.
 * @date	2018-11-2
 *
 * @var	computer	winner is computer.
 * @var	user		winner is user.
 * @var	none		nobody win.
 */
typedef enum
{
	computer = 0,
	user,
	none
} Game_Player;

/**
 * @enum	General_Result
 * @brief	a enum type to represent the input result.
 * @date	2018-11-2
 *
 * @var	result_OK		the input is legal.
 * @var	result_Error	the input is illegal.
 */
typedef enum
{
	result_OK = 0,
	result_Error
} General_Result;

/* Function declaration Start. */
void welcome_UI(char *option_choice);
void info_input(char **user_name_addr, int *game_times, int *name_length);
General_Select computer_select_get(void);
General_Select user_select_get(void);
Game_Player rounds_UI(char **user_name_addr, int *game_times, int *name_length);
Game_Player compare(General_Select computer_select, General_Select user_select);
void final_UI(Game_Player final_winner, char *option_choice);
void printf_position(char *data, int init_X, int init_Y);
void printf_delta(char *data, int delta_X, int delta_Y);
void print_rock(Character_Size size, int bias_X, int bias_Y);
void print_scissors(Character_Size size, int bias_X, int bias_Y);
void print_paper(Character_Size size, int bias_X, int bias_Y);
/* Function declaration End. */

/**
 * @name	main
 * @brief	main function of the project.
 * @date	2018-11-2
 *
 * @return	0 for success, other for fail.
 */
int main(void)
{
	char *pOption_choice, option_choice, **pName_addr, *name_addr;	/* Declare variables:
																	   pOption_choice: pointer to option_choice. 
																	   option_choice: store choice that start or exit game.
																	   pName_addr: pointer to name_addr.
																	   name_addr: store the first element of name string. */
	int *pGame_times, game_times, *pName_len, name_len;				/* Declare variables:
																	   pGame_times: pointer to game_times.
																	   game_times: store game times.
																	   pName_len: pointer to name_len.
																	   name_len: store the length of user name. */
	Game_Player final_winner;								/* Declare final_winner to store the final winner of the game. */
	pOption_choice = &option_choice;
	pGame_times = &game_times;
	pName_len = &name_len;
	pName_addr = &name_addr;

	system("mode con cols=100 lines=34");					/* Set the width of console is 100 and height is 34. */
	system("color 1f");										/* Set the color of console background in blue and font in white. */
	welcome_UI(pOption_choice);								/* Call welcome_UI function. */
	while (option_choice == 'a' || option_choice == 'y')	/* When user choose start or play again the game. */
	{
		info_input(pName_addr, pGame_times, pName_len);					/* Call info_input function. */
		final_winner = rounds_UI(pName_addr, pGame_times, pName_len);	/* Call rounds_UI function. */
		final_UI(final_winner, pOption_choice);							/* Call final_UI function. */
	}

	return 0;												/* Programm run successfully. */
}

/**
 * @name	welcome_UI
 * @brief	welcome UI of the game.
 * @date	2018-11-2
 *
 * @param	option_choice		the option user choose, which to decide start or exit game.
 */
void welcome_UI(char *option_choice)
{
	char user_choice[256] = { 0 };							/* Declare user_choice array to store user choice string. */
	int i = 0;												/* Declare i uses as run times of for loop. */
	General_Result user_result = result_Error;				/* Declare user_result to store the option input result. */

	printf_position("Welcome to the EXCITING GAME!\n",34,0);
	print_rock(mini, 21, 0);
	print_scissors(mini, 40, 0);
	print_paper(mini, 57, 0);
	printf_position("Please choose the option with serial number before it.\n",22,9);
	printf_delta("a. START!\n",41,1);
	printf_delta("b. EXIT.\n",41,1);

	while (user_result == result_Error)						/* When user input is illegal. */
	{
		printf_position("Your choice is(a/b): ",34,15);
		rewind(stdin);
		gets(user_choice);
		rewind(stdin);

		if (strlen(user_choice) == 1)						/* If the input is 1 character. */
		{
			switch (user_choice[0])							/* Judge the user choice. */
			{
			case 'a':
			case 'b':
				user_result = result_OK;					/* The choice is 'a' or 'b', input is legal. */
				break;
			default:
				user_result = result_Error;					/* The choice is others, input is illegal. */
			}
		}
		if (user_result == result_Error)					/* If the input is illegal. */
		{
			printf_delta("Your input is illegal, please try again!\n", 26, 1);
			Sleep(1500);									/* Wait for 1500 ms. */
			printf_delta("", 0, -3);						/* Change the position of cursor. */
			for (i = 0; i < X_LENGTH; i++)					/* Clear incorrect output on console. */
				printf(" ");
			printf("\n\n");
			for (i = 0; i < X_LENGTH; i++)
				printf(" ");
		}
	}

	if (user_choice[0] == 'a')
		printf_delta("The game will start!", 34, 1);
	else
		printf_delta("The game will exit...", 34, 1);

	Sleep(1000);
	*option_choice = user_choice[0];			/* Change the value on address option_choice to user_choice[0](to use in main function). */
}

/**
 * @name	info_input
 * @brief	information input UI of the game.
 * @date	2018-11-2
 * 
 * @param	user_name_addr	the first element address of the user name array.
 * @param	game_times		the times user want to play.
 * @param	name_length		the length of user name.
 */
void info_input(char **user_name_addr, int *game_times, int *name_length)
{
	static char user_name[256] = { 0 }, user_times[256] = { 0 };				/* Declare arrays:
																				   user_name[256]: store user name. 
																				   user_times[256]: store game times.*/
	int i = 0;																	/* Declare i uses as run times of for loop. */
	General_Result name_result = result_Error, times_result = result_Error;		/* Declare to store the info_input result. */
	*user_name_addr = user_name;

	while (name_result == result_Error)
	{
		system("cls");										/* Clear console. */
		printf("(If you want, press Ctrl + C to exit immediately during the game.)\n\n");
		printf("Enter your name first, press \"ENTER\" to confirm:");
		rewind(stdin);
		gets(user_name);
		rewind(stdin);

		*name_length = strlen(user_name);
		if (strlen(user_name) != 0)
		{
			for (i = 0; i < strlen(user_name); i++)			/* Check if the name is space. */
			{
				if (user_name[i] != 32)
				{
					name_result = result_OK;				/* The name is not space, input legal. */
					printf("\n");
					break;
				}
			}
		}
		if (name_result == result_Error)					/* If the name input is illegal(name is space). */
		{
			printf("\nThe name cannot be space, please try again!");
			Sleep(1500);
		}
	}

	while (times_result == result_Error)
	{
		times_result = result_OK;							/* Pretend the times input is legal at first. */
		printf_position("Enter the times you want to play(must be a POSITIVE INTEGER and SMALLER THAN 50!):", 0, 4);
		rewind(stdin);
		gets(user_times);
		rewind(stdin);

		if (strlen(user_times) != 0)
		{
			for (i = 0; i < strlen(user_times); i++)		/* Check if the times input is number. */
			{
				if (!isdigit(user_times[i]))
				{
					times_result = result_Error;			/* The times is not number, input illegal. */
					break;
				}
			}
		}
		if (times_result == result_OK)						/* Check if the times is less than 50. */
		{
			*game_times = atoi(user_times);
			if (*game_times == 0 || *game_times >= 50) times_result = result_Error;		/* The times is not less than 50, input illegal. */
		}
		if (times_result == result_Error)
		{
			printf("\nThe times you input is illegal, please try again!\n");
			Sleep(1500);
			printf_delta("", 0, -3);
			for (i = 0; i < X_LENGTH; i++)
				printf(" ");
			printf("\n\n");
			for (i = 0; i < X_LENGTH; i++)
				printf(" ");
		}
	}
}

/**
 * @name	computer_select_get
 * @brief	generate and print computer select result.
 * @date	2018-11-2
 *
 * @return	the character computer choose: rock, scissors or paper.
 */
General_Select computer_select_get(void)
{
	int randnum = 0;										/* Declare randnum to store random number. */
	General_Select computer_select;							/* Declare computer_select to store the character computer select. */

	srand((unsigned int)time(NULL));						/* Generate a seed with time to produce a random number. */
	randnum = rand() % 3;									/* Produce a random number among 0, 1, 2. */
	switch (randnum)
	{
	case 0:
		computer_select = rock;								/* Check and print computer character. */
		print_rock(normal, 0, rounds_Y_character_pos);
		break;
	case 1:
		computer_select = scissors;
		print_scissors(normal, 0, rounds_Y_character_pos);
		break;
	default:
		computer_select = paper;
		print_paper(normal, 0, rounds_Y_character_pos);
	}

	return computer_select;									/* Return the character computer selected. */
}

/**
 * @name	user_select_get
 * @brief	choose and print user select result.
 * @date	2018-11-3
 *
 * @return	the character user choose: rock, scissors or paper.
 */
General_Select user_select_get(void)
{
	char select_input[256] = { 0 };							/* Declare select_input to store the character user select in string. */
	int i = 0;												/* Declare i uses as run times of for loop. */
	General_Result select_result = result_Error;			/* Declare to store the select_input result. */
	General_Select user_select;								/* Declare user_select to store the character user select. */

	printf("Please use a letter to choose what you want, the meanings are as follows:\n");
	printf("r: Rock \t\t s: Scissors \t\t p: Paper\n\n");

	while (select_result == result_Error)
	{
		printf_position("Computer choice is:", 0, 13);
		printf_delta("Your choice is(r/s/p): ", 30, 0);
		rewind(stdin);
		gets(select_input);
		rewind(stdin);

		if (strlen(select_input) == 1)
		{
			switch (select_input[0])
			{
			case 'r':
			case 's':
			case 'p':
				select_result = result_OK;					/* The input is legal. */
				break;
			default:
				select_result = result_Error;				/* The input is illegal. */
			}
		}
		if (select_result == result_Error)
		{
			printf("\nYour input is illegal, please try again!\n");
			Sleep(1500);
			printf_delta("", 0, -3);
			for (i = 0; i < X_LENGTH; i++)
				printf(" ");
			printf("\n\n");
			for (i = 0; i < X_LENGTH; i++)
				printf(" ");
		}
	}

	switch(select_input[0])
	{
	case 'r':
		user_select = rock;														/* Assigning user select. */
		print_rock(normal, rounds_user_X_pos, rounds_Y_character_pos);			/* Print normal size of user select character. */
		break;
	case 's':
		user_select = scissors;
		print_scissors(normal, rounds_user_X_pos, rounds_Y_character_pos);
		break;
	default:
		user_select = paper;
		print_paper(normal, rounds_user_X_pos, rounds_Y_character_pos);
	}

	return user_select;															/* Return the character user selected. */
}

/**
 * @name	rounds_UI
 * @brief	rounds UI of the game.
 * @date	2018-11-3
 *
 * @param	user_name_addr	the first element address of the user name array.
 * @param	game_times		the times user want to play.
 * @param	name_length		the length of user name.
 * @return	the final winner of game: computer, user or none.
 */
Game_Player rounds_UI(char **user_name_addr, int *game_times, int *name_length)
{
	int remain_games = *game_times, computer_win = 0, user_win = 0, i;		/* Declare variables:
																			   remain_games: store the remain times of game.
																			   computer_win: store the times of computer win.
																			   user_win: store the times of user win.*/
	General_Select computer_select, user_select;			/* Declare to store the character computer and user select. */
	Game_Player current_winner, final_winner;				/* Declare to store the current and final winner of game. */

	for (remain_games = *game_times; remain_games > 0; remain_games--)		/* When the remain times of game is more than 0. */
	{
		system("cls");
		printf("(If you want, press Ctrl + C to exit immediately during the game.)\n\n");
		printf("You have %d times to play!\n\n", remain_games);
		printf_delta("Score List:\n\n", 40, 0);
		printf_delta("", 40, 0);
		for (i = 0; i < *name_length; i++)
			printf("%c", *(*user_name_addr + i));
		printf("(YOU): %d\n\n", user_win);
		printf_delta("", 40, 0);
		printf("COMPUTER: %d\n\n", computer_win);

		user_select = user_select_get();					/* Call user_select_get function and store user select to the variable. */
		computer_select = computer_select_get();			/* Call computer_select_get function and store computer select to the variable. */
		current_winner = compare(computer_select, user_select);		/* Call compare function and store current winner to the variable. */
		if (current_winner == computer)
		{
			printf_position("Computer wins this time!\n", rounds_X_current_result_pos, rounds_Y_current_result_pos);
			computer_win++;									/* Add times of computer win. */
		}
		else if (current_winner == user)
		{
			printf_position("You win this time!\n", rounds_X_current_result_pos, rounds_Y_current_result_pos);
			user_win++;										/* Add times of user win. */
		}
		else
			printf_position("Nobody wins this time!\n", rounds_X_current_result_pos, rounds_Y_current_result_pos);

		printf("\nPress \"Enter\" to continue game...");
		rewind(stdin);
		while (getchar() != '\n');							/* Get "Enter" to continue game. */
		rewind(stdin);
	}

	/* Compare the times of computer and user win and judge and final winner. */
	if (computer_win > user_win) final_winner = computer;
	else if (computer_win < user_win) final_winner = user;
	else final_winner = none;

	return final_winner;									/* Return the final winner of the game. */
}

/**
 * @name	compare
 * @brief	compare the character that computer and user select.
 * @date	2018-11-3
 *
 * @param	computer_select		the character computer select.
 * @param	user_select			the character user select.
 * @return	current winner: computer, user or none.
 */
Game_Player compare(General_Select computer_select, General_Select user_select)
{
	Game_Player current_winner;								/* Declare current_winner to store current winner. */

	if (computer_select == user_select) current_winner = none;		/* If the characters are same. Nobody win this time. */
	else
	{
		switch (computer_select)							/* Logic to judge the winner. */
		{
		case rock:
			if (user_select == rock) current_winner = none;
			if (user_select == scissors) current_winner = computer;
			if (user_select == paper) current_winner = user;
			break;
		case scissors:
			if (user_select == rock) current_winner = user;
			if (user_select == scissors) current_winner = none;
			if (user_select == paper) current_winner = computer;
			break;
		default:
			if (user_select == rock) current_winner = computer;
			if (user_select == scissors) current_winner = user;
			if (user_select == paper) current_winner = none;
		}
	}

	return current_winner;									/* Return the current winner. */
}

/**
 * @name	final_UI
 * @brief	final UI of the game.
 * @date	2018-11-3
 *
 * @param	final_winner	the final winner.
 * @param	option_choice	the user choice that whether to play the game again or not.
 */
void final_UI(Game_Player final_winner, char *option_choice)
{
	General_Result user_result = result_Error;				/* Declare user_result to store the user input result. */
	char user_choice[256] = { 0 };							/* Declare user_choice to store user choice as string. */
	int i = 0;												/* Declare i uses as run times of for loop. */

	system("cls");
	switch (final_winner)									/* Print different sentences with different final winner. */
	{
	case computer:
		printf_delta("Sorry, you lose :(\n\n", 41, 0);
		break;
	case user:
		printf_delta("Congratulations! You win :)\n\n", 36, 0);
		break;
	default:
		printf_delta("Nobody win the game =_=\n\n", 38, 0);
	}

	while (user_result == result_Error)
	{
		printf_position("Would you like to play again(y/n): ", 32, 2);
		rewind(stdin);
		gets(user_choice);
		rewind(stdin);

		if (strlen(user_choice) == 1)
		{
			switch (user_choice[0])							/* Judge the user choice. */
			{
			case 'y':
			case 'n':
				user_result = result_OK;					/* The input is 'y' or 'n', input is legal. */
				break;
			default:
				user_result = result_Error;					/* The input is other, input is illegal. */
			}
		}
		if (user_result == result_Error)
		{
			printf_delta("Your input is illegal, please try again!\n", 30, 1);
			Sleep(1500);
			printf_delta("", 0, -3);
			for (i = 0; i < 100; i++)
				printf(" ");
			printf("\n\n");
			for (i = 0; i < 100; i++)
				printf(" ");
		}
	}

	if (user_choice[0] == 'y')								/* If the choice is 'y'(Play again). */
		printf_delta("The game will start!", 40, 1);
	else
		printf_delta("The game will exit...", 40, 1);		/* If the choice is 'n'(Exit). */

	Sleep(1000);
	*option_choice = user_choice[0];		/* Change the value on address option_choice to user_choice[0](to use in main function). */
}

/**
 * @name	printf_position
 * @brief	printf on specific position.
 * @date	2018-11-3
 *
 * @param	data	string needs to be print.
 * @param	init_X	x-axis coordinates of the first character.
 * @param	init_Y	y-axis coordinates of the first character.
 */
void printf_position(char *data, int init_X, int init_Y)
{
	HANDLE hd;												/* Declare hd to store handle to standard output. */
	COORD position;											/* Declare position to store coordinates. */

	hd = GetStdHandle(STD_OUTPUT_HANDLE);					/* Get handle to standard output. */
	position.X = init_X;									/* Set the x-axis coordinates. */
	position.Y = init_Y;									/* Set the y-axis coordinates. */

	SetConsoleCursorPosition(hd, position);					/* Move the cursor to the set position of console. */
	printf("%s", data);										/* Print the data. */
}

/**
 * @name	printf_delta
 * @brief	printf on incremental position.
 * @date	2018-11-3
 *
 * @param	data	string needs to be print.
 * @param	init_X	x-axis coordinates of the first character.
 * @param	init_Y	y-axis coordinates of the first character.
 */
void printf_delta(char *data, int delta_X, int delta_Y)
{
	HANDLE hd;												/* Declare hd to store handle to standard output. */
	COORD position;											/* Declare position to store coordinates. */
	CONSOLE_SCREEN_BUFFER_INFO console_buf;					/* Declare to store buffer info of console. */

	hd = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hd, &console_buf);			/* Get buffer info of console. */
	position.X = console_buf.dwCursorPosition.X;			/* Get current x-axis coordinates of cursor. */
	position.Y = console_buf.dwCursorPosition.Y;			/* Get current y-axis coordinates of cursor. */
	position.X += delta_X;
	position.Y += delta_Y;
	
	SetConsoleCursorPosition(hd, position);					/* Move the cursor to the set position of console. */
	printf("%s", data);										/* Print the data. */
}

/**
 * @name	print_rock
 * @brief	print the picture of rock.
 * @date	2018-11-3
 *
 * @param	size	mini or normal.
 * @param	bias_X	x-axis coordinates of the picture.
 * @param	bias_Y	y-axis coordinates of the picture.
 */
void print_rock(Character_Size size, int bias_X, int bias_Y)
{
	/* Declare x_normal, y_normal, x_mini, y_mini to store the coordinates of points in the picture. */
	int x_normal[] = { 6,7,8,5,6,7,8,9,4,5,6,7,8,9,10,3,4,5,6,7,8,9,10,11,2,3,4,5,6,7,8,9,10,11,12,2,3,4,5,6,7,8,9,10,11,12,12,11,10,9,8,7,6,5,4,3,2,11,10,9,8,7,6,5,4,3,10, 9, 8, 7, 6, 5, 4, 9, 8, 7, 6, 5, 8, 7, 6 };
	int y_normal[] = { 2,2,2,3,3,3,3,3,4,4,4,4,4,4, 4,5,5,5,5,5,5,5, 5, 5,6,6,6,6,6,6,6,6, 6, 6, 6,7,7,7,7,7,7,7,7, 7, 7, 7, 8, 8, 8,8,8,8,8,8,8,8,8, 9, 9,9,9,9,9,9,9,9,10,10,10,10,10,10,10,11,11,11,11,11,12,12,12 };
	int x_mini[] = { 4,5,3,4,5,6,2,3,4,5,6,7,7,6,5,4,3,2,6,5,4,3,5,4 };
	int y_mini[] = { 2,2,3,3,3,3,4,4,4,4,4,4,5,5,5,5,5,5,6,6,6,6,7,7 };
	int pos_len, i;											/* Declare pos_len to store the array length.
															   Declare i uses as run times of for loop. */

	if (size == normal)										/* Print normal size of the picture. */
	{
		GET_ARRAY_LEN(x_normal, pos_len);					/* Get the length of the array. */
		for (i = 0; i < pos_len; i++)
			printf_position("*", bias_X + x_normal[i] * 2, bias_Y + y_normal[i]);
		printf_position("Rock", bias_X + rounds_X_text_pos, rounds_Y_text_pos);
	}
	else													/* Print mini size of the picture. */
	{
		GET_ARRAY_LEN(x_mini, pos_len);
		for (i = 0; i < pos_len; i++)
			printf_position("*", bias_X + x_mini[i] * 2, bias_Y + y_mini[i]);
		printf("\n");
	}
}

/**
 * @name	print_scissors
 * @brief	print the picture of scissors.
 * @date	2018-11-3
 *
 * @param	size	mini or normal.
 * @param	bias_X	x-axis coordinates of the picture.
 * @param	bias_Y	y-axis coordinates of the picture.
 */
void print_scissors(Character_Size size, int bias_X, int bias_Y)
{
	/* Declare x_normal, y_normal, x_mini, y_mini to store the coordinates of points in the picture. */
	int x_normal[] = { 3,4,11,2,5,10,3,5,9,4,8,5,7,6,7,5,8,4, 9, 5, 3,10, 5, 2,11, 4, 3 };
	int y_normal[] = { 2,2, 2,3,3, 3,4,4,4,5,5,6,6,7,8,8,9,9,10,10,10,11,11,11,12,12,12 };
	int x_mini[] = {2,3,6,2,3,5,4,5,3,2,6,3,2};
	int y_mini[] = {2,2,2,3,3,3,4,5,5,5,6,6,6};
	int pos_len, i;											/* Declare pos_len to store the array length.
															   Declare i uses as run times of for loop. */

	if (size == normal)
	{
		GET_ARRAY_LEN(x_normal, pos_len);
		for (i = 0; i < pos_len; i++)
			printf_position("*", bias_X + x_normal[i] * 2.5, bias_Y + y_normal[i]);
		printf_position("Scissors", bias_X + rounds_X_text_pos, rounds_Y_text_pos);
	}
	else
	{
		GET_ARRAY_LEN(x_mini, pos_len);
		for (i = 0; i < pos_len; i++)
			printf_position("*", bias_X + x_mini[i] * 2, bias_Y + y_mini[i]);
		printf("\n");
	}
}

/**
 * @name	print_paper
 * @brief	print the picture of paper.
 * @date	2018-11-3
 *
 * @param	size	mini or normal.
 * @param	bias_X	x-axis coordinates of the picture.
 * @param	bias_Y	y-axis coordinates of the picture.
 */
void print_paper(Character_Size size, int bias_X, int bias_Y)
{
	/* Declare x_normal, y_normal, x_mini, y_mini to store the coordinates of points in the picture. */
	int x_normal[] = { 2,2,2,2,2,2,2,2, 2, 2, 2,2,2,2,2,2,2,2,2,2,2,2 };
	int y_normal[] = { 2,3,4,5,6,7,8,9,10,11,12 };
	int x_mini[] = { 2,2,2,2,2,2,2,2,2,2,2,2 };
	int y_mini[] = { 2,3,4,5,6,7 };
	int pos_x_len, pos_y_len, i, j;							/* Declare pos_x_len, pos_y_len to store the array length.
															   Declare i, j use as run times of for loop. */

	if (size == normal)
	{
		GET_ARRAY_LEN(x_normal, pos_x_len);
		GET_ARRAY_LEN(y_normal, pos_y_len);
		for (i = 0; i < pos_y_len; i++)
		{
			printf_position("", bias_X + x_normal[i] * 2.5, bias_Y + y_normal[i]);
			for (j = 0; j < pos_x_len; j++)
				printf("~");
		}
		printf_position("Paper", bias_X + rounds_X_text_pos, rounds_Y_text_pos);
	}
	else
	{
		GET_ARRAY_LEN(x_mini, pos_x_len);
		GET_ARRAY_LEN(y_mini, pos_y_len);
		for (i = 0; i < pos_y_len; i++)
		{
			printf_position("", bias_X + x_normal[i] * 2, bias_Y + y_normal[i]);
			for (j = 0; j < pos_x_len; j++)
				printf("~");
		}
		printf("\n");
	}
}