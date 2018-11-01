#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>

#define GET_ARRAY_LEN(array,len){len = (sizeof(array) / sizeof(array[0]));}

typedef enum
{
	rock = 0,
	scissors,
	paper
} General_Select;

typedef enum
{
	computer = 0,
	user,
	none
} Game_Player;

typedef enum
{
	result_OK = 0,
	result_Error
} General_Result;

void welcome_UI(char *option_choice);
void info_input(char **user_name_addr, int *game_times, int *name_length);
General_Select computer_select_get(void);
General_Select user_select_get(void);
Game_Player rounds_UI(int *game_times);
Game_Player compare(General_Select computer_select, General_Select user_select);
void final_UI(Game_Player final_winner);
void printf_position(char *data, int initX, int initY);
void print_scissors(void);

int main()
{
	char *option_choice, c_pbase, **name_addr, *na_pbase;
	int *game_times, t_pbase, *name_len, nl_pbase, i = 2;
	Game_Player final_winner;
	option_choice = &c_pbase;
	game_times = &t_pbase;
	name_len = &nl_pbase;
	name_addr = &na_pbase;

	welcome_UI(option_choice);
	if (*option_choice == 'a')
	{
		info_input(name_addr, game_times, name_len);
		final_winner = rounds_UI(game_times);
		final_UI(final_winner);
	}

	system("pause");
	return 0;
}

void welcome_UI(char *option_choice)
{
	General_Result user_result = result_Error;
	char user_choice[256] = { 0 };

	printf_position("Welcome to the EXCITING GAME!\n\n",9,0);
	printf("Please choose the option with serial number before it.\n\n");
	printf_position("a. START!\n\n",19,4);
	printf_position("b. EXIT.\n\n",19,6);

	while (user_result == result_Error)
	{
		printf("Your choice is(a/b): ");
		gets(user_choice);
		rewind(stdin);

		if (strlen(user_choice) == 1)
		{
			switch (user_choice[0])
			{
			case 'a':
			case 'b':
				user_result = result_OK;
				break;
			default:
				user_result = result_Error;
			}
		}
		if (user_result == result_Error)
			printf("Your input is illegal, please try again!\n");
	}

	if (user_choice[0] == 'a')
	{
		printf("The game will start!\n");
	}
	else
		printf("The game will exit...\n");

	Sleep(1000);
	*option_choice = user_choice[0];
}

void info_input(char **user_name_addr, int *game_times, int *name_length)
{
	static char user_name[256] = { 0 }, user_times[256] = { 0 };
	int i = 0;
	General_Result name_result = result_Error, times_result = result_Error;
	*user_name_addr = user_name;

	system("cls");
	while (name_result == result_Error)
	{
		printf("Enter your name first, press \"ENTER\" to confirm:");
		gets(user_name);
		rewind(stdin);

		*name_length = strlen(user_name);
		if (strlen(user_name) != 0)
		{
			for (i = 0; i < strlen(user_name); i++)
			{
				if (user_name[i] != 32)
				{
					name_result = result_OK;
					break;
				}
			}
		}
		if (name_result == result_Error)
		{
			printf("The name cannot be space, please try again!\n");
			Sleep(1500);
			system("cls");
		}
	}

	system("cls");
	while (times_result == result_Error)
	{
		times_result = result_OK;
		printf("Enter the times you want to play(MUST BE A POSITIVE INTEGER!):");
		gets(user_times);
		rewind(stdin);

		if (strlen(user_times) != 0)
		{
			for (i = 0; i < strlen(user_times); i++)
			{
				if (!isdigit(user_times[i]))
				{
					times_result = result_Error;
					break;
				}
			}
		}
		if (times_result == result_Error)
		{
			printf("The times you input is illegal, please try again!\n");
			Sleep(1500);
			system("cls");
		}
	}
	*game_times = atoi(user_times);
}

General_Select computer_select_get(void)
{
	int randnum = 0;
	General_Select computer_select;

	srand((unsigned int)time(NULL));
	randnum = rand() % 3;
	switch (randnum)
	{
	case 0:
		computer_select = rock;
		printf("Computer choice is rock.\n\n");
		break;
	case 1:
		computer_select = scissors;
		printf("Computer choice is scissors.\n\n");
		break;
	default:
		computer_select = paper;
		printf("Computer choice is paper.\n\n");
	}

	return computer_select;
}

General_Select user_select_get(void)
{
	char select_input[256] = { 0 };
	General_Result select_result = result_Error;
	General_Select user_select;

	printf("Please use a letter to choose what you want, the meanings are as follows:\n");
	printf("r: Rock \t\t s: Scissors \t\t p: Paper\n\n");

	while (select_result == result_Error)
	{
		printf("Your choice is(r/s/p): ");
		gets(select_input);
		rewind(stdin);

		if (strlen(select_input) == 1)
		{
			switch (select_input[0])
			{
			case 'r':
			case 's':
			case 'p':
				select_result = result_OK;
				break;
			default:
				select_result = result_Error;
			}
		}
		if (select_result == result_Error)
		{
			printf("Your input is illegal, please try again!\n");
			Sleep(1000);
		}
	}

	switch(select_input[0])
	{
	case 'r':
		user_select = rock;
		break;
	case 's':
		user_select = scissors;
		break;
	default:
		user_select = paper;
	}

	return user_select;
}

Game_Player rounds_UI(int *game_times)
{
	int remain_games = *game_times, computer_win = 0, user_win = 0;
	General_Select computer_select, user_select;
	Game_Player current_winner, final_winner;

	for (remain_games = *game_times; remain_games > 0; remain_games--)
	{
		system("cls");
		printf("You have %d times to play!\n", remain_games);
		printf("Score List:\n\n");
		printf("YOU: %d\n", user_win);
		printf("COMPUTER: %d\n\n", computer_win);

		user_select = user_select_get();
		computer_select = computer_select_get();
		current_winner = compare(computer_select, user_select);
		if (current_winner == computer)
		{
			printf("Computer win this time!\n");
			computer_win++;
		}
		else if (current_winner == user)
		{
			printf("You win this time!\n");
			user_win++;
		}
		else
			printf("Nobody win this time!\n");

		Sleep(2500);
	}

	if (computer_win > user_win) final_winner = computer;
	else if (computer_win < user_win) final_winner = user;
	else final_winner = none;

	return final_winner;
}

Game_Player compare(General_Select computer_select, General_Select user_select)
{
	Game_Player current_winner;

	if (computer_select == user_select) current_winner = none;
	else
	{
		switch (computer_select)
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

		return current_winner;
	}
}

void final_UI(Game_Player final_winner)
{
	system("cls");
	switch (final_winner)
	{
	case computer:
		printf("Sorry, you lose :(\n");
		break;
	case user:
		printf("Congratulations! You win :)\n");
		break;
	default:
		printf("Nobody win the game =_=\n");
	}
	Sleep(1500);
}

void printf_position(char *data, int initX, int initY)
{
	HANDLE handle;
	COORD position;
	CONSOLE_SCREEN_BUFFER_INFO console_buf;

	position.X = initX;
	position.Y = initY;
	handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(handle, position);
	printf("%s", data);
}

void print_scissors(void)
{
	int x[] = { 17,4,16,3,5,15,2,6,14,3,7,13,4,6,12,5,11,6,10, 7, 9, 8, 9, 7,10, 6,11, 5,12, 6, 4,13, 7, 3,14, 6, 2,15, 5, 3,16, 4,17 };
	int y[] = { 2 ,3, 3,4,4, 4,5,5, 5,6,6, 6,7,7, 7,8, 8,9, 9,10,10,11,12,12,13,13,14,14,15,15,15,16,16,16,17,17,17,18,18,18,19,19,20 };
	int pos_len;

	GET_ARRAY_LEN(x, pos_len);
	for (int i = 0; i < pos_len; i++)
		printf_position("*", x[i], y[i]);
}