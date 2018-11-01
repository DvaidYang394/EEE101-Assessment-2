#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>

#define GET_ARRAY_LEN(array,len){len = (sizeof(array) / sizeof(array[0]));}
#define rounds_X_text_pos 13
#define rounds_Y_text_pos 27
#define rounds_Y_character_pos 12
#define rounds_Y_current_result_pos 29
#define rounds_user_X_pos 50

typedef enum
{
	rock = 0,
	scissors,
	paper
} General_Select;

typedef enum
{
	mini = 0,
	normal
} Character_Size;

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
General_Select computer_select_get();
General_Select user_select_get();
Game_Player rounds_UI(char **user_name_addr, int *game_times, int *name_length);
Game_Player compare(General_Select computer_select, General_Select user_select);
void final_UI(Game_Player final_winner, char *option_choice);
void printf_position(char *data, int init_X, int init_Y);
void printf_delta(char *data, int delta_X, int delta_Y);
void print_rock(Character_Size size, int bias_X, int bias_Y);
void print_scissors(Character_Size size, int bias_X, int bias_Y);
void print_paper(Character_Size size, int bias_X, int bias_Y);

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
	while (*option_choice == 'a' || *option_choice == 'y')
	{
		info_input(name_addr, game_times, name_len);
		final_winner = rounds_UI(name_addr, game_times, name_len);
		final_UI(final_winner, option_choice);
	}

	return 0;
}

void welcome_UI(char *option_choice)
{
	General_Result user_result = result_Error;
	char user_choice[256] = { 0 };
	int i = 0;

	printf_position("Welcome to the EXCITING GAME!\n",13,0);
	print_rock(mini, -1, 0);
	print_scissors(mini, 19, 0);
	print_paper(mini, 35, 0);
	printf_delta("Please choose the option with serial number before it.\n",0,1);
	printf_delta("a. START!\n",19,1);
	printf_delta("b. EXIT.\n",19,1);

	while (user_result == result_Error)
	{
		printf_position("Your choice is(a/b): ",12,15);
		rewind(stdin);
		gets(user_choice);

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
		{
			printf_delta("Your input is illegal, please try again!\n", 4, 1);
			Sleep(1500);
			printf_delta("                                                  \n\n", 0, -3);
			for (i = 0; i < 50; i++)
				printf(" ");
		}
	}

	if (user_choice[0] == 'a')
	{
		printf_delta("The game will start!", 12, 1);
	}
	else
		printf_delta("The game will exit...", 12, 1);

	Sleep(1000);
	*option_choice = user_choice[0];
}

void info_input(char **user_name_addr, int *game_times, int *name_length)
{
	static char user_name[256] = { 0 }, user_times[256] = { 0 };
	int i = 0;
	General_Result name_result = result_Error, times_result = result_Error;
	*user_name_addr = user_name;

	while (name_result == result_Error)
	{
		system("cls");
		printf("Enter your name first, press \"ENTER\" to confirm:");
		rewind(stdin);
		gets(user_name);

		*name_length = strlen(user_name);
		if (strlen(user_name) != 0)
		{
			for (i = 0; i < strlen(user_name); i++)
			{
				if (user_name[i] != 32)
				{
					name_result = result_OK;
					printf("\n");
					break;
				}
			}
		}
		if (name_result == result_Error)
		{
			printf("\nThe name cannot be space, please try again!");
			Sleep(1500);
		}
	}

	while (times_result == result_Error)
	{
		times_result = result_OK;
		printf("Enter the times you want to play(must be a POSITIVE INTEGER and SMALLER THAN 50!):");
		rewind(stdin);
		gets(user_times);

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
		if (times_result == result_OK)
		{
			*game_times = atoi(user_times);
			if (*game_times == 0 || *game_times >= 50) times_result = result_Error;
		}
		if (times_result == result_Error)
		{
			printf("\nThe times you input is illegal, please try again!\n");
			Sleep(1500);
			printf_delta("                                                                                    \n\n", 0, -3);
			for (i = 0; i < 50; i++)
				printf(" ");
			printf_delta("", -50, -2);
		}
	}
}

General_Select computer_select_get()
{
	int randnum = 0;
	General_Select computer_select;

	srand((unsigned int)time(NULL));
	randnum = rand() % 3;
	switch (randnum)
	{
	case 0:
		computer_select = rock;
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

	return computer_select;
}

General_Select user_select_get()
{
	char select_input[256] = { 0 };
	int i = 0;
	General_Result select_result = result_Error;
	General_Select user_select;

	printf("Please use a letter to choose what you want, the meanings are as follows:\n");
	printf("r: Rock \t\t s: Scissors \t\t p: Paper\n\n");

	while (select_result == result_Error)
	{
		printf_position("Computer choice is:", 0, 11);
		printf_delta("Your choice is(r/s/p): ", 30, 0);
		rewind(stdin);
		gets(select_input);

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
			printf("\nYour input is illegal, please try again!\n");
			Sleep(1500);
			printf_delta("                                                                               \n\n", 0, -3);
			for (i = 0; i < 50; i++)
				printf(" ");
		}
	}

	switch(select_input[0])
	{
	case 'r':
		user_select = rock;
		print_rock(normal, rounds_user_X_pos, rounds_Y_character_pos);
		break;
	case 's':
		user_select = scissors;
		print_scissors(normal, rounds_user_X_pos, rounds_Y_character_pos);
		break;
	default:
		user_select = paper;
		print_paper(normal, rounds_user_X_pos, rounds_Y_character_pos);
	}

	return user_select;
}

Game_Player rounds_UI(char **user_name_addr, int *game_times, int *name_length)
{
	int remain_games = *game_times, computer_win = 0, user_win = 0, i;
	General_Select computer_select, user_select;
	Game_Player current_winner, final_winner;

	for (remain_games = *game_times; remain_games > 0; remain_games--)
	{
		system("cls");
		printf("You have %d times to play!\n\n", remain_games);
		printf("Score List:\n\n");
		for (i = 0; i < *name_length; i++)
			printf("%c", *(*user_name_addr + i));
		printf("(YOU): %d\n\n", user_win);
		printf("COMPUTER: %d\n\n", computer_win);

		user_select = user_select_get();
		computer_select = computer_select_get();
		current_winner = compare(computer_select, user_select);
		if (current_winner == computer)
		{
			printf_position("Computer wins this time!\n", 0, rounds_Y_current_result_pos);
			computer_win++;
		}
		else if (current_winner == user)
		{
			printf_position("You win this time!\n", 0, rounds_Y_current_result_pos);
			user_win++;
		}
		else
			printf_position("Nobody wins this time!\n", 0, rounds_Y_current_result_pos);

		printf("\nPress \"Enter\" to continue game...");
		rewind(stdin);
		while (getchar() != '\n');
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
	}

	return current_winner;
}

void final_UI(Game_Player final_winner, char *option_choice)
{
	General_Result user_result = result_Error;
	char user_choice[256] = { 0 };
	int i = 0;

	system("cls");
	switch (final_winner)
	{
	case computer:
		printf("Sorry, you lose :(\n\n");
		break;
	case user:
		printf("Congratulations! You win :)\n\n");
		break;
	default:
		printf("Nobody win the game =_=\n\n");
	}

	while (user_result == result_Error)
	{
		printf("Would you like to play again(y/n): ");
		rewind(stdin);
		gets(user_choice);

		if (strlen(user_choice) == 1)
		{
			switch (user_choice[0])
			{
			case 'y':
			case 'n':
				user_result = result_OK;
				break;
			default:
				user_result = result_Error;
			}
		}
		if (user_result == result_Error)
		{
			printf_delta("Your input is illegal, please try again!\n", 0, 1);
			Sleep(1500);
			printf_delta("                                                  \n\n", 0, -3);
			for (i = 0; i < 50; i++)
				printf(" ");
			printf_delta("", -50, -2);
		}
	}

	if (user_choice[0] == 'y')
	{
		printf_delta("The game will start!", 0, 1);
	}
	else
		printf_delta("The game will exit...", 0, 1);

	Sleep(1000);
	*option_choice = user_choice[0];
}

void printf_position(char *data, int init_X, int init_Y)
{
	HANDLE hd;
	COORD position;

	hd = GetStdHandle(STD_OUTPUT_HANDLE);
	position.X = init_X;
	position.Y = init_Y;

	SetConsoleCursorPosition(hd, position);
	printf("%s", data);
}

void printf_delta(char *data, int delta_X, int delta_Y)
{
	HANDLE hd;
	COORD position;
	CONSOLE_SCREEN_BUFFER_INFO console_buf;

	hd = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hd, &console_buf);
	position.X = console_buf.dwCursorPosition.X;
	position.Y = console_buf.dwCursorPosition.Y;
	position.X += delta_X;
	position.Y += delta_Y;
	
	SetConsoleCursorPosition(hd, position);
	printf("%s", data);
}

void print_rock(Character_Size size, int bias_X, int bias_Y)
{
	int x_normal[] = { 5,7,9,11,4,6,8,10,12,2,3,4,6,8,10,12,2,4,6,8,10,12,2,4,5,6,7,8,9,10,11,12,2,12,2,12,2,3,4,5,6,7,8,9,10,11,12 };
	int y_normal[] = { 2,2,2, 2,3,3,3, 3, 3,4,4,4,4,4, 4, 4,5,5,5,5, 5, 5,6,6,6,6,6,6,6, 6, 6, 6,7, 7,8, 8,9,9,9,9,9,9,9,9, 9, 9, 9 };
	int x_mini[] = { 3,5,7,2,4,6,8,2,4,6,8,2,8,2,3,4,5,6,7,8 };
	int y_mini[] = { 2,2,2,3,3,3,3,4,4,4,4,5,5,6,6,6,6,6,6,6 };
	int pos_len;

	if (size == normal)
	{
		GET_ARRAY_LEN(x_normal, pos_len);
		for (int i = 0; i < pos_len; i++)
			printf_position("*", bias_X + x_normal[i] * 2.5, bias_Y+ y_normal[i]);
		printf_position("Rock", bias_X + rounds_X_text_pos, rounds_Y_text_pos);
	}
	else
	{
		GET_ARRAY_LEN(x_mini, pos_len);
		for (int i = 0; i < pos_len; i++)
			printf_position("*", bias_X + x_mini[i] * 2, bias_Y + y_mini[i]);
		printf("\n");
	}
}

void print_scissors(Character_Size size, int bias_X, int bias_Y)
{
	int x_normal[] = { 3,4,11,2,5,10,3,5,9,4,8,5,7,6,7,5,8,4, 9, 5, 3,10, 5, 2,11, 4, 3 };
	int y_normal[] = { 2,2, 2,3,3, 3,4,4,4,5,5,6,6,7,8,8,9,9,10,10,10,11,11,11,12,12,12 };
	int x_mini[] = {2,3,6,2,3,5,4,5,3,2,6,3,2};
	int y_mini[] = {2,2,2,3,3,3,4,5,5,5,6,6,6};
	int pos_len;

	if (size == normal)
	{
		GET_ARRAY_LEN(x_normal, pos_len);
		for (int i = 0; i < pos_len; i++)
			printf_position("*", bias_X + x_normal[i] * 2.5, bias_Y + y_normal[i]);
		printf_position("Scissors", bias_X + rounds_X_text_pos, rounds_Y_text_pos);
	}
	else
	{
		GET_ARRAY_LEN(x_mini, pos_len);
		for (int i = 0; i < pos_len; i++)
			printf_position("*", bias_X + x_mini[i] * 2, bias_Y + y_mini[i]);
		printf("\n");
	}
}

void print_paper(Character_Size size, int bias_X, int bias_Y)
{
	int x_normal[] = { 6,7,8,5,6,7,8,9,4,5,6,7,8,9,10,3,4,5,6,7,8,9,10,11,2,3,4,5,6,7,8,9,10,11,12,2,3,4,5,6,7,8,9,10,11,12,12,11,10,9,8,7,6,5,4,3,2,11,10,9,8,7,6,5,4,3,10, 9, 8, 7, 6, 5, 4, 9, 8, 7, 6, 5, 8, 7, 6 };
	int y_normal[] = { 2,2,2,3,3,3,3,3,4,4,4,4,4,4, 4,5,5,5,5,5,5,5, 5, 5,6,6,6,6,6,6,6,6, 6, 6, 6,7,7,7,7,7,7,7,7, 7, 7, 7, 8, 8, 8,8,8,8,8,8,8,8,8, 9, 9,9,9,9,9,9,9,9,10,10,10,10,10,10,10,11,11,11,11,11,12,12,12 };
	int x_mini[] = { 4,5,3,4,5,6,2,3,4,5,6,7,7,6,5,4,3,2,6,5,4,3,5,4 };
	int y_mini[] = { 2,2,3,3,3,3,4,4,4,4,4,4,5,5,5,5,5,5,6,6,6,6,7,7 };
	int pos_len;

	if (size == normal)
	{
		GET_ARRAY_LEN(x_normal, pos_len);
		for (int i = 0; i < pos_len; i++)
			printf_position("*", bias_X + x_normal[i] * 2, bias_Y + y_normal[i]);
		printf_position("Paper", bias_X + rounds_X_text_pos, rounds_Y_text_pos);
	}
	else
	{
		GET_ARRAY_LEN(x_mini, pos_len);
		for (int i = 0; i < pos_len; i++)
			printf_position("*", bias_X + x_mini[i] * 2, bias_Y + y_mini[i]);
		printf("\n");
	}
}